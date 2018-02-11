#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QWidget>
#include "tabcontent.h"

namespace Ui {
class Template;
}

class Template : public TabContent
{
    Q_OBJECT

public:
    explicit Template(QWidget *parent = 0);
    ~Template();
    void setInfo(const QVariantMap &);
    void info(QVariantMap &);

private:
    Ui::Template *ui;
};

#endif // TEMPLATE_H
