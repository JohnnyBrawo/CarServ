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
    ui->LText_RepairDescr->setText("Въведете текст");
    ui->LText_Quantity->setText("Въведете текст");
    ui->LText_SinglePrice->setText("Въведете текст");
    ui->LText_TotalValue->setText("Въведете текст");
}

void NewRepairItem::on_Button_ClearFields_clicked()
{
    ResetAllFields();
}
