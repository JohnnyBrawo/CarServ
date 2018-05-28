#include "newauto.h"
#include "ui_newauto.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include <qdebug.h>
#include "carsdatabase.h"

// Must have Automobile database here

NewAuto::NewAuto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAuto)
{
    ui->setupUi(this);
    CenterForm();
    setWindowTitle("New Auto");
}

NewAuto::~NewAuto()
{
    delete ui;
}


void NewAuto::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-width()*0.5, center.y()-height()*0.5);
}


void NewAuto::on_Button_CancelNewAuto_clicked()
{
    emit CloseNewAutoForm();
    this->hide();
}


void NewAuto::OpenClearWindow()
{
     ClearAllFields();
     FillCombos();
     this->show();
}

void NewAuto::ClearAllFields()
{
    ui->Combo_NewAuto_Fuel->setCurrentIndex(0);
    ui->Combo_NewAuto_Marka->setCurrentIndex(0);
    ui->Combo_NewAuto_Model->setCurrentIndex(0);
    ui->Combo_NewAuto_Model->setEnabled(false);
    ui->Combo_NewAuto_Year->setCurrentIndex(0);
    ui->LText_NewAutoRegNumber->clear();
    ui->LText_NewAutoVIN->clear();
}

void NewAuto::on_Button_AddNewAuto_clicked()
{

    CarsDatabase MyData;
    MyData.OpenConnection("Automobiles.sqlite");

    QSqlQuery AddNewAuto(MyData.CarsDB);
    AddNewAuto.prepare("INSERT INTO Automobiles_Table(AutoMarka, AutoModel, AutoYear, AutoFuel, Auto_RegNumber, AutoVIN) "
                       "VALUES(:AutoMarka, :AutoModel, :AutoYear, :AutoFuel, :Auto_RegNumber, :AutoVIN)");

    AddNewAuto.bindValue(":AutoMarka",ui->Combo_NewAuto_Marka->currentText());
    AddNewAuto.bindValue(":AutoModel",ui->Combo_NewAuto_Model->currentText());
    AddNewAuto.bindValue(":AutoYear",ui->Combo_NewAuto_Year->currentText());
    AddNewAuto.bindValue(":AutoFuel",ui->Combo_NewAuto_Fuel->currentText());
    AddNewAuto.bindValue(":Auto_RegNumber",ui->LText_NewAutoRegNumber->text());
    AddNewAuto.bindValue(":Auto_VIN",ui->LText_NewAutoVIN->text());

    qDebug() << AddNewAuto.exec() << endl;
    MyData.CloseConnection();
}


void NewAuto::FillCombos()
{
    FillComboMarki();
    FillComboModeli();
}


void NewAuto::FillComboMarki()
{
    CarsDatabase MyData;
    MyData.OpenConnection("Marki.sqlite");

    QSqlQueryModel * MyModel = new QSqlQueryModel();

    QSqlQuery ShowMakriQry(MyData.CarsDB);
    ShowMakriQry.prepare("SELECT Marki FROM AutoMarki_Table");

    qDebug() << ShowMakriQry.exec() << endl;
    MyModel->setQuery(ShowMakriQry);
    ui->Combo_NewAuto_Marka->setModel(MyModel);

    MyData.CloseConnection();

}

void NewAuto::FillComboModeli()
{
    CarsDatabase MyData;
    MyData.OpenConnection("All_Models.sqlite");

    QSqlQueryModel * MyModel = new QSqlQueryModel();

    QSqlQuery ShowMakriQry(MyData.CarsDB);
    ShowMakriQry.prepare("SELECT Model_Name FROM All_Models_Table");

    qDebug() << ShowMakriQry.exec() << endl;
    MyModel->setQuery(ShowMakriQry);
    ui->Combo_NewAuto_Model->setModel(MyModel);

    MyData.CloseConnection();

}

void NewAuto::on_Combo_NewAuto_Marka_currentIndexChanged(int index)
{
    qDebug() << "Selected index is " << index << endl;
}

void NewAuto::on_Combo_NewAuto_Marka_currentIndexChanged(const QString &arg1)
{
    qDebug() << "Selected String index is " << arg1 << endl;
    qDebug() << "Selected String index is " << arg1.size() << endl;
}
