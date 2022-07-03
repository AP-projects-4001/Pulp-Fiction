#include <QApplication>
#include "loginsystem.h"
#include <QSplashScreen>
#include <QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/splash/img/splash.png").scaled(850, 550));
    splash->show();

    LoginSystem ls;
    QTimer::singleShot(2500, splash, SLOT(close()));
    QTimer::singleShot(3000, &ls, SLOT(showNormal()));

    return a.exec();
}
