#ifndef NEWGROUP_H
#define NEWGROUP_H

#include <QDialog>
#include <QWidget>
#include <QCheckBox>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QVector>
#include "user.h"
#include <QCheckBox>

namespace Ui {
class newGroup;
}

class newGroup : public QDialog
{
    Q_OBJECT

public:
    explicit newGroup(user who ,QWidget *parent = nullptr);
    ~newGroup();
    QVector<QCheckBox*> cheVec;
    QVector<user> write;
    QVector<user> selected;
    int getCount()const;
    int check = 0;
    QString name;

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::newGroup *ui;
    user howAmI;

};

#endif // NEWGROUP_H
