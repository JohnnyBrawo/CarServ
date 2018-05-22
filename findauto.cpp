#include "findauto.h"
#include "ui_findauto.h"

FindAuto::FindAuto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindAuto)
{
    ui->setupUi(this);
}

FindAuto::~FindAuto()
{
    delete ui;
}
