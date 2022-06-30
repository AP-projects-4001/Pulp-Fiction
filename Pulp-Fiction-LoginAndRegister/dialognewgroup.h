#ifndef DIALOGNEWGROUP_H
#define DIALOGNEWGROUP_H

#include <QDialog>

namespace Ui {
class DialogNewGroup;
}

class DialogNewGroup : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewGroup(QWidget *parent = nullptr);
    ~DialogNewGroup();

private:
    Ui::DialogNewGroup *ui;
};

#endif // DIALOGNEWGROUP_H
