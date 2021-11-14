#ifndef PRINTFORMAT_H
#define PRINTFORMAT_H

#include <QDialog>
#include <QVector>
#include "carsdatabase.h"

namespace Ui {
class PrintFormat;
}

class PrintFormat : public QDialog
{
    Q_OBJECT

public:
    explicit PrintFormat(QWidget *parent = nullptr);
    ~PrintFormat();
    void SetRepairsText (QString AllRepairs){ m_strRepairs = AllRepairs;}
    void SetRepairsPagesText(QVector<QString> AllPagesTexts){
        strRepairTextOnPage = AllPagesTexts;
        PagesToShow = AllPagesTexts.size();
    }

    void SetRegNum (QString RegNumber){ m_strClientRegNumber = RegNumber;}
    void SetClientID (QString ClientBD_ID){ m_strClient_ID = ClientBD_ID;}
    void SetClientName(QString  ClientName){ m_strClient_Name = ClientName;}
    void SetRepairCost(double TotalCost, bool TaxesIncluded) { m_TotalRepairCost = TotalCost;
                                                               m_bTaxesIncluded = TaxesIncluded; }
    bool GetPrintStatus() { return m_bPrintingDone; }
    void ResetPrintStatus() { m_bPrintingDone = false; }

    void   keyPressEvent(QKeyEvent *event);
private slots:
    void on_B_PrintCancel_clicked();

private:
    Ui::PrintFormat *ui;

    bool m_bPrintingDone = false;
    CarsDatabase MyData;

    QString m_strRepairs="";
    QString m_strClientRegNumber="";
    QString m_strClient_ID="";
    QString m_strClient_Name="";
    QString m_strRepairNumber="";
    QString m_strRepairDescr="";
    QString m_strRepairCnt="";
    QString m_strRepairSPrice="";
    QString m_strRepairTotal="";
    double m_TotalRepairCost = 0.0;
    bool   m_bTaxesIncluded = false;
    bool   m_bMorePagesWaiting = false;
    unsigned short PagesToShow = 0;
    unsigned short CurrentPageToShow = 0;
    QList<double> m_list;
    QVector<QString> strRepairTextOnPage;
    void CenterForm();
    void FillClientData();
    void FillAutoData();
    void ReadRepairs();
    void FillRepairData(int RepairNum, bool IncludeTaxes);
    void HideAllDDSChecks();
    void EnableDDSCheck(unsigned short CheckIndex);
    QString GetWorkingPath();

    void SetPagesPrintView();
    void SetStandardPrintView();

signals:
    void ClosePrintForm();

private slots:
    void OpenPrintForm();
    void on_B_PrintDocument_clicked();
};

#endif // PRINTFORMAT_H
