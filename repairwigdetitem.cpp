#include "repairwigdetitem.h"
#include "ui_repairwigdetitem.h"
#include "qdebug.h"

NewRepairItem::NewRepairItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewRepairItem),
    m_uiRepairIndex(1),
    m_bSubMenuField(false)
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
    delete RepairIndex;
}

void NewRepairItem::ResetAllFields()
{
    DescrText = new QLineEdit();
    QuantityText = new QLineEdit();
    SinglePriceText = new QLineEdit();
    ValueText = new QLineEdit();
    RepairIndex = new QLineEdit();
    DescrText->setText("");
    QuantityText->setText("0");
    SinglePriceText->setText("0");
    ValueText->setText("0");

    RepairIndex->setText(QString::number(m_uiRepairIndex));
    RepairIndex->setFixedWidth(30);
    ui->HLayout->addWidget(RepairIndex);
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

void NewRepairItem::SetRepairIndex(unsigned int Idx,unsigned int SubMenuIdx)
{
    if(SubMenuIdx != 0){
        m_bSubMenuField = true;
        RepairIndex->setText(QString::number(Idx)+"." + QString::number(SubMenuIdx));
    }else {
        RepairIndex->setText(QString::number(Idx));
    }
}

QString NewRepairItem::GetRepairSinglePriceText()
{
    return SinglePriceText->text();
}

QString NewRepairItem::GetRepairValueText()
{
    return ValueText->text();
}

void NewRepairItem::SetRepairValueText(const QString &StrValue)
{
    ValueText->setText(StrValue);
}

QString NewRepairItem::GetRepairIndexText()
{
    return RepairIndex->text();
}


void NewRepairItem::on_ButtonClear_clicked()
{
    ClearFields();
}
