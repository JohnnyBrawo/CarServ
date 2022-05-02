#ifndef REPAIRWIDGETITEM_h
#define REPAIRWIDGETITEM_h

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class NewRepairItem;
}

class NewRepairItem : public QWidget
{
    Q_OBJECT

private:
    Ui::NewRepairItem *ui;

    void ResetAllFields();
    void CenterForm();
    void ClearFields();
    double GetValueMaths();

    unsigned int m_uiRepairIndex;
    bool       m_bSubMenuField;
    bool       m_bInitializeCheckboxes;
    bool       m_bGlobalTaxes=false;
    bool       m_bNeedUpdate=false;
    bool       m_bTaxesIncluded = false;

public:
    explicit NewRepairItem(QWidget *parent = nullptr);
    ~NewRepairItem();
    QString GetRepairDescrText();
    QString GetRepairQuantityText();
    QString GetRepairSinglePriceText();
    QString GetRepairValueText();
    void SetRepairValueText(const QString &StrValue);
    void ChangeTaxesCheckBox(bool GlobalTaxesChecked);
    QString GetRepairIndexText();
    void SetRepairIndex(unsigned int Idx, unsigned int SubMenuIdx=0);

    bool        IsFieldSubmenu() { return m_bSubMenuField;}
    bool        IsSomeFieldChanged();
    void        ReSetSomeFieldChanged();
    bool        GetTaxesIncluded(){ return m_bTaxesIncluded;}

private slots:
    void on_ButtonClear_clicked();
    void on_m_CheckDDS_clicked(bool checked);
    void on_ValueText_textChanged();
    void on_SinglePriceText_textChanged();
    void on_QuantityText_textChanged();
    void on_DescrText_textChanged();
    void on_TotalValueText_textChanged();
    void on_QuantityText_textChanged(const QString &arg1);
};

#endif // REPAIRWIDGETITEM_h
