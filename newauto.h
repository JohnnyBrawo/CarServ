#ifndef NEWAUTO_H
#define NEWAUTO_H

#include <QDialog>

namespace Ui {
class NewAuto;
}

class NewAuto : public QDialog
{
    Q_OBJECT

public:
    explicit NewAuto(QWidget *parent = 0);
    ~NewAuto();

private:
    Ui::NewAuto *ui;

signals:
    void CloseNewAutoForm();

private slots:
    void on_Button_CancelNewAuto_clicked();
//    void ShowNewAutoForm();
    void CenterForm();
};

#endif // NEWAUTO_H
