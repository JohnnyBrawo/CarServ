#include "showallcars.h"
#include "ui_showallcars.h"
#include "QDate"
#include "QDateTime"
#include <qdebug.h>
#include "carsdatabase.h"

ShowAllcars::ShowAllcars(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowAllcars),
    m_ComboClientName(""),
    m_ComboRegNumber("")
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
    m_ComboClientName = "";
    m_ComboRegNumber = "";
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
    this->hide();
    emit CloseShowAllAutoForm();
    ClearAllFields();
}


void ShowAllcars::FillClientsNameCombo()
{
    qDebug() << "ShowAllcars::FillClientsNameCombo()   ++++++   ";
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

void ShowAllcars::on_RButton_SearchAutos_clicked()
{
    /*  1 - Autos */
    m_uiSearchChoice = eAutos;
    DeactivateAllFields();
    ui->Combo_SearchAuto->setEnabled(true);
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

        CarsDatabase MyData;
        MyData.OpenConnection("Automobiles.sqlite");
        QSqlQuery EditAutoQry(MyData.CarsDB);



//        m_SelectedRegNumber = arg1;

//        if(m_bComboRegsHit)
//        {
//            MyData.CloseConnection();
//            return;
//        }
//        qDebug() << " eAutoRegs_  arg1  " << arg1 << "  m_bComboClientsHit  " <<m_bComboClientsHit  ;
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
//                if(m_SelectedClientID.isEmpty() ){
//                    qDebug() << "1111111111111111111111111111111111111111 m_bComboClientsHit   " << m_bComboClientsHit;
//                    qDebug() << "1111111111111111111111111111111111111111 m_bComboRegsHit   " << m_bComboRegsHit;
//                    qDebug() << "1111111111111111111111111111111111111111 m_SentClientName   " << m_SentClientName;
//                    qDebug() << "1111111111111111111111111111111111111111 m_SentClientID   " << m_SentClientID;

//                    ui->L_UnkownClients->setVisible(false);
//                    m_SelectedClientID = EditAutoQry.value(1).toString();
//                }

                qDebug() << "1111111111111111111111111111111111111111    " << EditAutoQry.value(2).toString();
                ui->LText_RepairMarka->setText(EditAutoQry.value(2).toString());
                ui->LText_RepairModel->setText(EditAutoQry.value(3).toString());
                ui->LText_RepairYear->setText(EditAutoQry.value(4).toString());
                ui->LText_RepairFuel->setText(EditAutoQry.value(5).toString());
                ui->LText_RepairRegNumber->setText(EditAutoQry.value(6).toString());
                ui->LText_RepairVIN->setText(EditAutoQry.value(7).toString());
                ui->LText_RepairType->setText(EditAutoQry.value(8).toString());

//                /// Record selected AutoID - attach it to the New client
//                m_strAutoReg = EditAutoQry.value(6).toString();
//                ui->Combo_DelChangeAutoRegs->setCurrentText(EditAutoQry.value(6).toString());
            }else {
                /// Fill all automobiles with No cliet assigned
                qDebug() << " Autos Not Found !  ";
//                m_SelectedClientID.clear();
                //            ClearAllFields();
            }
        }

//        // We still have no records for this client - show all unassigned autos
//        if(ui->L_UnkownClients->isVisible())
//        {
//            EditAutoQry.prepare("SELECT * FROM Automobiles_Table WHERE CLIENT_ID='""' ");
//            if(!EditAutoQry.exec()){
//                qDebug() << "EditAutoQry.Exec() unassigned autos Fail "<< EditAutoQry.lastError().text();
//            }else {
//                /// Fill all automobiles with speciffic ClientID or Auto_Reg Number
//                if (EditAutoQry.next()) {
//                    qDebug() << " There are some unassigned autos   " << EditAutoQry.value(6).toString();
//                }
//            }
//        }

        MyData.CloseConnection();

//        if(!m_SelectedClientID.isEmpty() && !m_bComboClientsHit)
//        {
//            ui->Combo_DelChangeClientName->setCurrentIndex(m_SelectedClientID.toInt()-1);
//        }

//        UpdateFlags();
}


void ShowAllcars::on_Button_Search_clicked()
{
    if(m_uiSearchChoice == 0) {
        qDebug() <<"\n  Nothing to search \n";
        return;
    }


    QString strClientID = "";

    switch (static_cast<int>(m_uiSearchChoice) ) {
    case eAutos : {
    qDebug() << "Search Autos   \n";
        break;
    }
    case eClients: {
          CarsDatabase MyClientData;
            MyClientData.OpenConnection("Clients.sqlite");
             QSqlQuery EditClientsQry(MyClientData.CarsDB);

                /** Namireme klienta po ime. Sled koeto mu wzemame CLIENT_ID- to , za da move da go namerim w bazata s kolite ! Ako move da mu izmislq neshto po-umno -> Chudesno*/
             qDebug() << "ui->Combo_Search_Klient->currentText()   " << ui->Combo_Search_Klient->currentText();
                 EditClientsQry.prepare("SELECT * FROM Clients_Table WHERE ClientName='"+ui->Combo_Search_Klient->currentText()+"' ");
                 if(!EditClientsQry.exec()){
                     qDebug() << "SELECT * FROM Clients WHERE ClientName== "<< EditClientsQry.lastError().text();
                 }else {
                     /// Fill all automobiles with speciffic ClientID or Auto_Reg Number
                     if (EditClientsQry.next()) {
                         qDebug() << " Towa sme procheli 1   "<<EditClientsQry.value(1).toString();
                         qDebug() << " Towa sme procheli 0  "<<EditClientsQry.value(0).toString();
                         qDebug() << " Towa sme procheli 2  "<<EditClientsQry.value(2).toString();
                         strClientID = EditClientsQry.value(0).toString();
                     }else {
                         qDebug() << " Nqma kakwo powe4e da prawim , zatwarqme klientskata baza ";
                     }
                 }
                 MyClientData.CloseConnection();
         qDebug() << "Search eClients   \n";
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
     FillAutoData(strClientID);
}

void ShowAllcars::on_Combo_Search_Klient_currentTextChanged(const QString &arg1)
{
    qDebug() << "    on_Combo_Search_Klient_currentTextChanged " <<arg1;
}
