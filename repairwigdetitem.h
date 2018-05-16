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

public:
    explicit NewRepairItem(QWidget *parent = 0);
    ~NewRepairItem();

private slots:
    void on_Button_ClearFields_clicked();

private:
    Ui::NewRepairItem *ui;

    void ResetAllFields();
    void CenterForm();
};

#endif // REPAIRWIDGETITEM_h
