#ifndef MEMBERS_H
#define MEMBERS_H

#include <QDialog>
#include<QtPrintSupport/QPrintDialog>
#include<QtPrintSupport/QPrinter>

namespace Ui {
class Members;
}

class Members : public QDialog
{
    Q_OBJECT

public:
    explicit Members(QWidget *parent = 0);
    void load();
    ~Members();

private slots:
    void on_commandLinkButton_Back_clicked();

    void on_pushButton_clicked();

private:
    Ui::Members *ui;

};

#endif // MEMBERS_H
