#ifndef PULP_H
#define PULP_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QList>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QListWidget>
#include <QWidget>
#include <QVector>
QT_BEGIN_NAMESPACE
namespace Ui { class mainClass; }
QT_END_NAMESPACE
class Pulp : public QWidget
{
    Q_OBJECT
public:
    Pulp(QWidget *parent = nullptr);
private:

    QPushButton* newChannel;
    QPushButton* newGroup;
    QPushButton* setting;
    QPushButton* graph;
    QPushButton* findSomeOne;

    QListWidget* history;

    QLineEdit* search;
    QPushButton* showButton;

    QVector<QString> chats = {"famiy chat", "iut chat" , "ap"};

    void convertVectorToList(QVector<QString> svec , QListWidget* chatList);

};

#endif // PULP_H
