#ifndef GRAPHDIALOG_H
#define GRAPHDIALOG_H
#include <QDialog>
#include <QCoreApplication>
#include "user.h"
#include "graph.h"
#include "customshadoweffect.h"
namespace Ui {
class graphdialog;
}

class graphdialog : public QDialog
{
    Q_OBJECT

public:
    explicit graphdialog( user me ,QWidget *parent = nullptr);
    ~graphdialog();

private slots:
    void on_opensite_clicked();

    void on_backtohomepage_clicked();

    void on_copybtn_clicked();

    void on_copybtn_2_clicked();

private:
    Ui::graphdialog *ui;
    Graph *mygraph;
    user howAmI ;
};

#endif // GRAPHDIALOG_H
