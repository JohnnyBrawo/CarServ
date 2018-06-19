#include "clientsform.h"
#include "ui_clientsform.h"

ClientsForm::ClientsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientsForm),
    m_NewClient(new NewClient()),
    m_RemoveClient(new RemoveClient())
{
    ui->setupUi(this);
    // Connect all new windows
    QObject::connect(m_NewClient, SIGNAL(CloseNewClientForm()), this, SLOT(RestoreClientsForm()));
    QObject::connect(m_RemoveClient, SIGNAL(CloseRemoveClientPage()), this, SLOT(RestoreClientsForm()));

    QObject::connect(ui->Button_NewClient, SIGNAL(clicked()), m_NewClient, SLOT(OpenClearWindow()));
    QObject::connect(ui->Button_RemoveClient, SIGNAL(clicked()), m_RemoveClient, SLOT(OpenRemoveClientPage()));

}

ClientsForm::~ClientsForm()
{
    delete m_NewClient;
//    delete m_RemoveClient;
    delete ui;
}

void ClientsForm::on_Button_NewClient_clicked()
{
    hide();
}

void ClientsForm::on_Button_RemoveClient_clicked()
{
    hide();
}

void ClientsForm::OpenClearWindow()
{
    show();
}


void ClientsForm::RestoreClientsForm()
{
    this->show();
}


void ClientsForm::on_pushButton_clicked()
{
    hide();
    emit CloseClientsPage();
}


void ClientsForm::on_Button_EditClient_clicked()
{

}