 #ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include<QtSql>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlDriver>
#include<QDebug>
#include<QFileInfo>
#include"memberDetails.h"
#include<QtGui>


namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    QSqlDatabase db;
    void connClose();
    bool connOpen();
    void showCurrentDate();
    ~Login();

private slots:

    void on_commandLinkButton_clicked();

    void on_commandLinkButton_Exit_clicked();

    void on_commandLinkButton_3_clicked();

    void on_commandLinkButton_Save_clicked();

    void on_commandLinkButton_Employees_clicked();

private:
    Ui::Login *ui;

};

#endif // LOGIN_H




