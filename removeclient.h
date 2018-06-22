#ifndef REMOVECLIENT_H
#define REMOVECLIENT_H

#include <QDialog>

namespace Ui {
class RemoveClient;
}

class RemoveClient : public QDialog
{
    Q_OBJECT

private:
    Ui::RemoveClient *ui;

public:
    explicit RemoveClient(QWidget *parent = 0);
    ~RemoveClient();

private slots:
    void on_Button_Back_clicked();
    void OpenRemoveClientPage();

signals:
    void CloseRemoveClientPage();

};

#endif // REMOVECLIENT_H
