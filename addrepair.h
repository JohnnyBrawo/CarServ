#ifndef ADDREPAIR_H
#define ADDREPAIR_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVector>
#include <QDebug>

#include "repairwigdetitem.h"

namespace Ui {
class AddRepair;
}

class AddRepair : public QWidget
{
    Q_OBJECT

public:
    explicit AddRepair(QWidget *parent = 0);
    ~AddRepair();

    QVector <NewRepairItem*> m_vRepairItem;

signals:
    void CloseNewRepairForm();

private slots:
    void on_Button_ExitRepair_clicked();

    void on_Button_InsertRepair_clicked();

    void on_Button_DeleteRepair_clicked();

    void on_pushButton_clicked();

private:
    Ui::AddRepair *ui;
};

#endif // ADDREPAIR_H
