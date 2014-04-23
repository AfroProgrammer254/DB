#include "employees.h"
#include "ui_employees.h"
#include "login.h"
#include<QMessageBox>

Employees::Employees(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Employees)
{
    ui->setupUi(this);
}

Employees::~Employees()
{
    delete ui;
}

void Employees::on_pushButton_Set_clicked()
{
    QString EID,pass1,pass2;
    EID=ui->lineEdit_EID->text();
    pass1=ui->lineEdit_Password->text();
    pass2=ui->lineEdit_Password2->text();
    bool ok;
    //validation of inputs
    if(EID.length()>0 && pass1.length()>0 && pass2.length()>0)
    {
        ok=true;
    }
    else
    {
        QMessageBox::critical(this,tr("Settings"),tr("All fields must be filled..."));
        ok=false;
    }
    if(ok==true)
    {
        //validation that all passwords are equal
        if(pass1==pass2)
        {
            ok=true;
        }
        else
        {
            QMessageBox::critical(this,tr("Settings"),tr("Check passwords entered..."));
            ok=false;
        }
    }
    //insert into database
    if(ok==true)
    {
        QSqlQuery insert;
        insert.prepare("insert into employees (username,password)values('"+EID+"','"+pass1+"')");
        if(insert.exec())
        {
           QMessageBox::information(this,tr("Deenze"),tr("Employee Saved..."));
           //clear the values on screen
           ui->lineEdit_EID->setText("");
           ui->lineEdit_Password->setText("");
           ui->lineEdit_Password2->setText("");
        }
        else
        {
            QMessageBox::critical(this,tr("Error"),insert.lastError().text());
        }
    }





}

void Employees::on_pushButton_Back_clicked()
{
    this->hide();
}
