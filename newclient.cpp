#include "newclient.h"
#include "ui_newclient.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include "newauto.h"
#include <QtWidgets>
#include <QKeyEvent>

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

    QObject::connect(this, SIGNAL(AddExistingAutoHit(QString)), m_AttachAuto, SLOT(OpenExistingAutosWindow(QString)) );
    QObject::connect(this, SIGNAL(ButtonEditHit(QString,QString)), m_AttachAuto, SLOT(EditClientAuto(QString,QString)));
    QObject::connect(ui->Button_AddClientAutoNew, SIGNAL(clicked()), m_NewAuto, SLOT(OpenClearWindow()));

    ui->Button_AddExistAuto->setEnabled(false);
    ui->Button_AddClientAutoNew->setEnabled(false);

    ui->Combo_Clients->setMaxVisibleItems(10);
    ui->Combo_Clients->setStyleSheet("combobox-popup: 0;");
}

NewClient::~NewClient()
{
    delete ui;
    delete m_AttachAuto;
    delete m_NewAuto;
}

void NewClient::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
            on_Button_CancelAdd_clicked();
    }
    else{
            QDialog::keyPressEvent(event);
    }
}

void NewClient::SetEditDesignMode()
{
    ui->L_Klient_Name_Edit->setVisible(true);
    ui->Combo_Clients->setVisible(true);
    ui->Button_AddClientAutoEdit->setVisible(true);
    ui->L_MainFormLabel->setText("Корекция на клиент");
    ui->Button_AddExistAuto->setVisible(true);
    ui->Button_AddClientAutoNew->setVisible(true);
    ui->Button_Add_Client->setEnabled(true);
    ui->L_MustAddCar->setVisible(false);
    ui->Check_SelectExistingKlient->setVisible(false);

    FillClientsNameCombo();
}

void NewClient::SetNewClientDesignMode()
{
    ui->L_MainFormLabel->setText("Добавяне на клиент");
    if(!m_bAttachClientToLastAddedAuto){
        ui->L_MustAddCar->setText("Всеки клиент е нужно\n да се свърже с автомобил !\n Моля изберете автомобил");
        ui->Combo_Clients->setVisible(true);
    }else {
        ui->L_MustAddCar->setText("Към избрания клиент ще се добави \n послено въведения автомобил ! ");
        FillClientsNameCombo();
        ui->Combo_Clients->setVisible(true);
        ui->Combo_Clients->setEnabled(false);
        ui->L_Klient_Name_Edit->setVisible(true);
    }
    ui->L_MustAddCar->setVisible(true);



    /** Record the last added auto for this client. No other buttons needed, but OK/Cancel */
    ui->Button_AddClientAutoEdit->setVisible(!m_bAttachClientToLastAddedAuto);
    ui->Button_AddExistAuto->setVisible(!m_bAttachClientToLastAddedAuto);
    ui->Button_AddClientAutoNew->setVisible(!m_bAttachClientToLastAddedAuto);
    ui->Button_Add_Client->setEnabled(false);
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
    qDebug() << " NewClient::OpenEditClientForm() ";
    m_bClientFormEditMode = true;
    ClearAllFields();
    SetEditDesignMode();
    this->show();
}


void NewClient::RestoreFormAttachAuto()
{
 qDebug() << "RestoreFormAttachAuto "<<m_AttachAuto->GetSelectedCarReg();
    if(m_AttachAuto->GetSelectedCarReg() != "None")
    {
        m_strClientCarReg = m_AttachAuto->GetSelectedCarReg();
        m_bRecordPermission = true;
        ui->Button_Add_Client->setEnabled(true);
    }else {
        m_bRecordPermission = false;
        //QMessageBox::information(this,"Attention!","No Auto selected !");
    }

    this->show();
    CenterForm();
}


void NewClient::RestoreFormNewAuto()
{
    this->show();
    CenterForm();
     qDebug() << "RestoreFormAttachAuto "<<m_NewAuto->GetNewCarReg();
    if(m_NewAuto->GetNewCarReg() != "None")
    {
        m_strClientCarReg = m_NewAuto->GetNewCarReg();
        m_bRecordPermission = true;
        ui->Button_Add_Client->setEnabled(true);
    }else {
        m_bRecordPermission = false;
     //   QMessageBox::information(this,"Attention!","No Auto selected !");
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
    if(m_bAttachClientToLastAddedAuto){
        m_strClientCarReg = m_NewAuto->GetLastCarReg();
    }

     qDebug() << " NewClient::RecordCarToClient()   "<<m_strClientCarReg;
    MyData.OpenConnection("Automobiles.sqlite");

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
        return false;
    }
    return true;
}

bool NewClient::CheckRecordObligatory(){

    if(ui->LText_ClientName->text().isEmpty() || ui->LText_ClientPhone->text().isEmpty()){
        QMessageBox::information(this,"Attention!","Missin information in some fields  ( * ).");
        return false;
    }

    return true;
}

void NewClient::on_Button_Add_Client_clicked()
{
    qDebug() << " on_Button_Add_Client_clicked  m_bRecordPermission "<<m_bRecordPermission;
    qDebug() << " on_Button_Add_Client_clicked  m_bAttachClientToLastAddedAuto  "<<m_bAttachClientToLastAddedAuto;

    if (CheckRecordObligatory()){
        if(ui->Check_SelectExistingKlient->isChecked() &&  m_bAttachClientToLastAddedAuto ){
            RecordCarToClient();
            m_bRecordPermission = false;
            m_bAttachClientToLastAddedAuto = false;
        }
        else
        {
            if(!AddClentInfo( ui->LText_ClientName->text(),
                     ui->LText_ClientPhone->text(),
                     ui->LText_ClientFirm->text(),
                     ui->LText_ClientCity->text(),
                     ui->Text_ClientAddress->toPlainText()))
            {
                return;
            }
            else if(m_bRecordPermission || m_bAttachClientToLastAddedAuto)
            {
                RecordCarToClient();
                m_bRecordPermission = false;
                m_bAttachClientToLastAddedAuto = false;
            }
        }
    }
    ClearAllFields();
    on_Button_CancelAdd_clicked();
}

void NewClient::FillClientsNameCombo()
{
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
    if(m_bAttachClientToLastAddedAuto && !ui->Check_SelectExistingKlient->isChecked()){
         qDebug() << " Do not fill autodata now ! ";
        return;
    }

    MyData.OpenConnection("Clients.sqlite");
    QSqlQuery SelectClientQry(MyData.CarsDB);

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
    emit ButtonEditHit(GetClientName(),GetClientID());
    hide();
}

void NewClient::on_Button_CancelAdd_clicked()
{
    emit CloseNewClientForm();
    hide();
}

void NewClient::on_Button_AddExistAuto_clicked()
{
    emit AddExistingAutoHit(GetClientName());
    hide();
}

void NewClient::on_Button_AddClientAutoNew_clicked()
{
    hide();
}


bool NewClient::ClientExsist(QString ClientName, QString ClientPhone){

    QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
    if (!re.exactMatch(ClientPhone)){
       QMessageBox::information(this,"Error !"," Only Gidits in phone number !! ");
       return true;
    }

    MyData.OpenConnection("Clients.sqlite");
    QSqlQuery ShowModelQry(MyData.CarsDB);
    bool m_bfoundName = false;
    bool m_bfoundPhone = false;
    ShowModelQry.prepare("SELECT ClientPhone FROM Clients_Table WHERE ClientPhone='"+ClientPhone+"' ");

    if(ShowModelQry.exec()){
       if(ShowModelQry.next()){
           m_bfoundName = true;
       }
    }else{
          qDebug() << "ClientPhone Ima problem s cheteneto ot bazata ";
    }

    ShowModelQry.prepare("SELECT ClientName FROM Clients_Table WHERE ClientName='"+ClientName+"' ");
    if(ShowModelQry.exec()){
       if(ShowModelQry.next()){
           m_bfoundPhone = true;
       }
    }else{
          qDebug() << "ClientName Ima problem s cheteneto ot bazata ";
    }

    MyData.CloseConnection();

    if(m_bfoundPhone && m_bfoundName){
         QMessageBox::information(this,"ERROR!"," Phone and name exist !! ");
         return true;
    }
    else if (m_bfoundPhone){
         QMessageBox::information(this,"ERROR!"," There is a client with this phone !! ");
         return true;
    }else if(m_bfoundName){
        QMessageBox::information(this,"ERROR!"," There is a client with this name !! ");
        return true;
    }

    return false;
}


bool NewClient::AddClentInfo(QString ClientName ,QString ClientPhone , QString ClientFirm, QString ClientCity,  QString ClientAddress)
{

    qDebug() << "AddClentInfo m_bClientFormEditMode "<<m_bClientFormEditMode;
    qDebug() << "AddClentInfo m_strLastClientName "<<m_strLastClientName;
    qDebug() << "AddClentInfo ClientName "<<ClientName<< " ClientPhone"<<ClientPhone<<" ClientFirm "<<ClientFirm<<" ClientCity-"<<ClientCity<<" ClientAddress - "<<ClientAddress;

    if( !m_bClientFormEditMode ){

        if (ClientExsist(ClientName,ClientPhone )) {
            return false;
        }
        MyData.OpenConnection("Clients.sqlite");
        QSqlQuery ClientQry(MyData.CarsDB);


        ClientQry.prepare("INSERT INTO Clients_Table(ClientName, ClientCity, ClientFirm, ClientPhone, ClientAddress) "
                          "VALUES(:ClientName, :ClientCity, :ClientFirm, :ClientPhone, :ClientAddress)");

        ClientQry.bindValue(":ClientName",ClientName.toUpper());
        ClientQry.bindValue(":ClientCity",ClientCity);
        ClientQry.bindValue(":ClientFirm",ClientFirm);
        ClientQry.bindValue(":ClientPhone",ClientPhone);
        ClientQry.bindValue(":ClientAddress",ClientAddress);

        if(!ClientQry.exec()){
            qDebug() << "INSERT INTO Clients_Table fail "<< ClientQry.lastError().text() << " return ";
            return false;
        }else {
            m_strLastClientName =ui->LText_ClientName->text();
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
            qDebug() << "NewClient::AddClentInfo m_strClientID  "<< m_strClientID;
        }
    }
    else {
        MyData.OpenConnection("Clients.sqlite");
        QSqlQuery ClientQry(MyData.CarsDB);


        ClientQry.prepare("UPDATE Clients_Table SET ClientName='"+ClientName+"' , ClientCity='"+ClientCity+"' , ClientFirm='"+ClientFirm+"' , ClientPhone='"+ClientPhone+"' , ClientAddress='"+ClientAddress+"' WHERE ClientName='"+m_strLastClientName+"'  ");

        if(!ClientQry.exec()){
            qDebug() << "UPDATE Clients_Table fail "<< ClientQry.lastError().text();
            MyData.CloseConnection();
            return false;
        }
    }

    MyData.CloseConnection();
    return true;
}

void NewClient::on_LText_ClientName_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty() && (!ui->Button_AddExistAuto->isEnabled() || !ui->Button_AddClientAutoNew->isEnabled() ) )
    {
        ui->Button_AddExistAuto->setEnabled(true);
        ui->Button_AddClientAutoNew->setEnabled(true);
    }else if(arg1.isEmpty()){
        ui->Button_AddExistAuto->setEnabled(false);
        ui->Button_AddClientAutoNew->setEnabled(false);
    }
    ui->Button_Add_Client->setEnabled((!ui->LText_ClientName->text().isEmpty() && !ui->LText_ClientPhone->text().isEmpty()));
}


void NewClient::on_LText_ClientPhone_editingFinished()
{
    ui->LText_ClientPhone->setText(ui->LText_ClientPhone->text().replace(" ",""));
}
void NewClient::on_Check_SelectExistingKlient_clicked(bool checked)
{
    ClearAllFields();
    if(checked){
        ui->Combo_Clients->setEnabled(true);
    }else {
        ui->Combo_Clients->setEnabled(false);
    }
}

void NewClient::on_LText_ClientPhone_textChanged()
{
    ui->Button_Add_Client->setEnabled((!ui->LText_ClientName->text().isEmpty() && !ui->LText_ClientPhone->text().isEmpty()));
}
