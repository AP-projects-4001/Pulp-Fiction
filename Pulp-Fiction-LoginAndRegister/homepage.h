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
#include "createchannel.h"
#include "groupinfo.h"
#include "channelinfo.h"
#include "pvinfo.h"
#include "mythread.h"
#include "setting.h"
#include "contacts.h"
#include "creategroup.h"
#include "graphdialog.h"
enum Mode { GroupMode, ChannnelMode, PvMode };
namespace Ui {
class homepage;
}
class homepage : public QMainWindow
{
    Q_OBJECT

public:
    explicit homepage(user me , QWidget *parent = nullptr);

    void vectroToList();

    ~homepage();

public slots:
    void clicked_list_item(QListWidgetItem* item);

    void getMessage();


signals:
   void itemClicked(QListWidgetItem*);


private slots:
   void on_actionNew_group_triggered();

   void on_newgroupbtn_clicked();

   void on_newchannelbtn_clicked();

   void on_actionSetting_triggered();

   void on_infobtn_clicked();

   void on_contactsbtn_clicked();

   void on_settingbtn_clicked();

   void on_actionContacts_triggered();

   void on_actionExit_triggered();

   void on_actionNew_channel_triggered();

   void on_Sendbtn_clicked();

   void on_graphbtn_clicked();

private:
    Ui::homepage *ui;
    QVector<QListWidgetItem*> list;
    QVector<int> StorePv;
    QVector<int> StoreGroup;
    QVector<int> StoreChannel;
    QVector<int> StorePos;
    QVector<chat*> vec;
    QVector<user> PVs;

    int  checkThread = 0;
    int  index = 0;
    user howAmI;

    QVBoxLayout* layout;

    chat   * ptr;
    channel* channelOB;
    Group  * group;
    pvchat * pv;

    Mode           currentMode ;
    createchannel * dialog;
    creategroup   * creategroupdialog;
    groupInfo     * infoGroup;
    channelInfo   * infoChannel;
    PvInfo        * infoPv;
    Setting       * settingDialog;
    Contacts      * contactDialog;
    MyThread      * mythread;
    graphdialog   * graphd ;
    void Display(bool isAd);
    void whatIsNew();
    bool isAdmin(user me);
};

#endif // HOMEPAGE_H
