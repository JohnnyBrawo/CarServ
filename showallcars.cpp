#include "showallcars.h"
#include "ui_showallcars.h"

ShowAllcars::ShowAllcars(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowAllcars)
{
    ui->setupUi(this);

}

ShowAllcars::~ShowAllcars()
{
    delete ui;
}

void ShowAllcars::ClearAllFields()
{
    ui->LText_RepairDate->setText("");
    ui->LText_RepairFuel->setText("");
    ui->LText_RepairMarka->setText("");
    ui->LText_RepairModel->setText("");
    ui->LText_RepairRegNumber->setText("");
    ui->LText_RepairType->setText("");
    ui->LText_RepairVIN->setText("");
    ui->LText_RepairYear->setText("");
}

void ShowAllcars::OpenClearWindow()
{
     ClearAllFields();
     this->show();
}

void ShowAllcars::on_Button_Back_clicked()
{
    this->hide();
    emit CloseShowAllAutoForm();
    ClearAllFields();

}
