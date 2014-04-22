#include "memberdetails.h"
#include "ui_memberdetails.h"
#include"panel.h"
#include<QMessageBox>


MemberDetails::MemberDetails(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MemberDetails)
{
    ui->setupUi(this);
    //Validate inputs
    QRegExpValidator *validator= new QRegExpValidator(QRegExp("[MFmf]{1}"),ui->lineEdit_Gender);
    ui->lineEdit_Gender->setValidator(validator);

}

MemberDetails::~MemberDetails()
{
    delete ui;
}

void MemberDetails::on_pushButton_Register_clicked()
{

    QString fName,lName,gender,id,mobile;
    //assign variables
    fName=ui->lineEdit_FName->text();
    lName=ui->lineEdit_LName->text();
    gender=ui->lineEdit_Gender->text();
    id=ui->lineEdit_ID->text();
    mobile=ui->lineEdit_Mobile->text();
    QString bal="0";
    //if all fields are filled
    if(fName.length()>0 && lName.length()>0 && gender.length()>0 && id.length()>0 && mobile.length()>0)
    {
    //Insert data into the database
    QSqlQuery qry;
    QSqlQuery qry2;
    qry.prepare("insert into member_details (firstName,lastName,gender,idNumber,mobileNumber) values('"+fName+"','"+lName+"','"+gender+"','"+id+"','"+mobile+"')");
    qry2.prepare("insert into member_accounts(accountBal)values('"+bal+"')");

    if(qry.exec())
    {
        if(qry2.exec())
        {
        QMessageBox::information(this,tr("Save Member"),tr("Member Details Saved"));

        this->hide();


        }
        else
        {
            QMessageBox::critical(this,tr("Error"),qry2.lastError().text());
        }

    }
    else
    {
        QMessageBox::critical(this,tr("Error"),qry.lastError().text());

    } 
    }
    else
    {
        QMessageBox::critical(this,tr("Member Details"),tr("All fields must be filled..."));
    }

}


void MemberDetails::on_pushButton_Cancel_clicked()
{
    this->hide();//closes form
}

void MemberDetails::on_pushButton_Clear_clicked()
{
    //clears all the text fields
    ui->lineEdit_FName->setText("");
    ui->lineEdit_Gender->setText("");
    ui->lineEdit_ID->setText("");
    ui->lineEdit_LName->setText("");
    ui->lineEdit_Mobile->setText("");

}
