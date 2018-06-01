#include "findauto.h"
#include "ui_findauto.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include "carsdatabase.h"

// Must have Automobile database here

FindAuto::FindAuto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindAuto)
{
    ui->setupUi(this);
    CenterForm();
    setWindowTitle("Find Auto");
    ui->Text_AutoInformation->setDisabled(true);
    FillPage();
}

FindAuto::~FindAuto()
{
    delete ui;
}

void FindAuto::FillPage()
{
    CarsDatabase MyData;
    MyData.OpenConnection("Automobiles.sqlite");
    QSqlQueryModel * MyModel = new QSqlQueryModel();
    QSqlQuery ShowModelQry(MyData.CarsDB);

    ShowModelQry.prepare("SELECT Auto_RegNumber FROM Automobiles_Table ");


    if(! ShowModelQry.exec()){
        qDebug() << "FindAuto Form ShowModelQry.Exec() SELECT Auto_RegNumber FROM Automobiles_Table Fail "<< endl;
    }

    MyModel->setQuery(ShowModelQry);
    ui->Combo_FindAutoRegNumber->setModel(MyModel);
    MyData.CloseConnection();
}

void FindAuto::on_Button_FindAutoDone_clicked()
{
    hide();
    emit CloseAddAutoForm();
}


void FindAuto::on_Button_FindAutoCancel_clicked()
{
    hide();
    emit CloseAddAutoForm();
}

void FindAuto::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-width()*0.5, center.y()-height()*0.5);
}


void FindAuto::OpenClearWindow()
{
    ui->Text_AutoInformation->clear();
    ui->Combo_FindAutoRegNumber->setCurrentIndex(0);
    this->show();
}
