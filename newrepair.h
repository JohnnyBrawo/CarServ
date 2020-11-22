#ifndef NEWREPAIR_H
#define NEWREPAIR_H

#include <QDialog>

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

    void FillComboMarki();
    void FillComboModeli(int MarkaIndex);
    bool CheckSelected(QString SelectedString);
    void ActivateField(NewRepair::NewAutoFields Field);
    void DeActivateField(NewRepair::NewAutoFields Field);
    bool CheckRecordInformation();
    bool CheckRecordObligatory();
    QString m_strSelectedCarReg;


private slots:
    void CenterForm();
    void OpenNewRepairWindow();
    void on_Button_AddNewRepair_clicked();
    void on_Combo_NewRepair_Marka_currentIndexChanged(int index);
//    void on_Combo_NewAuto_Model_currentIndexChanged(int index);
    void on_Button_CancelNewRepair_clicked();

signals:
    void CloseNewRepairForm();
};

#endif // NEWREPAIR_H
