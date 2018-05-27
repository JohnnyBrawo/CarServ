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

private:
    Ui::AddRepair *ui;
    void CenterForm();
    void InsertRepair();
    void SetInitialDesign();
    void SetRandomDesign();
    bool m_bChecked;

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
    void on_Button_RecordRepairs_clicked();
    void on_Check_RandomClient_clicked(bool checked);
    void on_Button_Search_clicked();
    void OpenClearWindow();
};

#endif // ADDREPAIR_H
