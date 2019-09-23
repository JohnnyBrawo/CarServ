#ifndef SHOWALLCARS_H
#define SHOWALLCARS_H

#include <QDialog>

namespace Ui {
class ShowAllcars;
}

class ShowAllcars : public QDialog
{
    Q_OBJECT

private:
    Ui::ShowAllcars *ui;
    void ClearAllFields();
    void FillClientsNameCombo();
    void FillRegNumbersCombo();
    void FillAutosCombo();
    void DeactivateAllFields();

public:
    explicit ShowAllcars(QWidget *parent = nullptr);
    ~ShowAllcars();

signals:
    void CloseShowAllAutoForm();

private slots:
    void OpenClearWindow();
    void on_Button_Back_clicked();

    void on_RButton_SearchRegNumbers_clicked();
    void on_RButton_SearchClients_clicked();
    void on_RButton_SearchAutos_clicked();
    void on_RButton_SearchDate_clicked();
};

#endif // SHOWALLCARS_H
