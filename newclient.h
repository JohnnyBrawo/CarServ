#ifndef NEWCLIENT_H
#define NEWCLIENT_H

#include <QDialog>
#include "findauto.h"
#include "newauto.h"

namespace Ui {
class NewClient;
}

class NewClient : public QDialog
{
    Q_OBJECT

private:
    Ui::NewClient *ui;
    FindAuto    *m_FindAuto;
    NewAuto     *m_NewAuto;
    void CenterForm();
     void ClearAllFields();

public:
    explicit NewClient(QWidget *parent = 0);
    ~NewClient();

signals:
    void CloseNewClientForm();

private slots:
    void on_Button_CancelAdd_clicked();
    void RestoreForm();
    void on_Button_AddClientAuto_clicked();
    void on_Button_AddClientAutoNew_clicked();
    void OpenClearWindow();

    void on_Button_Add_Client_clicked();
};

#endif // NEWCLIENT_H
