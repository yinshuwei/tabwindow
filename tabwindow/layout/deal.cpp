#include "deal.h"
#include "ui_deal.h"

Deal::Deal(QWidget *parent) :
    TabContent(parent),
    ui(new Ui::Deal)
{
    ui->setupUi(this);
}

Deal::~Deal()
{
    delete ui;
}
