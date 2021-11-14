#include "removeclient.h"
#include "ui_removeclient.h"
#include <QtWidgets>
#include <QKeyEvent>

RemoveClient::RemoveClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveClient)
{
    ui->setupUi(this);
    CenterForm();
    ui->m_ComboBoxClients->setMaxVisibleItems(10);
    ui->m_ComboBoxClients->setStyleSheet("combobox-popup: 0;");
}

RemoveClient::~RemoveClient()
{
    delete ui;
}

void RemoveClient::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
            on_Button_Back_clicked();
    }
    else{
            QDialog::keyPressEvent(event);
    }
}

void RemoveClient::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-static_cast<int>(width()*0.5), center.y()-static_cast<int>(height()*0.5) );
}

void RemoveClient::on_Button_Back_clicked()
{
    hide();
    emit CloseRemoveClientPage();
}

void RemoveClient::OpenRemoveClientPage()
{
    qDebug() << "RemoveClient::OpenRemoveClientPage() ";
    FillClientsNameCombo();
    show();
}

void RemoveClient::FillClientsNameCombo()
{
    MyData.OpenConnection("Clients.sqlite");

    QSqlQueryModel * ClientsNameComboModel = new QSqlQueryModel();

    QSqlQuery ShowClientsQry(MyData.CarsDB);
    ShowClientsQry.prepare("SELECT ClientName FROM Clients_Table");

    if(! ShowClientsQry.exec()){
        qDebug() << "ShowClientsQry.Exec() SELECT ClientName FROM Clients_Table fail "<< ShowClientsQry.lastError().text();
    }

    ClientsNameComboModel->setQuery(ShowClientsQry);
    ui->m_ComboBoxClients->setModel(ClientsNameComboModel);


    MyData.CloseConnection();
}


void RemoveClient::on_Button_DeleteClient_clicked()
{
    //1......... Get Klient name from Combo
    QString KlientName = ui->m_ComboBoxClients->currentText();
    QString KlientID = "";
    std::vector<QString> KlientCarsRegNumbers;

    // Get Klient's ID - we are going to use it to delete all klient's cars
    MyData.OpenConnection("Clients.sqlite");

    QSqlQuery ClientData(MyData.CarsDB);
    ClientData.prepare("SELECT * FROM Clients_Table WHERE ClientName='"+KlientName+"' ");

    if(!ClientData.exec()){
        qDebug() << "SelectClientQry.Exec() SELECT Client PR_ID Fail "<< ClientData.lastError().text();
    }else {
         if (ClientData.next()) {
                KlientID = ClientData.value(0).toString();
         }else {
             qDebug() << "Sometring wrong with this Klient - No ID found !!!  ";
         }
    }

    ClientData.prepare("DELETE FROM Clients_Table WHERE ClientName='"+KlientName+"' ");
    if(!ClientData.exec()){
        qDebug() << "DELETE FROM Clients_Table FAIL ";
    }
    MyData.CloseConnection();


    //2......... Get Klient cars and delete them
    MyData.OpenConnection("Automobiles.sqlite");
    QSqlQuery ClientAutoData(MyData.CarsDB);
    ClientAutoData.prepare("SELECT * FROM Automobiles_Table WHERE CLIENT_ID='"+KlientID+"' ");

    if(!ClientAutoData.exec()){
        qDebug() << "SelectClientQry.Exec() SELECT auto from CLIENT_ID Fail "<< ClientAutoData.lastError().text();
    }else {
         if (ClientAutoData.next()) {
             // Record all client autos
              KlientCarsRegNumbers.push_back(ClientAutoData.value(2).toString());
         }
    }

    for(unsigned int i=0; i < KlientCarsRegNumbers.size();   i++){
        ClientAutoData.prepare("DELETE FROM Automobiles_Table WHERE Auto_RegNumber='"+KlientCarsRegNumbers.at(i)+"' ");
        if(!ClientAutoData.exec()){
            qDebug() << "DELETE FROM Clients_Table FAIL ";
        }
    }
    MyData.CloseConnection();

    //3......... Delete all klient cars repair records
    MyData.OpenConnection("Repairs.sqlite");
    QSqlQuery ClientAutoRepairData(MyData.CarsDB);
    for(unsigned int i=0; i < KlientCarsRegNumbers.size();   i++){
        ClientAutoRepairData.prepare("DELETE FROM Repair_Table WHERE RepairCarRegNumber='"+KlientCarsRegNumbers.at(i)+"' ");
        if(!ClientAutoRepairData.exec()){
            qDebug() << "DELETE FROM Repair_Table FAIL ";
        }else {
            qDebug() << "Delete Car Done ";
        }
    }
    MyData.CloseConnection();


    //3......... Update Combo
    MyData.CloseConnection();
    FillClientsNameCombo();
}
