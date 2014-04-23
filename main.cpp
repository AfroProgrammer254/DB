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
    QIcon icon;
    icon.addPixmap(QPixmap(QCoreApplication::applicationDirPath()+"/member1.ico"));
    Login w;
    QTimer::singleShot(2500,image,SLOT(close()));
    QTimer::singleShot(2500,&w,SLOT(show()));
    a.setWindowIcon(icon);
    a.setApplicationName("Deenze Finance Management System");
    a.setApplicationVersion("1.0.0");
    a.setOrganizationName("Deenze Incorporated");

    return a.exec();
}
