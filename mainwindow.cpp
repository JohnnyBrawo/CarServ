#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qapplication.h"
#include "qdesktopwidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Repairs(new AddRepair()),
    m_Search(new SearchForm()),
    m_BasePath(new CarsDatabase()),

    m_Autos(new CarsForm()),
    m_ShowAllAutos(new ShowAllcars()),
    m_NewAuto(new NewAuto()),
    m_DelEdtiAuto(new RemoveChangeAuto()),

    m_Clients(new ClientsForm()),
    m_NewClient(new NewClient()),
    m_RemoveClient(new RemoveClient())
{
    ui->setupUi(this);
    setWindowTitle("Euro Kriss Service");
    CenterForm();
    LoadDesignView();

    /** Main form buttons */
    QObject::connect(ui->Button_OpenRepairs, SIGNAL(clicked()), m_Repairs, SLOT(OpenClearWindow()));
    QObject::connect(ui->Button_Search, SIGNAL(clicked()), m_Search, SLOT(OpenClearWindow()));

    QObject::connect(m_Repairs, SIGNAL(CloseNewRepairForm()), this, SLOT(RestoreMainForm()));
    QObject::connect(m_Search, SIGNAL(CloseSearchForm()), this, SLOT(RestoreMainForm()));


    /**Autos Menu - Close */
    QObject::connect(m_ShowAllAutos, SIGNAL(CloseShowAllAutoForm()), this, SLOT(RestoreMainForm()));
    QObject::connect(m_NewAuto, SIGNAL(CloseNewAutoForm()), this, SLOT(RestoreMainForm()));
    QObject::connect(m_DelEdtiAuto, SIGNAL(CloseDeletePage()), this, SLOT(RestoreMainForm()));

    /**Clients Menu - Close */
    QObject::connect(m_NewClient, SIGNAL(CloseClientsPage()), this, SLOT(RestoreMainForm()));
    QObject::connect(m_NewClient, SIGNAL(CloseNewClientForm()), this, SLOT(RestoreMainForm()));
    QObject::connect(m_RemoveClient, SIGNAL(CloseRemoveClientPage()), this, SLOT(RestoreMainForm()));


    /**Autos Menu - trigger */
    QObject::connect(ui->ShowAllAutos, SIGNAL(triggered()), m_ShowAllAutos, SLOT(OpenClearWindow()));
    QObject::connect(ui->AddNewAuto, SIGNAL(triggered()), m_NewAuto, SLOT(OpenClearWindow()));
    QObject::connect(ui->EditDeleteAuto, SIGNAL(triggered()), m_DelEdtiAuto, SLOT(OpenClearEditWindow()));

    /**Clients menu - trigger */
    QObject::connect(ui->AddNewClient, SIGNAL(triggered()), m_NewClient, SLOT(OpenNewClientForm()));
    QObject::connect(ui->EditClient, SIGNAL(triggered()), m_NewClient, SLOT(OpenEditClientForm()));
    QObject::connect(ui->DeleteClient, SIGNAL(triggered()), m_RemoveClient, SLOT(OpenRemoveClientPage()));

}

void MainWindow::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-static_cast<int>(width()*0.5), center.y()-static_cast<int>(height()*0.5));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_Clients;
    delete m_Repairs;
    delete m_Autos;
    delete m_Search;
    delete m_BasePath;
    delete m_ShowAllAutos;
    delete m_NewAuto;
    delete m_DelEdtiAuto;
    delete m_NewClient;
    delete m_RemoveClient;
}

void MainWindow::LoadDesignView()
{

    //    setStyleSheet("background-image: url(:/images/Images/ideas.jpg);");
    //    setStyleSheet("background-image: url(:"+m_BasePath->GetReousrcesPath()+"ideas.jpg);");
}

void MainWindow::on_Button_Search_clicked()
{
    hide();
}

//void MainWindow::on_Button_OpenAutoForm_clicked()
//{
//    hide();
//}

//void MainWindow::on_Button_OpenClents_clicked()
//{
//    hide();
//}

void MainWindow::on_Button_OpenRepairs_clicked()
{
    hide();
}

void MainWindow::RestoreMainForm()
{
    this->show();
}

void MainWindow::on_Exit_clicked()
{
    this->close();
}


void MainWindow::on_ShowAllAutos_triggered()
{
     hide();
}

void MainWindow::on_AddNewAuto_triggered()
{
    hide();
}

void MainWindow::on_EditDeleteAuto_triggered()
{
    hide();
}

void MainWindow::on_DeleteClient_triggered()
{
    hide();
}

void MainWindow::on_AddNewClient_triggered()
{
    hide();
}

void MainWindow::on_EditClient_triggered()
{
    hide();
}
