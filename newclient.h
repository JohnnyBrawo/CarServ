#ifndef NEWCLIENT_H
#define NEWCLIENT_H

#include <QDialog>

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

private:
    Ui::NewClient *ui;
    void CenterForm();

signals:
    void CloseNewClientForm();
};

#endif // NEWCLIENT_H
