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

    unsigned int m_uiRepairIndex;
    bool       m_bSubMenuField;
    bool       m_bGlobatTaxEnabled;

public:
    explicit NewRepairItem(QWidget *parent = nullptr);
    ~NewRepairItem();
    QString GetRepairDescrText();
    QString GetRepairQuantityText();
    QString GetRepairSinglePriceText();
    QString GetRepairValueText();
    void SetRepairValueText(const QString &StrValue);
    void SetGlobalTaxes(bool AddTaxes){m_bGlobatTaxEnabled=AddTaxes;};
    QString GetRepairIndexText();
    void SetRepairIndex(unsigned int Idx, unsigned int SubMenuIdx=0);
    QLineEdit *DescrText;
    QLineEdit *QuantityText;
    QLineEdit *SinglePriceText;
    QLineEdit *ValueText;
    QLineEdit *RepairIndex;

    bool        IsFieldSubmenu() { return m_bSubMenuField;}

private slots:
    void on_ButtonClear_clicked();
    void on_m_CheckDDS_clicked(bool checked);
    void on_QuantityText_editingFinished();
};

#endif // REPAIRWIDGETITEM_h
