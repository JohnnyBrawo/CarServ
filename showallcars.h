#ifndef SHOWALLCARS_H
#define SHOWALLCARS_H

#include <QDialog>
#include "carsdatabase.h"
#include <QVector>
#include "printformat.h"

namespace Ui {
class ShowAllcars;
}

class ShowAllcars : public QDialog
{
    Q_OBJECT

private:
    Ui::ShowAllcars *ui;
    PrintFormat *m_Print;

    void ClearAllFields();
    void FillClientsNameCombo();
    void FillRegNumbersCombo();
    void FillAutosCombo();
    void DeactivateAllFields();
    void FillAutoData();
    void FillRepairsList();
    bool CalculateRepairIndex(bool NextRepair = true);
    void ShowRepairData(bool NextRepair = false);
    QVector<QString> strRepairVector;
    enum SearchChoise {
        eNone,
        eAutos,
        eClients,
        eRegNumber,
        eDate
    };

    SearchChoise m_uiSearchChoice;
    QString         m_ComboClientName;
    QString         m_ClientDB_ID;
    QString         m_ComboRegNumber;
    int    m_uiRepairIndex;
    double m_dTotalPrice = 0.0;
    bool   m_bTaxesIncluded = false;
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
//    void on_RButton_Autos_clicked();
    void on_RButton_SearchDate_clicked();
    void on_Button_Search_clicked();
    void on_Combo_Search_Klient_currentTextChanged(const QString &arg1);
    void on_Button_NextRepair_clicked();
    void on_Button_PrevRepair_clicked();
    void on_Button_PRINT_clicked();
    QString RepairText();
};

#endif // SHOWALLCARS_H
