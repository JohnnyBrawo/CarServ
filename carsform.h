#ifndef CARSFORM_H
#define CARSFORM_H

#include <QDialog>
#include "newauto.h"
#include "showallcars.h"
#include "removechangeauto.h"

namespace Ui {
class CarsForm;
}

class CarsForm : public QDialog
{
    Q_OBJECT

public:
    explicit CarsForm(QWidget *parent = 0);
    ~CarsForm();

private:
    Ui::CarsForm *ui;

    NewAuto *m_NewAuto;
    ShowAllcars *m_ShowAllAutos;
    RemoveChangeAuto *m_DelEdtiAuto;

    void CenterForm();

signals:
    void CloseNewAutoForm();

private slots:
    void OpenClearWindow();
    void on_Button_Back_clicked();
    void RestoreView();
    void on_Button_AddNewAuto_clicked();
    void on_Button_ShowAllAutos_clicked();
    void on_Button_EditAuto_clicked();
};

#endif // CARSFORM_H
