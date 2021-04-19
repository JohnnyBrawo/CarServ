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
    FillClientsNameCombo();
    show();
}

void RemoveClient::FillClientsNameCombo()
{
    qDebug() << "RemoveClient::FillClientsNameCombo()   ";

    MyData.OpenConnection("Clients.sqlite");

    QSqlQueryModel * ClientsNameComboModel = new QSqlQueryModel();

    QSqlQuery ShowClientsQry(MyData.CarsDB);
    ShowClientsQry.prepare("SELECT ClientName FROM Clients_Table");

    if(! ShowClientsQry.exec()){
        qDebug() << "ShowClientsQry.Exec() SELECT ClientName FROM Clients_Table fail "<< ShowClientsQry.lastError().text();
    }

    ClientsNameComboModel->setQuery(ShowClientsQry);
    ui->m_ComboBoxClients->setModel(ClientsNameComboModel);
    ui->m_ComboBoxClients->setMaxVisibleItems(10);
    ui->m_ComboBoxClients->setStyleSheet("combobox-popup: 0;");

    MyData.CloseConnection();
}



