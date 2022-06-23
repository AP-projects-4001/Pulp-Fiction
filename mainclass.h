#ifndef MAINCLASS_H
#define MAINCLASS_H

#include "mainwindow.h"
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QList>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QWidget>
#include <QListView>
#include <QStringListModel>
class mainClass
{ 
public:

    virtual void vectorToVector(QVector<QString> first , QVector<QString> second)
    {
        QVector<QString>::iterator itt;
        for (itt = first.begin(); itt != first.end(); ++itt) {
             second.push_back(*itt);
        }
    }

    void vectroToList(QVector<QString> write , QTextEdit* read)
    {
        QVector<QString>::iterator itt;
        for (itt = write.begin(); itt != write.end(); ++itt) {
             read->append(*itt);
        }
    }
protected:
    int ID;
    QString name;

    QPushButton* send;
    QPushButton* info;
    QTextEdit* message;
    QLineEdit* sendMessage;

};

#endif // MAINCLASS_H
