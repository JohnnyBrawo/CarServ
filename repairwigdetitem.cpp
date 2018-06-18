#include "repairwigdetitem.h"
#include "ui_repairwigdetitem.h"
#include "qdebug.h"

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
    delete DescrText;
    delete QuantityText;
    delete SinglePriceText;
    delete ValueText;
}

void NewRepairItem::ResetAllFields()
{
    DescrText = new QLineEdit();
    QuantityText = new QLineEdit();
    SinglePriceText = new QLineEdit();
    ValueText = new QLineEdit();
    DescrText->setText("");
    QuantityText->setText("");
    SinglePriceText->setText("");
    ValueText->setText("");
    ui->HLayout->addWidget(DescrText);
    ui->HLayout->addWidget(QuantityText);
    ui->HLayout->addWidget(SinglePriceText);
    ui->HLayout->addWidget(ValueText);
}

void NewRepairItem::ClearFields()
{
    DescrText->setText("");
    QuantityText->setText("");
    SinglePriceText->setText("");
    ValueText->setText("");
}

QString NewRepairItem::GetRepairDescrText()
{
    return DescrText->text();
}

QString NewRepairItem::GetRepairQuantityText()
{
    return QuantityText->text();
}

QString NewRepairItem::GetRepairSinglePriceText()
{
    return SinglePriceText->text();
}

QString NewRepairItem::GetRepairValueText()
{
    return ValueText->text();
}

void NewRepairItem::on_ButtonClear_clicked()
{
    ClearFields();
}
