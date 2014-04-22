#include "year_deposits.h"
#include "ui_year_deposits.h"
#include"login.h"
#include<QDate>
#include<QMessageBox>


Year_Deposits::Year_Deposits(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Year_Deposits)
{
    ui->setupUi(this);
}

Year_Deposits::~Year_Deposits()
{
    delete ui;
}
void Year_Deposits::showRecords(QString id)
{
    QSqlQuery qry;
    memberID=id;
        qry.prepare("select * from deposits where  memberID='"+memberID+"' and dateDeposited> date('now','start of year')");
        QSqlQueryModel *modal=new QSqlQueryModel();
        if(qry.exec())
        {

        }
        else
        {
           qry.lastError().text();
        }
        qry.exec();
        modal->setQuery(qry);
        ui->tableView_Reports->setModel(modal);


}




void Year_Deposits::on_commandLinkButton_Back_clicked()
{
    this->hide();
}
