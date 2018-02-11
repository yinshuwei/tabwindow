#ifndef TabButtonBarList_H
#define TabButtonBarList_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QListWidget>
#include "layoutwindow.h"
#include "tabbuttonbarbutton.h"
#include "tab.h"

class TabButtonBarList : public QWidget
{
    Q_OBJECT

public:
    explicit TabButtonBarList(QWidget *parent = 0);
    void setParentWindow(LayoutWindow *);
    void addButton(TabButtonBarButton *button,const int &index);

protected:
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dragLeaveEvent(QDragLeaveEvent *);
    void dropEvent(QDropEvent *);

public slots:
//    void actionChangedHandler(Qt::DropAction);
//    void targetChangedHandler(QObject *newTarget);

private:
    LayoutWindow * parentWindow_;
    TabButtonBarButton *dragButton;
};

#endif // TabButtonBarList_H
