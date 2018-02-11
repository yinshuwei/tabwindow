#include "tabbuttonbarlist.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>
#include <QApplication>
#include <QPainter>
#include "layoutmanager.h"
#include "drag.h"

TabButtonBarList::TabButtonBarList(QWidget *parent)
    : QWidget(parent){
    setAcceptDrops(true);
    dragButton = NULL;
}

void TabButtonBarList::setParentWindow(LayoutWindow * parentWindow){
    parentWindow_ = parentWindow;
}

void TabButtonBarList::dragEnterEvent(QDragEnterEvent *event){
    if (event->mimeData()->hasFormat("tab/x-layoutwindow-tab")){
        dragButton = qobject_cast<TabButtonBarButton *>(event->source());
        int newTabIndex = (event->pos().x()+TabButtonBarButton::WIDTH_DEFULT/2)/TabButtonBarButton::WIDTH_DEFULT;
        addButton(dragButton,newTabIndex);
        event->accept();
        activateWindow();
    } else{
        event->ignore();
    }
}

void TabButtonBarList::dragLeaveEvent(QDragLeaveEvent *){
    if(dragButton!=NULL){
        parentWindow_->removeButton(dragButton->tabIndex());
        dragButton=NULL;
        parentWindow_->moveByIndexAll();
    }
}

void TabButtonBarList::dragMoveEvent(QDragMoveEvent *event){
    if (event->mimeData()->hasFormat("tab/x-layoutwindow-tab")){
        dragButton = qobject_cast<TabButtonBarButton *>(event->source());
        int newX = event->pos().x()-30;
        dragButton->move(newX,0);
        int newTabIndex = (newX+TabButtonBarButton::WIDTH_DEFULT/2)/TabButtonBarButton::WIDTH_DEFULT;
        parentWindow_->moveButton(dragButton->tabIndex(),newTabIndex);
    } else{
        event->ignore();
    }
}

void TabButtonBarList::dropEvent(QDropEvent *event){
    if (event->source() != this) {
        if (event->mimeData()->hasFormat("tab/x-layoutwindow-tab")) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->ignore();
        }
    }else{
        QWidget::dropEvent(event);
    }
}

void TabButtonBarList::addButton(TabButtonBarButton *button,const int &index){
    int tabSize = parentWindow_->tabSize();

    parentWindow_->addTabToTabs(button->tab());
    parentWindow_->addButtonToButtons(button);
    button->show();
    button->setTabIndex(tabSize);
    if(index<tabSize){
        parentWindow_->moveButton(tabSize,index);
    }
    parentWindow_->openTab(button->tabIndex());
}
