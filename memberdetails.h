#ifndef MEMBERDETAILS_H
#define MEMBERDETAILS_H

#include <QDialog>
#include"login.h"

namespace Ui {
class MemberDetails;
}

class MemberDetails : public QDialog
{
    Q_OBJECT

public:
    explicit MemberDetails(QWidget *parent = 0);

    ~MemberDetails();

private slots:

    void on_pushButton_Register_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_Clear_clicked();

private:
    Ui::MemberDetails *ui;

};

#endif // MEMBERDETAILS_H
