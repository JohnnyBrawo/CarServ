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
    int GetSelectedCarID() { return m_iAutoID;}

private:
    Ui::RemoveChangeAuto *ui;

    void FillPage();
    void SetUnactiveFields();
    void ClearAllFields();
    QString m_SelectedRegNumber;
    void ShowAllFieldsText();
    int  m_iAutoID;

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
};

#endif // REMOVECHANGEAUTO_H
