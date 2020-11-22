#include "newrepair.h"
#include "ui_newrepair.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include <qdebug.h>
#include "carsdatabase.h"
#include <QtWidgets>

NewRepair::NewRepair(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRepair)
{
    ui->setupUi(this);
}

NewRepair::~NewRepair()
{
    delete ui;
}


void NewRepair::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-static_cast<int>(width()*0.5), center.y()-static_cast<int>(height()*0.5) );
}

void NewRepair::OpenNewRepairWindow()
{
     FillComboMarki();
     ClearAllFields();
     this->show();
}

void NewRepair::ClearAllFields()
{
    //  Disable all fields except Auto Model.
    //  Enable fields one after other
    ui->Combo_NewRepair_Marka->setCurrentIndex(0);

    ui->Combo_NewRepair_Model->clear();
    ui->Combo_NewRepair_Model->setCurrentIndex(-1);
    ui->Combo_NewRepair_Model->setEnabled(false);

    ui->Combo_NewRepair_Year->setCurrentIndex(0);
    ui->Combo_NewRepair_Year->setEnabled(false);

    ui->Combo_NewRepair_Fuel->setCurrentIndex(0);
    ui->Combo_NewRepair_Fuel->setEnabled(false);

    ui->LText_NewRepairAutoRegNumber->clear();
    ui->LText_NewRepairAutoRegNumber->setEnabled(false);

    ui->Button_AddNewRepair->setEnabled(false);

    ui->LText_NewRepairKlientName->clear();
    ui->LText_NewRepairKlientPhone->clear();
}

bool NewRepair::CheckRecordInformation(){

    QString EmptyFields = "";
    QMessageBox::StandardButton UserReply;

    if(!CheckSelected(ui->Combo_NewRepair_Year->currentText())){
        EmptyFields = EmptyFields + " Година " + "\n";
    }

    if(!CheckSelected(ui->Combo_NewRepair_Fuel->currentText())){
        EmptyFields = EmptyFields + " Гориво " + "\n";
    }

    /**  Ако дразни съобщението може да се направи само да blink-ват полетата и да иска повторно натиска не на
          ЗАПИШИ бутона
        for(int i=1;i<15;i+=2){
            QTimer::singleShot(100*i, this, SLOT(changeBackgroundColor()));
            QTimer::singleShot(100*(i+1), this, SLOT(retrieveBackgroundColor()));
    }**/

    if(EmptyFields !="")
    {
     UserReply =  QMessageBox::question(this,"Опаа! Спиш нещо!", "Има непопълнени полета!" + EmptyFields + "\n Да продължа ли със записа ?",QMessageBox::Yes | QMessageBox::No);
     if(UserReply == QMessageBox::No){
         return false;
     }
    }

    return true;
}


bool NewRepair::CheckRecordObligatory(){

    if(!CheckSelected(ui->Combo_NewRepair_Marka->currentText()) ||
       !CheckSelected(ui->LText_NewRepairAutoRegNumber->text()) ||
       !CheckSelected(ui->LText_NewRepairKlientName->text()) ||
       !CheckSelected(ui->LText_NewRepairKlientPhone->text())){

        QMessageBox::information(this,"Важно!","Не сте попълнили задължителните полега ( * ).");
         return false;
     }

    return true;
}

void NewRepair::on_Button_AddNewRepair_clicked()
{

    if(!CheckRecordObligatory()){
        qDebug() << " MUST fields empty ";
        return;
    }
    if(!CheckRecordInformation())
    {
         qDebug() << "INSERT Rejected because of empty fields ";
        return;
    }

    CarsDatabase MyData;
    MyData.OpenConnection("Automobiles.sqlite");

    QSqlQuery AddNewAuto(MyData.CarsDB);
    AddNewAuto.prepare("INSERT INTO Automobiles_Table(AutoMarka, AutoModel, AutoYear, AutoFuel, Auto_RegNumber, AutoVIN, AutoType) "
                       "VALUES(:AutoMarka, :AutoModel, :AutoYear, :AutoFuel, :Auto_RegNumber, :AutoVIN, :AutoType)");

    AddNewAuto.bindValue(":AutoMarka",ui->Combo_NewRepair_Marka->currentText());
    AddNewAuto.bindValue(":AutoModel",CheckSelected(ui->Combo_NewRepair_Model->currentText())?ui->Combo_NewRepair_Model->currentText():"None");
    AddNewAuto.bindValue(":AutoYear",CheckSelected(ui->Combo_NewRepair_Year->currentText())?ui->Combo_NewRepair_Year->currentText():"None");
    AddNewAuto.bindValue(":AutoFuel",CheckSelected(ui->Combo_NewRepair_Fuel->currentText())?ui->Combo_NewRepair_Fuel->currentText():"None");
    AddNewAuto.bindValue(":Auto_RegNumber",CheckSelected(ui->LText_NewRepairAutoRegNumber->text())?ui->LText_NewRepairAutoRegNumber->text():"None");
    AddNewAuto.bindValue(":AutoVIN","None");
    AddNewAuto.bindValue(":AutoType","None");

    m_strSelectedCarReg = ui->LText_NewRepairAutoRegNumber->text();
    if(!AddNewAuto.exec()){
        qDebug() << "INSERT INTO Automobiles_Table fail "<< AddNewAuto.lastError().text();
    }

//    // Get Last RowID
//    QSqlQuery query(MyData.CarsDB);
//        query.prepare("SELECT last_insert_rowid()");
//        if(!query.exec())
//        {
//            qDebug() << "SELECT last_insert_rowid() "<< AddNewAuto.lastError().text();
//        }
//        else {
//            m_strSelectedCarReg = query.lastInsertId().toString();
             qDebug() << "m_strSelectedCarReg   "<< m_strSelectedCarReg;
             ClearAllFields();
//        }
     MyData.CloseConnection();
}


void NewRepair::FillComboMarki()
{
    CarsDatabase MyData;
    MyData.OpenConnection("Marki.sqlite");

    QSqlQueryModel * MyModel = new QSqlQueryModel();

    QSqlQuery ShowMakriQry(MyData.CarsDB);
    ShowMakriQry.prepare("SELECT Marki FROM AutoMarki_Table");

    if(! ShowMakriQry.exec()){
        qDebug() << "ShowMakriQry.Exec() SELECT Model_Name FROM AutoMarki_Table fail "<< ShowMakriQry.lastError().text();
    }

    MyModel->setQuery(ShowMakriQry);
    ui->Combo_NewRepair_Marka->setModel(MyModel);

    MyData.CloseConnection();

}

bool NewRepair::CheckSelected(QString SelectedString)
{
    if((static_cast<int>(SelectedString.size()) < 2 ) || (SelectedString == "Select") || SelectedString == "")
    {
        qDebug() << "CheckSelected  FAIL SelectedString " << SelectedString;
        return false;
    }
    return true;
}


void NewRepair::DeActivateField(NewRepair::NewAutoFields Field)
{
    switch (Field)
    {
    case NewRepair::eModel :
    {
        ClearAllFields();
        break;
    }

    default:
        qDebug() << "DeActivate UnknownField";
        break;
    }
}


void NewRepair::ActivateField(NewRepair::NewAutoFields Field)
{
    switch (Field)
    {
    case NewRepair::eModel :
    {
        ui->Combo_NewRepair_Model->setEnabled(true);

        ui->Combo_NewRepair_Year->setCurrentIndex(0);
        ui->Combo_NewRepair_Year->setEnabled(true);

        ui->Combo_NewRepair_Fuel->setCurrentIndex(0);
        ui->Combo_NewRepair_Fuel->setEnabled(true);

        ui->LText_NewRepairAutoRegNumber->clear();
        ui->LText_NewRepairAutoRegNumber->setEnabled(true);

        ui->Button_AddNewRepair->setEnabled(true);
        break;
    }

    default:
        qDebug() << "Activate UnknownField";
        break;
    }
}

void NewRepair::FillComboModeli(int MarkaIndex)
{
    CarsDatabase MyData;
    MyData.OpenConnection("All_Models.sqlite");
    QSqlQueryModel *MyModel = new QSqlQueryModel();
    QSqlQuery ShowModelQry(MyData.CarsDB);

    ShowModelQry.prepare("SELECT Model_Name FROM All_Models_Table WHERE Model_ID='"+QString::number(MarkaIndex)+"' ");


    if(! ShowModelQry.exec()){
        qDebug() << "ShowModelQry.Exec() SELECT Model_Name FROM All_Models_Table fail "<< ShowModelQry.lastError().text();
    }

    MyModel->setQuery(ShowModelQry);
    ui->Combo_NewRepair_Model->setModel(MyModel);
    MyData.CloseConnection();

    if(ui->Combo_NewRepair_Model->count() == 1)
    {
        ActivateField(NewRepair::eYear);
    }

}

void NewRepair::on_Combo_NewRepair_Marka_currentIndexChanged(int index)
{
    if(CheckSelected(ui->Combo_NewRepair_Marka->currentText()))  {
      ActivateField(NewRepair::eModel);
      FillComboModeli(index);

    }
    else {
        DeActivateField(NewRepair::eModel);
    }
}

//void NewRepair::on_Combo_NewRepair_Model_currentIndexChanged(int index)
//{

//    if(CheckSelected(ui->Combo_NewRepair_Model->currentText()) && index !=0)  {
//      ActivateField(NewRepair::eYear);
//    }
//}

void NewRepair::on_Button_CancelNewRepair_clicked()
{
    ClearAllFields();
    this->hide();
    emit CloseNewRepairForm();
}
