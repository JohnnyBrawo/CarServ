#ifndef NEWREPAIR_H
#define NEWREPAIR_H

#include <QDialog>

namespace Ui {
class NewRepair;
}

class NewRepair : public QDialog
{
    Q_OBJECT

public:
    explicit NewRepair(QWidget *parent = 0);
    ~NewRepair();

private:
    Ui::NewRepair *ui;

signals:
    void CloseNewRepairForm();
private slots:
    void on_Button_RepairDone_clicked();
};

#endif // NEWREPAIR_H
