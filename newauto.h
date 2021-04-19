#ifndef NEWAUTO_H
#define NEWAUTO_H

#include <QDialog>
#include "carsdatabase.h"


namespace Ui {
class NewAuto;
}

class NewAuto : public QDialog
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

private:
    Ui::NewAuto *ui;
    CarsDatabase MyData;
    void FillComboMarki();
    void FillComboModeli(int MarkaIndex);
    bool CheckSelected(QString SelectedString);
    void ActivateField(NewAuto::NewAutoFields Field);
    void DeActivateField(NewAuto::NewAutoFields Field);
    bool CheckRecordInformation();
    bool CheckRecordObligatory();
    QString m_strSelectedCarReg;
public:
    explicit NewAuto(QWidget *parent = 0);
    ~NewAuto();
    void ClearAllFields();
    QString GetNewCarReg(){ return m_strSelectedCarReg;}

    bool AddCarInfo(QString RegNumber, QString AutoMarka = "None", QString AutoModel = "None", QString AutoYear = "None"
            , QString AutoFuel = "None", QString AutoVIN = "None", QString AutoType = "None");

    bool AutoExsist(QString RegNum);

signals:
    void CloseNewAutoForm();

private slots:
    void on_Button_CancelNewAuto_clicked();
    void CenterForm();
    void OpenClearWindow();
    void on_Button_AddNewAuto_clicked();
    void on_Combo_NewAuto_Marka_currentIndexChanged(int index);
    void on_Combo_NewAuto_Model_currentIndexChanged(int index);
    void on_LText_NewAutoRegNumber_editingFinished();
    void on_LText_NewAutoVIN_editingFinished();
};

#endif // NEWAUTO_H
