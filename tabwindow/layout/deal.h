#ifndef DEAL_H
#define DEAL_H

#include <QWidget>
#include "tabcontent.h"

namespace Ui {
class Deal;
}

class Deal : public TabContent
{
    Q_OBJECT

public:
    explicit Deal(QWidget *parent = 0);
    ~Deal();

private:
    Ui::Deal *ui;
};

#endif // DEAL_H
