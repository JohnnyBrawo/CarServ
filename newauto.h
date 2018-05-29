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
        eFuel,
        eRegNumber,
        eAutoVin,
        eFieldsNum
    };

public:
    explicit NewAuto(QWidget *parent = 0);
    ~NewAuto();
    void ClearAllFields();

private:
    Ui::NewAuto *ui;
    void FillCombos();
    void FillComboMarki();
    void FillComboModeli();
    bool CheckSelected(QString SelectedString);
    void ActivateField(NewAuto::NewAutoFields Field);
    void DeActivateField(NewAuto::NewAutoFields Field);

signals:
    void CloseNewAutoForm();

private slots:
    void on_Button_CancelNewAuto_clicked();
    void CenterForm();
    void OpenClearWindow();
    void on_Button_AddNewAuto_clicked();
    void on_Combo_NewAuto_Marka_currentIndexChanged();
    void on_Combo_NewAuto_Model_activated();
};

#endif // NEWAUTO_H
