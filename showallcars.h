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

public:
    explicit ShowAllcars(QWidget *parent = 0);
    ~ShowAllcars();

signals:
    void CloseShowAllAutoForm();

private slots:
    void OpenClearWindow();
    void on_Button_Back_clicked();

};

#endif // SHOWALLCARS_H
