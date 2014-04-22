#include "panel.h"
#include "ui_panel.h"
#include"login.h"
#include"year_deposits.h"
#include"prevdeposits.h"
#include"members.h"
#include"memberdetails.h"
#include"loans.h"
#include<QMenu>
#include<QMessageBox>


Panel::Panel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Panel)
{
    ui->setupUi(this);
    //Validate inputs
    QIntValidator *decValidator=new QIntValidator(100,200000,ui->lineEdit_LoanAmt);
    ui->lineEdit_LoanAmt->setValidator(decValidator);
    QIntValidator *decValidator2=new QIntValidator(100,1000000,ui->lineEdit_Deposit);
    ui->lineEdit_Deposit->setValidator(decValidator2);
    ui->lineEdit_PaymentAmt->setValidator(decValidator2);
    QIntValidator *decValidator3=new QIntValidator(0,1000,ui->lineEdit_MemID);
    ui->lineEdit_MemID->setValidator(decValidator3);
    ui->lineEdit_MemIDAcc->setValidator(decValidator3);
    ui->lineEdit_MemIDLoan->setValidator(decValidator3);
    QString style="QLabel{background-color:white;}";
    ui->pushButton_ProcessLoan->setStyleSheet(style);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(showContextMenu(const QPoint&)));

}
void Panel::showContextMenu(const QPoint& pos)
{
    QPoint globalPos=this->mapToGlobal(pos);
    QMenu myMenu;
    myMenu.addAction("Refresh");
    QAction* selectedItem=myMenu.exec(globalPos);
    if(selectedItem)
    {
      refresh();
    }

}
void Panel::refresh()
{
    //clears all the values on the screen
    ui->lineEdit_MemIDAcc->setText("");
    ui->label_FName->setText("");
    ui->label_LName->setText("");
    ui->label_IdNumber->setText("");
    ui->label_Balance->setText("");
    ui->label_Status->setText("");
    ui->label_LoanBalance->setText("");
}

Panel::~Panel()
{
    delete ui;
}
void Panel::update(int dep)
{
    int val=dep;
    int total_funds;
    QString total;
    QSqlQuery qry,qry2;
    qry.prepare("select total_funds from group_details");
    if(qry.exec())
    {
        while(qry.next())
        {
            total_funds=qry.value(0).toInt();

        }
    }
    else
    {
        QMessageBox::critical(this,tr("Error"),qry.lastError().text());
    }
    total_funds+=val;
    total=QString::number(total_funds);
    qry2.prepare("update group_details set total_funds='"+total+"'");
    if(qry2.exec())
    {
        qDebug()<<"deposited..."<<total;

    }
    else
    {
        QMessageBox::critical(this,tr("Error"),qry2.lastError().text());
    }

}

int Panel::setLoanLimits(QString id)
{
    //Set loan limit
    int limit1a,limit1b,limit2a,limit2b,limit3a,limit3b,limit4a,limit4b,limit5a,limit5b,limit6;
    int amt1,amt2,amt3,amt4,amt5,amt6;
    int lim1=0,lim2=0,lim3=0,lim4=0,lim5=0,lim6=0,limAmt=0;
    QString memid=id;
    QSqlQuery qry1,qry2,qry3,qry4,qry5,qry6;
    qry1.prepare("select a,b,amount from loan_limits where rowid=1");
    qry2.prepare("select a,b,amount from loan_limits where rowid=2");
    qry3.prepare("select a,b,amount from loan_limits where rowid=3");
    qry4.prepare("select a,b,amount from loan_limits where rowid=4");
    qry5.prepare("select a,b,amount from loan_limits where rowid=5");
    qry6.prepare("select a,amount from loan_limits where rowid=6");
    if(qry1.exec())
    {
        while(qry1.next())
        {
        limit1a=qry1.value(0).toInt();
        limit1b=qry1.value(1).toInt();
        amt1=qry1.value(2).toInt();
        }
    }
    if(qry2.exec())
    {
        while(qry2.next())
        {
        limit2a=qry2.value(0).toInt();
        limit2b=qry2.value(1).toInt();
        amt2=qry2.value(2).toInt();
        }
    }
    if(qry3.exec())
    {
        while(qry3.next())
        {
        limit3a=qry3.value(0).toInt();
        limit3b=qry3.value(1).toInt();
        amt3=qry3.value(2).toInt();
        }
    }
    if(qry4.exec())
    {
        while(qry4.next())
        {
        limit4a=qry4.value(0).toInt();
        limit4b=qry4.value(1).toInt();
        amt4=qry4.value(2).toInt();
        }
    }
    if(qry5.exec())
    {
        while(qry5.next())
        {
        limit5a=qry5.value(0).toInt();
        limit5b=qry5.value(1).toInt();
        amt5=qry5.value(2).toInt();
        }
    }
    if(qry6.exec())
    {
        while(qry6.next())
        {
        limit6=qry6.value(0).toInt();
        amt6=qry6.value(1).toInt();
        }
    }

    qDebug()<<amt1<<amt2<<amt3<<amt4<<amt5<<amt6;
    QSqlQuery dep;
    dep.prepare("select depositAmount from deposits where memberID='"+memid+"'");
    if(dep.exec())
    {
        while(dep.next())
        {
          int depAmt=dep.value(0).toInt();
          if(depAmt>limit1a && depAmt<=limit1b)
          {
              lim1++;
          }
          if(depAmt>limit2a && depAmt<=limit2b)
          {
              lim2++;
          }
          if(depAmt>limit3a && depAmt<=limit3b)
          {
              lim3++;
          }
          if(depAmt>limit4a && depAmt<=limit4b)
          {
              lim4++;
          }
          if(depAmt>limit5a && depAmt<=limit5b)
          {
              lim5++;
          }
          if(depAmt>limit6)
          {
              lim6++;
          }
        }
    }
    else
    {
        qDebug()<<dep.lastError().text();
        qDebug()<<dep.lastQuery();
    }

    qDebug()<<lim1<<lim2<<lim3<<lim4<<lim5<<lim6;

    if(lim1>lim2 && lim1> lim3 && lim1> lim4 && lim1> lim5 && lim1>lim6)
    {

        limAmt=amt1;
        qDebug()<<"limAmt:"<<limAmt;
        return limAmt;
    }
    if(lim2>lim1 && lim2>lim3 && lim2>lim4 && lim2>lim5 && lim2>lim6)
    {
        limAmt=amt2;
        qDebug()<<"limAmt:"<<limAmt;
        return limAmt;
    }
    if(lim3>lim2 && lim3>lim1 && lim3>lim4 && lim3>lim5 && lim3>lim6)
    {
        limAmt=amt3;
        qDebug()<<"limAmt:"<<limAmt;
        return limAmt;
    }
    if(lim4>lim2 && lim4>lim3 && lim4>lim1 && lim4>lim5 && lim4>lim6)
    {
        limAmt=amt4;
        qDebug()<<"limAmt:"<<limAmt;
        return limAmt;
    }
    if(lim5>lim2 && lim5>lim3 && lim5>lim4 && lim5>lim1 && lim5>lim6)
    {
        limAmt=amt5;
        qDebug()<<"limAmt:"<<limAmt;
        return limAmt;
    }
    if(lim6>lim2 && lim6>lim3 && lim6>lim4 && lim6>lim5 && lim6>lim1)
    {
        limAmt=amt6;
        qDebug()<<"limAmt:"<<limAmt;
        return limAmt;
    }
    else
    {
        limAmt=amt3;
        qDebug()<<"limAmt:"<<limAmt;
        return limAmt;
    }

}

void Panel::depositNoLoan()
{

    QString amount,memID,memBal;
    int bal=0;
    int amt=0;
    QVariant accBal;
    bool ok;
    amount=ui->lineEdit_Deposit->text();
    memID=getMemID();//acquire member ID
    //Make sure a value has been entered
    if(amount.length()>1)
    {
        ok=true;
    }
    else
    {
        ok=false;
        QMessageBox::critical(this,tr("Deposit"),tr("No amount entered..."));
    }
    //Make sure MemberID has been entered
    if(memID=="")
    {
        ok=false;
        QMessageBox::critical(this,tr("Deposit"),tr("No Member ID entered..."));
    }

    //Validate Minimum Deposit
    if(ok==true)
    {

        QSqlQuery dep;
        dep.prepare("select minimumAmount from group_details");
        if(dep.exec())
        {
            while(dep.next())
            {
            int amountdep;
            amountdep=amount.toInt();
            if(amountdep>=dep.value(0).toInt())
            {
                ok=true;
            }
            else
            {
                ok=false;
                QMessageBox::critical(this,tr("Deposit"),tr("Amount to be deposited is less than the required amount"));
            }
            }
        }
        else
        {
            qDebug()<<dep.lastError().text();
            qDebug()<<dep.lastQuery();
        }
    }
    //Insert data into the database
    if(ok==true)
    {
    QSqlQuery qry1;

    qry1.prepare("select accountBal from member_accounts where memberID='"+memID+"'");
    if(qry1.exec())
    {

        while(qry1.next())
        {
        bal=qry1.value(0).toInt();
        amt=amount.toInt();
        bal+=amt;
        update(amt);//update the system
         accBal=bal;

        }
    }
    memBal=accBal.value<QString>();
    QSqlQuery qry2,qry3;
    qry2.prepare("insert into deposits (memberID,depositAmount,dateDeposited) values('"+memID+"','"+amount+"',date('now'))");
    qry3.prepare("update member_accounts set accountBal='"+memBal+"' where memberID='"+memID+"'");
    if(qry2.exec())
    {
        if(qry3.exec())
        {
        QMessageBox::information(this,tr("Deposit Amount"),tr("Amount Deposited..."));
        }
        else
        {
            qDebug()<<qry3.lastError().text();
        }
    }
    else
    {
        QMessageBox::information(this,tr("Error"),qry2.lastError().text());
        qDebug()<<qry2.lastQuery();
    }

    }

    ui->lineEdit_Deposit->setText("");

}
void Panel::depositLoan()
{

    QString amount,memID,memBal;
   int bal=0;
    int amt=0;
    int interest=0,loan=0,currbal=0;
    QVariant accBal;
    bool ok;
    amount=ui->lineEdit_PaymentAmt->text();
     memID=getMemIDLoan();

    //Check that value has been entered
    if(amount.length()>1)
    {
        ok=true;
    }
    else
    {
        ok=false;
        QMessageBox::critical(this,tr("Deposit"),tr("No amount entered..."));
    }
    //Validate Minimum Deposit
    if(ok==true)
    {

        QSqlQuery min;
        min.prepare("select minimumAmount from group_details");
        if(min.exec())
        {
            while(min.next())
            {
            int amountdep;
            amountdep=amount.toInt();
            if(amountdep>=min.value(0).toInt())
            {
                ok=true;
            }
            else
            {
                ok=false;
                QMessageBox::critical(this,tr("Deposit"),tr("Amount to be deposited is less than the required amount"));
            }
            }
        }
        else
        {
            qDebug()<<min.lastError().text();
            qDebug()<<min.lastQuery();
        }
    }
    if(ok==true)
    {
         //Insert data into the database
        QSqlQuery qryLoan,qrybal;

        qryLoan.prepare("select loanAmountTaken,interestAccrued from loans where memberID='"+memID+"'");
        if(qryLoan.exec())
        {
            while(qryLoan.next())
            {
                loan=qryLoan.value(0).toInt();
                interest=qryLoan.value(1).toInt();
            }
        }
        amt=amount.toInt();
        if(amt>=(loan+interest))
        {
            qrybal.prepare("select accountBal from member_accounts where memberID='"+memID+"'");
            if(qrybal.exec())
            {
                while(qrybal.next())
                {
                    currbal=qrybal.value(0).toInt();
            bal=amt-(loan+interest);
            currbal+=bal;
            accBal=currbal;
            memBal=accBal.value<QString>();
            update(amt);//update system

                }
            }

            QSqlQuery dep,memAcc,drop;
            dep.prepare("insert into deposits(memberID,depositAmount,dateDeposited) values('"+memID+"','"+amount+"',date('now'))");
            memAcc.prepare("update member_accounts set accountBal='"+memBal+"' where memberID='"+memID+"'");
            drop.prepare("delete from loans where memberID='"+memID+"'");
            if(dep.exec())
            {
                if(memAcc.exec())
                {
                    if(drop.exec())
                    {
                        QMessageBox::information(this,tr("Deposit"),tr("Amount Deposited and Loan cleared..."));
                    }
                    else
                    {
                        qDebug()<<drop.lastError().text();
                    }
                }
                else
                {
                    qDebug()<<memAcc.lastError().text();
                }
            }
            else
            {
                qDebug()<<dep.lastError().text();
            }
        }
        else
        {
            bal=(loan+interest)-amt;
            accBal=bal;
            memBal=accBal.value<QString>();
            QString currdate,zero="0";
            currdate=QDate::currentDate().toString();
            QSqlQuery dep,memAcc;
             dep.prepare("insert into deposits(memberID,depositAmount,dateDeposited) values('"+memID+"','"+amount+"','"+currdate+"')");
             memAcc.prepare("update loans set loanAmountTaken='"+memBal+"',interestAccrued='"+zero+"' where memberID='"+memID+"'");
             if(dep.exec())
             {
                 if(memAcc.exec())
                 {
                     QMessageBox::information(this,tr("Deposit"),tr("Amount Deposited and Records Updated..."));
                 }
                 else
                 {
                     qDebug()<<memAcc.lastError().text();
                 }
             }
             else
             {
                 qDebug()<<dep.lastError().text();
             }
             update(amt);//update system
        }
        QSqlQuery display;
        display.prepare("select accountBal from member_accounts where memberID='"+memID+"'");
        if(display.exec())
        {
            while(display.next())
            {
                ui->label_Balance->setText(display.value(0).toString());
            }
        }
    }

    ui->lineEdit_PaymentAmt->setText("");

}
void Panel::requestLoan()
{
    QString memID,interest,loanAmt;
    QVariant interestAccrued;
    int count=0,loanLimit;
    double i;
    int principal,rate,time,total_funds;
    loanAmt=ui->lineEdit_LoanAmt->text();
    principal=loanAmt.toInt();
    bool pending=true;
    bool ok=false;
    //Acquire the member id
        memID=getMemIDLoan();
    //Check if amount has been entered
        if(loanAmt.length()>1)
        {
            ok=true;
        }
        else
        {
            ok=false;
            QMessageBox::critical(this,tr("Loan Request"),tr("No Amount entered..."));
        }
        if(memID=="")
        {
            ok=false;
            QMessageBox::critical(this,tr("Loan Request"),tr("No Member ID entered..."));
        }
    //check if the SACCO has enough funds to issue the loan
    if(ok==true)
    {
        QSqlQuery funds;
        int total_funds;
        funds.prepare("select total_funds from group_details");
        if(funds.exec())
        {
            while(funds.next())
            {
                total_funds=funds.value(0).toInt();
            }
        }
        if(principal>=total_funds)
        {
            ok=false;
            QMessageBox::critical(this,tr("Loan Request"),tr("Loan Request Denied. Not enough funds to grant request.."));
        }
        else
        {
            ok=true;
        }
    }
    if(ok==true)
    {
     //Check if member has been depositing throughout the year
    int dep,num=0;
    QSqlQuery mindep,activity;
    mindep.prepare("select minNumOfDeposits from group_details");
    if(mindep.exec())
    {
        while(mindep.next())
        {
            dep=mindep.value(0).toInt();
        }
    }
    else
    {
        qDebug()<<mindep.lastError().text();
    }
    activity.prepare("select * from deposits where dateDeposited> date('now','start of month','-12 months')and memberID='"+memID+"'");
    if(activity.exec())
    {
        while(activity.next())
        {
            num++;
        }
    }
    else
    {
        QMessageBox::critical(this,tr("Loan Request"),tr("No deposits found..."));
        qDebug()<<activity.lastError().text();
    }
    if(num>=dep)
    {
        ok=true;
    }
    else
    {
        ok=false;
        QMessageBox::critical(this,tr("Loan Request"),tr("The Member does not  have the minimum number of deposits in order to request a loan"));
    }
    }
    if(ok==true)
    {
    //Check Loan Limits
    loanLimit=setLoanLimits(memID);
    if(principal>loanLimit)
    {
        QMessageBox::critical(this,tr("Loan Request"),tr("Loan denied as it is beyond the Member's allowed limit"));
        ok=false;
    }
    else
    {
        ok=true;
    }
    }
    //if conditions to apply for a loan are all true
    if(ok==true)
    {
    //Check if member has a pending loan
    QSqlQuery qry2;
    qry2.prepare("select * from loans where memberID='"+memID+"'");
    if(qry2.exec())
    {
        while(qry2.next())
        {
            count++;
        }
        if(count==0)
        {
            pending=false;
        }
        else
        {
            pending=true;
            QMessageBox::critical(this,tr("Loan Request"),("The Member already has a pending loan"));
        }

    }
    //If member has no pending loan and loan is within limit he is allowed to take a loan
    if(pending==false)
    {
        //Acquire the SACCO's rate and time period required to pay a loan
        QSqlQuery qry3;
        qry3.prepare("select interestRate,time from group_details");
        if(qry3.exec())
        {
            while(qry3.next())
            {
                rate=qry3.value(0).toInt();
                time=qry3.value(1).toInt();
            }
        }
        //get the interest
        i=(principal*rate*time/12)/100;
      interestAccrued=i;
      interest=interestAccrued.value<QString>();

        //Record the loan
        QSqlQuery qry4,qry5,qry6,records;
        qry4.prepare("insert into loans(memberID,loanAmountTaken,interestAccrued,dateOfLoan) values('"+memID+"','"+loanAmt+"','"+interest+"',date('now'))");
        records.prepare("insert into loan_records(memberID,loanAmountTaken,dateOfLoan) values('"+memID+"','"+loanAmt+"',date('now'))");
        if(qry4.exec())
        {
            if(records.exec())
            {
            QMessageBox::information(this,tr("Loan Request"),tr("Loan Request Approved...Loan Granted"));
            }
            else
            {
                QMessageBox::critical(this,tr("Loan Request"),records.lastError().text());
            }
        }
        else
        {
            QMessageBox::critical(this,tr("Loan Request"),qry4.lastError().text());
            qDebug()<<qry4.lastQuery();
        }
        //Deduct the loan amount from the SACCO's total funds
        qry5.prepare("select total_funds from group_details");
        if(qry5.exec())
        {
            while(qry5.next())
            {
                total_funds=qry5.value(0).toInt();
            }

        }
        total_funds-=principal;
        QString total;
        total=QString::number(total_funds);
        qry6.prepare("update group_details set total_funds='"+total+"'");
        if(qry6.exec())
        {
            qDebug()<<"Total funds should be:"<<total;
        }
        else
        {
            QMessageBox ::critical(this,tr("Loan Request"),qry6.lastError().text());
        }
    }
    }
    ui->lineEdit_LoanAmt->setText("");
     ui->checkBox->toggle();
}

void Panel::on_pushButton_Deposit_clicked()
{
          depositNoLoan();//call deposit function

}

void Panel::on_checkBox_toggled(bool checked)
{
    if(checked==true)
    {
        QString style="QPushButton{background-color:black; color:red;}";
        ui->pushButton_ProcessLoan->setEnabled(true);
        ui->pushButton_ProcessLoan->setStyleSheet(style);
    }
    else
    {
        QString label="QLabel{background-color:white;}";
        ui->pushButton_ProcessLoan->setEnabled(false);
        ui->pushButton_ProcessLoan->setStyleSheet(label);
    }
}

void Panel::on_pushButton_ProcessLoan_clicked()
{
   requestLoan();//calls function which processes a loan request


}

void Panel::on_pushButton_YearDeposits_clicked()
{
    QString memID;
    memID=getMemID();
    if(memID=="")
    {
        QMessageBox::information(this,tr("Year Deposits"),("No Member ID entered..."));
        return;
    }
    Year_Deposits report;
    report.showRecords(memID);
    report.setModal(false);
    report.exec();//Opens the Yearly deposits form
}

void Panel::on_commandLinkButton_Back_clicked()
{
    this->hide();//Closes the panel
}

void Panel::on_pushButton_List_clicked()
{
    Members list;
    list.setModal(true);
    list.load();
    list.exec();//Opens the List of Members Window
}

void Panel::on_pushButton_TotalSavings_clicked()
{
    QString total;
    QSqlQuery qry;
    qry.prepare("select total_funds from group_details");
    if(qry.exec())
    {
        while(qry.next())
        {
            total=qry.value(0).toString();
        }

    }
    else
    {
        qDebug()<<qry.lastError().text();
    }
    QString savings="The Total funds accumulated by the SACCO is: Kshs."+total;
    QMessageBox::information(this,tr("Total SACCO Savings"),savings);

}

void Panel::on_pushButton_PrevDeposits_clicked()
{
    QString memID;
    memID=getMemID();
    if(memID=="")
    {
        QMessageBox::information(this,tr("Previous Deposits"),tr("No Member ID entered..."));
        return;
    }

     PrevDeposits list;
     list.showPrevDeposits(memID);
     list.setModal(false);
     list.exec();//opens the previous deposits

}

QString Panel::getMemID()
{
    QString memID;
    memID=ui->lineEdit_MemID->text();
    return memID;
}

void Panel::on_pushButton_CreateMember_clicked()
{
    MemberDetails  member;
    member.setModal(true);
    member.exec();//opens the new members form

}

void Panel::on_pushButton_LoanPayment_clicked()
{
    //Check if member has a pending loan
        QSqlQuery qryloan;
        int count=0;
       QString memID;
        memID=getMemIDLoan();//get the memberID
        if(memID=="")
        {
            QMessageBox::critical(this,tr("Loan Payment"),tr("No Member ID entered..."));
            return;
        }
        qryloan.prepare("select * from loans where memberID='"+memID+"'");
        if(qryloan.exec())
        {
            while(qryloan.next())
            {
                count++;
            }
            if(count==0)//No pending loan
            {
                QMessageBox::information(this,tr("Loan Payment"),tr("The Member does not have any pending loan"));
                ui->lineEdit_PaymentAmt->setText("");
            }
            else//Loan
            {
                depositLoan();//call deposit function for loan payment

            }

        }
}

QString Panel::getMemIDLoan()
{
    QString MemID;
    MemID=ui->lineEdit_MemIDLoan->text();
    return MemID;

}
void Panel::on_lineEdit_MemID_editingFinished()
{
    QString MemID=ui->lineEdit_MemID->text();
    QSqlQuery load;
    load.prepare("select firstName,lastName from member_details where memberID='"+MemID+"'");
    if(load.exec())
    {
        while(load.next())
        {
            ui->label_firstName->setText(load.value(0).toString());
            ui->label_lastName->setText(load.value(1).toString());


        }
    }
    else
    {
        qDebug()<<load.lastError().text();
    }
}

void Panel::on_lineEdit_MemIDLoan_editingFinished()
{
    QString MemID=ui->lineEdit_MemIDLoan->text();
    QSqlQuery load;
    load.prepare("select firstName,lastName from member_details where memberID='"+MemID+"'");
    if(load.exec())
    {
        while(load.next())
        {
            ui->label_loaneeFirstName->setText(load.value(0).toString());
            ui->label_loaneeLastName->setText(load.value(1).toString());


        }
    }
    else
    {
        qDebug()<<load.lastError().text();
    }
    if(MemID=="")
    {
        ui->label_loaneeFirstName->setText("");
        ui->label_loaneeLastName->setText("");
        qDebug()<<"Davinci!";
    }
}

void Panel::on_lineEdit_MemIDAcc_textChanged(const QString &arg1)
{
    QString MemID=arg1;
    int count=0;
    QSqlQuery load,status,bal;
    load.prepare("select firstName,lastName,idNumber from member_details where memberID='"+MemID+"'");
    if(load.exec())
    {
        while(load.next())
        {
            ui->label_FName->setText(load.value(0).toString());
            ui->label_LName->setText(load.value(1).toString());
            ui->label_IdNumber->setText(load.value(2).toString());

        }
    }
    else
    {
        qDebug()<<load.lastError().text();
    }

    status.prepare("select * from loans where memberID='"+MemID+"'");
    if(status.exec())
    {
        while(status.next())
        {
            count++;
        }
    }
    if(count==0)
    {
        ui->label_Status->setText("Member has no pending loan");
        ui->label_LoanBalance->setText("No outstanding Loan Amount");

    }
    else
    {
        ui->label_Status->setText("Member has a pending loan");
        QSqlQuery loan;
        loan.prepare("select loanAmountTaken,interestAccrued from loans");
        if(loan.exec())
        {
            while(loan.next())
            {
                int outstandingLoan=loan.value(0).toInt()+loan.value(1).toInt();
                ui->label_LoanBalance->setText(QString::number(outstandingLoan));
            }
        }
    }
    bal.prepare("select accountBal from member_accounts where memberID='"+MemID+"'");
    if(bal.exec())
    {
        while(bal.next())
        {
            ui->label_Balance->setText(bal.value(0).toString());

        }
    }

}

void Panel::on_tabWidget_tabBarClicked(int index)
{
    if(index==0)
    {
        refresh();//calls refresh function to clear the screen
    }
}

void Panel::on_pushButton_Records_clicked()
{
    Loans records;
    records.setModal(true);
    records.exec();

}
