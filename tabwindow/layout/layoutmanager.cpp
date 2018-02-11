#include "layoutmanager.h"
#include <QJsonDocument>
#include <QDebug>

#include "template.h"
#include "deal.h"

LayoutManager::LayoutManager(){
    willRemoveWindow = NULL;
}

LayoutManager &LayoutManager::instance(){
    static LayoutManager instance;
    return instance;
}

void LayoutManager::fromJson(const QByteArray &json){
    QJsonDocument jsonDoc= QJsonDocument::fromJson(json);
    QVariant result = jsonDoc.toVariant();
    QVariantList windowVars = result.toMap()["windows"].toList();
    foreach (QVariant (windowInfo), windowVars) {
       LayoutWindow * window = createWindow(windowInfo);
       window->show();
       windows_.append(window);
    }
}

void LayoutManager::createWindow(TabButtonBarButton *button){
    LayoutWindow *window = new LayoutWindow();
    window->setGeometry(QCursor::pos().x(),QCursor::pos().y(),
                        button->tab()->width(),button->tab()->height());
    window->show();
    windows_.append(window);
    window->addButton(button);
}

LayoutWindow *LayoutManager::createWindow(const QVariant &info){
    QVariantMap windowMap = info.toMap();

    LayoutWindow *window = new LayoutWindow();
    window->setGeometry(windowMap["x"].toInt(),windowMap["y"].toInt(),windowMap["width"].toInt(),windowMap["height"].toInt());
    QVariantList tabVars =windowMap["tabs"].toList();
    foreach (QVariant (tabInfo), tabVars) {
        createTab(window,tabInfo);
    }
    window->openTab(windowMap["currTabIndex"].toInt());
    return window;
}

Tab *LayoutManager::createTab(LayoutWindow * parentWindow,const QVariant &info){
    QVariantMap tabMap = info.toMap();
    Tab *tab = new Tab();
    tab->setName(tabMap["name"].toString());
    parentWindow->addTab(tab);

    int type = tabMap["type"].toInt();
    TabContent * tabContent;
    switch (type) {
    case Layout::Template:
        tabContent = new Template();
        break;
    case Layout::Deal:
        tabContent = new Deal();
        break;
    default:
        break;
    }

    tabContent->setInfo(tabMap["info"].toMap());

    tab->setTabContent(tabContent);
    return tab;
}

void LayoutManager::tryPrepareCloseWindow(LayoutWindow *window){
    if(window!=NULL&&window->tabSize()==0){
        if(windows_.contains(window)){
            windows_.removeOne(window);
        }
        /**
        window->close();
        delete window;
        @ses doTypeCloseWindow
        **/
//        window->setVisible(false);
        willRemoveWindow = window;
        qDebug() << "window Prepare close!";
    }
}

void LayoutManager::tryCloseWindow(){
    if(willRemoveWindow!=NULL){
        willRemoveWindow->close();
        delete willRemoveWindow;
        willRemoveWindow = NULL;
        qDebug() << "window closed!";
    }
}
