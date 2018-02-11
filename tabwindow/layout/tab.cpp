#include "tab.h"
#include "ui_tab.h"
#include "layoutwindow.h"
#include <QHBoxLayout>
#include <QDebug>

Tab::Tab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab)
{
    ui->setupUi(this);
    parentWindow_ = NULL;
}

Tab::~Tab()
{
    delete ui;
    qDebug() << "tab closed!";
}

void Tab::setParentWindow(LayoutWindow * parentWindow){
    parentWindow_ = parentWindow;

    if(parentWindow==NULL){
        setParent(NULL);
    }else{
        setParent(parentWindow->tabParent());
    }
}

QString Tab::name(){
    return name_;
}

void Tab::setName(const QString &name){
    name_ = name;
}


void Tab::setTabContent(TabContent * tabContent){
    QHBoxLayout *layout = new QHBoxLayout(ui->tabContent);
    layout->addWidget(tabContent);
    tabContent->setParent(ui->tabContent);
    ui->tabContent->setLayout(layout);
}

void Tab::setTabToolButtonBox(TabToolButtonBox * tabToolButtonBox){
    QHBoxLayout *layout = new QHBoxLayout(ui->tabToolButtonBox);
    layout->addWidget(tabToolButtonBox);
    tabToolButtonBox->setParent(ui->tabToolButtonBox);
    ui->tabToolButtonBox->setLayout(layout);
}

