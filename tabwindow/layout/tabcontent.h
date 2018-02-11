#ifndef TABCONTENT_H
#define TABCONTENT_H

#include <QWidget>
#include <QVariantMap>

class TabContent : public QWidget
{
    Q_OBJECT
public:
    explicit TabContent(QWidget *parent = 0);
    virtual void setInfo(const QVariantMap &);
    virtual void info(QVariantMap &);

signals:

public slots:

};

#endif // TABCONTENT_H
