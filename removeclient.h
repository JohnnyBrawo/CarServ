#ifndef REMOVECLIENT_H
#define REMOVECLIENT_H

#include <QDialog>
#include "carsdatabase.h"

namespace Ui {
class RemoveClient;
}

class RemoveClient : public QDialog
{
    Q_OBJECT

private:
    Ui::RemoveClient *ui;
    void FillClientsNameCombo();
    CarsDatabase MyData;

public:
    explicit RemoveClient(QWidget *parent = nullptr);
    ~RemoveClient();

private slots:
    void on_Button_Back_clicked();
    void OpenRemoveClientPage();

    void on_Button_DeleteClient_clicked();

signals:
    void CloseRemoveClientPage();

};

#endif // REMOVECLIENT_H
