#ifndef TAB_H
#define TAB_H

#include <QWidget>
#include "tabcontent.h"
#include "tabtoolbuttonbox.h"

class LayoutWindow;

namespace Ui {
class Tab;
}

class Tab : public QWidget
{
    Q_OBJECT

public:
    explicit Tab(QWidget *parent = 0);
    ~Tab();
    void open();
    void info();
    void setParentWindow(LayoutWindow *);
    QString name();
    void setName(const QString &);
    void setTabContent(TabContent *);
    void setTabToolButtonBox(TabToolButtonBox *);

private:
    Ui::Tab *ui;
    LayoutWindow * parentWindow_;
    QString name_;
    QString type_;

};

#endif // TAB_H
