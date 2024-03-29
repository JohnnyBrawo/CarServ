﻿#include "searchform.h"
#include "ui_searchform.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include "QDate"
#include "QDateTime"
#include <qdebug.h>
#include <QKeyEvent>

SearchForm::SearchForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchForm)
{
    ui->setupUi(this);
    setWindowTitle("Search");
    CenterForm();
}

SearchForm::~SearchForm()
{
    delete ui;
}

void SearchForm::OpenClearWindow()
{
//    qDebug() << " SearchForm::OpenClearWindow() ENTER  ";
    ui->Combo_SearchAuto->setCurrentIndex(0);
    ui->Combo_Search_Klient->setCurrentIndex(0);
    ui->Combo_Search_RegNumber->setCurrentIndex(0);

    ui->Combo_SearchAuto->setMaxVisibleItems(10);
    ui->Combo_SearchAuto->setStyleSheet("combobox-popup: 0;");

    ui->Combo_Search_Klient->setMaxVisibleItems(10);
    ui->Combo_Search_Klient->setStyleSheet("combobox-popup: 0;");

    ui->Combo_Search_RegNumber->setMaxVisibleItems(10);
    ui->Combo_Search_RegNumber->setStyleSheet("combobox-popup: 0;");

    QDate CurrentDate= QDate::currentDate();

    ui->LText_SearchFROMdate->setText(CurrentDate.toString("dd.MM.yyyy"));
    ui->LText_SearchTOdate->setText(CurrentDate.toString("dd.MM.yyyy"));

    FillClientsNameCombo();
    FillRegNumbersCombo();
    FillAutosCombo();
    DeactivateAllFields();

    this->show();
}


void SearchForm::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
            on_Button_Search_Back_clicked();
    }
    else{
            QDialog::keyPressEvent(event);
    }
}

void SearchForm::FillClientsNameCombo()
{
//    qDebug() << "SearchForm::FillClientsNameCombo()   ";
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


void SearchForm::FillRegNumbersCombo()
{
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


void SearchForm::FillAutosCombo()
{
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


void SearchForm::DeactivateAllFields()
{
    ui->Combo_SearchAuto->setEnabled(false);
    ui->Combo_Search_Klient->setEnabled(false);
    ui->Combo_Search_RegNumber->setEnabled(false);
    ui->LText_SearchTOdate->setEnabled(false);
    ui->LText_SearchFROMdate->setEnabled(false);
}

void SearchForm::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-static_cast<int>(width()*0.5), center.y()-static_cast<int>(height()*0.5));
}

void SearchForm::on_Button_Search_Back_clicked()
{
    emit CloseSearchForm();
    hide();
}

void SearchForm::on_RButton_SearchAutos_clicked()
{
    DeactivateAllFields();
    ui->Combo_SearchAuto->setEnabled(true);
//    ui->Combo_SearchAuto->setMaxVisibleItems(10);
//    ui->Combo_SearchAuto->setStyleSheet("combobox-popup: 0;");
}

void SearchForm::on_RButton_SearchClients_clicked()
{
    DeactivateAllFields();
    ui->Combo_Search_Klient->setEnabled(true);
//    ui->Combo_Search_Klient->setMaxVisibleItems(10);
//    ui->Combo_Search_Klient->setStyleSheet("combobox-popup: 0;");
}

void SearchForm::on_RButton_SearchRegNumbers_clicked()
{
    DeactivateAllFields();
    ui->Combo_Search_RegNumber->setEnabled(true);
}

void SearchForm::on_RButton_SearchDate_clicked()
{
    DeactivateAllFields();
    ui->LText_SearchTOdate->setEnabled(true);
    ui->LText_SearchFROMdate->setEnabled(true);
}
