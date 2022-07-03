#ifndef CREATECHANNEL_H
#define CREATECHANNEL_H

#include <QDialog>
#include "user.h"

namespace Ui {
class createchannel;
}

class createchannel : public QDialog
{
    Q_OBJECT

public:
    explicit createchannel(user me ,QWidget *parent = nullptr);
    ~createchannel();

private:
    Ui::createchannel *ui;
    user howAmI;
};

#endif // CREATECHANNEL_H
