#include "removechangeauto.h"
#include "ui_removechangeauto.h"
#include <QtWidgets>

RemoveChangeAuto::RemoveChangeAuto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveChangeAuto),
    m_SelectedRegNumber(""),
    m_SelectedClientID(""),
    m_SentClientName(""),
    m_SentClientID("None"),
    m_strAutoReg(""),
    m_bInitialize(true),
    m_bComboClientsHit(false),
    m_bComboRegsHit(false),
    m_bEditFromClients(false)
{
    ui->setupUi(this);
    CenterForm();
    setWindowTitle("Euro Kriss - Edit AUTOS ");

    ui->Combo_DelChangeAutoRegs->setMaxVisibleItems(10);
    ui->Combo_DelChangeAutoRegs->setStyleSheet("combobox-popup: 0;");

    ui->Combo_DelChangeClientName->setMaxVisibleItems(10);
    ui->Combo_DelChangeClientName->setStyleSheet("combobox-popup: 0;");

    ui->m_ComboFuel->setMaxVisibleItems(10);
    ui->m_ComboFuel->setStyleSheet("combobox-popup: 0;");

    ui->m_ComboMarka->setMaxVisibleItems(10);
    ui->m_ComboMarka->setStyleSheet("combobox-popup: 0;");

    ui->m_ComboModel->setMaxVisibleItems(10);
    ui->m_ComboModel->setStyleSheet("combobox-popup: 0;");

    ui->m_ComboType->setMaxVisibleItems(10);
    ui->m_ComboType->setStyleSheet("combobox-popup: 0;");

    ui->m_ComboYear->setMaxVisibleItems(10);
    ui->m_ComboYear->setStyleSheet("combobox-popup: 0;");

}


void RemoveChangeAuto::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-static_cast<int>(width()*0.5), center.y()-static_cast<int>(height()*0.5) );
}

RemoveChangeAuto::~RemoveChangeAuto()
{
    delete ui;
}

void RemoveChangeAuto::SetUnactiveFields()
{
    //  Enable fields one after other
    ui->LText_DelChangeRegNumber->setEnabled(false);
    ui->LText_DelChangeVIN->setEnabled(false);

    ui->Button_Record->setVisible(false);
    ui->Button_DeleteAuto->setVisible(false);
    ui->L_ChangeClientName->setVisible(false);
    ui->Combo_DelChangeClientName->setVisible(false);

    ui->L_ChangeAutoMain->setText("Добавяне на автомобил");
}


void RemoveChangeAuto::ClearAllFields()
{
    qDebug() << "RemoveChangeAuto::ClearAllFields()";

    //  Enable fields one after other
    ui->LText_DelChangeRegNumber->setText("");
    ui->LText_DelChangeVIN->setText("");
    ui->Combo_DelChangeAutoRegs->setCurrentIndex(-1);

    ui->LText_ClientName->setVisible(false);
    ui->L_LineClientName->setVisible(false);
    ui->L_UnkownClients->setVisible(false);


    ui->m_ComboFuel->setCurrentIndex(0);
    ui->m_ComboFuel->setEnabled(false);

    ui->m_ComboMarka->setCurrentIndex(0);
    ui->m_ComboMarka->setEnabled(false);

    ui->m_ComboModel->setCurrentIndex(0);
    ui->m_ComboModel->setEnabled(false);

    ui->m_ComboType->setCurrentIndex(0);
    ui->m_ComboType->setEnabled(false);

    ui->m_ComboYear->setCurrentIndex(0);
    ui->m_ComboYear->setEnabled(false);

    m_SelectedRegNumber.clear();
    m_SelectedClientID.clear();
    m_SentClientName.clear();
    m_SentClientID.clear();

    m_bComboClientsHit = false;
    m_bComboRegsHit = false;
    m_bEditFromClients = false;
}


void RemoveChangeAuto::AddAutoToClient(QString ClientName, QString ClientEditID)
{
    qDebug() << "RemoveChangeAuto::AddAutoToClient()   ";
    m_bInitialize = true;
    ClearAllFields();

    qDebug() << " AddAutoToClient  ClientName   " << ClientName << "   ClientEditID    " << ClientEditID;
    m_SentClientName = ClientName;
    m_SentClientID = ClientEditID;
    ui->Combo_DelChangeClientName->setVisible(false);
    ui->L_ChangeClientName->setVisible(false);
    ui->LText_ClientName->setVisible(true);
    ui->L_UnkownClients->setVisible(false);

    m_bEditFromClients = true;
    ui->Button_Add->setVisible(false);
    //    FillPage();
    FillRegCombo();

    m_bInitialize = false;
    ui->LText_ClientName->setText(ClientName);
    ui->LText_ClientName->setEnabled(false);
    show();
}

void RemoveChangeAuto::OpenClearEditWindow()
{
    m_bInitialize = true;
    ClearAllFields();
    show();
    ui->Button_Add->setVisible(false);
    FillPage();
    m_bInitialize = false;
}

void RemoveChangeAuto::OpenClearWindow()
{
    m_bInitialize = true;
    show();
    ClearAllFields();
    FillPage();
    SetUnactiveFields();
    m_bInitialize = false;
}


void RemoveChangeAuto::FillPage()
{
    FillClientNameCombo();
    FillRegCombo();
}

void RemoveChangeAuto::FillRegCombo()
{
    MyData.OpenConnection("Automobiles.sqlite");
    QSqlQueryModel * MyModel = new QSqlQueryModel();
    QSqlQuery RegComboQry(MyData.CarsDB);

    if(m_SentClientName.isEmpty())
    {
        RegComboQry.prepare("SELECT Auto_RegNumber FROM Automobiles_Table ");
    }else {
        RegComboQry.prepare("SELECT Auto_RegNumber FROM Automobiles_Table WHERE CLIENT_ID='"+m_SentClientID+"'");
    }

    if(! RegComboQry.exec()){
        qDebug() << "EditAutoQry.Exec() SELECT Auto_RegNumber FROM Automobiles_Table Fail ";
        return;
    }

    if(!RegComboQry.next())
    {
        // Тука зареждаме празните атомобили.
        RegComboQry.prepare("SELECT Auto_RegNumber FROM Automobiles_Table WHERE CLIENT_ID='""'");
        if(! RegComboQry.exec()){
            return;
        }
        if(!RegComboQry.next())
        {
            qDebug() << "Nqma neregistrirani awtomobili !!!  ";
        }
    }else {
        qDebug() << "  FillRegCombo Sent Client ID  ->  "<< RegComboQry.value(0).toString();
    }

    MyModel->setQuery(RegComboQry);
    ui->Combo_DelChangeAutoRegs->setModel(MyModel);


    MyData.CloseConnection();
}

void RemoveChangeAuto::FillClientNameCombo()
{
    MyData.OpenConnection("Clients.sqlite");
    QSqlQueryModel * MyModel = new QSqlQueryModel();
    QSqlQuery ClientComboQry(MyData.CarsDB);

    ClientComboQry.prepare("SELECT ClientName FROM Clients_Table ");

    if(! ClientComboQry.exec()){
        qDebug() << "ClientComboQry.Exec() SELECT ClientName FROM Clients_Table Fail ";
    }

    if(! ClientComboQry.exec()){
        qDebug() << "ClientComboQry.Exec() SELECT ClientName FROM Clients_Table Fail ";
    }

    MyModel->setQuery(ClientComboQry);
    ui->Combo_DelChangeClientName->setModel(MyModel);
    MyData.CloseConnection();
}


void RemoveChangeAuto::ShowAllFieldsText()
{
    qDebug() << " ui->LText_DelChangeRegNumber->text "  << ui->LText_DelChangeRegNumber->text();
    qDebug() << " ui->LText_DelChangeVIN->text "  << ui->LText_DelChangeVIN->text();
}

void RemoveChangeAuto::on_Button_Record_clicked()
{
//    MyData.OpenConnection("Automobiles.sqlite");

    /** Towa e qko typo , obache trqbwa da ima kontrol na dannite predi da se zapishat. Inache nqma hwashtane */
//    QString RegNumber = CheckField(ui->LText_DelChangeRegNumber->text())?ui->LText_DelChangeRegNumber->text():"None";
//    QString Vin = CheckField(ui->LText_DelChangeVIN->text())?ui->LText_DelChangeVIN->text():"None";
   //@ TODO - make this from combo boxes selection
//    QSqlQuery AddNewAuto(MyData.CarsDB);
   // AddNewAuto.prepare("UPDATE Automobiles_Table set Auto_RegNumber='"+RegNumber+"',Auto_Marka='"+Marka+"', Auto_Model='"+Model+"', Auto_Year='"+Year+"', Auto_Fuel='"+Fuel+"',  Auto_VIN='"+Vin+"', Auto_Type='"+Type+"' WHERE Auto_RegNumber='"+m_SelectedRegNumber+"' ");

//    if(!AddNewAuto.exec()){
//        qDebug() << "UPDATE Automobiles_Table fail ";
//    }

    // Update Current Changes
//    m_SelectedRegNumber = ui->LText_DelChangeRegNumber->text();
//    MyData.CloseConnection();
    ClearAllFields();
    FillPage();
}

void RemoveChangeAuto::on_Button_DeleteAuto_clicked()
{
    MyData.OpenConnection("Automobiles.sqlite");

    QSqlQuery AddNewAuto(MyData.CarsDB);
    AddNewAuto.prepare("DELETE FROM Automobiles_Table WHERE Auto_RegNumber='"+m_SelectedRegNumber+"' ");

    QMessageBox::StandardButton UserReply;
    UserReply =  QMessageBox::question(this,"Attention ! ", "Atomobile with registration  : \n " + ui->LText_DelChangeRegNumber->text() + " \n will be deleted!! \n Continue ?",QMessageBox::Yes | QMessageBox::No);
    if(UserReply == QMessageBox::Yes){
        if(!AddNewAuto.exec()){
            qDebug() << "DELETE FROM Automobiles_Table WHERE Auto_RegNumber FAIL ";
        }

        // Update Current Changes
        m_SelectedRegNumber = ui->LText_DelChangeRegNumber->text();
        MyData.CloseConnection();
        ClearAllFields();
        FillPage();
    }
}

void RemoveChangeAuto::on_Button_Add_clicked()
{
    hide();
    emit CloseDeletePage();
}


void RemoveChangeAuto::on_Button_Back_clicked()
{
    m_strAutoReg = "None";
    m_SelectedClientID="";
    m_SelectedRegNumber="";
    hide();
    emit CloseDeletePage();
}

void RemoveChangeAuto::on_Combo_DelChangeClientName_currentIndexChanged(QString)
{
    if((!m_bInitialize || m_SentClientName.isEmpty()) && !m_bComboRegsHit)
    {
        m_bComboClientsHit = true;
        on_Combo_DelChangeAutoRegs_currentIndexChanged(QString::number(ui->Combo_DelChangeClientName->currentIndex()+1));
    }
}


void RemoveChangeAuto::on_Combo_DelChangeAutoRegs_currentIndexChanged(const QString &arg1)
{
    if(m_bInitialize){
        return;
    }

    MyData.OpenConnection("Automobiles.sqlite");
    QSqlQuery EditAutoQry(MyData.CarsDB);

    m_SelectedRegNumber = arg1;

    if(m_bComboRegsHit)
    {
        MyData.CloseConnection();
        return;
    }

//    if( m_bComboClientsHit)
//    {
//        EditAutoQry.prepare("SELECT * FROM Automobiles_Table WHERE CLIENT_ID='""' ");
//    }else {
        EditAutoQry.prepare("SELECT * FROM Automobiles_Table WHERE Auto_RegNumber='"+arg1+"' ");
//    }

    m_bComboRegsHit = true;
    if(!EditAutoQry.exec()){
        qDebug() << "EditAutoQry.Exec() SELECT Auto_RegNumber FROM Automobiles_Table Fail "<< EditAutoQry.lastError().text();
    }else {
        /// Fill all automobiles with speciffic ClientID or Auto_Reg Number
        if (EditAutoQry.next()) {
            qDebug() << " Value(0) "<<EditAutoQry.value(0).toString();
             qDebug() << " Value(1) "<<EditAutoQry.value(1).toString();
             qDebug() << " Value(2) "<<EditAutoQry.value(2).toString();
             qDebug() << " Value(3) "<<EditAutoQry.value(3).toString();
             qDebug() << " Value(4) "<<EditAutoQry.value(4).toString();

            if(m_SelectedClientID.isEmpty() ){
                ui->L_UnkownClients->setVisible(false);
                m_SelectedClientID = EditAutoQry.value(1).toString();
            }

//            ui->m_ComboFuel->find

//            ui->LText_DelChangeRegNumber->setText(EditAutoQry.value(2).toString());
//            ui->LText_DelChangeMarka->setText(EditAutoQry.value(3).toString());
//            ui->LText_DelChangeModel->setText(EditAutoQry.value(4).toString());
//            ui->LText_DelChangeType->setText(EditAutoQry.value(8).toString());
//            ui->LText_DelChangeYear->setText(EditAutoQry.value(5).toString());
//            ui->LText_DelChangeFuel->setText(EditAutoQry.value(6).toString());
//            ui->LText_DelChangeVIN->setText(EditAutoQry.value(7).toString());

            /// Record selected AutoID - attach it to the New client
//            m_strAutoReg = EditAutoQry.value(2).toString();
//            ui->Combo_DelChangeAutoRegs->setCurrentText(EditAutoQry.value(6).toString()); // ?? Why, we select it !
        }else {
            /// Fill all automobiles with No cliet assigned
            qDebug() << " Autos Not Found !  ";
            m_SelectedClientID.clear();
            ClearAllFields();
        }
    }

    // We still have no records for this client - show all unassigned autos
    if(ui->L_UnkownClients->isVisible())
    {
        EditAutoQry.prepare("SELECT * FROM Automobiles_Table WHERE CLIENT_ID='""' ");
        if(!EditAutoQry.exec()){
            qDebug() << "EditAutoQry.Exec() unassigned autos Fail "<< EditAutoQry.lastError().text();
        }else {
            /// Fill all automobiles with speciffic ClientID or Auto_Reg Number
            if (EditAutoQry.next()) {
                qDebug() << " There are some unassigned autos   " << EditAutoQry.value(6).toString();
            }
        }
    }

    MyData.CloseConnection();

    if(!m_SelectedClientID.isEmpty() && !m_bComboClientsHit)
    {
        ui->Combo_DelChangeClientName->setCurrentIndex(m_SelectedClientID.toInt()-1);
    }

    UpdateFlags();
}


void RemoveChangeAuto::UpdateFlags()
{
    m_bComboClientsHit = false;
    m_bComboRegsHit = false;
    m_SelectedClientID.clear();
}

bool RemoveChangeAuto::CheckField(QString SelectedString)
{
    if(( static_cast<int>(SelectedString.size()) < 2 ) || (SelectedString == "Select") || SelectedString == "")
    {
        qDebug() << "RemoveChangeAuto::CheckField  FAIL SelectedString " << SelectedString;
        return false;
    }
    return true;
}
