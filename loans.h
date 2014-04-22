#ifndef LOANS_H
#define LOANS_H

#include <QDialog>

namespace Ui {
class Loans;
}

class Loans : public QDialog
{
    Q_OBJECT

public:
    explicit Loans(QWidget *parent = 0);
    ~Loans();

private slots:
    void on_lineEdit_MemID_textChanged(const QString &arg1);

    void on_commandLinkButton_clicked();

private:
    Ui::Loans *ui;
};

#endif // LOANS_H
