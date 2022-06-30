#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include <QVector>
#include <QListWidgetItem>
#include "channelclass.h"
#include "groupclass.h"
#include "pvchat.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include "user.h"
#include "newgroup.h"
enum Mode { ChatMode, ChannnelMode, PvMode };
namespace Ui {
class homepage;
}
class homepage : public QMainWindow
{
    Q_OBJECT

public:
    explicit homepage(user me , QWidget *parent = nullptr);
    void vectroToList(QVector<QString> write);
    ~homepage();

public slots:
    void clicked_list_item(QListWidgetItem* item);
    void slidebar_clicked(QListWidgetItem* item);
    void send_clicked();
    void info_clicked();

//    void on_actionExit_triggered();

//    void on_Sendbtn_clicked();

//    void on_listofusersgroupschanels_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

//    void on_listofusersgroupschanels_itemClicked(QListWidgetItem *item);


signals:
   void itemClicked(QListWidgetItem*);
   void slidebarClicked(QListWidgetItem*);

private:
    Ui::homepage *ui;
    QVector<QListWidgetItem*> list;


    int index;
    user howAmI;

    chat* ptr;
    channel* channelOB;
    Group* group;
    pvchat* pv;

    Mode currentMode ;
    newGroup* dialog;

    void Display(bool isAd);
};

#endif // HOMEPAGE_H
