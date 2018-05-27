#ifndef CARSFORM_H
#define CARSFORM_H

#include <QDialog>

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
};

#endif // CARSFORM_H
