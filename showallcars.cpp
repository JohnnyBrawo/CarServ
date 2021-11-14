#include "showallcars.h"
#include "ui_showallcars.h"
#include <QKeyEvent>
#include "QDate"
#include "QDateTime"
#include <qdebug.h>
#include <QtWidgets>

ShowAllcars::ShowAllcars(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowAllcars),
    m_Print(new PrintFormat()),
    m_ComboClientName(""),
    m_ComboRegNumber(""),
    m_uiRepairIndex(-1)
{
    ui->setupUi(this);
    CenterForm();
    QObject::connect(m_Print, SIGNAL(ClosePrintForm()), this, SLOT(OpenClearWindow()));
    QObject::connect(ui->Button_PRINT, SIGNAL(clicked()), m_Print, SLOT(OpenPrintForm()));
}

ShowAllcars::~ShowAllcars()
{
    delete ui;
}


void ShowAllcars::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
            on_Button_Back_clicked();
    }
    else{
            QDialog::keyPressEvent(event);
    }
}


void ShowAllcars::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-static_cast<int>(width()*0.5), center.y()-static_cast<int>(height()*0.5) );
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
    ui->RButton_SearchDate->setEnabled(false);
    ui->RButton_SearchClients->setChecked(false);
    ui->RButton_SearchRegNumbers->setChecked(false);

    ui->Button_NextRepair->setEnabled(false);

    ui->Button_PrevRepair->setEnabled(false);

    m_uiRepairIndex = -1;
}

bool ShowAllcars::CalculateRepairIndex(bool Upper /** = true */)
{
    if(strRepairVector.size() == 0){
        return false;
    }

    if(m_uiRepairIndex ==0 && !Upper){
         if(strRepairVector.size() >1){
             ui->Button_NextRepair->setEnabled(true);
         }

        ui->Button_PrevRepair->setEnabled(false);
        return true;
    }

    if(strRepairVector.size() == 1){
        ui->Button_NextRepair->setEnabled(false);
        ui->Button_PrevRepair->setEnabled(false);
        m_uiRepairIndex = 0;
        return true;
    }

    if((m_uiRepairIndex == -1) && strRepairVector.size()>1){
        m_uiRepairIndex = 0;
         ui->Button_PrevRepair->setEnabled(false);
        return true;
    }

    if(Upper && (m_uiRepairIndex < strRepairVector.size()-1 ) ){
        m_uiRepairIndex++;
        ui->Button_NextRepair->setEnabled(true);
        ui->Button_PrevRepair->setEnabled(true);
        if(m_uiRepairIndex == strRepairVector.size()-1 ){
            ui->Button_NextRepair->setEnabled(false);
             return true;
        }
        return true;
    }

    if(!Upper && (m_uiRepairIndex > 0 )){
        m_uiRepairIndex--;
        ui->Button_PrevRepair->setEnabled(true);
        ui->Button_NextRepair->setEnabled(true);
        if(m_uiRepairIndex == 0 ){
                ui->Button_PrevRepair->setEnabled(false);
                return true;
        }
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
    ui->RepairsList->clear();
    m_ComboClientName = "";
    m_ComboRegNumber = "";
    m_uiRepairIndex = -1;
    strRepairVector.clear();
    m_uiSearchChoice = eNone;
}

void ShowAllcars::OpenClearWindow()
{
     qDebug() << "  ShowAllcars::OpenClearWindow()";
    if(m_Print->GetPrintStatus()){
        m_Print->ResetPrintStatus();
        on_Button_Back_clicked();
        qDebug() << "  ShowAllcars::OpenClearWindow() return ";
        return;
    }

    QDate CurrentDate= QDate::currentDate();
    ui->LText_SearchFROMdate->setText(CurrentDate.toString("dd.MM.yyyy"));
    ui->LText_SearchTOdate->setText(CurrentDate.toString("dd.MM.yyyy"));

    FillClientsNameCombo();
    FillRegNumbersCombo();
    ClearAllFields();
    DeactivateAllFields();
    this->show();
}

void ShowAllcars::on_Button_Back_clicked()
{
    ClearAllFields();
    DeactivateAllFields();
    MyData.CloseConnection();
    this->hide();
    emit CloseShowAllAutoForm();

}


void ShowAllcars::FillClientsNameCombo()
{
    MyData.OpenConnection("Clients.sqlite");

    QSqlQueryModel * ClientsNameComboModel = new QSqlQueryModel();

    QSqlQuery ShowClientsQry(MyData.CarsDB);
    ShowClientsQry.prepare("SELECT ClientName FROM Clients_Table");

    if(! ShowClientsQry.exec()){
        qDebug() << "ShowClientsQry.Exec() SELECT ClientName FROM Clients_Table fail "<< ShowClientsQry.lastError().text();
    }

    ClientsNameComboModel->setQuery(ShowClientsQry);
    ui->Combo_Search_Klient->setModel(ClientsNameComboModel);
    ui->Combo_Search_Klient->setMaxVisibleItems(10);
    ui->Combo_Search_Klient->setStyleSheet("combobox-popup: 0;");

    MyData.CloseConnection();
}


void ShowAllcars::FillRegNumbersCombo()
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
    ui->Combo_Search_RegNumber->setMaxVisibleItems(10);
    ui->Combo_Search_RegNumber->setStyleSheet("combobox-popup: 0;");

    MyData.CloseConnection();

}


void ShowAllcars::FillAutosCombo()
{
    MyData.OpenConnection("Automobiles.sqlite");

    QSqlQueryModel * CarsComboModel = new QSqlQueryModel();

    QSqlQuery ShowClientsQry(MyData.CarsDB);
    ShowClientsQry.prepare("SELECT AutoModel FROM Automobiles_Table");

    if(! ShowClientsQry.exec()){
        qDebug() << "ShowClientsQry.Exec() SELECT AutoModel FROM Automobiles_Table fail "<< ShowClientsQry.lastError().text();
    }

    CarsComboModel->setQuery(ShowClientsQry);
    MyData.CloseConnection();

}


void ShowAllcars::on_RButton_SearchClients_clicked()
{
    /*  2 - Clients */
    m_uiSearchChoice = eClients;
    DeactivateAllFields();
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
    // @ TODO - Do it later . It must be done, after all !!
    /*  4 - Date */
//    m_uiSearchChoice = eDate;
//    DeactivateAllFields();
//    ui->Button_FromDate->setEnabled(false);
//    ui->Button_ToDate->setEnabled(false);
//    ui->LText_SearchTOdate->setEnabled(true);
//    ui->LText_SearchFROMdate->setEnabled(true);

}

void ShowAllcars::FillAutoData()
{
    MyData.OpenConnection("Automobiles.sqlite");
    QSqlQuery EditAutoQry(MyData.CarsDB);
        QString m_strAutoReg="";

        switch (m_uiSearchChoice) {
            case eClients: {
                EditAutoQry.prepare("SELECT * FROM Automobiles_Table WHERE CLIENT_ID='"+m_ClientDB_ID+"' ");
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

        if(!EditAutoQry.exec()){
            qDebug() << "EditAutoQry.Exec() SELECT Auto_RegNumber FROM Automobiles_Table Fail "<< EditAutoQry.lastError().text();
        }else {
            /// Fill all automobiles with speciffic ClientID or Auto_Reg Number
            if (EditAutoQry.next()) {
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
            m_ComboRegNumber = m_strAutoReg;
            FillRepairsList();

        }
}

void ShowAllcars::FillRepairsList()
{
    m_bTaxesIncluded = false;
    m_dTotalPrice = 0.0;

    QString RepairText = "";
    QString RepairData = "";

    unsigned short RepairsCount = 0;

    MyData.OpenConnection("Repairs.sqlite");
    QSqlQuery EditClientsQry(MyData.CarsDB);

    EditClientsQry.prepare("SELECT * FROM Repair_Table WHERE RepairCarRegNumber='"+m_ComboRegNumber+"' ");
    if(!EditClientsQry.exec()){
        qDebug() << "SELECT RepairName FROM Repair_Table WHERE RepairCarRegNumber== "<< EditClientsQry.lastError().text();
    }
    else {
        while (EditClientsQry.next()) {
            bool ChangeDate = RepairData != EditClientsQry.value(6).toString();

            if(ChangeDate && !RepairData.isEmpty()){
                strRepairVector.push_back(RepairText);
                RepairText ="";
            }

            if(ChangeDate){
                RepairData = EditClientsQry.value(6).toString();
                RepairText ="Date : \n" + RepairData;
            }

            RepairText += "\nRepair name: " + EditClientsQry.value(1).toString();
            RepairText += "\n   Repair cout : " + EditClientsQry.value(2).toString();
            RepairText += "   Single Price : " + EditClientsQry.value(3).toString();
            RepairText += "   Final Price : " + EditClientsQry.value(4).toString();
//            RepairText += "   Total Price : " + EditClientsQry.value(5).toString();
            m_dTotalPrice += EditClientsQry.value(4).toDouble();

            if(EditClientsQry.value(8).toString()=="1"){
                RepairText += "\t Taxes included! ";
                m_bTaxesIncluded = true;
            }

            RepairsCount++;
            if((RepairsCount+1) % 15 == 0){
                strRepairVectorPages.push_back(RepairText);
                RepairText="";
                qDebug() << " Show this page ... more waiting .. ";
            }
            RepairText += "\n===================";

        }

        if(RepairText.isEmpty()){
            qDebug() <<"\n  Nothing to show \n";
        }
        else {
            RepairText +="\n   Total Price : " +  QString::number(m_dTotalPrice);
            RepairText += "\n--------------------------------------------------------------";
            if(RepairsCount > 15)
            {
                 strRepairVectorPages.push_back(RepairText);
            }
            strRepairVector.push_back(RepairText);
        }
    }
    MyData.CloseConnection();
    ShowRepairData();
}

void ShowAllcars::on_Button_Search_clicked()
{
    if(m_uiSearchChoice == 0) {
        qDebug() <<"\n  Nothing to search \n";
        return;
    }

    RepairPages = 0;
    m_ComboClientName = ui->Combo_Search_Klient->currentText();
    /* Erase all data if search button clicked ! Need this is search method is changed */
    ui->RepairsList->clear();
    strRepairVector.clear();
    strRepairVectorPages.clear();

    m_ClientDB_ID.clear();
    m_uiRepairIndex = 0;
    switch (static_cast<int>(m_uiSearchChoice) ) {
    case eAutos : {
        break;
    }
    case eClients: {
            MyData.OpenConnection("Clients.sqlite");
            QSqlQuery EditClientsQry(MyData.CarsDB);

            /** Namireme klienta po ime. Sled koeto mu wzemame CLIENT_ID- to , za da move da go namerim w bazata s kolite ! Ako move da mu izmislq neshto po-umno -> Chudesno*/
            EditClientsQry.prepare("SELECT * FROM Clients_Table WHERE ClientName='"+ui->Combo_Search_Klient->currentText()+"' ");
            if(!EditClientsQry.exec()){
                qDebug() << "SELECT * FROM Clients WHERE ClientName== "<< EditClientsQry.lastError().text();
            }
            else {
                /// Fill all automobiles with speciffic ClientID or Auto_Reg Number
                if (EditClientsQry.next()) {
                    m_ClientDB_ID = EditClientsQry.value(0).toString();
                }
            }
            MyData.CloseConnection();
            FillAutoData();
           break;
    }
    case eRegNumber : {
        MyData.OpenConnection("Automobiles.sqlite");
        QSqlQuery EditClientsQry(MyData.CarsDB);

        /** Namireme klienta po ime. Sled koeto mu wzemame CLIENT_ID- to , za da move da go namerim w bazata s kolite ! Ako move da mu izmislq neshto po-umno -> Chudesno*/
        EditClientsQry.prepare("SELECT * FROM Automobiles_Table WHERE Auto_RegNumber='"+ui->Combo_Search_RegNumber->currentText()+"' ");
        if(!EditClientsQry.exec()){
            qDebug() << " on_Button_Search_clicked REG_NUMBER QUery failed "<< EditClientsQry.lastError().text();
        }
        else {
            /// Fill all automobiles with speciffic ClientID or Auto_Reg Number
            if (EditClientsQry.next()) {
                m_ClientDB_ID = EditClientsQry.value(0).toString();
            }
        }
        MyData.CloseConnection();
        FillAutoData();
       break;
    }
    case eDate : {
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

    QStringList items;
    ui->RepairsList->clear();
     qDebug() << "ShowRepairData "<<strRepairVector.size();
     qDebug() << "ShowRepairData "<<strRepairVectorPages.size();
    if(!strRepairVectorPages.isEmpty()){
       for(int i=0;i<strRepairVectorPages.size(); i++){
           items += strRepairVectorPages.at(i);
       }
    }
    else {
        items += strRepairVector.at(m_uiRepairIndex);
    }
    ui->RepairsList->addItems(items);
}

void ShowAllcars::on_Combo_Search_Klient_currentTextChanged(const QString &arg1)
{
    m_ComboClientName = arg1;
    m_uiRepairIndex = 0;
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
    MyData.CloseConnection();

    if(!strRepairVectorPages.isEmpty()){
         m_Print->SetRepairsPagesText(strRepairVectorPages);
    }
    else
    {
         m_Print->SetRepairsText(strRepairVector.at(m_uiRepairIndex));
    }
    m_Print->SetRegNum(m_ComboRegNumber);
    m_Print->SetClientID(m_ClientDB_ID);
    m_Print->SetClientName(m_ComboClientName);
    m_Print->SetRepairCost(m_dTotalPrice, m_bTaxesIncluded);

    this->hide();
}

QString ShowAllcars::RepairText(){
    return strRepairVector.at(m_uiRepairIndex);
}
