#ifndef NEWAUTO_H
#define NEWAUTO_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class NewAuto;
}

class NewAuto : public QDialog
{
    Q_OBJECT

public:
    explicit NewAuto(QWidget *parent = 0);
    ~NewAuto();
    void ClearAllFields();

private:
    Ui::NewAuto *ui;

signals:
    void CloseNewAutoForm();

private slots:
    void on_Button_CancelNewAuto_clicked();
    void CenterForm();
    void OpenClearWindow();
    void on_Button_AddNewAuto_clicked();
};

#endif // NEWAUTO_H
