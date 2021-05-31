#ifndef NEWREPAIR_H
#define NEWREPAIR_H

#include <QDialog>
#include "newclient.h"
#include "newauto.h"
#include "carsdatabase.h"

namespace Ui {
class NewRepair;
}

class NewRepair : public QDialog
{
    Q_OBJECT

enum NewAutoFields
    {
        eModel,
        eYear,
        eType,
        eFuel,
        eRegNumber,
        eAutoVin,
        eFieldsNum
    };

public:
    explicit NewRepair(QWidget *parent = nullptr);
    ~NewRepair();
    void ClearAllFields();
    QString GetNewCarReg(){ return m_strSelectedCarReg;}

private:
    Ui::NewRepair *ui;

    NewClient *m_Client;
    NewAuto  *m_Auto;
    CarsDatabase MyData;

    void FillComboMarki();
    void FillComboModeli(int MarkaIndex);
    bool CheckSelected(QString SelectedString);
    void ActivateField(NewRepair::NewAutoFields Field);
    void DeActivateField(NewRepair::NewAutoFields Field);
    bool CheckRecordInformation();
    bool CheckRecordObligatory();
    QString m_strSelectedCarReg;
    bool ClientInfoDone = false;
    bool AutoInfoDone = false;

    void    keyPressEvent(QKeyEvent *event);
private slots:
    void CenterForm();
    void OpenNewRepairWindow();
    void on_Button_AddNewRepair_clicked();
    void on_Combo_NewRepair_Marka_currentIndexChanged(int index);
    void on_Button_CancelNewRepair_clicked();

    void on_LText_NewRepairAutoRegNumber_editingFinished();

    void on_LText_NewRepairKlientName_editingFinished();

    void on_LText_NewRepairKlientPhone_editingFinished();

    void on_LText_NewRepairAutoMillage_editingFinished();

signals:
    void CloseNewRepairForm();
};

#endif // NEWREPAIR_H
