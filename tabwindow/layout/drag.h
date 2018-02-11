#ifndef DRAG_H
#define DRAG_H
#include <QDrag>
#include <QPixmap>

class Drag : public QDrag
{

    Q_OBJECT

public:
    Drag(QObject *parent=0);

private:
    QPixmap qpix;

public slots:
};

#endif // DRAG_H
