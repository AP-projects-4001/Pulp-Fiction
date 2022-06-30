#ifndef NEWGROUP_H
#define NEWGROUP_H

#include <QDialog>
#include <QWidget>
#include <QCheckBox>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QVector>
#include "user.h"
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
    int getCount()const;

public slots:
    void clickedMe();
private:
    Ui::newGroup *ui;

    user howAmI;

};

#endif // NEWGROUP_H
