#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include <QVector>
#include <QListWidgetItem>
#include "baseclass.h"
#include "channelclass.h"
#include "groupclass.h"
#include "pvclass.h"
#include <QTextEdit>
#include <QVBoxLayout>

namespace Ui {
class homepage;
}

class homepage : public QMainWindow
{
    Q_OBJECT

public:
    explicit homepage(QWidget *parent = nullptr);
//    enum Mode { ChatMode, ChannnelMode, PvMode };
//    void vectroToList(QVector<QString> write);
    ~homepage();

private slots:
    void on_actionExit_triggered();

//    void on_Sendbtn_clicked();

//    void on_listofusersgroupschanels_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

//    void on_listofusersgroupschanels_itemClicked(QListWidgetItem *item);

private:
    Ui::homepage *ui;
//    QVector<QListWidgetItem*> chat;
//    QVector<baseClass*> vec;

//    int index;
//    QString name;
//    int ID;

//    channelClass* chanel;
//    groupClass* group;
//    pvClass* pv;

//    Mode currentMode ;


//    void Display(bool isAd);
};

#endif // HOMEPAGE_H
