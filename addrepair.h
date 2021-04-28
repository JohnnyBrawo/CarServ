#ifndef ADDREPAIR_H
#define ADDREPAIR_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVector>
#include <QDebug>
#include "newrepair.h"
#include "carsdatabase.h"

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
    void InsertRepair(bool SubMenu = false);
    void SetInitialDesign();
    void SetRandomDesign();
    void ClearAllinputs();
    void FillPage();
    bool CheckRecordInformation();
    void ReFillRepairIndexes();
    void ListAllMenus();
    void SetFieldWithSubMenus();
    void RecordRepair();
    void SetKlientName(QString CarNumber);

    QString m_strSelCarNumber;
    unsigned int m_uiRepairsNumber;
    unsigned int m_uiSubMenuNumber;
    bool         m_bSubMenuADD;
    double       m_dTotalCost;
    bool         m_bRecordSuccess = false;
    /** Repair  */
    NewRepair         *m_NewRepairForm; // ????

    /** DataBase */
    CarsDatabase MyData;

public:
    explicit AddRepair(QWidget *parent = 0);
    ~AddRepair();

    QVector <NewRepairItem*> m_vRepairItem;
    QVector <unsigned int> m_vMenusAndSubmebus;

signals:
    void CloseNewRepairForm();

private slots:
    void on_Button_ExitRepair_clicked();
    void on_Button_InsertRepair_clicked();
    void on_Button_DeleteRepair_clicked();
    void on_Button_RecordRepairs_clicked();
    void on_Button_Search_clicked();
    void OpenClearWindow();
    void on_Combo_RepairAutoRegNumber_currentIndexChanged(const QString &arg1);
    void on_Button_InsertSubMenu_clicked();

    void on_Button_TotalCostCalc_clicked();
    void on_Button_NewClientRepair_clicked();

    void RestoreAutoRepairForm();
    void on_CheckBox_DDS_clicked(bool checked);
};

#endif // ADDREPAIR_H
