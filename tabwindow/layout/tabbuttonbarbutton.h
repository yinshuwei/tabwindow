#ifndef TABBUTTONBARBUTTON_H
#define TABBUTTONBARBUTTON_H

#include <QToolButton>
#include <QMouseEvent>
#include <QPoint>
#include <QPropertyAnimation>
#include "layoutwindow.h"
#include "tab.h"

class TabButtonBarButton : public QToolButton
{
    Q_OBJECT
public:
    explicit TabButtonBarButton(Tab *tab,QWidget *parent = 0);
    ~TabButtonBarButton();
    static int WIDTH_DEFULT;
    static int HEIGHT_DEFULT;
    void setParentWindow(LayoutWindow *);
    void setTabIndex(const int &tabIndex);
    int tabIndex();
    void moveByIndex();
    Tab *tab();
    void open();

public slots:
    void animationFinishedHandler();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    int mouseOffset_;
    int tabIndex_;
    QPropertyAnimation *animation_;
    LayoutWindow * parentWindow_;
    Tab *tab_;

};

#endif // TABBUTTONBARBUTTON_H
