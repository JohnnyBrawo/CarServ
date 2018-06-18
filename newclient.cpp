#include "newclient.h"
#include "ui_newclient.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include "newauto.h"
#include "carsdatabase.h"
#include <QtWidgets>

NewClient::NewClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewClient),
    m_AttachAuto(new RemoveChangeAuto()),
    m_NewAuto(new NewAuto())
{
    ui->setupUi(this);
    setWindowTitle("New Client");
    CenterForm();
    m_strClientID = -1;
    m_strLastClientName.clear();
    m_bRecordPermission = false;
    ui->Button_Add_Client->setEnabled(false);

    QObject::connect(m_AttachAuto, SIGNAL(CloseDeletePage()), this, SLOT(RestoreFormAttachAuto()));
    QObject::connect(ui->Button_AddClientAuto, SIGNAL(clicked()), m_AttachAuto, SLOT(OpenClearWindow()));


    QObject::connect(m_NewAuto, SIGNAL(CloseNewAutoForm()), this, SLOT(RestoreFormNewAuto()));
    QObject::connect(ui->Button_AddClientAutoNew, SIGNAL(clicked()), m_NewAuto, SLOT(OpenClearWindow()));

    ui->Button_AddClientAuto->setEnabled(false);
    ui->Button_AddClientAutoNew->setEnabled(false);

//    ui->Button_AddClientAuto->setEnabled(false);

        // Да може да се добавя кола само при въведени определени полета !!
//    connect(ui->LText_DelChangeRegNumber, SIGNAL(textChanged(const QString &)), this, SLOT(HandleNewText(const QString &)));


}

NewClient::~NewClient()
{
    delete ui;
    delete m_AttachAuto;
    delete m_NewAuto;
}

void NewClient::ClearAllFields()
{
    ui->LText_ClientCity->clear();
    ui->LText_ClientPhone->clear();
    ui->LText_ClientFirm->clear();
    ui->LText_ClientName->clear();
    ui->PText_ClientAddress->document()->setPlainText("");
}

void NewClient::OpenClearWindow()
{
     ClearAllFields();
     this->show();
}


void NewClient::RestoreFormAttachAuto()
{
    this->show();
    CenterForm();
    qDebug() << "Selected Car ID is  : " << m_AttachAuto->GetSelectedCarID();
    if(m_AttachAuto->GetSelectedCarID() != "None")
    {
        m_bRecordPermission = true;
        ui->Button_Add_Client->setEnabled(true);
    }

}


void NewClient::RestoreFormNewAuto()
{
    this->show();
    CenterForm();
    qDebug() << "Selected Car ID is  : " << m_NewAuto->GetNewCarID();
    if(m_NewAuto->GetNewCarID() != "None")
    {
        m_bRecordPermission = true;
        ui->Button_Add_Client->setEnabled(true);
    }

}


void NewClient::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-width()*0.5, center.y()-height()*0.5);
}


void NewClient::RecordCarToClient()
{
    CarsDatabase MyData;
    MyData.OpenConnection("Automobiles.sqlite");

    QSqlQuery AddNewClient(MyData.CarsDB);
    AddNewClient.prepare("UPDATE Automobiles_Table set CLIENT_ID='"+m_strClientID+"' WHERE PR_ID='"+m_AttachAuto->GetSelectedCarID()+"' ");

    if(!AddNewClient.exec()){
        qDebug() << "UPDATE Automobiles_Table set CLIENT_ID faile with "<< AddNewClient.lastError().text();
    }

    // Update Current Changes
    MyData.CloseConnection();
}

void NewClient::on_Button_CancelAdd_clicked()
{
    emit CloseNewClientForm();
    hide();
}

void NewClient::on_Button_AddClientAuto_clicked()
{
    hide();
}

void NewClient::on_Button_AddClientAutoNew_clicked()
{
    hide();
}


bool NewClient::CheckRecordObligatory(){

    if(ui->LText_ClientName->text().isEmpty() ){
        QMessageBox::information(this,"Важно!","Не сте попълнили задължителните полега ( * ).");
         return false;
     }

    return true;
}

void NewClient::on_Button_Add_Client_clicked()
{
    CarsDatabase MyData;
    MyData.OpenConnection("Clients.sqlite");

    QSqlQuery AddNewClient(MyData.CarsDB);
    AddNewClient.prepare("INSERT INTO Clients_Table(ClientName, ClientCity, ClientFirm, ClientPhone, ClientAddress) "
                       "VALUES(:ClientName, :ClientCity, :ClientFirm, :ClientPhone, :ClientAddress)");

    AddNewClient.bindValue(":ClientName",ui->LText_ClientName->text());
    AddNewClient.bindValue(":ClientCity",ui->LText_ClientCity->text());
    AddNewClient.bindValue(":ClientFirm",ui->LText_ClientFirm->text());
    AddNewClient.bindValue(":ClientPhone",ui->LText_ClientPhone->text());
    AddNewClient.bindValue(":ClientAddress",ui->PText_ClientAddress->toPlainText());

    if(!AddNewClient.exec()){
        qDebug() << "INSERT INTO Clients_Table fail "<< AddNewClient.lastError().text() << " return ";
        return;
    }else {
        m_strLastClientName =ui->LText_ClientName->text();
         qDebug() << "m_strLastClientName   "<< m_strLastClientName;
    }

    // Get Last RowID
    QSqlQuery query(MyData.CarsDB);
        query.prepare("SELECT last_insert_rowid()");
        if(!query.exec())
        {
            qDebug() << "SELECT last_insert_rowid() "<< AddNewClient.lastError().text();
        }
        else {
            m_strClientID = query.lastInsertId().toString();
             qDebug() << "m_strClientID   "<< m_strClientID;
            MyData.CloseConnection();
            RecordCarToClient();
            ClearAllFields();
            on_Button_CancelAdd_clicked();
        }
}

void NewClient::on_LText_ClientName_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty() && (!ui->Button_AddClientAuto->isEnabled() || !ui->Button_AddClientAutoNew->isEnabled() ) )
    {
            qDebug() << "Button_AddClientAuto set active   ";
        ui->Button_AddClientAuto->setEnabled(true);
        ui->Button_AddClientAutoNew->setEnabled(true);
    }else if(arg1.isEmpty()){
            qDebug() << "Button_AddClientAuto set INactive   ";
            ui->Button_AddClientAuto->setEnabled(false);
            ui->Button_AddClientAutoNew->setEnabled(false);
    }
}
