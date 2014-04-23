#include "login_form.h"
#include "ui_login_form.h"
#include"login.h"
#include"panel.h"
#include<QMessageBox>


Login_Form::Login_Form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login_Form)
{
    ui->setupUi(this);
    load();//load Employee Usernames from the database into the combobox
}

Login_Form::~Login_Form()
{
    delete ui;
}

void Login_Form::load()
{

    QSqlQuery load;
    QSqlQueryModel *modal=new QSqlQueryModel();
    load.prepare("select username from employees");
    load.exec();
    modal->setQuery(load);
    ui->comboBox_ID->setModel(modal);
}

void Login_Form::on_commandLinkButton_Login_clicked()
{
    QString id,password;
    int count=0;
    id=ui->comboBox_ID->currentText();
    password=ui->lineEdit_Password->text();
    QSqlQuery qry;
    qry.prepare("select * from employees where username='"+id+"' and password='"+password+"'");

    if(qry.exec())
    {

        while(qry.next())
        {
            count++;
        }
        if(count==1)
        {
        QMessageBox::information(this,tr("Login"),tr("Password confirmed.."));

        this->hide();
        Panel member;
        member.setModal(true);
        member.exec();
        }
        else
        {
            QMessageBox::critical(this,tr("Login"),tr("Unable to log you in! Check password..."));
            ui->lineEdit_Password->setText("");

        }

    }
    else
    {
        QMessageBox::information(this,tr("Deenze"),qry.lastError().text());
        qDebug()<<qry.lastQuery();

    }



}
