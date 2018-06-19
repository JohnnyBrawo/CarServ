#ifndef CLIENTSFORM_H
#define CLIENTSFORM_H

#include <QDialog>
#include "newclient.h"
#include "removeclient.h"

namespace Ui {
class ClientsForm;
}

class ClientsForm : public QDialog
{
    Q_OBJECT

public:
    explicit ClientsForm(QWidget *parent = 0);
    ~ClientsForm();

private slots:
    void on_Button_NewClient_clicked();
     void OpenClearWindow();
     void on_pushButton_clicked();
     void on_Button_RemoveClient_clicked();

     void RestoreClientsForm();

     void on_Button_EditClient_clicked();

signals:
    void CloseClientsPage();

private:
    Ui::ClientsForm *ui;
    NewClient       *m_NewClient;
    RemoveClient    *m_RemoveClient;
};

#endif // CLIENTSFORM_H
