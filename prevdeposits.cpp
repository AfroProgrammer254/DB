#include "prevdeposits.h"
#include "ui_prevdeposits.h"
#include "login.h"
#include<QMessageBox>


PrevDeposits::PrevDeposits(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrevDeposits)
{
    ui->setupUi(this);
}

PrevDeposits::~PrevDeposits()
{
    delete ui;
}
void PrevDeposits::showPrevDeposits(QString id)
{
    //loads the latest 10 deposits from the database
        QString memID=id;
        QSqlQuery  deposits;
        QSqlQueryModel *list=new QSqlQueryModel();
        deposits.prepare("select * from deposits where memberID='"+memID+"' order by rowid desc limit 10");
        deposits.exec();
        list->setQuery(deposits);
        ui->tableView_Deposits->setModel(list);


}
void PrevDeposits::on_commandLinkButton_clicked()
{
    this->hide();
}
