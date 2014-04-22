#ifndef PANEL_H
#define PANEL_H

#include <QDialog>

namespace Ui {
class Panel;
}

class Panel : public QDialog
{
    Q_OBJECT

public:
    explicit Panel(QWidget *parent = 0);
    ~Panel();
    QString getMemID();
    QString getMemIDLoan();
    int setLoanLimits(QString);
    void depositNoLoan();
    void depositLoan();
    void requestLoan();
    void update(int);
    void refresh();


private slots:

    void on_pushButton_Deposit_clicked();

    void on_checkBox_toggled(bool checked);

    void on_pushButton_ProcessLoan_clicked();

    void on_pushButton_YearDeposits_clicked();

    void on_commandLinkButton_Back_clicked();

    void on_pushButton_List_clicked();

    void on_pushButton_TotalSavings_clicked();

    void on_pushButton_PrevDeposits_clicked();

    void on_pushButton_CreateMember_clicked();

    void on_pushButton_LoanPayment_clicked();

    void on_lineEdit_MemID_editingFinished();

    void on_lineEdit_MemIDLoan_editingFinished();

    void on_lineEdit_MemIDAcc_textChanged(const QString &arg1);
    void showContextMenu(const QPoint&);

    void on_tabWidget_tabBarClicked(int index);

    void on_pushButton_Records_clicked();

private:
    Ui::Panel *ui;

};

#endif // PANEL_H
