#ifndef PVINFO_H
#define PVINFO_H

#include <QDialog>
#include "user.h"
namespace Ui {
class PvInfo;
}

class PvInfo : public QDialog
{
    Q_OBJECT

public:
    explicit PvInfo(user me , user you ,QWidget *parent = nullptr);
    ~PvInfo();

private:
    Ui::PvInfo *ui;
    user Me;
    user You;
};

#endif // PVINFO_H
