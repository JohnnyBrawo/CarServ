﻿#ifndef NEWCLIENT_H
#define NEWCLIENT_H

#include <QDialog>
#include "newauto.h"
#include "removechangeauto.h"
#include "carsdatabase.h"

namespace Ui {
class NewClient;
}

class NewClient : public QDialog
{
    Q_OBJECT

private:
    Ui::NewClient *ui;
    RemoveChangeAuto    *m_AttachAuto;
    NewAuto             *m_NewAuto;
    CarsDatabase MyData;

    QString            m_strClientID;
    QString             m_strLastClientName;
    QString             m_strClientCarReg;

    bool m_bRecordPermission;
    bool m_bClientFormEditMode;

    bool CheckRecordObligatory();
    bool CheckField(QString SelectedString);

    void CenterForm();
    void ClearAllFields();
    void SetNewClientDesignMode();
    void SetEditDesignMode();
    void FillClientsNameCombo();
    void keyPressEvent(QKeyEvent *event);

public:
    explicit NewClient(QWidget *parent = 0);
    ~NewClient();
    QString GetClientName(){return m_strLastClientName;}
    QString GetClientID(){return m_strClientID;}
    void SetNewRepairRegNumber(QString RegNum){m_strClientCarReg = RegNum;}

    void RecordCarToClient();
    bool ClientExsist(QString ClientName, QString ClientPhone);
    bool AddClentInfo(QString ClientName ,QString ClientPhone , QString ClientFirm = "None", QString ClientCity  = "None",  QString ClientAddress = "None");
signals:
    void CloseNewClientForm();
    void ButtonEditHit(QString CLientName,QString ClientID);
    void AddExistingAutoHit(QString CLientName);

private slots:
    void OpenNewClientForm();
    void OpenEditClientForm();

    void on_Button_CancelAdd_clicked();
    void RestoreFormAttachAuto();
    void RestoreFormNewAuto();
    void on_Button_AddExistAuto_clicked();
    void on_Button_AddClientAutoNew_clicked();

    void on_Button_Add_Client_clicked();
    void on_LText_ClientName_textChanged(const QString &arg1);
    void on_Combo_Clients_currentIndexChanged(const QString &arg1);
    void on_Button_AddClientAutoEdit_clicked();
    void on_LText_ClientPhone_editingFinished();
};

#endif // NEWCLIENT_H
