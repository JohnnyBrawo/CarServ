#include "removeclient.h"
#include "ui_removeclient.h"

RemoveClient::RemoveClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveClient)
{
    ui->setupUi(this);
}

RemoveClient::~RemoveClient()
{
    delete ui;
}

void RemoveClient::on_Button_Back_clicked()
{
    hide();
    emit CloseRemoveClientPage();
}

void RemoveClient::OpenRemoveClientPage()
{
    show();
}



