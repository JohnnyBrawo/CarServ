#include "newclient.h"
#include "ui_newclient.h"
#include "qapplication.h"
#include "qdesktopwidget.h"

NewClient::NewClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewClient),
    m_FindAuto(new FindAuto())
{
    ui->setupUi(this);
    setWindowTitle("New Client");
    CenterForm();
    QObject::connect(m_FindAuto, SIGNAL(CloseAddAutoForm()), this, SLOT(RestoreForm()));
    QObject::connect(ui->Button_AddClientAuto, SIGNAL(clicked()), m_FindAuto, SLOT(show()));
}

NewClient::~NewClient()
{
    delete ui;
    delete m_FindAuto;
}

void NewClient::ClearAllFields()
{
    ui->LText_ClientCity->clear();
    ui->LText_ClientPhone->clear();
    ui->LText_ClientFirm->clear();
    ui->LText_ClientName->clear();
    ui->Text_KlientAddress->clear();
}


void NewClient::RestoreForm()
{
    this->show();
    CenterForm();
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
