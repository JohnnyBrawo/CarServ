#include "newauto.h"
#include "ui_newauto.h"

NewAuto::NewAuto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAuto)
{
    ui->setupUi(this);
}

NewAuto::~NewAuto()
{
    delete ui;
}

void NewAuto::on_Button_CancelNewAuto_clicked()
{
    emit CloseNewAutoForm();
    this->hide();
}
