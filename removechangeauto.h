#ifndef REMOVECHANGEAUTO_H
#define REMOVECHANGEAUTO_H

#include <QDialog>

namespace Ui {
class RemoveChangeAuto;
}

class RemoveChangeAuto : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveChangeAuto(QWidget *parent = 0);
    ~RemoveChangeAuto();
    QString GetSelectedCarID() { return m_strAutoID;}

private:
    Ui::RemoveChangeAuto *ui;

    void FillPage();
    void FillRegCombo();
    void FillClientNameCombo();

    void SetUnactiveFields();
    void ClearAllFields();
    void ShowAllFieldsText();

    QString m_SelectedRegNumber;
    QString m_SelectedClientName;
    QString  m_strAutoID;

    bool m_bRefillTable;

signals:
    void CloseDeletePage();
//    void CloseAttachPage();

private slots:
     void OpenClearEditWindow();
     void OpenClearWindow();
     void on_Button_Back_clicked();

     void on_Combo_DelChangeAutoRegs_currentIndexChanged(const QString &arg1);
     void on_Button_Record_clicked();

     //Edit handler
//     void HandleNewText(const QString &);

     void on_Button_DeleteAuto_clicked();
     void on_Button_Add_clicked();
     void on_Combo_DelChangeClientName_currentIndexChanged(const QString &arg1);
};

#endif // REMOVECHANGEAUTO_H
