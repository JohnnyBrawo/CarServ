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
     FillCombos();
     ClearAllFields();
     this->show();
}

void NewAuto::ClearAllFields()
{
    //  Disable all fields except Auto Model.
    //  Enable fields one after other
    ui->Combo_NewAuto_Marka->setCurrentIndex(0);

    ui->Combo_NewAuto_Model->setCurrentIndex(0);
    ui->Combo_NewAuto_Model->setEnabled(false);

    ui->Combo_NewAuto_Year->setCurrentIndex(0);
    ui->Combo_NewAuto_Year->setEnabled(false);

    ui->Combo_NewAuto_Fuel->setCurrentIndex(0);
    ui->Combo_NewAuto_Fuel->setEnabled(false);

    ui->LText_NewAutoRegNumber->clear();
    ui->LText_NewAutoRegNumber->setEnabled(false);

    ui->LText_NewAutoVIN->clear();
    ui->LText_NewAutoVIN->setEnabled(false);
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
//    FillComboModeli();
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

bool NewAuto::CheckSelected(QString SelectedString)
{
    if(( (int)SelectedString.size() < 2 ) || (SelectedString == "Select"))
    {
        qDebug() << "Back to Select  " << SelectedString << endl;
        return false;
    }
    else
    {
         qDebug() << "Selected String  " << SelectedString << endl;
        return true;
    }
}


void NewAuto::DeActivateField(NewAuto::NewAutoFields Field)
{
    switch (Field)
    {
    case NewAuto::eModel :
    {
        qDebug() << "DeActivate All Field below MODEL ";

        ui->Combo_NewAuto_Model->setCurrentIndex(0);
        ui->Combo_NewAuto_Model->setEnabled(false);

        ui->Combo_NewAuto_Year->setCurrentIndex(0);
        ui->Combo_NewAuto_Year->setEnabled(false);

        ui->Combo_NewAuto_Fuel->setCurrentIndex(0);
        ui->Combo_NewAuto_Fuel->setEnabled(false);

        ui->LText_NewAutoRegNumber->clear();
        ui->LText_NewAutoRegNumber->setEnabled(false);

        ui->LText_NewAutoVIN->clear();
        ui->LText_NewAutoVIN->setEnabled(false);
        break;
    }
    case NewAuto::eYear :
    {
        qDebug() << "DeActivate Field YEAR ";

        ui->Combo_NewAuto_Year->setCurrentIndex(0);
        ui->Combo_NewAuto_Year->setEnabled(false);

        ui->Combo_NewAuto_Fuel->setCurrentIndex(0);
        ui->Combo_NewAuto_Fuel->setEnabled(false);

        ui->LText_NewAutoRegNumber->clear();
        ui->LText_NewAutoRegNumber->setEnabled(false);

        ui->LText_NewAutoVIN->clear();
        ui->LText_NewAutoVIN->setEnabled(false);
        break;
    }
    case NewAuto::eFuel :
    {
        qDebug() << "DeActivate Field FUEL ";

        ui->Combo_NewAuto_Fuel->setCurrentIndex(0);
        ui->Combo_NewAuto_Fuel->setEnabled(false);

        break;
    }
    case NewAuto::eRegNumber :
    {
        qDebug() << "DeActivate Field REG_NUMBER ";
        break;
    }
    case NewAuto::eAutoVin :
    {
        qDebug() << "DeActivate Field VIN ";

        break;
    }
    default:
        qDebug() << "DeActivate UnknownField";
        break;
    }
}


void NewAuto::ActivateField(NewAuto::NewAutoFields Field)
{
    switch (Field)
    {
    case NewAuto::eModel :
    {
        qDebug() << "Activate Field MODEL ";
        ui->Combo_NewAuto_Model->setCurrentIndex(0);
        ui->Combo_NewAuto_Model->setEnabled(true);
        break;
    }
    case NewAuto::eYear :
    {
        qDebug() << "Activate Field YEAR ";
        ui->Combo_NewAuto_Year->setCurrentIndex(0);
        ui->Combo_NewAuto_Year->setEnabled(true);
        break;
    }
    case NewAuto::eFuel :
    {
        qDebug() << "Activate Field FUEL ";
        ui->Combo_NewAuto_Fuel->setCurrentIndex(0);
        ui->Combo_NewAuto_Fuel->setEnabled(true);

        ui->LText_NewAutoRegNumber->clear();
        ui->LText_NewAutoRegNumber->setEnabled(true);

        ui->LText_NewAutoVIN->clear();
        ui->LText_NewAutoVIN->setEnabled(true);

        break;
    }
    case NewAuto::eRegNumber :
    case NewAuto::eAutoVin :
    {
        qDebug() << "Activate Field REG_NUMBER and VIN";
        break;
    }

    default:
        qDebug() << "Activate UnknownField";
        break;
    }
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

void NewAuto::on_Combo_NewAuto_Marka_currentIndexChanged()
{
    if(CheckSelected(ui->Combo_NewAuto_Marka->currentText()))  {
      FillComboModeli();
      ActivateField(NewAuto::eModel);
    }
    else {
        DeActivateField(NewAuto::eModel);
    }
}

void NewAuto::on_Combo_NewAuto_Model_activated()
{
    if(CheckSelected(ui->Combo_NewAuto_Model->currentText()))  {
      ActivateField(NewAuto::eYear);
    }
    else {
        DeActivateField(NewAuto::eYear);
    }
}
