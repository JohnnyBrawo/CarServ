#include "newclient.h"
#include "ui_newclient.h"

NewClient::NewClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewClient)
{
    ui->setupUi(this);
}

NewClient::~NewClient()
{
    delete ui;
}
