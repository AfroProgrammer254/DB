#ifndef YEAR_DEPOSITS_H
#define YEAR_DEPOSITS_H

#include <QDialog>

namespace Ui {
class Year_Deposits;
}

class Year_Deposits : public QDialog
{
    Q_OBJECT

public:
    explicit Year_Deposits(QWidget *parent = 0);

    void showRecords(QString);
    ~Year_Deposits();

private slots:


    void on_commandLinkButton_Back_clicked();

private:
    Ui::Year_Deposits *ui;
    QString memberID;
};

#endif // YEAR_DEPOSITS_H
