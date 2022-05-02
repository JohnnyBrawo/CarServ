#ifndef REMOVECHANGEAUTO_H
#define REMOVECHANGEAUTO_H

#include <QDialog>
#include "carsdatabase.h"

namespace Ui {
class RemoveChangeAuto;
}

class RemoveChangeAuto : public QDialog
{
    Q_OBJECT

private:
    Ui::RemoveChangeAuto *ui;
    enum States{
        eNormalMode,
        eEditMode,
        eAddExistingAutoMode,
        eEditDelAuto
    };

    States m_State;
    CarsDatabase MyData;

    bool FillPage();
    void FillAutoData();
    bool FillRegCombo();
    void FillClientNameCombo();

    void SetUnactiveFields();
    void ClearAllFields();
    void ReActivateAllFields();
    void UpdateFlags();
    bool CheckField(QString SelectedString);
    void CenterForm();
    void FillComboMarki();
    void FillComboModeli(int MarkaIdx);
    void ActivateAutoCombos(bool DeactiavateAll = false);
    void SetFieldsClientWithNoAuto();

    QString m_SelectedRegNumber;
    QString m_SelectedClientID;
    QString m_SentClientName;
    QString m_SentClientID;
    QString m_strAutoReg;

    QString m_strAutoMarka;
    QString m_strAutoModel;


    bool m_bInitialize;
    bool m_bComboClientsHit;
    bool m_bComboRegsHit;
    bool m_bEditFromClients;
//    bool m_bCancelAllActions = false;
    void   keyPressEvent(QKeyEvent *event);

public:
    explicit RemoveChangeAuto(QWidget *parent = 0);
    ~RemoveChangeAuto();
    QString GetSelectedCarReg() { return m_strAutoReg;}

//    bool IsActionsCanceled() { return m_bCancelAllActions; }

signals:
    void CloseDeletePage();

private slots:
    void OpenClearEditWindow();
    void EditClientAuto(QString ClientName,QString ClientEditID);
    void OpenExistingAutosWindow(QString ClientName);
    void OpenClearWindow();
    void on_Button_Back_clicked();

    void on_Combo_DelChangeAutoRegs_currentIndexChanged(const QString &arg1);
    void on_Button_Record_clicked();

    void on_Button_DeleteAuto_clicked();
    void on_Button_Add_clicked();
    void on_m_ComboMarka_currentIndexChanged(int index);
    void on_m_ComboMarka_currentTextChanged(const QString &arg1);
    void on_Combo_ClientName_currentIndexChanged(int index);
};

#endif // REMOVECHANGEAUTO_H
