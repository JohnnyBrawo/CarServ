#ifndef NEWCLIENT_H
#define NEWCLIENT_H

#include <QDialog>
#include "newauto.h"
#include "removechangeauto.h"

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
    QString            m_strClientID;
    QString             m_strLastClientName;

    void CenterForm();
    void ClearAllFields();
    void RecordCarToClient();
    bool CheckRecordObligatory();
    bool m_bRecordPermission;
    bool m_bClientFormEditMode;
    void SetNewClientDesignMode();
    void SetEditDesignMode();
    void FillClientsNameCombo();

public:
    explicit NewClient(QWidget *parent = 0);
    ~NewClient();
    QString GetClientName(){return m_strLastClientName;}

signals:
    void CloseNewClientForm();
    void ButtonEditHit(QString CLientName);

private slots:
    void OpenNewClientForm();
    void OpenEditClientForm();

    void on_Button_CancelAdd_clicked();
    void RestoreFormAttachAuto();
    void RestoreFormNewAuto();
    void on_Button_AddClientAuto_clicked();
    void on_Button_AddClientAutoNew_clicked();

    void on_Button_Add_Client_clicked();
    void on_LText_ClientName_textChanged(const QString &arg1);
    void on_Combo_Clients_currentIndexChanged(const QString &arg1);
    void on_Button_AddClientAutoEdit_clicked();
};

#endif // NEWCLIENT_H
