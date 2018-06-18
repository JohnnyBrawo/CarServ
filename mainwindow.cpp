#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qapplication.h"
#include "qdesktopwidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Clients(new NewClient()),
    m_Repairs(new AddRepair()),
    m_Autos(new CarsForm()),
    m_Search(new SearchForm()),
    m_BasePath(new CarsDatabase)

{
    ui->setupUi(this);
    setWindowTitle("Euro Kriss Service");
    CenterForm();
    LoadDesignView();

    // Connect all new windows
    QObject::connect(m_Autos, SIGNAL(CloseNewAutoForm()), this, SLOT(RestoreMainForm()));
    QObject::connect(m_Clients, SIGNAL(CloseNewClientForm()), this, SLOT(RestoreMainForm()));
    QObject::connect(m_Repairs, SIGNAL(CloseNewRepairForm()), this, SLOT(RestoreMainForm()));
    QObject::connect(m_Search, SIGNAL(CloseSearchForm()), this, SLOT(RestoreMainForm()));

    QObject::connect(ui->Button_OpenAutoForm, SIGNAL(clicked()), m_Autos, SLOT(OpenClearWindow()));
    QObject::connect(ui->Button_OpenClents, SIGNAL(clicked()), m_Clients, SLOT(OpenClearWindow()));
    QObject::connect(ui->Button_OpenRepairs, SIGNAL(clicked()), m_Repairs, SLOT(OpenClearWindow()));
    QObject::connect(ui->Button_Search, SIGNAL(clicked()), m_Search, SLOT(OpenClearWindow()));

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
    delete m_Clients;
    delete m_Repairs;
    delete m_Autos;
    delete m_Search;
    delete m_BasePath;
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

void MainWindow::on_Button_OpenAutoForm_clicked()
{
    hide();
}

void MainWindow::on_Button_OpenClents_clicked()
{
    hide();
}

void MainWindow::on_Button_OpenRepairs_clicked()
{
    hide();
}

void MainWindow::RestoreMainForm()
{
    this->show();
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}
