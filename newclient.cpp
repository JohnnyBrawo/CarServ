#include "newclient.h"
#include "ui_newclient.h"
#include "qapplication.h"
#include "qdesktopwidget.h"

NewClient::NewClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewClient)
{
    ui->setupUi(this);
    CenterForm();
}

NewClient::~NewClient()
{
    delete ui;
}


void NewClient::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-width()*0.5, center.y()-height()*0.5);
}


void NewClient::on_Button_CancelAdd_clicked()
{
    emit CloseNewClientForm();
    this->hide();
}
