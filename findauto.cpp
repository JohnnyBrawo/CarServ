#include "findauto.h"
#include "ui_findauto.h"
#include "qapplication.h"
#include "qdesktopwidget.h"

FindAuto::FindAuto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindAuto)
{
    ui->setupUi(this);
    CenterForm();
    setWindowTitle("Find Auto");
    ui->Text_AutoInformation->setDisabled(true);
}

FindAuto::~FindAuto()
{
    delete ui;
}

void FindAuto::on_Button_FindAutoDone_clicked()
{
    hide();
    emit CloseAddAutoForm();
}


void FindAuto::on_Button_FindAutoCancel_clicked()
{
    hide();
    emit CloseAddAutoForm();
}

void FindAuto::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-width()*0.5, center.y()-height()*0.5);
}
