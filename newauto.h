#ifndef NEWAUTO_H
#define NEWAUTO_H

#include <QDialog>


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

    void FillComboMarki();
    void FillComboModeli(int MarkaIndex);
    bool CheckSelected(QString SelectedString);
    void ActivateField(NewAuto::NewAutoFields Field);
    void DeActivateField(NewAuto::NewAutoFields Field);
    bool CheckRecordInformation();
    bool CheckRecordObligatory();
    QString m_strSelectedCarID;

public:
    explicit NewAuto(QWidget *parent = 0);
    ~NewAuto();
    void ClearAllFields();
    QString GetNewCarID(){ return m_strSelectedCarID;}

signals:
    void CloseNewAutoForm();

private slots:
    void on_Button_CancelNewAuto_clicked();
    void CenterForm();
    void OpenClearWindow();
    void on_Button_AddNewAuto_clicked();
    void on_Combo_NewAuto_Marka_currentIndexChanged(int index);
    void on_Combo_NewAuto_Model_currentIndexChanged(int index);
};

#endif // NEWAUTO_H
