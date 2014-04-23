#include "loans.h"
#include"login.h"
#include "ui_loans.h"

Loans::Loans(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loans)
{
    ui->setupUi(this);
    //Validation of the Member ID field
    QIntValidator *decValidator=new QIntValidator(0,1000,this);
    ui->lineEdit_MemID->setValidator(decValidator);
}

Loans::~Loans()
{
    delete ui;
}

void Loans::on_lineEdit_MemID_textChanged(const QString &arg1)
{
    //load records from the database for an individual member
    QString MemID=arg1;
    QSqlQuery records;
    QSqlQueryModel *model=new QSqlQueryModel();
    records.prepare("select * from loan_records where memberID='"+MemID+"'");
    records.exec();
    model->setQuery(records);
    ui->tableView_Records->setModel(model);
}

void Loans::on_commandLinkButton_clicked()
{
    this->hide();
}
