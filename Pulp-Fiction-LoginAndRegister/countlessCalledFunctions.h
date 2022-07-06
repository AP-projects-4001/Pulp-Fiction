#ifndef COUNTLESSCALLEDFUNCTIONS_H
#define COUNTLESSCALLEDFUNCTIONS_H
#include <QTextEdit>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QCheckBox>
inline QListWidgetItem* setItemsInListWIdget(QListWidget* list , QString name)
{
    QByteArray ba = name.toLocal8Bit();
    const char *c_str2 = ba.data();
    QListWidgetItem* item = new QListWidgetItem;
    item->setText(c_str2);
    item->setForeground(Qt::white);
    list->addItem(item);
    return item;
}

inline QVBoxLayout* setQwidgetItemsInListWidget(QListWidget* list , int w , int h)
{
    list->setFlow(QListView::LeftToRight);
    list->setGridSize(QSize(w, h));
    list->setResizeMode(QListView::Adjust);
    list->setViewMode(QListView::ListMode);
    list->setWrapping(true);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    list->setLayout(layout);
    return layout;
}
inline void writeMessages(QListWidget* list ,QVBoxLayout* layout , QString mes, int status = 0)
{
    auto item = new QListWidgetItem("", list);
    auto text = new QTextEdit;
    QByteArray ba = mes.toLocal8Bit();
    const char *c_str2 = ba.data();
    text->setText(c_str2);

    if(status)
        text->setStyleSheet("QTextEdit "
                            "{color: black;border-radius: 10px;background-color: rgb(177,141,9);padding-left: 10px;}"
                            " QTextEdit:hover "
                            "{background-color: rgb(42, 46, 52);border-style: solid;border-color: rgb(53, 159, 159);"
                            "border-width: 1px;color: rgb(241, 182, 88);}");
    else
        text->setStyleSheet("QTextEdit "
                            "{color: black;border-radius: 10px;background-color: rgb(154,123,8);padding-left: 10px;}"
                            " QTextEdit:hover "
                            "{background-color: rgb(42, 46, 52);border-style: solid;border-color: rgb(53, 159, 159);"
                            "border-width: 1px;color: rgb(241, 182, 88);}");

    text->setMinimumSize(200, 50);
    text->setReadOnly(true);
    layout->addWidget(text);
    list->setItemWidget(item, text);
}
inline QCheckBox* writeCheckBox(QListWidget* list ,QVBoxLayout* layout , QString mes)
{
    auto item = new QListWidgetItem("", list);
    auto text = new QCheckBox;
    QByteArray ba = mes.toLocal8Bit();
    const char *c_str2 = ba.data();
    text->setText(c_str2);
    text->setStyleSheet("QCheckBox { background-color : rgba(0,0,0,0%); color : yellow; }");
    text->setMinimumSize(100, 20);
    layout->addWidget(text);
    list->setItemWidget(item, text);
    return text;
}
inline QRadioButton* writeRAdioButton(QListWidget* list ,QVBoxLayout* layout , QString mes)
{
    auto item = new QListWidgetItem("", list);
    auto text = new QRadioButton;
    QByteArray ba = mes.toLocal8Bit();
    const char *c_str2 = ba.data();
    text->setText(c_str2);
    text->setStyleSheet("QRadioButton { background-color : rgba(0,0,0,0%); color : white; padding-left:10px; padding-top:5px;}");
    text->setMinimumSize(100, 20);
    text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    layout->addWidget(text);
    list->setItemWidget(item, text);
    return text;
}

#endif // COUNTLESSCALLEDFUNCTIONS_H
