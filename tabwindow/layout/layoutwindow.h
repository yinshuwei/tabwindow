#ifndef WINDOW_H
#define WINDOW_H

#include <QList>
#include <QMainWindow>

class Tab;
class TabButtonBarButton;
class TabButtonBarList;

class LayoutWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit LayoutWindow(QWidget *parent = 0);
    ~LayoutWindow();
    void dragEnterEvent(QDragEnterEvent *event);

    void addTabToTabs(Tab *);
    void removeTabFromTabs(Tab *);

    void addButtonToButtons(TabButtonBarButton *);
    void removeButtonFromButtons(TabButtonBarButton *);

    void addButton(TabButtonBarButton *);

    void addTab(Tab *);
    void openTab(Tab *);
    void openTab(const int &index);
    void info();
    bool containsTab(Tab *);
    bool containsButton(TabButtonBarButton *button);
    QWidget *tabParent();
    TabButtonBarList *buttonBarList();
//    QList<Tab *>& tabs();
//    QList<TabButtonBarButton *>& buttons();
    int tabSize();
    virtual void resizeEvent(QResizeEvent *event);
    TabButtonBarButton *getButtonByIndex(const int &tabIndex);
    void moveButton(const int &fromTabIndex,const int &toTabIndex);
    void removeButton(const int &tabIndex);
    void moveByIndexAll();

private:
    Tab *currTab_;
    QList<Tab *> tabs_;
    QList<TabButtonBarButton *> buttons_;
    TabButtonBarList *buttonBarList_;
    QWidget * tabParent_;

signals:

public slots:

};

#endif // WINDOW_H
