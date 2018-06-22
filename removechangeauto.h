#ifndef REMOVECHANGEAUTO_H
#define REMOVECHANGEAUTO_H

#include <QDialog>

namespace Ui {
class RemoveChangeAuto;
}

class RemoveChangeAuto : public QDialog
{
    Q_OBJECT

private:
    Ui::RemoveChangeAuto *ui;

    void FillPage();
    void FillRegCombo();
    void FillClientNameCombo();

    void SetUnactiveFields();
    void ClearAllFields();
    void ShowAllFieldsText();
    void UpdateFlags();
    bool CheckField(QString SelectedString);

    QString m_SelectedRegNumber;
    QString m_SelectedClientID;
    QString m_SentClientName;
    QString m_SentClientID;
    QString m_strAutoReg;

    bool m_bInitialize;
    bool m_bComboClientsHit;
    bool m_bComboRegsHit;
    bool m_bEditFromClients;

public:
    explicit RemoveChangeAuto(QWidget *parent = 0);
    ~RemoveChangeAuto();
    QString GetSelectedCarReg() { return m_strAutoReg;}

signals:
    void CloseDeletePage();

private slots:
    void OpenClearEditWindow();
    void OpenClientEditWindow(QString ClientName, QString ClientEditID);
    void OpenClearWindow();
    void on_Button_Back_clicked();

    void on_Combo_DelChangeAutoRegs_currentIndexChanged(const QString &arg1);
    void on_Button_Record_clicked();

    void on_Button_DeleteAuto_clicked();
    void on_Button_Add_clicked();
    void on_Combo_DelChangeClientName_currentIndexChanged(QString);
};

#endif // REMOVECHANGEAUTO_H
