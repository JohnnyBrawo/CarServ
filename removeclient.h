#ifndef REMOVECLIENT_H
#define REMOVECLIENT_H

#include <QDialog>

namespace Ui {
class RemoveClient;
}

class RemoveClient : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveClient(QWidget *parent = 0);
    ~RemoveClient();

private slots:
    void on_Button_Back_clicked();
    void OpenRemoveClientPage();

signals:
    void CloseRemoveClientPage();

private:
    Ui::RemoveClient *ui;
};

#endif // REMOVECLIENT_H
