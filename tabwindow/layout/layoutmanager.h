#ifndef LAYOUTMANAGER_H
#define LAYOUTMANAGER_H

#include <QList>
#include <QVariant>
#include "layoutwindow.h"
#include "tab.h"
#include "tabbuttonbarbutton.h"

namespace Layout {
    enum TabType{
        Template = 1,
        Deal
    };
}

class LayoutManager
{
public:
    static LayoutManager &instance();

    LayoutWindow *createWindow(const QVariant &);
    void createWindow(TabButtonBarButton *);
    Tab *createTab(LayoutWindow *,const QVariant &);
    void fromJson(const QByteArray &);
    void tryPrepareCloseWindow(LayoutWindow *);
    void tryCloseWindow();

private:
    LayoutManager();
    LayoutManager(const LayoutManager &);
    const LayoutManager& operator=(const LayoutManager &);
    QList<LayoutWindow *> windows_;
    LayoutWindow *willRemoveWindow;

};

#endif // LAYOUTMANAGER_H
