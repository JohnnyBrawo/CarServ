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
    m_bClientFormEditMode = false;
    m_strClientID = -1;
    m_strLastClientName.clear();
    m_bRecordPermission = false;
    ui->Button_Add_Client->setEnabled(false);

    QObject::connect(m_AttachAuto, SIGNAL(CloseDeletePage()), this, SLOT(RestoreFormAttachAuto()));
    QObject::connect(m_NewAuto, SIGNAL(CloseNewAutoForm()), this, SLOT(RestoreFormNewAuto()));

    QObject::connect(ui->Button_AddClientAuto, SIGNAL(clicked()), m_AttachAuto, SLOT(OpenClearWindow()));
    QObject::connect(this, SIGNAL(ButtonEditHit(QString)), m_AttachAuto, SLOT(OpenClientEditWindow(QString)));
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

    QSqlQuery ClientQry(MyData.CarsDB);
    ClientQry.prepare("UPDATE Automobiles_Table set CLIENT_ID='"+m_strClientID+"' WHERE PR_ID='"+m_AttachAuto->GetSelectedCarID()+"' ");

    if(!ClientQry.exec()){
        qDebug() << "UPDATE Automobiles_Table set CLIENT_ID faile with "<< ClientQry.lastError().text();
    }

    // Update Current Changes
    MyData.CloseConnection();
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
    QSqlQuery ClientQry(MyData.CarsDB);

    if( !m_bClientFormEditMode ){

    ClientQry.prepare("INSERT INTO Clients_Table(ClientName, ClientCity, ClientFirm, ClientPhone, ClientAddress) "
                       "VALUES(:ClientName, :ClientCity, :ClientFirm, :ClientPhone, :ClientAddress)");

    ClientQry.bindValue(":ClientName",ui->LText_ClientName->text());
    ClientQry.bindValue(":ClientCity",ui->LText_ClientCity->text());
    ClientQry.bindValue(":ClientFirm",ui->LText_ClientFirm->text());
    ClientQry.bindValue(":ClientPhone",ui->LText_ClientPhone->text());
    ClientQry.bindValue(":ClientAddress",ui->Text_ClientAddress->toPlainText());

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
        ClientQry.prepare("UPDATE Clients_Table set ClientName='"+ui->LText_ClientName->text()+"', ClientCity='"+ui->LText_ClientCity->text()+"', ClientFirm='"+ui->LText_ClientFirm->text()+"', ClientPhone='"+ui->LText_ClientPhone->text()+"', ClientAddress='"+ui->Text_ClientAddress->toPlainText()+"' WHERE ClientName='"+m_strLastClientName+"'  ");

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
            qDebug() << "Button_AddClientAuto set active   ";
        ui->Button_AddClientAuto->setEnabled(true);
        ui->Button_AddClientAutoNew->setEnabled(true);
    }else if(arg1.isEmpty()){
            qDebug() << "Button_AddClientAuto set INactive   ";
            ui->Button_AddClientAuto->setEnabled(false);
            ui->Button_AddClientAutoNew->setEnabled(false);
    }
}

void NewClient::FillClientsNameCombo()
{
    CarsDatabase MyData;
    MyData.OpenConnection("Clients.sqlite");

    QSqlQueryModel * MyModel = new QSqlQueryModel();

    QSqlQuery ShowClientsQry(MyData.CarsDB);
    ShowClientsQry.prepare("SELECT ClientName FROM Clients_Table");

    if(! ShowClientsQry.exec()){
        qDebug() << "ShowClientsQry.Exec() SELECT ClientName FROM Clients_Table fail "<< ShowClientsQry.lastError().text();
    }

    MyModel->setQuery(ShowClientsQry);
    ui->Combo_Clients->setModel(MyModel);

    MyData.CloseConnection();

}

void NewClient::on_Combo_Clients_currentIndexChanged(const QString &arg1)
{
    CarsDatabase MyData;
      MyData.OpenConnection("Clients.sqlite");
      QSqlQuery EditClientQry(MyData.CarsDB);

//      if(m_bComboRegsHit)
//      {
//          MyData.CloseConnection();
//          return;
//      }

      qDebug() << "on_Combo_Clients_currentIndexChanged arg1 "<< arg1;

      EditClientQry.prepare("SELECT * FROM Clients_Table WHERE ClientName='"+arg1+"' ");

      if(!EditClientQry.exec()){
          qDebug() << "EditClientQry.Exec() SELECT Clients_Table FROM ClientName Fail "<< endl;
      }else {
          if (EditClientQry.next()) {
              ui->LText_ClientName->setText(EditClientQry.value(1).toString());
              ui->LText_ClientCity->setText(EditClientQry.value(2).toString());
              ui->LText_ClientFirm->setText(EditClientQry.value(3).toString());
              ui->LText_ClientPhone->setText(EditClientQry.value(4).toString());
              ui->Text_ClientAddress->document()->setPlainText(EditClientQry.value(5).toString());
          }else {
              ClearAllFields();
          }
      }
      MyData.CloseConnection();
      m_strLastClientName =ui->LText_ClientName->text();
}

void NewClient::on_Button_AddClientAutoEdit_clicked()
{
    emit ButtonEditHit( GetClientName());
    hide();
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
