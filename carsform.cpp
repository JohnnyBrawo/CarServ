#include "carsform.h"
#include "ui_carsform.h"
#include "qapplication.h"
#include "qdesktopwidget.h"


CarsForm::CarsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CarsForm)
{
    ui->setupUi(this);
    CenterForm();
}

CarsForm::~CarsForm()
{
    delete ui;
}

void CarsForm::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-width()*0.5, center.y()-height()*0.5);
}
