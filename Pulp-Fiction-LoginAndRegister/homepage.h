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
    void send_clicked();
    void getMessage();


signals:
   void itemClicked(QListWidgetItem*);


private slots:
   void on_actionNew_group_triggered();

   void on_newgroupbtn_clicked();

   void on_newchannelbtn_clicked();

   void on_actionSetting_triggered();

   void on_infobtn_clicked();

   void on_actionNew_chnale_triggered();



private:
    Ui::homepage *ui;
    QVector<QListWidgetItem*> list;
    QVector<int> StorePv;
    QVector<int> StoreGroup;
    QVector<int> StoreChannel;

    QVBoxLayout *layout;

    int index;
    user howAmI;

    chat* ptr;
    channel* channelOB;
    Group* group;
    pvchat* pv;

    Mode currentMode ;
    createchannel* dialog;
    groupInfo* infoGroup;
    channelInfo* infoChannel;
    PvInfo* infoPv;
    MyThread * mythread;

    void Display(bool isAd);
    void whatIsNew();
    bool isAdmin(user me);
};

#endif // HOMEPAGE_H
