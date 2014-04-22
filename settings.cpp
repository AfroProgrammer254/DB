#include "settings.h"
#include "ui_settings.h"
#include"login.h"
#include<QMessageBox>


Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    //validate inputs
    QIntValidator *decvalidator=new QIntValidator(0,1000000,this);
    ui->lineEdit_Amt1->setValidator(decvalidator);
    ui->lineEdit_Amt2->setValidator(decvalidator);
    ui->lineEdit_Amt3->setValidator(decvalidator);
    ui->lineEdit_Amt4->setValidator(decvalidator);
    ui->lineEdit_Amt5->setValidator(decvalidator);
    ui->lineEdit_Amt6->setValidator(decvalidator);
    ui->lineEdit_Limit1a->setValidator(decvalidator);
    ui->lineEdit_Limit1b->setValidator(decvalidator);
    ui->lineEdit_Limit2a->setValidator(decvalidator);
    ui->lineEdit_Limit2b->setValidator(decvalidator);
    ui->lineEdit_Limit3a->setValidator(decvalidator);
    ui->lineEdit_Limit3b->setValidator(decvalidator);
    ui->lineEdit_Limit4a->setValidator(decvalidator);
    ui->lineEdit_Limit4b->setValidator(decvalidator);
    ui->lineEdit_Limit5a->setValidator(decvalidator);
    ui->lineEdit_Limit5b->setValidator(decvalidator);
    ui->lineEdit_Limit6->setValidator(decvalidator);

}

Settings::~Settings()
{
    delete ui;
}


void Settings::on_pushButton_SetLimits_clicked()
{
    //variables for the limits
    QString Limit1="Limit1",Limit2="Limit2",Limit3="Limit3",Limit4="Limit4",Limit5="Limit5",Limt6="Limit6";
    QString Limit1a,Limit1b,Limit2a,Limit2b,Limit3a,Limit3b,Limit4a,Limit4b,Limit5a,Limit5b,Limit6;
    QString amt1,amt2,amt3,amt4,amt5,amt6;
    Limit1a=ui->lineEdit_Limit1a->text();
    Limit1b=ui->lineEdit_Limit1b->text();
    Limit2a=ui->lineEdit_Limit2a->text();
    Limit2b=ui->lineEdit_Limit2b->text();
    Limit3a=ui->lineEdit_Limit3a->text();
    Limit3b=ui->lineEdit_Limit3b->text();
    Limit4a=ui->lineEdit_Limit4a->text();
    Limit4b=ui->lineEdit_Limit4b->text();
    Limit5a=ui->lineEdit_Limit5a->text();
    Limit5b=ui->lineEdit_Limit5b->text();
    Limit6=ui->lineEdit_Limit6->text();
    amt1=ui->lineEdit_Amt1->text();
    amt2=ui->lineEdit_Amt2->text();
    amt3=ui->lineEdit_Amt3->text();
    amt4=ui->lineEdit_Amt4->text();
    amt5=ui->lineEdit_Amt5->text();
    amt6=ui->lineEdit_Amt6->text();
    //insert the values into the database
    QSqlQuery qry1,qry2,qry3,qry4,qry5,qry6;
    qry1.prepare("update loan_limits set a='"+Limit1a+"',b='"+Limit1b+"',amount='"+amt1+"' where Limits='"+Limit1+"'");
    qry2.prepare("update loan_limits set a='"+Limit2a+"',b='"+Limit2b+"',amount='"+amt2+"' where Limits='"+Limit2+"'");
    qry3.prepare("update loan_limits set a='"+Limit3a+"',b='"+Limit3b+"',amount='"+amt3+"' where Limits='"+Limit3+"'");
    qry4.prepare("update loan_limits set a='"+Limit4a+"',b='"+Limit4b+"',amount='"+amt4+"' where Limits='"+Limit4+"'");
    qry5.prepare("update loan_limits set a='"+Limit5a+"',b='"+Limit5b+"',amount='"+amt5+"' where Limits='"+Limit5+"'");
    qry6.prepare("update loan_limits set a='"+Limit6+"',amount='"+amt6+"' where Limits='"+Limt6+"'");
       if(qry1.exec())
       {
           if(qry2.exec())
           {
               if(qry3.exec())
               {
                   if(qry4.exec())
                   {
                       if(qry5.exec())
                       {
                           if(qry6.exec())
                           {
                              QMessageBox::information(this,tr("Loan Limits"),tr("Set..."));
                           }
                           else
                           {
                               qDebug()<<qry6.lastError().text();
                           }
                       }
                   }
               }
           }
       }


}

void Settings::on_pushButton_clicked()
{
    this->hide();
}
