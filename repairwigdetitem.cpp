#include "repairwigdetitem.h"
#include "ui_repairwigdetitem.h"
#include "qdebug.h"
#include <QDoubleValidator>

NewRepairItem::NewRepairItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewRepairItem),
    m_uiRepairIndex(1),
    m_bSubMenuField(false),
    m_bInitializeCheckboxes(false)
{
    qDebug() << "  NewRepairItem::NewRepairItem";
    ui->setupUi(this);
    ResetAllFields();
}

NewRepairItem::~NewRepairItem()
{
    delete ui;
}

void NewRepairItem::ResetAllFields()
{
    ui->DescrText->setText("");
    ui->QuantityText->setText("0");
    ui->QuantityText->setValidator(new QDoubleValidator(0, 100, 2, this) );
    ui->SinglePriceText->setText("0");
    ui->SinglePriceText->setValidator(new QDoubleValidator(0, 100, 2, this) );
    ui->TotalValueText->setText("0");
    ui->TotalValueText->setValidator(new QDoubleValidator(0, 100, 2, this) );

    ui->RepairIndex->setText(QString::number(m_uiRepairIndex));
    ui->RepairIndex->setFixedWidth(30);
}

void NewRepairItem::ChangeTaxesCheckBox(bool GlobalTaxesChecked)
{
    m_bGlobalTaxes = GlobalTaxesChecked;
    m_bInitializeCheckboxes = true;
    QString CheckBoxText = GlobalTaxesChecked?"Извади ДДС":"Начисли ДДС";
    ui->m_CheckDDS->setText(CheckBoxText);
    if(ui->m_CheckDDS->isChecked()){
        qDebug()<<"\n  IsChecked "<<ui->m_CheckDDS->isChecked();

        ui->m_CheckDDS->setChecked(false);
    }
    on_m_CheckDDS_clicked(GlobalTaxesChecked);
    m_bInitializeCheckboxes = false;
}

void NewRepairItem::ClearFields()
{
    ui->DescrText->setText("");
    ui->QuantityText->setText("");
    ui->SinglePriceText->setText("");
    ui->TotalValueText->setText("");
}

QString NewRepairItem::GetRepairDescrText()
{
    return ui->DescrText->text();
}

QString NewRepairItem::GetRepairQuantityText()
{
    return ui->QuantityText->text();
}

void NewRepairItem::SetRepairIndex(unsigned int Idx,unsigned int SubMenuIdx)
{
    if(SubMenuIdx != 0){
        m_bSubMenuField = true;
        ui->RepairIndex->setText(QString::number(Idx)+"." + QString::number(SubMenuIdx));
    }else {
        ui->RepairIndex->setText(QString::number(Idx));
    }
}

QString NewRepairItem::GetRepairSinglePriceText()
{
    return ui->SinglePriceText->text();
}

QString NewRepairItem::GetRepairValueText()
{
    return ui->TotalValueText->text();
}

void NewRepairItem::SetRepairValueText(const QString &StrValue)
{
    ui->TotalValueText->setText(StrValue);
}

double NewRepairItem::GetValueMaths()
{
    return GetRepairQuantityText().toDouble()*GetRepairSinglePriceText().toDouble();
}

QString NewRepairItem::GetRepairIndexText()
{
    return ui->RepairIndex->text();
}


void NewRepairItem::on_ButtonClear_clicked()
{
    ClearFields();
}

bool    NewRepairItem::IsSomeFieldChanged()
{
     qDebug()<<"\n  IsSomeFieldChanged "<<m_bNeedUpdate;
    return m_bNeedUpdate;
}

void NewRepairItem::ReSetSomeFieldChanged()
{
   m_bNeedUpdate = false;
   qDebug()<<"\n  ReSetSomeFieldChanged "<<m_bNeedUpdate;
}

void NewRepairItem::on_m_CheckDDS_clicked(bool checked)
{
    m_bTaxesIncluded = checked;

    if(m_bInitializeCheckboxes){
        if(m_bGlobalTaxes){
            ui->TotalValueText->setText( QString::number(GetValueMaths()+(GetValueMaths()/5)));
        }else {
            ui->TotalValueText->setText( QString::number(GetValueMaths()) );
        }
        return;
    }else {

        if(checked){
            if(m_bGlobalTaxes){
                // Wadim DDS
                ui->TotalValueText->setText( QString::number(GetValueMaths())); // Set original value
            }else {
                // Nachislqwame DDS
                ui->TotalValueText->setText( QString::number(GetValueMaths()+(GetValueMaths()/5))); // Set value with taxes
            }
        }else {
             if(m_bGlobalTaxes){
                // Dobavqme DDS
                ui->TotalValueText->setText( QString::number(GetValueMaths()+(GetValueMaths()/5)) );// Set value with taxes
             }else {
                 // Nachislqwame DDS
                ui->TotalValueText->setText( QString::number(GetValueMaths()));// Set original value
             }
        }
    }
}

void NewRepairItem::on_ValueText_textChanged()
{
    qDebug()<<"\n  on_ValueText_textChanged ";
    m_bNeedUpdate = true;
//    ui->TotalValueText->setText( QString::number(GetRepairQuantityText().toDouble()*GetRepairSinglePriceText().toDouble()) );
    ui->TotalValueText->setText( QString::number(GetValueMaths()) );
}

void NewRepairItem::on_SinglePriceText_textChanged()
{
    qDebug()<<"\n  on_SinglePriceText_textChanged ";
    m_bNeedUpdate = true;
     ui->TotalValueText->setText( QString::number(GetValueMaths()) );
}

void NewRepairItem::on_QuantityText_textChanged()
{
    qDebug()<<"\n  on_QuantityText_textChanged ";
    m_bNeedUpdate = true;
    ui->TotalValueText->setText( QString::number(GetValueMaths()) );
}

void NewRepairItem::on_DescrText_textChanged()
{
    qDebug()<<"\n  on_DescrText_textChanged ";
    m_bNeedUpdate = true;
}

void NewRepairItem::on_TotalValueText_textChanged()
{
    qDebug()<<"\n  on_TotalValueText_textChanged ";
    m_bNeedUpdate = true;
}

void NewRepairItem::on_QuantityText_textChanged(const QString &arg1)
{
    qDebug()<<"\n  on_QuantityText_textChanged "<<arg1;
    ui->TotalValueText->setText( QString::number(GetValueMaths()) );
}
