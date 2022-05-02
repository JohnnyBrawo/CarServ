#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include <QDialog>
#include "carsdatabase.h"

namespace Ui {
class SearchForm;
}

class SearchForm : public QDialog
{
    Q_OBJECT

private:
    Ui::SearchForm *ui;
    CarsDatabase MyData;

    void CenterForm();
    void FillClientsNameCombo();
    void FillRegNumbersCombo();
    void FillAutosCombo();
    void DeactivateAllFields();
    void keyPressEvent(QKeyEvent *event);
public:
    explicit SearchForm(QWidget *parent = nullptr);
    ~SearchForm();

signals:
    void CloseSearchForm();

private slots:
    void on_Button_Search_Back_clicked();
    void OpenClearWindow();

    void on_RButton_SearchAutos_clicked();
    void on_RButton_SearchClients_clicked();
    void on_RButton_SearchRegNumbers_clicked();
    void on_RButton_SearchDate_clicked();
};

#endif // SEARCHFORM_H
