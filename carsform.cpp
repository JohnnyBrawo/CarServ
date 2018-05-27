#include "carsform.h"
#include "ui_carsform.h"

CarsForm::CarsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CarsForm)
{
    ui->setupUi(this);
}

CarsForm::~CarsForm()
{
    delete ui;
}
