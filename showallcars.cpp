#include "showallcars.h"
#include "ui_showallcars.h"
#include "QDate"
#include "QDateTime"
#include <qdebug.h>
#include <QtWidgets>

ShowAllcars::ShowAllcars(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowAllcars),
    m_ComboClientName(""),
    m_ComboRegNumber(""),
    m_uiRepairIndex(-1)
{
    ui->setupUi(this);
}

ShowAllcars::~ShowAllcars()
{
    delete ui;
}


void ShowAllcars::DeactivateAllFields()
{
//    ui->Combo_SearchAuto->setEnabled(false);
    ui->Combo_Search_Klient->setEnabled(false);
    ui->Combo_Search_RegNumber->setEnabled(false);
    ui->LText_SearchTOdate->setEnabled(false);
    ui->LText_SearchFROMdate->setEnabled(false);
    ui->Button_FromDate->setEnabled(false);
    ui->Button_ToDate->setEnabled(false);
}

bool ShowAllcars::CalculateRepairIndex(bool Upper /** = true */)
{
    if(strRepairVector.size() == 0){
        qDebug()<<" No Repairs ";
        return false;
    }

    if(strRepairVector.size() == 1){
        ui->Button_NextRepair->setEnabled(false);
        ui->Button_PrevRepair->setEnabled(false);
        m_uiRepairIndex = 0;
        qDebug()<<" SINGLE Repair ";
        return true;
    }

    if((m_uiRepairIndex == -1) && strRepairVector.size()>1){
        m_uiRepairIndex = 0;
         ui->Button_PrevRepair->setEnabled(false);
         qDebug()<<" Initial SHOW ";
        return true;
    }

    qDebug()<<" Going UP ";
    if(Upper && (m_uiRepairIndex < strRepairVector.size()-1 ) ){
        m_uiRepairIndex++;
        ui->Button_NextRepair->setEnabled(true);
        ui->Button_PrevRepair->setEnabled(true);
        return true;
    }
    else if(Upper && (m_uiRepairIndex == strRepairVector.size()-1 ) ){
        qDebug()<<" Going UP - No UP Left";
        ui->Button_NextRepair->setEnabled(false);
         return true;
    }


    if(!Upper && (m_uiRepairIndex > 0 )){
        m_uiRepairIndex--;
        ui->Button_PrevRepair->setEnabled(true);
        ui->Button_NextRepair->setEnabled(true);
        return true;
    }
    else if(!Upper && (m_uiRepairIndex == 0 )){
        ui->Button_PrevRepair->setEnabled(false);
         return true;
    }

    return false;
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
    m_ComboClientName = "";
    m_ComboRegNumber = "";
    m_uiRepairIndex = -1;
    strRepairVector.clear();
    m_uiSearchChoice = eNone;
}

void ShowAllcars::OpenClearWindow()
{
     qDebug() << "ShowAllcars::OpenClearWindow() ";
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
    MyData.CloseConnection();
    this->hide();
    emit CloseShowAllAutoForm();
    ClearAllFields();
}


void ShowAllcars::FillClientsNameCombo()
{
    qDebug() << "ShowAllcars::FillClientsNameCombo()   ++++++   ";
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
    MyData.OpenConnection("Automobiles.sqlite");

    QSqlQueryModel * CarsComboModel = new QSqlQueryModel();

    QSqlQuery ShowClientsQry(MyData.CarsDB);
    ShowClientsQry.prepare("SELECT AutoModel FROM Automobiles_Table");

    if(! ShowClientsQry.exec()){
        qDebug() << "ShowClientsQry.Exec() SELECT AutoModel FROM Automobiles_Table fail "<< ShowClientsQry.lastError().text();
    }

    CarsComboModel->setQuery(ShowClientsQry);
//    ui->Combo_SearchAuto->setModel(CarsComboModel);

    MyData.CloseConnection();

}

void ShowAllcars::on_RButton_SearchAutos_clicked()
{
    /*  1 - Autos */
    m_uiSearchChoice = eAutos;
    DeactivateAllFields();
//    ui->Combo_SearchAuto->setEnabled(true);
}

void ShowAllcars::on_RButton_SearchClients_clicked()
{
    /*  2 - Clients */
    m_uiSearchChoice = eClients;
    DeactivateAllFields();
    qDebug()<<" TEXT "  << ui->Combo_Search_Klient->itemData(ui->Combo_Search_Klient->currentIndex());
    ui->Combo_Search_Klient->setEnabled(true);
}

void ShowAllcars::on_RButton_SearchRegNumbers_clicked()
{
    /*  3 - Reg Number */
    m_uiSearchChoice = eRegNumber;
    DeactivateAllFields();
    ui->Combo_Search_RegNumber->setEnabled(true);
}

void ShowAllcars::on_RButton_SearchDate_clicked()
{
    /*  4 - Date */
    m_uiSearchChoice = eDate;
    DeactivateAllFields();
    ui->Button_FromDate->setEnabled(false);
    ui->Button_ToDate->setEnabled(false);
    ui->LText_SearchTOdate->setEnabled(true);
    ui->LText_SearchFROMdate->setEnabled(true);
}

void ShowAllcars::FillAutoData(QString CurrentClientID)
{
    qDebug() << "ShowAllcars::FillAutoData()   ";

        MyData.OpenConnection("Automobiles.sqlite");
        QSqlQuery EditAutoQry(MyData.CarsDB);
        QString m_strAutoReg="";

        switch (m_uiSearchChoice) {
            case eClients: {
                  qDebug() << " Populwame Query-to ot bazata s kolite :  " << CurrentClientID;
                EditAutoQry.prepare("SELECT * FROM Automobiles_Table WHERE CLIENT_ID='"+CurrentClientID+"' ");
                break;
            }
            case eRegNumber : {
                EditAutoQry.prepare("SELECT * FROM Automobiles_Table WHERE Auto_RegNumber='"+ui->Combo_Search_RegNumber->currentText()+"' ");
                break;
            }
            default :{
                break;
            }
        }

//        m_bComboRegsHit = true;
        if(!EditAutoQry.exec()){
            qDebug() << "EditAutoQry.Exec() SELECT Auto_RegNumber FROM Automobiles_Table Fail "<< EditAutoQry.lastError().text();
        }else {
            /// Fill all automobiles with speciffic ClientID or Auto_Reg Number
            if (EditAutoQry.next()) {
                qDebug() << " Show Car's details    ";
                qDebug() << " Index 0     "<<EditAutoQry.value(0).toString();
                qDebug() << " Index 1     "<<EditAutoQry.value(1).toString();
                qDebug() << " Index 2     "<<EditAutoQry.value(2).toString();
                qDebug() << " Index 3     "<<EditAutoQry.value(3).toString();
                qDebug() << " Index 4     "<<EditAutoQry.value(4).toString();
                qDebug() << " Index 5     "<<EditAutoQry.value(5).toString();
                qDebug() << " Index 6     "<<EditAutoQry.value(6).toString();
                qDebug() << " Index 7     "<<EditAutoQry.value(7).toString();
                qDebug() << " Index 8     "<<EditAutoQry.value(8).toString();
                qDebug() << " Index 9     "<<EditAutoQry.value(9).toString();

                ui->LText_RepairRegNumber->setText(EditAutoQry.value(2).toString());
                 ui->LText_RepairMarka->setText(EditAutoQry.value(3).toString());
                ui->LText_RepairModel->setText(EditAutoQry.value(4).toString());
                ui->LText_RepairYear->setText(EditAutoQry.value(5).toString());
                ui->LText_RepairFuel->setText(EditAutoQry.value(6).toString());
                ui->LText_RepairVIN->setText(EditAutoQry.value(7).toString());
                ui->LText_RepairType->setText(EditAutoQry.value(8).toString());

                /// Record selected AutoID - attach it to the New client
                m_strAutoReg = EditAutoQry.value(2).toString();
            }else {
                /// Fill all automobiles with No cliet assigned
                qDebug() << " Autos Not Found !  ";
            }
        }
        MyData.CloseConnection();

        if(!m_strAutoReg.isEmpty()){
            FillRepairsList(m_strAutoReg);
        }
}

void ShowAllcars::FillRepairsList(QString CarRegNumber /*= ""*/)
{
    qDebug()<<" Show all repairs for " << CarRegNumber <<" auto ";
    QString RepairText = "";
    QString RepairData = "";

    MyData.OpenConnection("Repairs.sqlite");
    QSqlQuery EditClientsQry(MyData.CarsDB);

    EditClientsQry.prepare("SELECT * FROM Repair_Table WHERE RepairCarRegNumber='"+CarRegNumber+"' ");
    if(!EditClientsQry.exec()){
        qDebug() << "SELECT RepairName FROM Repair_Table WHERE RepairCarRegNumber== "<< EditClientsQry.lastError().text();
    }
    else {
        while (EditClientsQry.next()) {
            qDebug()<<" RepairData  " << RepairData;
            qDebug()<<" Current Data  " << EditClientsQry.value(6).toString();
            bool ChangeDate = RepairData != EditClientsQry.value(6).toString();

            qDebug()<<" +++++++++++++ ChangeDate  " << ChangeDate;

            if(ChangeDate && !RepairData.isEmpty()){
                qDebug()<<" push_back ";
                strRepairVector.push_back(RepairText);
                RepairText ="";
            }

            if(ChangeDate){
                RepairData = EditClientsQry.value(6).toString();
                RepairText ="Дата :    " + RepairData;
            }

            RepairText += "\n Ремонт : ";
            RepairText += "\n Наименование на ремонта : " + EditClientsQry.value(1).toString();
            RepairText += "\n Брой : " + EditClientsQry.value(2).toString();
            RepairText += "\t Единична Цена : " + EditClientsQry.value(3).toString();
            RepairText += "\t Крайна Цена : " + EditClientsQry.value(4).toString();
            RepairText += "\n Общо Цена на ремонта : " + EditClientsQry.value(5).toString();
            qDebug()<<" RECORD   ";
        }
        qDebug()<<" push_back Last ";
        strRepairVector.push_back(RepairText);
    }

    MyData.CloseConnection();
    qDebug() << "strRepairVector  "<<strRepairVector.size();
    ShowRepairData(true);
}

void ShowAllcars::on_Button_Search_clicked()
{
    if(m_uiSearchChoice == 0) {
        qDebug() <<"\n  Nothing to search \n";
        return;
    }

    /* Erase all data if search button clicked ! Need this is search method is changed */
    ui->RepairsList->clear();
    QString strClientID = "";

    switch (static_cast<int>(m_uiSearchChoice) ) {
    case eAutos : {
    qDebug() << "Search Autos   \n";
        break;
    }
    case eClients: {
//          CarsDatabase MyClientData;
            MyData.OpenConnection("Clients.sqlite");
            QSqlQuery EditClientsQry(MyData.CarsDB);

            /** Namireme klienta po ime. Sled koeto mu wzemame CLIENT_ID- to , za da move da go namerim w bazata s kolite ! Ako move da mu izmislq neshto po-umno -> Chudesno*/
            qDebug() << "ui->Combo_Search_Klient->currentText()   " << ui->Combo_Search_Klient->currentText();
            EditClientsQry.prepare("SELECT * FROM Clients_Table WHERE ClientName='"+ui->Combo_Search_Klient->currentText()+"' ");
            if(!EditClientsQry.exec()){
                qDebug() << "SELECT * FROM Clients WHERE ClientName== "<< EditClientsQry.lastError().text();
            }
            else {
                /// Fill all automobiles with speciffic ClientID or Auto_Reg Number
                if (EditClientsQry.next()) {
                    qDebug() << " Towa sme procheli 1 -  "<<EditClientsQry.value(1).toString();
                    qDebug() << " Towa sme procheli 0 - "<<EditClientsQry.value(0).toString();
                    qDebug() << " Towa sme procheli 2 - "<<EditClientsQry.value(2).toString();
                    strClientID = EditClientsQry.value(0).toString();
                }else {
                    qDebug() << " Nqma kakwo powe4e da prawim , zatwarqme klientskata baza ";
                }
            }
            MyData.CloseConnection();
            qDebug() << "Search By ClentID \n";
            FillAutoData(strClientID);
           break;
    }
    case eRegNumber : {
    qDebug() << "Search RegNumber   \n";
        break;
    }
    case eDate : {
    qDebug() << "Search Date   \n";
        break;
    }
    default :
    {
      qDebug() << "Something is very Wrong !! \n";
      break;
    }
    }

}

void ShowAllcars::ShowRepairData(bool NextRepair )
{
    if(!CalculateRepairIndex(NextRepair)){
         QMessageBox::information(this,"Attention!","No Repairs!");
         return;
    }

    qDebug()<<" Repair index    "<<m_uiRepairIndex;
    QStringList items;
    ui->RepairsList->clear();
    items += strRepairVector.at(m_uiRepairIndex);
    ui->RepairsList->addItems(items);
}

void ShowAllcars::on_Combo_Search_Klient_currentTextChanged(const QString &arg1)
{
    qDebug() << "    on_Combo_Search_Klient_currentTextChanged " <<arg1;
}

void ShowAllcars::on_RButton_SearchAutos_pressed()
{
    qDebug() << " Search button pressed  ";
}

void ShowAllcars::on_Button_NextRepair_clicked()
{
    ShowRepairData(true);
}

void ShowAllcars::on_Button_PrevRepair_clicked()
{
    ShowRepairData(false);
}

void ShowAllcars::on_Button_PRINT_clicked()
{

}
