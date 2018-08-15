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
public:
    explicit NewRepairItem(QWidget *parent = 0);
    ~NewRepairItem();
    QString GetRepairDescrText();
    QString GetRepairQuantityText();
    QString GetRepairSinglePriceText();
    QString GetRepairValueText();
    void SetRepairIndex(unsigned int Idx);
    QLineEdit *DescrText;
    QLineEdit *QuantityText;
    QLineEdit *SinglePriceText;
    QLineEdit *ValueText;
    QLineEdit *RepairIndex;

private slots:
    void on_ButtonClear_clicked();
};

#endif // REPAIRWIDGETITEM_h
