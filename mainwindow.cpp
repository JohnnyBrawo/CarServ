#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_NewClient(new NewClient()),
    m_NewRepair(new NewRepair()),
    m_SearchForm(new SearchForm())
{
    ui->setupUi(this);
    m_NewAuto = new NewAuto();
    QObject::connect(m_NewAuto, SIGNAL(CloseNewAutoForm()), this, SLOT(RestoreMainForm()));
    QObject::connect(m_NewClient, SIGNAL(CloseNewClientForm()), this, SLOT(RestoreMainForm()));
    QObject::connect(m_NewRepair, SIGNAL(CloseNewRepairForm()), this, SLOT(RestoreMainForm()));
    QObject::connect(m_SearchForm, SIGNAL(CloseSearchForm()), this, SLOT(RestoreMainForm()));

    QObject::connect(ui->Button_AddNewAuto, SIGNAL(clicked()), m_NewAuto, SLOT(show()));
    QObject::connect(ui->Button_AddNewClient, SIGNAL(clicked()), m_NewClient, SLOT(show()));
    QObject::connect(ui->Button_AddNewRepair, SIGNAL(clicked()), m_NewRepair, SLOT(show()));
    QObject::connect(ui->Button_Search, SIGNAL(clicked()), m_SearchForm, SLOT(show()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_NewClient;
    delete m_NewRepair;
    delete m_NewAuto;
    delete m_SearchForm;
}

void MainWindow::on_Button_Search_clicked()
{
    hide();
}

void MainWindow::on_Button_AddNewAuto_clicked()
{
    hide();
}

void MainWindow::on_Button_AddNewClient_clicked()
{
    hide();
}

void MainWindow::on_Button_AddNewRepair_clicked()
{
    hide();
}

void MainWindow::RestoreMainForm()
{
    this->show();
}
