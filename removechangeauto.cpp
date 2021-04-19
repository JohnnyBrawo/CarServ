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
    setWindowTitle("Euro Kriss - Edit AUTOS ");
}

RemoveChangeAuto::~RemoveChangeAuto()
{
    delete ui;
}

void RemoveChangeAuto::SetUnactiveFields()
{
    //  Enable fields one after other
    ui->LText_DelChangeFuel->setEnabled(false);
    ui->LText_DelChangeMarka->setEnabled(false);
    ui->LText_DelChangeModel->setEnabled(false);
    ui->LText_DelChangeRegNumber->setEnabled(false);
    ui->LText_DelChangeType->setEnabled(false);
    ui->LText_DelChangeVIN->setEnabled(false);
    ui->LText_DelChangeYear->setEnabled(false);

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
    ui->LText_DelChangeFuel->setText("");
    ui->LText_DelChangeMarka->setText("");
    ui->LText_DelChangeModel->setText("");
    ui->LText_DelChangeRegNumber->setText("");
    ui->LText_DelChangeType->setText("");
    ui->LText_DelChangeVIN->setText("");
    ui->LText_DelChangeYear->setText("");
    ui->Combo_DelChangeAutoRegs->setCurrentIndex(-1);

    ui->LText_ClientName->setVisible(false);
    ui->L_LineClientName->setVisible(false);
    ui->L_UnkownClients->setVisible(false);

    m_SelectedRegNumber.clear();
    m_SelectedClientID.clear();
    m_SentClientName.clear();
    m_SentClientID.clear();

    m_bComboClientsHit = false;
    m_bComboRegsHit = false;
    m_bEditFromClients = false;


}


void RemoveChangeAuto::OpenClientEditWindow(QString ClientName, QString ClientEditID)
{
    qDebug() << "RemoveChangeAuto::OpenClientEditWindow()   ";
    m_bInitialize = true;
    ClearAllFields();

    qDebug() << " OpenClientEditWindow  ClientName   " << ClientName << "   ClientEditID    " << ClientEditID;
    m_SentClientName = ClientName;
    m_SentClientID = ClientEditID;
    ui->Combo_DelChangeClientName->setVisible(false);
    ui->L_ChangeClientName->setVisible(false);
    ui->LText_ClientName->setVisible(true);
    ui->L_UnkownClients->setVisible(true);

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
    ui->Combo_DelChangeAutoRegs->setMaxVisibleItems(10);
    ui->Combo_DelChangeAutoRegs->setStyleSheet("combobox-popup: 0;");

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
    ui->Combo_DelChangeClientName->setMaxVisibleItems(10);
    ui->Combo_DelChangeClientName->setStyleSheet("combobox-popup: 0;");
    MyData.CloseConnection();
}


void RemoveChangeAuto::ShowAllFieldsText()
{
    qDebug() << " ui->LText_DelChangeMarka->text "  << ui->LText_DelChangeMarka->text();
    qDebug() << " ui->LText_DelChangeModel->text "  << ui->LText_DelChangeModel->text();
    qDebug() << " ui->LText_DelChangeType->text "  << ui->LText_DelChangeType->text();
    qDebug() << " ui->LText_DelChangeYear->text "  << ui->LText_DelChangeYear->text();
    qDebug() << " ui->LText_DelChangeFuel->text "  << ui->LText_DelChangeFuel->text();
    qDebug() << " ui->LText_DelChangeRegNumber->text "  << ui->LText_DelChangeRegNumber->text();
    qDebug() << " ui->LText_DelChangeVIN->text "  << ui->LText_DelChangeVIN->text();
}

void RemoveChangeAuto::on_Button_Record_clicked()
{
    MyData.OpenConnection("Automobiles.sqlite");

    /** Towa e qko typo , obache trqbwa da ima kontrol na dannite predi da se zapishat. Inache nqma hwashtane */
    QString Marka = CheckField(ui->LText_DelChangeMarka->text())?ui->LText_DelChangeMarka->text():"None";
    QString Model = CheckField(ui->LText_DelChangeModel->text())?ui->LText_DelChangeModel->text():"None";
    QString Type = CheckField(ui->LText_DelChangeType->text())?ui->LText_DelChangeType->text():"None";
    QString Year = CheckField(ui->LText_DelChangeYear->text())?ui->LText_DelChangeYear->text():"None";
    QString Fuel = CheckField(ui->LText_DelChangeFuel->text())?ui->LText_DelChangeFuel->text():"None";
    QString RegNumber = CheckField(ui->LText_DelChangeRegNumber->text())?ui->LText_DelChangeRegNumber->text():"None";
    QString Vin = CheckField(ui->LText_DelChangeVIN->text())?ui->LText_DelChangeVIN->text():"None";

    QSqlQuery AddNewAuto(MyData.CarsDB);
    AddNewAuto.prepare("UPDATE Automobiles_Table set Auto_RegNumber='"+RegNumber+"',Auto_Marka='"+Marka+"', Auto_Model='"+Model+"', Auto_Year='"+Year+"', Auto_Fuel='"+Fuel+"',  Auto_VIN='"+Vin+"', Auto_Type='"+Type+"' WHERE Auto_RegNumber='"+m_SelectedRegNumber+"' ");

    if(!AddNewAuto.exec()){
        qDebug() << "UPDATE Automobiles_Table fail ";
    }

    // Update Current Changes
    m_SelectedRegNumber = ui->LText_DelChangeRegNumber->text();
    MyData.CloseConnection();
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

    if( m_bComboClientsHit)
    {
        EditAutoQry.prepare("SELECT * FROM Automobiles_Table WHERE CLIENT_ID='"+arg1+"' ");
    }else {
        EditAutoQry.prepare("SELECT * FROM Automobiles_Table WHERE Auto_RegNumber='"+arg1+"' ");
    }

    m_bComboRegsHit = true;
    if(!EditAutoQry.exec()){
        qDebug() << "EditAutoQry.Exec() SELECT Auto_RegNumber FROM Automobiles_Table Fail "<< EditAutoQry.lastError().text();
    }else {
        /// Fill all automobiles with speciffic ClientID or Auto_Reg Number
        if (EditAutoQry.next()) {

            qDebug() << " RemoveChangeAuto   " << EditAutoQry.value(1).toString();
            qDebug() << " RemoveChangeAuto   " << EditAutoQry.value(2).toString();
            qDebug() << " RemoveChangeAuto  " << EditAutoQry.value(3).toString();
            qDebug() << " RemoveChangeAuto   " << EditAutoQry.value(4).toString();
            qDebug() << " RemoveChangeAuto   " << EditAutoQry.value(5).toString();
            qDebug() << " RemoveChangeAuto   " << EditAutoQry.value(6).toString();
            qDebug() << " RemoveChangeAuto   " << EditAutoQry.value(7).toString();
            qDebug() << " RemoveChangeAuto   " << EditAutoQry.value(8).toString();


            if(m_SelectedClientID.isEmpty() ){
                ui->L_UnkownClients->setVisible(false);
                m_SelectedClientID = EditAutoQry.value(1).toString();
            }
            ui->LText_DelChangeMarka->setText(EditAutoQry.value(2).toString());
            ui->LText_DelChangeModel->setText(EditAutoQry.value(3).toString());
            ui->LText_DelChangeYear->setText(EditAutoQry.value(4).toString());
            ui->LText_DelChangeFuel->setText(EditAutoQry.value(5).toString());
            ui->LText_DelChangeRegNumber->setText(EditAutoQry.value(6).toString());
            ui->LText_DelChangeVIN->setText(EditAutoQry.value(7).toString());
            ui->LText_DelChangeType->setText(EditAutoQry.value(8).toString());

            /// Record selected AutoID - attach it to the New client
            m_strAutoReg = EditAutoQry.value(6).toString();
            ui->Combo_DelChangeAutoRegs->setCurrentText(EditAutoQry.value(6).toString());
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
