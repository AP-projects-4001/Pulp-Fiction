#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include "maindatabase.h"
#include <QCoreApplication>
#include "user.h"
#include "graph.h"

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(user me ,QWidget *parent = nullptr);
    ~Setting();
    QString getName () const{return name;}
    QVector<user> write;
    QVector<QCheckBox*> cheVec;
    QVector<user> selected;
    int getCount();

private slots:
    void on_editprofile_clicked();

    void on_backtohomepage_clicked();

    void on_backbtn_clicked();

    void on_editprivacy_clicked();

    void on_backbtn_2_clicked();

    void on_showpassforeditprofile_stateChanged(int arg1);

    void on_savebtn_clicked();

    void on_setonlyfreindsbtn_clicked();

    void on_settonoonebtn_clicked();

    void on_resettodefault_clicked();

    void on_editcontacts_clicked();

    void on_backbtn_3_clicked();

    void on_uplButton_clicked();

    void on_saveeditprivacy_clicked();

    void on_searchcontact_textChanged(const QString &arg1);

    void on_deletefriend_clicked();

    void on_selectallbtneditfriends_clicked();

    void on_selectnonebtneditfriends_clicked();

private:
    Ui::Setting *ui;
    user howAmI;
    QString name;

    QString picName_1, picName_2;
    QString picDir = QCoreApplication::applicationDirPath()+"/../";
    QString createprofileandstylesheet(QString picDir);
};

#endif // SETTING_H
