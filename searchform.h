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

public:
    explicit SearchForm(QWidget *parent = 0);
    ~SearchForm();

signals:
    void CloseSearchForm();

private slots:
    void on_Button_Search_Back_clicked();
    void OpenClearWindow();


};

#endif // SEARCHFORM_H
