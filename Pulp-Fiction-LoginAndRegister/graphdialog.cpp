#include "graphdialog.h"
#include "ui_graphdialog.h"
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
#include <QClipboard>
graphdialog::graphdialog( user me, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graphdialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(20.0);
    bodyShadow->setDistance(4.0);
    bodyShadow->setColor(QColor(10, 5, 45, 80));
    ui->winstack->setGraphicsEffect(bodyShadow);

    howAmI = me ;
    mygraph = new Graph;
    QVector<QVector<int>> graphComponents = mygraph->Creat_AdjacencyMatrix(howAmI.get_ID());
    QVector<QString> convrted = mygraph->Convert_MatrixToString(graphComponents);
    foreach(const QString item, convrted)
    {
        ui->matrix->append(item + "\n");
    }

    QVector<QString> graphComponentsguide = mygraph->Creat_Guidlist(howAmI.get_ID());
    foreach(const QString item, graphComponentsguide)
    {

        ui->list_2->append(item + "\n");
    }
}

graphdialog::~graphdialog()
{
    delete ui;
}

void graphdialog::on_opensite_clicked()
{
    QString link =  "https://graphonline.ru/en/create_graph_by_matrix";
    QDesktopServices::openUrl(QUrl(link));
}


void graphdialog::on_backtohomepage_clicked()
{
    graphdialog::close();
}


void graphdialog::on_copybtn_clicked()
{
    QClipboard *clip = QApplication::clipboard();
    QString input = ui->matrix->toPlainText();
    clip->setText(input);
}


void graphdialog::on_copybtn_2_clicked()
{
    QClipboard *clip = QApplication::clipboard();
    QString input = ui->list_2->toPlainText();
    clip->setText(input);
}

