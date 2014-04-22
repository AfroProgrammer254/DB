#ifndef LOGIN_FORM_H
#define LOGIN_FORM_H

#include <QDialog>

namespace Ui {
class Login_Form;
}

class Login_Form : public QDialog
{
    Q_OBJECT

public:
    explicit Login_Form(QWidget *parent = 0);
    void load();
    ~Login_Form();

private slots:

    void on_commandLinkButton_Login_clicked();

private:
    Ui::Login_Form *ui;
};

#endif // LOGIN_FORM_H
