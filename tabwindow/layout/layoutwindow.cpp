#include "layoutwindow.h"
#include "tab.h"
#include "tabbuttonbarbutton.h"
#include "tabbuttonbarlist.h"
#include <QDebug>
#include <QBoxLayout>
#include <QMimeData>
#include "layoutmanager.h"

LayoutWindow::LayoutWindow(QWidget *parent) :
    QMainWindow(parent)
{
    tabParent_ = new QWidget(this);
    buttonBarList_ = new TabButtonBarList(this);
    buttonBarList_->setParentWindow(this);
    currTab_ = NULL;

    setMinimumWidth(800);
    setMinimumHeight(500);

    setAcceptDrops(true);
}

void LayoutWindow::resizeEvent( QResizeEvent *event )
{
    tabParent_->setGeometry(0,0,this->width(),this->height());
    buttonBarList_->setGeometry(0,40,this->width()-200,30);
    if(currTab_!=NULL){
        currTab_->setGeometry(0,0,this->width(),this->height());
    }
    return QMainWindow::resizeEvent(event);
}

LayoutWindow::~LayoutWindow(){
    delete tabParent_;
    delete buttonBarList_;
    if(buttons_.size()>0){
        foreach (TabButtonBarButton *button, buttons_) {
            delete button;
        }
    }
    if(tabs_.size()>0){
        foreach (Tab *tab, tabs_) {
            delete tab;
        }
    }
}

bool LayoutWindow::containsTab(Tab *tab){
    return tabs_.contains(tab);
}

bool LayoutWindow::containsButton(TabButtonBarButton *button){
    return buttons_.contains(button);
}

void LayoutWindow::addTab(Tab *tab){
    if(!containsTab(tab)){
        TabButtonBarButton *button = new TabButtonBarButton(tab,this);
        tab->setParentWindow(this);
        button->setParentWindow(this);
        button->setTabIndex(tabSize());
        addTabToTabs(tab);
        addButtonToButtons(button);
    }
}

void LayoutWindow::addButton(TabButtonBarButton *button){
    buttonBarList_->addButton(button,buttons_.size());
    addTabToTabs(button->tab());
    addButtonToButtons(button);
}

void LayoutWindow::openTab(Tab *tab){
    foreach (Tab *tabTemp, tabs_) {
        if(tabTemp!=tab){
            tabTemp->setGeometry(-width()*2,-height()*2,width(),height());
        }
    }
    tab->setGeometry(0,0,width(),height());
    currTab_ = tab;
    currTab_->show();
    currTab_->raise();
}

void LayoutWindow::openTab(const int &index){
    if(buttons_.size()<=0){
        return;
    }
    int openIndex = 0;
    if(buttons_.size()>index&&index>=0){
        openIndex = index;
    }
    foreach (TabButtonBarButton *button, buttons_) {
        if(button->tabIndex()==openIndex){
            openTab(button->tab());
            button->setProperty("isOpen",true);
        }else{
            button->setProperty("isOpen",false);
        }
        button->style()->polish(button);
    }
}

//QList<Tab *>& LayoutWindow::tabs(){
//    return tabs_;
//}

//QList<TabButtonBarButton *>& LayoutWindow::buttons_{
//    return buttons_;
//}

QWidget *LayoutWindow::tabParent(){
    return tabParent_;
}
TabButtonBarList *LayoutWindow::buttonBarList(){
    return buttonBarList_;
}

void LayoutWindow::addTabToTabs(Tab *tab){
    if(!containsTab(tab)){
        tabs_.append(tab);
    }
    tab->setParentWindow(this);
}

void LayoutWindow::removeTabFromTabs(Tab *tab){
    if(containsTab(tab)){
        tabs_.removeOne(tab);
    }
    tab->setParentWindow(NULL);
}

void LayoutWindow::addButtonToButtons(TabButtonBarButton *button){
    if(!containsButton(button)){
        buttons_.append(button);
    }
    button->setParentWindow(this);
}

void LayoutWindow::removeButtonFromButtons(TabButtonBarButton *button){
    if(containsButton(button)){
        buttons_.removeOne(button);
    }
    button->setParentWindow(NULL);
}

void LayoutWindow::dragEnterEvent(QDragEnterEvent *event){
    if (event->mimeData()->hasFormat("tab/x-layoutwindow-tab")){
        this->activateWindow();
    }
    QMainWindow::dragEnterEvent(event);
}

int LayoutWindow::tabSize(){
    return buttons_.size();
}

TabButtonBarButton *LayoutWindow::getButtonByIndex(const int &tabIndex){
    TabButtonBarButton *currButton = NULL;
    foreach (TabButtonBarButton *button, buttons_) {
        if(button->tabIndex()==tabIndex){
            currButton = button;
        }
    }
    return currButton;
}

void LayoutWindow::moveButton(const int &fromTabIndex,const int &toTabIndex){
    if(toTabIndex>=tabSize()||
        toTabIndex<0||
        fromTabIndex>=tabSize()||
        fromTabIndex<0){
        return;
    }
    TabButtonBarButton *currButton = getButtonByIndex(fromTabIndex);
    if(fromTabIndex>toTabIndex){
        foreach (TabButtonBarButton *button, buttons_) {
            if(button->tabIndex()>=toTabIndex && button->tabIndex()<fromTabIndex ){
                button->setTabIndex(button->tabIndex()+1);
            }
        }
    }else if(fromTabIndex<toTabIndex){
        foreach (TabButtonBarButton *button, buttons_) {
            if(button->tabIndex()<=toTabIndex && button->tabIndex()>fromTabIndex ){
                button->setTabIndex(button->tabIndex()-1);
            }
        }
    }
    if(currButton!=NULL){
        currButton->setTabIndex(toTabIndex);
    }
}

void LayoutWindow::removeButton(const int &tabIndex){
    if(tabIndex>=buttons_.size()||
        tabIndex<0){
        return;
    }
    TabButtonBarButton *currButton = getButtonByIndex(tabIndex);
    foreach (TabButtonBarButton *button, buttons_) {
        if(button->tabIndex()>tabIndex ){
            button->setTabIndex(button->tabIndex()-1);
        }
    }
    if(currButton!=NULL){
        removeTabFromTabs(currButton->tab());
        removeButtonFromButtons(currButton);
        currButton->setParent(NULL);
        if(tabIndex>0){
            openTab(tabIndex-1);
        }else{
            openTab(0);
        }
    }
    LayoutManager::instance().tryPrepareCloseWindow(this);
}

void LayoutWindow::moveByIndexAll(){
    foreach (TabButtonBarButton *button, buttons_) {
        button->moveByIndex();
    }
}
