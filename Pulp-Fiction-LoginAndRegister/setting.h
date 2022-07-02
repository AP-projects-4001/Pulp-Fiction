#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include "maindatabase.h"
#include "user.h"

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(user me ,QWidget *parent = nullptr);
    ~Setting();

private slots:
    void on_editprofile_clicked();

    void on_backtohomepage_clicked();

    void on_backbtn_clicked();

    void on_editprivacy_clicked();

    void on_backbtn_2_clicked();

    void on_showpassforeditprofile_stateChanged(int arg1);

    void on_savebtn_clicked();

private:
    Ui::Setting *ui;
    user howAmI;
};

#endif // SETTING_H
