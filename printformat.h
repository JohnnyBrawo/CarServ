﻿#ifndef PRINTFORMAT_H
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
    void SetRegNum (QString RegNumber){ m_strClientRegNumber = RegNumber;}
    void SetClientID (QString ClientBD_ID){ m_strClient_ID = ClientBD_ID;}
    void SetClientName(QString  ClientName){ m_strClient_Name = ClientName;}
private slots:
    void on_B_PrintCancel_clicked();

private:
    Ui::PrintFormat *ui;

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
    QList<int> m_list;
    void FillClientData();
    void FillAutoData();
    void ReadRepairs();
    void FillRepairData(int RepairNum);

signals:
    void ClosePrintForm();

private slots:
    void OpenPrintForm();

};

#endif // PRINTFORMAT_H
