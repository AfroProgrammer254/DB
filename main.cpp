#include "login.h"
#include "year_deposits.h"
#include <QApplication>
#include<QSplashScreen>
#include<QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen *image=new QSplashScreen;
    image->setPixmap(QPixmap(QCoreApplication::applicationDirPath()+"/splash.jpg"));
    image->show();
    Login w;
    QTimer::singleShot(2500,image,SLOT(close()));
    QTimer::singleShot(2500,&w,SLOT(show()));

    return a.exec();
}
