#include "newrepair.h"
#include "ui_newrepair.h"

NewRepair::NewRepair(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRepair)
{
    ui->setupUi(this);
}

NewRepair::~NewRepair()
{
    delete ui;
}
