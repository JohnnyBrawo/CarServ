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

private:
    Ui::RemoveChangeAuto *ui;

    void FillPage();
    void SetUnactiveFields();
    void ClearAllFields();
    QString m_SelectedRegNumber;

signals:
    void CloseDeletePage();
    void CloseChangePage();

private slots:
     void OpenClearEditWindow();
     void OpenClearDeleteWindow();
     void on_Button_ChangeBack_clicked();

     void on_Combo_DelChangeAutoRegs_currentIndexChanged(const QString &arg1);
     void on_Button_RecordChange_clicked();

     //Edit handler
//     void HandleNewText(const QString &);

};

#endif // REMOVECHANGEAUTO_H
