#include "template.h"
#include "ui_template.h"

Template::Template(QWidget *parent) :
    TabContent(parent),
    ui(new Ui::Template)
{
    ui->setupUi(this);
}

Template::~Template()
{
    delete ui;
}


void Template::setInfo(const QVariantMap &info){
    ui->typeLabel->setText(info["type"].toString());
    ui->nameLabel->setText(info["name"].toString());
}

void Template::info(QVariantMap &info){
    info["name"] = "haha";
}
