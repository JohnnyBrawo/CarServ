#include "carsform.h"
#include "ui_carsform.h"
#include "qapplication.h"
#include "qdesktopwidget.h"


CarsForm::CarsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CarsForm)
{
    ui->setupUi(this);
    setWindowTitle("Euro Kriss - AUTOS ");
    CenterForm();
}

CarsForm::~CarsForm()
{
    delete ui;
}


void CarsForm::RestoreView()
{
    show();
}

void CarsForm::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-width()*0.5, center.y()-height()*0.5);
}

void CarsForm::OpenClearWindow()
{
    show();
}

void CarsForm::on_Button_Back_clicked()
{
    hide();
    emit CloseNewAutoForm();

}

void CarsForm::on_Button_AddNewAuto_clicked()
{
    hide();
}


void CarsForm::on_Button_ShowAllAutos_clicked()
{
    hide();
}

void CarsForm::on_Button_EditAuto_clicked()
{
    hide();
}
