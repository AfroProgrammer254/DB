#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include <QDialog>

namespace Ui {
class Employees;
}

class Employees : public QDialog
{
    Q_OBJECT

public:
    explicit Employees(QWidget *parent = 0);
    ~Employees();

private slots:
    void on_pushButton_Set_clicked();

    void on_pushButton_Back_clicked();

private:
    Ui::Employees *ui;
};

#endif // EMPLOYEES_H
