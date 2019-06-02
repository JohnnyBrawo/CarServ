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
    m_NewAuto(new NewAuto()),
    m_strClientID(""),
    m_strLastClientName(""),
    m_strClientCarReg(""),
    m_bRecordPermission(false),
    m_bClientFormEditMode(false)

{
    ui->setupUi(this);
    setWindowTitle("New Client");
    CenterForm();
    ui->Button_Add_Client->setEnabled(false);

    QObject::connect(m_AttachAuto, SIGNAL(CloseDeletePage()), this, SLOT(RestoreFormAttachAuto()));
    QObject::connect(m_NewAuto, SIGNAL(CloseNewAutoForm()), this, SLOT(RestoreFormNewAuto()));

    QObject::connect(ui->Button_AddClientAuto, SIGNAL(clicked()), m_AttachAuto, SLOT(OpenClearWindow()));
    QObject::connect(this, SIGNAL(ButtonEditHit(QString, QString)), m_AttachAuto, SLOT(OpenClientEditWindow(QString, QString)));
    QObject::connect(ui->Button_AddClientAutoNew, SIGNAL(clicked()), m_NewAuto, SLOT(OpenClearWindow()));

    ui->Button_AddClientAuto->setEnabled(false);
    ui->Button_AddClientAutoNew->setEnabled(false);
}

NewClient::~NewClient()
{
    delete ui;
    delete m_AttachAuto;
    delete m_NewAuto;
}

void NewClient::SetEditDesignMode()
{
    ui->L_Klient_Name_Edit->setVisible(true);
    ui->Combo_Clients->setVisible(true);
    ui->Button_AddClientAutoEdit->setVisible(true);
    ui->L_MainFormLabel_Edit->setVisible(true);
    ui->L_MainFormLabel_Add->setVisible(false);
    ui->Button_AddClientAuto->setVisible(false);
    ui->Button_AddClientAutoNew->setVisible(false);
    ui->Button_Add_Client->setEnabled(true);

    FillClientsNameCombo();
}

void NewClient::SetNewClientDesignMode()
{
    ui->L_Klient_Name_Edit->setVisible(false);
    ui->Combo_Clients->setVisible(false);
    ui->Button_AddClientAutoEdit->setVisible(false);
    ui->L_MainFormLabel_Edit->setVisible(false);
    ui->L_MainFormLabel_Add->setVisible(true);
    ui->Button_AddClientAuto->setVisible(true);
    ui->Button_AddClientAutoNew->setVisible(true);
}

void NewClient::ClearAllFields()
{
    ui->LText_ClientCity->clear();
    ui->LText_ClientPhone->clear();
    ui->LText_ClientFirm->clear();
    ui->LText_ClientName->clear();
    ui->Text_ClientAddress->document()->setPlainText("");
    m_strClientCarReg.clear();

}

void NewClient::OpenNewClientForm()
{
    m_bClientFormEditMode = false;
    ClearAllFields();
    SetNewClientDesignMode();
    this->show();

}

void NewClient::OpenEditClientForm()
{
    m_bClientFormEditMode = true;
    ClearAllFields();
    SetEditDesignMode();
    this->show();
}


void NewClient::RestoreFormAttachAuto()
{
    this->show();
    CenterForm();

    if(m_AttachAuto->GetSelectedCarReg() != "None")
    {
        m_strClientCarReg = m_AttachAuto->GetSelectedCarReg();
        m_bRecordPermission = true;
        ui->Button_Add_Client->setEnabled(true);
    }else {
        m_bRecordPermission = false;
        QMessageBox::information(this,"Важно!","Не сте задали автомобил!");
    }

}


void NewClient::RestoreFormNewAuto()
{
    this->show();
    CenterForm();
    if(m_NewAuto->GetNewCarReg() != "None")
    {
        m_strClientCarReg = m_NewAuto->GetNewCarReg();
        m_bRecordPermission = true;
        ui->Button_Add_Client->setEnabled(true);
    }else {
        m_bRecordPermission = false;
        QMessageBox::information(this,"Важно!","Не сте задали автомобил!");
    }

}


void NewClient::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-static_cast<int>(width()*0.5), center.y()-static_cast<int>(height()*0.5) );
}


void NewClient::RecordCarToClient()
{
    CarsDatabase MyData;
    MyData.OpenConnection("Automobiles.sqlite");

     qDebug() << "RecordCarToClient  m_strClientCarReg " << m_strClientCarReg;
    QSqlQuery ClientQry(MyData.CarsDB);
    ClientQry.prepare("UPDATE Automobiles_Table set CLIENT_ID='"+m_strClientID+"' WHERE Auto_RegNumber='"+m_strClientCarReg+"' ");

    if(!ClientQry.exec()){
        qDebug() << "UPDATE Automobiles_Table set CLIENT_ID faile with "<< ClientQry.lastError().text();
    }

    // Update Current Changes
    MyData.CloseConnection();
}

bool NewClient::CheckField(QString SelectedString)
{
    if(( static_cast<int>(SelectedString.size()) < 2 ) || SelectedString.isEmpty())
    {
        qDebug() << "NewClient::CheckField  FAIL SelectedString " << SelectedString;
        return false;
    }
    return true;
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
    qDebug() << "NewClient::on_Button_Add_Client_clicked()   ";
    CarsDatabase MyData;
    MyData.OpenConnection("Clients.sqlite");
    QSqlQuery ClientQry(MyData.CarsDB);

    QString ClientName = CheckField(ui->LText_ClientName->text())?ui->LText_ClientName->text():"None";
    QString ClientCity = CheckField(ui->LText_ClientCity->text())?ui->LText_ClientCity->text():"None";
    QString ClientFirm = CheckField(ui->LText_ClientFirm->text())?ui->LText_ClientFirm->text():"None";
    QString ClientPhone = CheckField(ui->LText_ClientPhone->text())?ui->LText_ClientPhone->text():"None";
    QString ClientAddress = CheckField(ui->Text_ClientAddress->toPlainText())?ui->Text_ClientAddress->toPlainText():"None";


    if( !m_bClientFormEditMode ){

        ClientQry.prepare("INSERT INTO Clients_Table(ClientName, ClientCity, ClientFirm, ClientPhone, ClientAddress) "
                          "VALUES(:ClientName, :ClientCity, :ClientFirm, :ClientPhone, :ClientAddress)");

        ClientQry.bindValue(":ClientName",ClientName);
        ClientQry.bindValue(":ClientCity",ClientCity);
        ClientQry.bindValue(":ClientFirm",ClientFirm);
        ClientQry.bindValue(":ClientPhone",ClientPhone);
        ClientQry.bindValue(":ClientAddress",ClientAddress);

        if(!ClientQry.exec()){
            qDebug() << "INSERT INTO Clients_Table fail "<< ClientQry.lastError().text() << " return ";
            return;
        }else {
            m_strLastClientName =ui->LText_ClientName->text();
            qDebug() << "m_strLastClientName   "<< m_strLastClientName;
        }

        // Get Last RowID
        QSqlQuery LastRowQry(MyData.CarsDB);
        LastRowQry.prepare("SELECT last_insert_rowid()");
        if(!LastRowQry.exec())
        {
            qDebug() << "SELECT LastRowQry last_insert_rowid() "<< LastRowQry.lastError().text();
        }
        else {
            m_strClientID = LastRowQry.lastInsertId().toString();
            qDebug() << "m_strClientID   "<< m_strClientID;

            RecordCarToClient();

        }
    }
    else {

        qDebug() << "m_strLastClientName  EDIT MODE  "<< m_strLastClientName;
        ClientQry.prepare("UPDATE Clients_Table set ClientName='"+ClientName+"', ClientCity='"+ClientCity+"', ClientFirm='"+ClientFirm+"', ClientPhone='"+ClientPhone+"', ClientAddress='"+ClientAddress+"' WHERE ClientName='"+m_strLastClientName+"'  ");

        if(!ClientQry.exec()){
            qDebug() << "UPDATE Clients_Table fail "<< ClientQry.lastError().text();
        }
    }

    ClearAllFields();
    MyData.CloseConnection();
    on_Button_CancelAdd_clicked();

}

void NewClient::on_LText_ClientName_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty() && (!ui->Button_AddClientAuto->isEnabled() || !ui->Button_AddClientAutoNew->isEnabled() ) )
    {
        ui->Button_AddClientAuto->setEnabled(true);
        ui->Button_AddClientAutoNew->setEnabled(true);
    }else if(arg1.isEmpty()){
        ui->Button_AddClientAuto->setEnabled(false);
        ui->Button_AddClientAutoNew->setEnabled(false);
    }
}

void NewClient::FillClientsNameCombo()
{
    qDebug() << "NewClient::FillClientsNameCombo()   ";
    CarsDatabase MyData;
    MyData.OpenConnection("Clients.sqlite");

    QSqlQueryModel * ClientsNameComboModel = new QSqlQueryModel();

    QSqlQuery ShowClientsQry(MyData.CarsDB);
    ShowClientsQry.prepare("SELECT ClientName FROM Clients_Table");

    if(! ShowClientsQry.exec()){
        qDebug() << "ShowClientsQry.Exec() SELECT ClientName FROM Clients_Table fail "<< ShowClientsQry.lastError().text();
    }

    ClientsNameComboModel->setQuery(ShowClientsQry);
    ui->Combo_Clients->setModel(ClientsNameComboModel);

    MyData.CloseConnection();

}

void NewClient::on_Combo_Clients_currentIndexChanged(const QString &arg1)
{
    qDebug() << "NewClient::on_Combo_Clients_currentIndexChanged()   ";
    CarsDatabase MyData;
    MyData.OpenConnection("Clients.sqlite");
    QSqlQuery SelectClientQry(MyData.CarsDB);

    //      if(m_bComboRegsHit)
    //      {
    //          MyData.CloseConnection();
    //          return;
    //      }

    SelectClientQry.prepare("SELECT * FROM Clients_Table WHERE ClientName='"+arg1+"' ");

    if(!SelectClientQry.exec()){
        qDebug() << "SelectClientQry.Exec() SELECT Clients_Table FROM ClientName Fail "<< SelectClientQry.lastError().text();
    }else {
        if (SelectClientQry.next()) {
            m_strClientID = SelectClientQry.value(0).toString();
            ui->LText_ClientName->setText(SelectClientQry.value(1).toString());
            ui->LText_ClientCity->setText(SelectClientQry.value(2).toString());
            ui->LText_ClientFirm->setText(SelectClientQry.value(3).toString());
            ui->LText_ClientPhone->setText(SelectClientQry.value(4).toString());
            ui->Text_ClientAddress->document()->setPlainText(SelectClientQry.value(5).toString());
        }else {
            qDebug() << "SelectClientQry.Exec() Invalid query record ! ";
            ClearAllFields();
        }
    }
    MyData.CloseConnection();
    m_strLastClientName =ui->LText_ClientName->text();
}

void NewClient::on_Button_AddClientAutoEdit_clicked()
{
    qDebug() << "NewClient::on_Button_AddClientAutoEdit_clicked()   ";
    emit ButtonEditHit( GetClientName(), GetClientID());
    hide();
}

void NewClient::on_Button_CancelAdd_clicked()
{
    qDebug() << "NewClient::on_Button_CancelAdd_clicked()   ";
    emit CloseNewClientForm();
    hide();
}

void NewClient::on_Button_AddClientAuto_clicked()
{
    qDebug() << "NewClient::on_Button_AddClientAuto_clicked()   ";
    hide();
}

void NewClient::on_Button_AddClientAutoNew_clicked()
{
    qDebug() << "NewClient::on_Button_AddClientAutoNew_clicked()   ";
    hide();
}
