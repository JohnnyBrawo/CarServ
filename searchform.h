#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include <QDialog>

namespace Ui {
class SearchForm;
}

class SearchForm : public QDialog
{
    Q_OBJECT

public:
    explicit SearchForm(QWidget *parent = 0);
    ~SearchForm();

private slots:
    void on_Button_Search_Back_clicked();

private:
    Ui::SearchForm *ui;

signals:
    void CloseSearchForm();
};

#endif // SEARCHFORM_H
