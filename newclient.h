#ifndef NEWCLIENT_H
#define NEWCLIENT_H

#include <QDialog>
#include "findauto.h"

namespace Ui {
class NewClient;
}

class NewClient : public QDialog
{
    Q_OBJECT

public:
    explicit NewClient(QWidget *parent = 0);
    ~NewClient();

private slots:
    void on_Button_CancelAdd_clicked();
    void RestoreForm();

    void on_Button_AddClientAuto_clicked();

private:
    Ui::NewClient *ui;
    FindAuto    *m_FindAuto;
    void CenterForm();
     void ClearAllFields();

signals:
    void CloseNewClientForm();
};

#endif // NEWCLIENT_H
