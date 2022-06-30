#include "pulp.h"
#include "maindatabase.h"
#include <QApplication>
#include "user.h"
#include "pvchat.h"
#include "loginsystem.h"
#include "homepage.h"
#include "newgroup.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginSystem ls;
    ls.show();
    return a.exec();
}
