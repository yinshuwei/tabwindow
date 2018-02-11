#include "drag.h"
#include <QDebug>
#include <QCursor>
#include <QApplication>

Drag::Drag(QObject * parent):QDrag(parent)
{
    qpix = QPixmap(":/resource/bcm_warning_22.png");
}

