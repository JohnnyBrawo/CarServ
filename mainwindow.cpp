#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qapplication.h"
#include "qdesktopwidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_NewClient(new NewClient()),
    m_NewRepair(new AddRepair()),
    m_NewAuto(new NewAuto()),
    m_SearchForm(new SearchForm())

{
    ui->setupUi(this);
    setWindowTitle("Euro Kriss Service");
    CenterForm();

    // Connect all new windows
    QObject::connect(m_NewAuto, SIGNAL(CloseNewAutoForm()), this, SLOT(RestoreMainForm()));
    QObject::connect(m_NewClient, SIGNAL(CloseNewClientForm()), this, SLOT(RestoreMainForm()));
    QObject::connect(m_NewRepair, SIGNAL(CloseNewRepairForm()), this, SLOT(RestoreMainForm()));
    QObject::connect(m_SearchForm, SIGNAL(CloseSearchForm()), this, SLOT(RestoreMainForm()));

    QObject::connect(ui->Button_AddNewAuto, SIGNAL(clicked()), m_NewAuto, SLOT(OpenClearWindow()));
    QObject::connect(ui->Button_AddNewClient, SIGNAL(clicked()), m_NewClient, SLOT(OpenClearWindow()));
    QObject::connect(ui->Button_AddNewRepair, SIGNAL(clicked()), m_NewRepair, SLOT(OpenClearWindow()));
    QObject::connect(ui->Button_Search, SIGNAL(clicked()), m_SearchForm, SLOT(OpenClearWindow()));

    // Clear all new windows on load
//    QObject::connect(ui->Button_AddNewClient, SIGNAL(clicked()), m_NewClient, SLOT(ClearAllFields()));
//    QObject::connect(ui->Button_AddNewAuto, SIGNAL(clicked()), m_NewClient, SLOT(ClearAllFields()));
//    QObject::connect(ui->Button_AddNewRepair, SIGNAL(clicked()), m_NewClient, SLOT(ClearAllFields()));
//    QObject::connect(ui->Button_Search, SIGNAL(clicked()), m_NewClient, SLOT(ClearAllFields()));



    setStyleSheet("background-image: url(:/images/Images/ideas.jpg);");

}

void MainWindow::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-width()*0.5, center.y()-height()*0.5);
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
//    CenterForm();     uncomment to set the MainForm position in the middle of the screen
}
