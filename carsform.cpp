#include "carsform.h"
#include "ui_carsform.h"
#include "qapplication.h"
#include "qdesktopwidget.h"


CarsForm::CarsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CarsForm),
    m_NewAuto(new NewAuto()),
    m_ShowAllAutos(new ShowAllcars()),
    m_DelEdtiAuto(new RemoveChangeAuto())
{
    ui->setupUi(this);
    setWindowTitle("Euro Kriss - AUTOS ");
    CenterForm();

    // Connect all new windows
    QObject::connect(m_NewAuto, SIGNAL(CloseNewAutoForm()), this, SLOT(RestoreView()));
    QObject::connect(m_ShowAllAutos, SIGNAL(CloseShowAllAutoForm()), this, SLOT(RestoreView()));
    //    QObject::connect(m_DelEdtiAuto, SIGNAL(CloseChangePage()), this, SLOT(RestoreView()));
    QObject::connect(m_DelEdtiAuto, SIGNAL(CloseDeletePage()), this, SLOT(RestoreView()));

    QObject::connect(ui->Button_AddNewAuto, SIGNAL(clicked()), m_NewAuto, SLOT(OpenClearWindow()));
    QObject::connect(ui->Button_ShowAllAutos, SIGNAL(clicked()), m_ShowAllAutos, SLOT(OpenClearWindow()));
    QObject::connect(ui->Button_EditAuto, SIGNAL(clicked()), m_DelEdtiAuto, SLOT(OpenClearEditWindow()));
    //QObject::connect(ui->Button_ChangeAuto, SIGNAL(clicked()), m_DelEdtiAuto, SLOT(OpenClearEditWindow())); - > Not Used

    //    setStyleSheet("background-image: url(:/images/Images/ideas.jpg);");
}

CarsForm::~CarsForm()
{
    delete ui;
    delete m_NewAuto;
    delete m_ShowAllAutos;
    delete m_DelEdtiAuto;
}


void CarsForm::RestoreView()
{
    show();
    //    CenterForm();     uncomment to set the MainForm position in the middle of the screen
}

void CarsForm::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-width()*0.5, center.y()-height()*0.5);
}

void CarsForm::OpenClearWindow()
{
    show();
}

void CarsForm::on_Button_Back_clicked()
{
    hide();
    emit CloseNewAutoForm();

}

void CarsForm::on_Button_AddNewAuto_clicked()
{
    hide();
}


void CarsForm::on_Button_ShowAllAutos_clicked()
{
    hide();
}

void CarsForm::on_Button_EditAuto_clicked()
{
    hide();
}
