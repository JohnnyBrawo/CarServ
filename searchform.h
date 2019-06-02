#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include <QDialog>

namespace Ui {
class SearchForm;
}

class SearchForm : public QDialog
{
    Q_OBJECT

private:
    Ui::SearchForm *ui;
    void CenterForm();
    void FillClientsNameCombo();
    void FillRegNumbersCombo();
    void FillAutosCombo();
    void DeactivateAllFields();
public:
    explicit SearchForm(QWidget *parent = nullptr);
    ~SearchForm();

signals:
    void CloseSearchForm();

private slots:
    void on_Button_Search_Back_clicked();
    void OpenClearWindow();

    void on_Combo_Search_Klient_currentTextChanged(const QString &arg1);
    void on_RButton_SearchAutos_clicked();
    void on_RButton_SearchClients_clicked();
    void on_RButton_SearchRegNumbers_clicked();
    void on_RButton_SearchDate_clicked();
};

#endif // SEARCHFORM_H
