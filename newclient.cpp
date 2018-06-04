#include "newclient.h"
#include "ui_newclient.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include "newauto.h"
#include "carsdatabase.h"

NewClient::NewClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewClient),
    m_AttachAuto(new RemoveChangeAuto()),
    m_NewAuto(new NewAuto())
{
    ui->setupUi(this);
    setWindowTitle("New Client");
    CenterForm();
    QObject::connect(m_AttachAuto, SIGNAL(CloseDeletePage()), this, SLOT(RestoreForm()));
    QObject::connect(ui->Button_AddClientAuto, SIGNAL(clicked()), m_AttachAuto, SLOT(OpenClearWindow()));


    QObject::connect(m_NewAuto, SIGNAL(CloseNewAutoForm()), this, SLOT(RestoreForm()));
    QObject::connect(ui->Button_AddClientAutoNew, SIGNAL(clicked()), m_NewAuto, SLOT(OpenClearWindow()));

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


void NewClient::RestoreForm()
{
    this->show();
    CenterForm();
    qDebug() << "Selected Car ID is  : " << m_AttachAuto->GetSelectedCarID();
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


void NewClient::on_Button_Add_Client_clicked()
{
    CarsDatabase MyData;
    MyData.OpenConnection("Clients.sqlite");

    QSqlQuery AddNewAuto(MyData.CarsDB);
    AddNewAuto.prepare("INSERT INTO Clients_Table(ClientName, ClientCity, ClientFirm, ClientPhone, ClientAddress) "
                       "VALUES(:ClientName, :ClientCity, :ClientFirm, :ClientPhone, :ClientAddress)");

    AddNewAuto.bindValue(":ClientName",ui->LText_ClientName->text());
    AddNewAuto.bindValue(":ClientCity",ui->LText_ClientCity->text());
    AddNewAuto.bindValue(":ClientFirm",ui->LText_ClientFirm->text());
    AddNewAuto.bindValue(":ClientPhone",ui->LText_ClientPhone->text());
    AddNewAuto.bindValue(":ClientAddress",ui->PText_ClientAddress->toPlainText());

//    qDebug() << " ui->LText_ClientName->text()  " << ui->LText_ClientName->text();
//    qDebug() << " ui->LText_ClientCity->text()  " << ui->LText_ClientCity->text();
//    qDebug() << " ui->LText_ClientFirm->text()  " << ui->LText_ClientFirm->text();
//    qDebug() << " ui->LText_ClientPhone->text()  " << ui->LText_ClientPhone->text();
//    qDebug() << " ui->PText_ClientAddress->toPlainText() " << ui->PText_ClientAddress->toPlainText();


    if(!AddNewAuto.exec()){
        qDebug() << "INSERT INTO Clients_Table fail "<< endl;

    }

    MyData.CloseConnection();
    ClearAllFields();
}
