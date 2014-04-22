#include "members.h"
#include"login.h"
#include "ui_members.h"
#include<QPainter>


Members::Members(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Members)
{
    ui->setupUi(this);
}

Members::~Members()
{
    delete ui;
}

void Members::load()
{
    //load employeeIDs from the database
    QSqlQueryModel *modal=new QSqlQueryModel();
    QSqlQuery qry,qry2;
    qry.prepare("select memberID,firstName,lastName,mobileNumber from member_details");
    qry.exec();
    modal->setQuery(qry);
    ui->tableView_List->setModel(modal);
    qry2.prepare("select COUNT(*) from member_details");
    if(qry2.exec())
    {
        while(qry2.next())
        {
        QString res;
        res=qry2.value(0).toString();
        ui->label_Total->setText(res);
        }
    }
    else
    {
        qDebug()<<qry2.lastError().text();
    }
}

void Members::on_commandLinkButton_Back_clicked()
{
    this->hide();
}

void Members::on_pushButton_clicked()
{

}
