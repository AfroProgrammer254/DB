#ifndef PREVDEPOSITS_H
#define PREVDEPOSITS_H

#include <QDialog>

namespace Ui {
class PrevDeposits;
}

class PrevDeposits : public QDialog
{
    Q_OBJECT

public:
    explicit PrevDeposits(QWidget *parent = 0);
    void showPrevDeposits(QString);
    ~PrevDeposits();

private slots:
    void on_commandLinkButton_clicked();

private:
    Ui::PrevDeposits *ui;
};

#endif // PREVDEPOSITS_H
