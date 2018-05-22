#include "newauto.h"
#include "ui_newauto.h"
#include "qapplication.h"
#include "qdesktopwidget.h"

NewAuto::NewAuto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAuto)
{
    ui->setupUi(this);
    CenterForm();
    setWindowTitle("New Auto");
}

NewAuto::~NewAuto()
{
    delete ui;
}


void NewAuto::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-width()*0.5, center.y()-height()*0.5);
}


void NewAuto::on_Button_CancelNewAuto_clicked()
{
    emit CloseNewAutoForm();
    this->hide();
}


void NewAuto::OpenClearWindow()
{
     ClearAllFields();
     this->show();
}

void NewAuto::ClearAllFields()
{
    ui->Combo_NewAuto_Fuel->setCurrentIndex(0);
    ui->Combo_NewAuto_Marka->setCurrentIndex(0);
    ui->Combo_NewAuto_Model->setCurrentIndex(0);
    ui->Combo_NewAuto_Year->setCurrentIndex(0);
    ui->LText_NewAutoRegNumber->clear();
    ui->LText_NewAutoVIN->clear();
}
