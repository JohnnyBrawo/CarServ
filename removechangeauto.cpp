#include "removechangeauto.h"
#include "ui_removechangeauto.h"
#include <QtWidgets>
#include <QKeyEvent>

RemoveChangeAuto::RemoveChangeAuto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveChangeAuto),
    m_SelectedRegNumber(""),
    m_SelectedClientID(""),
    m_SentClientName(""),
    m_SentClientID(""),
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

    ui->Combo_ClientName->setMaxVisibleItems(10);
    ui->Combo_ClientName->setStyleSheet("combobox-popup: 0;");

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
    m_State = eNormalMode;
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


void RemoveChangeAuto::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
            on_Button_Back_clicked();
    }
    else{
            QDialog::keyPressEvent(event);
    }
}

void RemoveChangeAuto::SetFieldsClientWithNoAuto()
{
    ActivateAutoCombos(false);
    ClearAllFields();
    ui->Button_DeleteAuto->setVisible(false);

//    qDebug() << "RemoveChangeAuto::SetFieldsClientWithNoAuto()   ";
}


void RemoveChangeAuto::SetUnactiveFields()
{
        qDebug() << "RemoveChangeAuto::SetUnactiveFields()   ";
    //  Enable fields one after other
    ui->LText_DelChangeRegNumber->setEnabled(false);
    ui->LText_DelChangeRegNumber->clear();
    ui->LText_AutoMillage->setEnabled(false);
    ui->LText_AutoMillage->clear();
    ui->LText_DelChangeVIN->setEnabled(false);
    ui->LText_DelChangeVIN->clear();
    ui->L_ChangeClientName->setVisible(false);

    ui->Button_Record->setVisible(false);
    ui->Button_DeleteAuto->setVisible(false);
    ui->Combo_ClientName->setVisible(false);
}

void RemoveChangeAuto::ActivateAutoCombos(bool DeactiavateAll)
{
//    qDebug() << "RemoveChangeAuto::ActivateAutoCombos() "<<DeactiavateAll;
    ui->m_ComboFuel->setEnabled(DeactiavateAll);
    ui->m_ComboMarka->setEnabled(DeactiavateAll);
    ui->m_ComboModel->setEnabled(DeactiavateAll);
    ui->m_ComboType->setEnabled(DeactiavateAll);
    ui->m_ComboYear->setEnabled(DeactiavateAll);
    ui->LText_DelChangeRegNumber->setEnabled(DeactiavateAll);
    ui->LText_AutoMillage->setEnabled(DeactiavateAll);
    ui->LText_DelChangeVIN->setEnabled(DeactiavateAll);
}

void RemoveChangeAuto::ReActivateAllFields()
{
//    qDebug() << "RemoveChangeAuto::ReActivateAllFields()   ";
    //  Enable fields one after other
    ui->LText_DelChangeRegNumber->setEnabled(true);
    ui->LText_AutoMillage->setEnabled(true);
    ui->LText_DelChangeVIN->setEnabled(true);
    ui->L_ChangeClientName->setVisible(true);

    ui->m_ComboFuel->setEnabled(true);
    ui->m_ComboMarka->setEnabled(true);
    ui->m_ComboModel->setEnabled(true);
    ui->m_ComboType->setEnabled(true);
    ui->m_ComboYear->setEnabled(true);
}
void RemoveChangeAuto::ClearAllFields()
{
//    qDebug() << "RemoveChangeAuto::ClearAllFields()";

//    m_bCancelAllActions = false;
    //  Enable fields one after other
    ui->LText_DelChangeRegNumber->setEnabled(false);
    ui->LText_DelChangeRegNumber->clear();
    ui->LText_AutoMillage->setEnabled(false);
    ui->LText_AutoMillage->clear();
    ui->LText_DelChangeVIN->setEnabled(false);
    ui->LText_DelChangeVIN->clear();
    ui->L_ChangeClientName->setVisible(false);

    ui->Button_Add->setVisible(false);
    ui->Button_Record->setVisible(false);

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

    m_strAutoMarka.clear();
    m_strAutoModel.clear();

     qDebug() << "RemoveChangeAuto::ClearAllFields()  m_State   "<<m_State;
    switch (m_State) {
    case eNormalMode :

        ui->L_ChangeAutoMain->setText("Добавяне на автомобил");
        break;
    case eEditMode :

        ui->L_ChangeAutoMain->setText("Корекция на автомобил");
        ui->Combo_ClientName->setVisible(false);
        ui->L_ChangeClientName->setVisible(false);
        ui->L_UnkownClients->setVisible(false);
        ui->Button_Record->setVisible(true);
        ui->LText_ClientName->setVisible(true);
        ui->LText_ClientName->setEnabled(false);

        break;
    case eAddExistingAutoMode :

        ui->L_ChangeAutoMain->setText("Добавяне на съществуващ автомобил");

        ui->L_ChangeClientName->setVisible(false);
        ui->Combo_ClientName->setVisible(false);
        ui->L_LineClientName->setVisible(true);

        ui->LText_DelChangeRegNumber->setEnabled(false);
        ui->LText_DelChangeVIN->setEnabled(false);
        ui->LText_AutoMillage->setEnabled(false);

        ui->LText_ClientName->setVisible(true);
        ui->LText_ClientName->setEnabled(false);

        ui->Button_Record->setVisible(true);
        ui->Button_DeleteAuto->setVisible(false);
        break;
    case eEditDelAuto :

        ui->L_ChangeAutoMain->setText("Корекция / Изтриване на автомобил");
        ui->Button_Record->setVisible(true);

         ui->L_ChangeClientName->setVisible(true);
         ui->Combo_ClientName->setEnabled(false);

        ui->LText_ClientName->setVisible(false);
        ui->LText_ClientName->setVisible(false);
        ui->L_UnkownClients->setVisible(false);
        ui->L_LineClientName->setVisible(false);

        ui->Button_DeleteAuto->setVisible(true);

        break;
    default :
        qDebug() << "  ClearAllFields - UnKnown Mode";
        break;
    }

    m_bComboClientsHit = false;
    m_bComboRegsHit = false;
    m_bEditFromClients = false;
}


void RemoveChangeAuto::EditClientAuto(QString ClientName,QString ClientEditID)
{
    qDebug() << "RemoveChangeAuto::EditClientAuto()  ENTER  ClientName   "<<ClientName<<"   ClientEditID "<<ClientEditID;
    m_State = eEditMode;
    m_bInitialize = true;
    ClearAllFields();

    FillComboMarki();
    FillComboModeli(0);

    m_SentClientName = ClientName;
    m_SentClientID = ClientEditID;
    // Edit Mode !! Enable all auto combos !
    if(!ClientName.isEmpty() && !ClientEditID.isEmpty()){
        ActivateAutoCombos(true);
    }

    m_bEditFromClients = true;
    FillRegCombo();
    FillAutoData();
    m_bInitialize = false;
    ui->LText_ClientName->setText(m_SentClientName);
    show();
}

void RemoveChangeAuto::OpenClearEditWindow()
{

    qDebug() << "RemoveChangeAuto::OpenClearEditWindow() ENTER   ";

    m_State = eEditDelAuto;
    m_bInitialize = true;
    ClearAllFields();
    FillComboMarki();
    FillComboModeli(0);
    FillPage();
    ActivateAutoCombos(true);
    m_bInitialize = false;
    show();
}

void RemoveChangeAuto::OpenClearWindow()
{
    qDebug() << "RemoveChangeAuto::OpenClearWindow()  ENTER  ";
    m_State = eNormalMode;
    m_bInitialize = true;
    ClearAllFields();
    FillPage();
//    SetUnactiveFields();
    m_bInitialize = false;
    show();
}


void RemoveChangeAuto::OpenExistingAutosWindow(QString ClientName)
{
    m_State = eAddExistingAutoMode;
    qDebug() << "RemoveChangeAuto::OpenExistingAutosWindow()  ENTER  "<<ClientName;
    m_bInitialize = true;

    ClearAllFields();

    m_SentClientName = ClientName;
    ui->LText_ClientName->setText(m_SentClientName);
    FillComboMarki();
    FillComboModeli(0);

    FillRegCombo();
    FillAutoData();
//    SetUnactiveFields();
    m_bInitialize = false;

    show();

}

void RemoveChangeAuto::FillPage()
{
    FillClientNameCombo();
    FillRegCombo();
}

void RemoveChangeAuto::FillAutoData()
{
//    qDebug() << "RemoveChangeAuto::FillAutoData()   m_SentClientID  "<<m_SentClientID<<"   m_SentClientName     "<<m_SentClientName;
    MyData.OpenConnection("Automobiles.sqlite");
    QSqlQuery RegComboQry(MyData.CarsDB);

    RegComboQry.prepare("SELECT * FROM Automobiles_Table WHERE Auto_RegNumber='"+m_SelectedRegNumber+"'");

    if(! RegComboQry.exec()){
        qDebug() << "EditAutoQry.Exec() SELECT Auto_RegNumber FROM Automobiles_Table Fail ";
        return;
    }else {

        if(!RegComboQry.next())
        {
            // Тука зареждаме празните атомобили.
            RegComboQry.prepare("SELECT * FROM Automobiles_Table WHERE CLIENT_ID='""'");
            if(! RegComboQry.exec()){
                return;
            }
            if(!RegComboQry.next())
            {
                qDebug() << "Nqma neregistrirani awtomobili !!!  ";
            }
        }else {
//            qDebug() << " RegComboQry   Value(0) "<<RegComboQry.value(0).toString();
            int index = -1;
//             qDebug() << " Value(1) "<<RegComboQry.value(1).toString();
//             qDebug() << " Value(2) "<<RegComboQry.value(2).toString();
//             qDebug() << " Value(3) "<<RegComboQry.value(3).toString();
//             qDebug() << " Value(4) "<<RegComboQry.value(4).toString();
//             qDebug() << " Value(5) "<<RegComboQry.value(5).toString();
//             qDebug() << " Value(6) "<<RegComboQry.value(6).toString();
//             qDebug() << " Value(7) "<<RegComboQry.value(7).toString();
//             qDebug() << " Value(8) "<<RegComboQry.value(8).toString();
//             qDebug() << " Value(9) "<<RegComboQry.value(9).toString();
             // Save Marka
             m_strAutoMarka = RegComboQry.value(3).toString();
             m_strAutoModel =  RegComboQry.value(4).toString();

             //Set Fuel
             index = ui->m_ComboFuel->findText(RegComboQry.value(6).toString()) ;
             if(index!=-1) ui->m_ComboFuel->setCurrentIndex(index);

             // Set year
             index = ui->m_ComboYear->findText(RegComboQry.value(5).toString()) ;
             if(index!=-1) ui->m_ComboYear->setCurrentIndex(index);

             //Set Type
             index = ui->m_ComboType->findText(RegComboQry.value(8).toString()) ;
             if(index!=-1) ui->m_ComboType->setCurrentIndex(index);

             // Set VIN
             ui->LText_DelChangeVIN->setText(RegComboQry.value(7).toString());
             // Set Millage
             ui->LText_AutoMillage->setText(RegComboQry.value(9).toString());
             //Set RegNumber
             ui->LText_DelChangeRegNumber->setText(RegComboQry.value(2).toString());
        }
    }

    MyData.CloseConnection();

    on_m_ComboMarka_currentTextChanged(m_strAutoMarka);
}

void RemoveChangeAuto::FillRegCombo()
{
//    qDebug() << "RemoveChangeAuto::FillRegCombo()   m_SentClientID  "<<m_SentClientID<<"   m_SentClientName     "<<m_SentClientName;
    MyData.OpenConnection("Automobiles.sqlite");
    QSqlQueryModel * MyModel = new QSqlQueryModel();
    QSqlQuery RegComboQry(MyData.CarsDB);

    if(m_State == eEditDelAuto){
        RegComboQry.prepare("SELECT Auto_RegNumber FROM Automobiles_Table");
    }else {
        if(m_SentClientID.isEmpty())
        {
            RegComboQry.prepare("SELECT Auto_RegNumber FROM Automobiles_Table WHERE CLIENT_ID IS NULL");
        }else {
            RegComboQry.prepare("SELECT Auto_RegNumber FROM Automobiles_Table WHERE CLIENT_ID='"+m_SentClientID+"'");
        }
    }

    if(! RegComboQry.exec()){
        qDebug() << "RegComboQry.Exec() SELECT Auto_RegNumber FROM Automobiles_Table Fail ";
        delete MyModel;
        return;
    }

    MyModel->setQuery(RegComboQry);
    ui->Combo_DelChangeAutoRegs->setModel(MyModel);

    MyData.CloseConnection();
}

void RemoveChangeAuto::FillClientNameCombo()
{
    qDebug() << "RemoveChangeAuto::FillClientNameCombo()   ";
    MyData.OpenConnection("Clients.sqlite");
    QSqlQueryModel * MyModel = new QSqlQueryModel();
    QSqlQuery ClientComboQry(MyData.CarsDB);

    ClientComboQry.prepare("SELECT ClientName FROM Clients_Table ");

    if(! ClientComboQry.exec()){
        qDebug() << "ClientComboQry.Exec() SELECT ClientName FROM Clients_Table Fail ";
    }

    MyModel->setQuery(ClientComboQry);
    ui->Combo_ClientName->setModel(MyModel);
    MyData.CloseConnection();
}

void RemoveChangeAuto::on_Button_Record_clicked()
{
//    qDebug() << "RemoveChangeAuto::on_Button_Record_clicked()   ";
    MyData.OpenConnection("Automobiles.sqlite");

    /** Towa e qko typo , obache trqbwa da ima kontrol na dannite predi da se zapishat. Inache nqma hwashtane */
//    QString RegNumber = CheckField(ui->LText_DelChangeRegNumber->text())?ui->LText_DelChangeRegNumber->text():"None";
//    QString Vin = CheckField(ui->LText_DelChangeVIN->text())?ui->LText_DelChangeVIN->text():"None";
   //@ TODO - make this from combo boxes selection


//    qDebug() << "   ui->LText_DelChangeRegNumber->text()     "<<ui->LText_DelChangeRegNumber->text();
//    qDebug() << "   m_SelectedRegNumber     "<<m_SelectedRegNumber;

//    qDebug() << "   m_ComboMarka    "<<ui->m_ComboMarka->currentText();
//    qDebug() << "   m_ComboModel)     "<<ui->m_ComboModel->currentText();
//    qDebug() << "   m_ComboYear     "<<ui->m_ComboYear->currentText();
//    qDebug() << "   m_ComboFuel     "<<ui->m_ComboFuel->currentText();
//    qDebug() << " LText_DelChangeVIN     "<<ui->LText_DelChangeVIN->text();
//    qDebug() << "  m_ComboType     "<<ui->m_ComboType->currentText();


    QSqlQuery AddNewAuto(MyData.CarsDB);
    AddNewAuto.prepare("UPDATE Automobiles_Table set Auto_RegNumber='"+ui->LText_DelChangeRegNumber->text()+"',Auto_Marka='"+ui->m_ComboMarka->currentText()+"', Auto_Model='"+ui->m_ComboModel->currentText()+"', Auto_Year='"+ui->m_ComboYear->currentText()+"', Auto_Fuel='"+ui->m_ComboFuel->currentText()+"',  Auto_VIN='"+ui->LText_DelChangeVIN->text()+"', Auto_Type='"+ui->m_ComboType->currentText()+"', Auto_Millage='"+ui->LText_AutoMillage->text()+"' WHERE Auto_RegNumber='"+m_SelectedRegNumber+"' ");

    if(!AddNewAuto.exec()){
        qDebug() << "UPDATE Automobiles_Table fail1111  ";
    }
    else {
        qDebug() << "UPDATE AddNewAuto.next() Done";
    }

    // Update Current Changes
    m_strAutoReg = ui->LText_DelChangeRegNumber->text();
    MyData.CloseConnection();

    ClearAllFields();
    on_Button_Add_clicked();
}

void RemoveChangeAuto::on_Button_DeleteAuto_clicked()
{

    qDebug() << "RemoveChangeAuto::on_Button_DeleteAuto_clicked()   ";
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
    MyData.RemoveConnection();
    hide();
    emit CloseDeletePage();
}


void RemoveChangeAuto::on_Button_Back_clicked()
{
    m_strAutoReg = "None";
    m_SelectedClientID="";
    m_SelectedRegNumber="";
//    m_bCancelAllActions = true;
    MyData.RemoveConnection();
    hide();
    emit CloseDeletePage();
}

void RemoveChangeAuto::on_Combo_ClientName_currentIndexChanged(QString)
{
//    qDebug() << "RemoveChangeAuto::on_Combo_ClientName_currentIndexChanged()   ";
    qDebug() << "m_bInitialize  "<<m_bInitialize<<" m_SentClientName    "<<m_SentClientName<<"  m_SelectedRegNumber "<<m_SelectedRegNumber;
//    if((!m_bInitialize || m_SentClientName.isEmpty()) && !m_bComboRegsHit)
//    {
//        m_bComboClientsHit = true;
//        on_Combo_DelChangeAutoRegs_currentIndexChanged(QString::number(ui->Combo_ClientName->currentIndex()+1));
//    }
}


void RemoveChangeAuto::on_Combo_DelChangeAutoRegs_currentIndexChanged(const QString &arg1)
{
    qDebug() << "RemoveChangeAuto::on_Combo_DelChangeAutoRegs_currentIndexChanged()  arg1    "<<arg1;
    m_SelectedRegNumber = arg1;
//    ReActivateAllFields();
    FillAutoData();

    if(m_bInitialize){
        return;
    }

    MyData.OpenConnection("Automobiles.sqlite");
    QSqlQuery EditAutoQry(MyData.CarsDB);

    if(m_bComboRegsHit)
    {
        MyData.CloseConnection();
        return;
    }
//qDebug() << "RemoveChangeAuto::on_Combo_DelChangeAutoRegs_currentIndexChanged()   ";
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
             qDebug() << " Value(5) "<<EditAutoQry.value(5).toString();
             qDebug() << " Value(6) "<<EditAutoQry.value(6).toString();
             qDebug() << " Value(7) "<<EditAutoQry.value(7).toString();
             qDebug() << " Value(8) "<<EditAutoQry.value(8).toString();
             qDebug() << " Value(9) "<<EditAutoQry.value(9).toString();

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
        }
//        else {
//            /// Fill all automobiles with No cliet assigned
//            qDebug() << " Autos Not Found !  ";
//            m_SelectedClientID.clear();
//            ClearAllFields();
//        }
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
        ui->Combo_ClientName->setCurrentIndex(m_SelectedClientID.toInt()-1);
    }

    UpdateFlags();
}


void RemoveChangeAuto::FillComboModeli(int MarkaIdx)
{
//     qDebug() << "RemoveChangeAuto::FillComboModeli()   MarkaIdx    "<<MarkaIdx << "    m_strAutoModel  "<<m_strAutoModel;
    MyData.OpenConnection("All_Models.sqlite");
    QSqlQueryModel *MyModel = new QSqlQueryModel();
    QSqlQuery ShowModelQry(MyData.CarsDB);

    ShowModelQry.prepare("SELECT Model_Name FROM All_Models_Table WHERE Model_ID='"+QString::number(MarkaIdx)+"' ");

    if(! ShowModelQry.exec()){
        qDebug() << "ShowModelQry.Exec() SELECT Model_Name FROM All_Models_Table fail "<< ShowModelQry.lastError().text();
    }

    MyModel->setQuery(ShowModelQry);
    ui->m_ComboModel->setModel(MyModel);

    MyData.CloseConnection();

    if(!m_strAutoModel.isEmpty()){
        int Idx = -1;
        Idx = ui->m_ComboModel->findText(m_strAutoModel) ;
        if(Idx!=-1) ui->m_ComboModel->setCurrentIndex(Idx);
    }
}


void RemoveChangeAuto::FillComboMarki()
{

//     qDebug() << "RemoveChangeAuto::FillComboMarki()   ";
    MyData.OpenConnection("Marki.sqlite");

    QSqlQueryModel * MyModel = new QSqlQueryModel();

    QSqlQuery ShowMakriQry(MyData.CarsDB);
    ShowMakriQry.prepare("SELECT Marki FROM AutoMarki_Table");

    if(! ShowMakriQry.exec()){
        qDebug() << "ShowMakriQry.Exec() SELECT Model_Name FROM AutoMarki_Table fail "<< ShowMakriQry.lastError().text();
    }

    MyModel->setQuery(ShowMakriQry);
    ui->m_ComboMarka->setModel(MyModel);
    MyData.CloseConnection();
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

void RemoveChangeAuto::on_m_ComboMarka_currentIndexChanged(int index)
{
//            qDebug() << "RemoveChangeAuto::on_m_ComboMarka_currentIndexChanged()   index    "<<index;
    FillComboModeli(index);
}

void RemoveChangeAuto::on_m_ComboMarka_currentTextChanged(const QString &arg1)
{
//    qDebug() << "RemoveChangeAuto::on_m_ComboMarka_currentTextChanged()   arg1    "<<arg1;
    int Idx = -1;
    if(!arg1.isEmpty()){
        Idx = ui->m_ComboMarka->findText(arg1) ;
        if(Idx!=-1) ui->m_ComboMarka->setCurrentIndex(Idx);
        FillComboModeli(Idx);
    }else {
         qDebug() << " No Auto found    ";
         SetUnactiveFields();
    }
}

void RemoveChangeAuto::on_Combo_ClientName_currentIndexChanged(int index)
{
    qDebug() << "on_Combo_ClientName_currentIndexChanged  index "<<index;
    m_SentClientID = QString::number(index+1);
    qDebug() << "on_Combo_ClientName_currentIndexChanged  m_SentClientID "<<m_SentClientID;

    MyData.OpenConnection("Automobiles.sqlite");
    QSqlQuery EditAutoQry(MyData.CarsDB);
    int Idx = -1;

    EditAutoQry.prepare("SELECT Auto_RegNumber FROM Automobiles_Table WHERE CLIENT_ID='"+m_SentClientID+"' ");
    if(! EditAutoQry.exec()){
        qDebug() << "Combo_ClientName SELECT Model_Name FROM All_Models_Table fail "<< EditAutoQry.lastError().text();
    }else {
         if( EditAutoQry.next()){
             ReActivateAllFields();
             qDebug() << "EditAutoQry.value(0).toString() "<<EditAutoQry.value(0).toString();
             Idx = ui->Combo_DelChangeAutoRegs->findText(EditAutoQry.value(0).toString()) ;
            int Idx22 = -1;
             Idx22 = ui->Combo_DelChangeAutoRegs->findText(m_SelectedRegNumber) ;
qDebug() << " Idx "<<Idx;
qDebug() << "Idx22 "<<Idx22;

             if(Idx!=-1) ui->Combo_DelChangeAutoRegs->setCurrentIndex(Idx);

//             qDebug() << " Valid index selected - Reactivate all fields +++++++++++++++++++++++++ ";
         }else {
//                qDebug() << "111 EditAutoQry.value(0).toString() "<<EditAutoQry.value(0).toString();
//             qDebug() << " No Auto for this client ";
//             SetFieldsClientWithNoAuto();
//             ClearAllFields();
         }
    }
    MyData.CloseConnection();
}
