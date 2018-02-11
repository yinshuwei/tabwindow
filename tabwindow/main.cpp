#include <QApplication>
#include <QFile>
#include <QJsonObject>
#include <QVariant>
#include <QJsonDocument>
#include <QDebug>
#include <QDir>
#include <QList>
#include "layout/layoutmanager.h"
#include "layout/tab.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 加载qss文件
    QString qssFile = ":/resource/qss/application.qss";
    QFile styleSheet(qssFile);
    if(QFile::exists(qssFile) && styleSheet.open(QIODevice::ReadOnly)){
        qDebug() << QString("Load qss File %1 ...").arg(qssFile);
        qApp->setStyleSheet(styleSheet.readAll());
    }else{
        qWarning() << QString("Load qss File %1 Error!").arg(qssFile);
    }

    QFile layoutFile(QDir::currentPath()+"/layout.json");
    if(layoutFile.open(QFile::ReadOnly | QFile::Text)){
        QByteArray json =layoutFile.readAll();
        LayoutManager::instance().fromJson(json);
        layoutFile.close();
    }else{
        qWarning() << QString("Not find 'layout.json'").arg(qssFile);
        return 0;
    }
    int result = a.exec();

    return result;
}
