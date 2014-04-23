#include "login.h"
#include "ui_login.h"
#include "login_form.h"
#include<QMessageBox>
#include"settings.h"
#include"employees.h"



Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    showCurrentDate();

    if(connOpen())
    {
        ui->statusBar->showMessage("Connected...");

    }
    else
    {
        ui->statusBar->showMessage("Not Connected...");

    }
    //Validate all integer inputs
     QIntValidator *decValidator=new QIntValidator(0,100000,ui->lineEdit_Amt);
     QIntValidator *decValidator2=new QIntValidator(0,100,ui->lineEdit_NumberOfDeposits);
     QIntValidator *decValidator3=new QIntValidator(0,100,ui->lineEdit_Rate);
     QIntValidator *decValidator4=new QIntValidator(0,48,ui->lineEdit_Time);
     ui->lineEdit_Amt->setValidator(decValidator);
     ui->lineEdit_NumberOfDeposits->setValidator(decValidator2);
     ui->lineEdit_Rate->setValidator(decValidator3);
     ui->lineEdit_Time->setValidator(decValidator4);

}

Login::~Login()
{
    delete ui;
}


bool Login::connOpen()
{
    db= QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath()+"/Deenze");

    if(db.open())//Open database
    {

       return true;
    }
    else
    {

        return false;
    }
}
void Login::connClose()
{
    //close the database
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);
}

void Login::showCurrentDate()
{
    //show current date in the welcome form
    QString currdate;
    currdate=QDate::currentDate().toString();
    ui->label_CurrDate->setText(currdate);

}

void Login::on_commandLinkButton_clicked()
{
    //open login form
    Login_Form login;
    login.setModal(true);
    login.exec();

}

void Login::on_commandLinkButton_Exit_clicked()
{
    //close database and exit the application
    connClose();
    QMessageBox::information(this,tr("Deenze"),tr("Thank you for using Deenze Finance Management System!"));
    exit(0);
}


void Login::on_commandLinkButton_3_clicked()
{
    //open settings form
    Settings limits;
    limits.setModal(true);
    limits.exec();
}


void Login::on_commandLinkButton_Save_clicked()
{
    //save rate
    QString rate;
    rate=ui->lineEdit_Rate->text();
    if(rate.length()>0)
    {
        QSqlQuery qry;
        qry.prepare("update group_details set interestRate='"+rate+"'");
        if(qry.exec())
        {
           //sets the interest rate


        }
        else
        {
            QMessageBox::information(this,tr("Error"),qry.lastError().text());
            qDebug()<<qry.lastQuery();
        }
    }



    //save time
    QString time;
    time=ui->lineEdit_Time->text();
    if(time.length()>0)
    {
        QSqlQuery qry1;
        qry1.prepare("update group_details set time='"+time+"'");
        if(qry1.exec())
        {
           //loan time period saved

        }
        else
        {
            QMessageBox::information(this,tr("Error"),qry1.lastError().text());
            qDebug()<<qry1.lastQuery();
        }
    }


    //save minimum number of deposits
    QString minDeposits;
    minDeposits=ui->lineEdit_NumberOfDeposits->text();
    if(minDeposits.length()>0)
    {
        QSqlQuery qry2;
        qry2.prepare("update group_details set minNumOfDeposits='"+minDeposits+"'");
        if(qry2.exec())
        {
            //sets minimum number of deposits required

        }
        else
        {
            QMessageBox::information(this,tr("Error"),qry2.lastError().text());
            qDebug()<<qry2.lastQuery();
        }
    }


    //save minimum amount
    QString minAmt;
    minAmt=ui->lineEdit_Amt->text();
    if(minAmt.length()>0)
    {
        QSqlQuery qry3;
        qry3.prepare("update group_details set minimumAmount='"+minAmt+"'");
        if(qry3.exec())
        {
           //sets minimum amount
        }
        else
        {
            QMessageBox::information(this,tr("Error"),qry3.lastError().text());
            qDebug()<<qry3.lastQuery();
        }
    }

    QMessageBox::information(this,tr("Deenze"),tr("Settings Saved..."));
}

void Login::on_commandLinkButton_Employees_clicked()
{
    //Open Employees form
    Employees employee;
    employee.setModal(false);
    employee.exec();
}
