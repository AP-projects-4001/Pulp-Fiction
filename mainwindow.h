#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QListWidgetItem>
#include "baseclass.h"
#include "channelclass.h"
#include "groupclass.h"
#include "pvclass.h"
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void clicked_list_item(QListWidgetItem* item);
    void send_clicked();

signals:
   void itemClicked(QListWidgetItem*);

private:
    Ui::MainWindow *ui;

    QVector<QListWidgetItem*> chat;
    QVector<baseClass*> vec;

    int index;
    QString name;
    int ID;

    channelClass* ob;
    groupClass* ob1;
    pvClass* ob2;
    void vectroToList(QVector<QString> write , QTextEdit* read)
    {
        QVector<QString>::iterator itt;
        for (itt = write.begin(); itt != write.end(); ++itt) {
             read->append(*itt);
        }
    }

    void Display(bool isAd);



};
#endif // MAINWINDOW_H
