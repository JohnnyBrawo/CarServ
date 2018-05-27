#include "repairwigdetitem.h"
#include "ui_repairwigdetitem.h"

NewRepairItem::NewRepairItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewRepairItem)
{
    ui->setupUi(this);
    ResetAllFields();
}

NewRepairItem::~NewRepairItem()
{
    delete ui;
}

void NewRepairItem::ResetAllFields()
{
    ui->LText_RepairDescr->setText("");
    ui->LText_Quantity->setText("");
    ui->LText_SinglePrice->setText("");
    ui->LText_TotalValue->setText("");
}

void NewRepairItem::on_Button_ClearFields_clicked()
{
    ResetAllFields();
}
