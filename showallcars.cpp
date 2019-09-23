#include "showallcars.h"
#include "ui_showallcars.h"
#include "QDate"
#include "QDateTime"
#include <qdebug.h>
#include "carsdatabase.h"

ShowAllcars::ShowAllcars(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowAllcars)
{
    ui->setupUi(this);

}

ShowAllcars::~ShowAllcars()
{
    delete ui;
}


void ShowAllcars::DeactivateAllFields()
{
    ui->Combo_SearchAuto->setEnabled(false);
    ui->Combo_Search_Klient->setEnabled(false);
    ui->Combo_Search_RegNumber->setEnabled(false);
    ui->LText_SearchTOdate->setEnabled(false);
    ui->LText_SearchFROMdate->setEnabled(false);
    ui->Button_FromDate->setEnabled(false);
    ui->Button_ToDate->setEnabled(false);
}

void ShowAllcars::ClearAllFields()
{
    ui->LText_RepairFuel->setText("");
    ui->LText_RepairMarka->setText("");
    ui->LText_RepairModel->setText("");
    ui->LText_RepairRegNumber->setText("");
    ui->LText_RepairType->setText("");
    ui->LText_RepairVIN->setText("");
    ui->LText_RepairYear->setText("");
}

void ShowAllcars::OpenClearWindow()
{
    ClearAllFields();
    QDate CurrentDate= QDate::currentDate();

    ui->LText_SearchFROMdate->setText(CurrentDate.toString("dd.MM.yyyy"));
    ui->LText_SearchTOdate->setText(CurrentDate.toString("dd.MM.yyyy"));

    FillClientsNameCombo();
    FillRegNumbersCombo();
    DeactivateAllFields();
    this->show();
}

void ShowAllcars::on_Button_Back_clicked()
{
    this->hide();
    emit CloseShowAllAutoForm();
    ClearAllFields();
}


void ShowAllcars::FillClientsNameCombo()
{
    qDebug() << "ShowAllcars::FillClientsNameCombo()   ";
    CarsDatabase MyData;
    MyData.OpenConnection("Clients.sqlite");

    QSqlQueryModel * ClientsNameComboModel = new QSqlQueryModel();

    QSqlQuery ShowClientsQry(MyData.CarsDB);
    ShowClientsQry.prepare("SELECT ClientName FROM Clients_Table");

    if(! ShowClientsQry.exec()){
        qDebug() << "ShowClientsQry.Exec() SELECT ClientName FROM Clients_Table fail "<< ShowClientsQry.lastError().text();
    }

    ClientsNameComboModel->setQuery(ShowClientsQry);
    ui->Combo_Search_Klient->setModel(ClientsNameComboModel);

    MyData.CloseConnection();
}


void ShowAllcars::FillRegNumbersCombo()
{
    qDebug() << "ShowAllcars::FillRegNumbersCombo()   ";
    CarsDatabase MyData;
    MyData.OpenConnection("Automobiles.sqlite");

    QSqlQueryModel * CarRegNumberComboModel = new QSqlQueryModel();

    QSqlQuery ShowClientsQry(MyData.CarsDB);
    ShowClientsQry.prepare("SELECT Auto_RegNumber FROM Automobiles_Table");

    if(! ShowClientsQry.exec()){
        qDebug() << "ShowClientsQry.Exec() SELECT Auto_RegNumber FROM Automobiles_Table fail "<< ShowClientsQry.lastError().text();
    }

    CarRegNumberComboModel->setQuery(ShowClientsQry);
    ui->Combo_Search_RegNumber->setModel(CarRegNumberComboModel);

    MyData.CloseConnection();

}


void ShowAllcars::FillAutosCombo()
{
    qDebug() << "SearchForm::FillRegNumbersCombo()   ";
    CarsDatabase MyData;
    MyData.OpenConnection("Automobiles.sqlite");

    QSqlQueryModel * CarsComboModel = new QSqlQueryModel();

    QSqlQuery ShowClientsQry(MyData.CarsDB);
    ShowClientsQry.prepare("SELECT AutoModel FROM Automobiles_Table");

    if(! ShowClientsQry.exec()){
        qDebug() << "ShowClientsQry.Exec() SELECT AutoModel FROM Automobiles_Table fail "<< ShowClientsQry.lastError().text();
    }

    CarsComboModel->setQuery(ShowClientsQry);
    ui->Combo_SearchAuto->setModel(CarsComboModel);

    MyData.CloseConnection();

}


void ShowAllcars::on_RButton_SearchRegNumbers_clicked()
{
    DeactivateAllFields();
    ui->Combo_Search_RegNumber->setEnabled(true);
}

void ShowAllcars::on_RButton_SearchClients_clicked()
{
    DeactivateAllFields();
    ui->Combo_Search_Klient->setEnabled(true);
}

void ShowAllcars::on_RButton_SearchAutos_clicked()
{
    DeactivateAllFields();
    ui->Combo_SearchAuto->setEnabled(true);
}

void ShowAllcars::on_RButton_SearchDate_clicked()
{
    DeactivateAllFields();
    ui->Button_FromDate->setEnabled(false);
    ui->Button_ToDate->setEnabled(false);
    ui->LText_SearchTOdate->setEnabled(true);
    ui->LText_SearchFROMdate->setEnabled(true);
}
