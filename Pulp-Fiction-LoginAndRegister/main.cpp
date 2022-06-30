#include <QApplication>
#include "loginsystem.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginSystem ls;
    ls.show();
    return a.exec();
}
