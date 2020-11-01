#ifndef SHOWALLCARS_H
#define SHOWALLCARS_H

#include <QDialog>
#include "carsdatabase.h"

namespace Ui {
class ShowAllcars;
}

class ShowAllcars : public QDialog
{
    Q_OBJECT

private:
    Ui::ShowAllcars *ui;
    void ClearAllFields();
    void FillClientsNameCombo();
    void FillRegNumbersCombo();
    void FillAutosCombo();
    void DeactivateAllFields();
    void FillAutoData(QString CurrentClientID = "");
    void FillRepairsList(QString CarRegNumber = "");
    enum SearchChoise {
        eNone,
        eAutos,
        eClients,
        eRegNumber,
        eDate
    };

    SearchChoise m_uiSearchChoice;
    QString         m_ComboClientName;
    QString         m_ComboRegNumber;
    CarsDatabase MyData;
public:
    explicit ShowAllcars(QWidget *parent = nullptr);
    ~ShowAllcars();

signals:
    void CloseShowAllAutoForm();

private slots:
    void OpenClearWindow();
    void on_Button_Back_clicked();

    void on_RButton_SearchRegNumbers_clicked();
    void on_RButton_SearchClients_clicked();
    void on_RButton_SearchAutos_clicked();
    void on_RButton_SearchDate_clicked();
    void on_Button_Search_clicked();
    void on_Combo_Search_Klient_currentTextChanged(const QString &arg1);
    void on_RButton_SearchAutos_pressed();
};

#endif // SHOWALLCARS_H
