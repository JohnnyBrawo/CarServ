#include "newauto.h"
#include "ui_newauto.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include <qdebug.h>
#include "carsdatabase.h"
//#include <QtCore>
//#include <QtGui>
#include <QtWidgets>

// Must have Automobile database here

NewAuto::NewAuto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAuto)
{
    ui->setupUi(this);
    m_strSelectedCarID = "None";
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
    ClearAllFields();
    this->hide();
}


void NewAuto::OpenClearWindow()
{
     FillComboMarki();
     ClearAllFields();
     this->show();
}

void NewAuto::ClearAllFields()
{
    //  Disable all fields except Auto Model.
    //  Enable fields one after other
    ui->Combo_NewAuto_Marka->setCurrentIndex(0);

    ui->Combo_NewAuto_Model->clear();
     ui->Combo_NewAuto_Model->setCurrentIndex(-1);
    ui->Combo_NewAuto_Model->setEnabled(false);

    ui->Combo_NewAuto_Year->setCurrentIndex(0);
    ui->Combo_NewAuto_Year->setEnabled(false);

    ui->Combo_NewAuto_Fuel->setCurrentIndex(0);
    ui->Combo_NewAuto_Fuel->setEnabled(false);

    ui->Combo_NewAuto_Type->setCurrentIndex(0);
    ui->Combo_NewAuto_Type->setEnabled(false);

    ui->LText_NewAutoRegNumber->clear();
    ui->LText_NewAutoRegNumber->setEnabled(false);

    ui->LText_NewAutoVIN->clear();
    ui->LText_NewAutoVIN->setEnabled(false);

    ui->Button_AddNewAuto->setEnabled(false);
}

bool NewAuto::CheckRecordInformation(){

    QString EmptyFields = "";
    QMessageBox::StandardButton UserReply;

    if(!CheckSelected(ui->Combo_NewAuto_Type->currentText())){
        EmptyFields = EmptyFields + " Купе " + "\n";
    }

    if(!CheckSelected(ui->Combo_NewAuto_Year->currentText())){
        EmptyFields = EmptyFields + " Година " + "\n";
    }

    if(!CheckSelected(ui->Combo_NewAuto_Fuel->currentText())){
        EmptyFields = EmptyFields + " Гориво " + "\n";
    }

    if(!CheckSelected(ui->LText_NewAutoVIN->text())) {
        EmptyFields =EmptyFields +  " Рама/Вин " + "\n";
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


bool NewAuto::CheckRecordObligatory(){

    if(!CheckSelected(ui->Combo_NewAuto_Marka->currentText()) || !CheckSelected(ui->LText_NewAutoRegNumber->text()) ){

        QMessageBox::information(this,"Важно!","Не сте попълнили задължителните полега ( * ).");
         return false;
     }

    return true;
}

void NewAuto::on_Button_AddNewAuto_clicked()
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

    AddNewAuto.bindValue(":AutoMarka",ui->Combo_NewAuto_Marka->currentText());
    AddNewAuto.bindValue(":AutoModel",CheckSelected(ui->Combo_NewAuto_Model->currentText())?ui->Combo_NewAuto_Model->currentText():"None");
    AddNewAuto.bindValue(":AutoYear",CheckSelected(ui->Combo_NewAuto_Year->currentText())?ui->Combo_NewAuto_Year->currentText():"None");
    AddNewAuto.bindValue(":AutoFuel",CheckSelected(ui->Combo_NewAuto_Fuel->currentText())?ui->Combo_NewAuto_Fuel->currentText():"None");
    AddNewAuto.bindValue(":Auto_RegNumber",CheckSelected(ui->LText_NewAutoRegNumber->text())?ui->LText_NewAutoRegNumber->text():"None");
    AddNewAuto.bindValue(":AutoVIN",CheckSelected(ui->LText_NewAutoVIN->text())?ui->LText_NewAutoVIN->text():"None");
    AddNewAuto.bindValue(":AutoType",CheckSelected(ui->Combo_NewAuto_Type->currentText())?ui->Combo_NewAuto_Type->currentText():"None");

    if(!AddNewAuto.exec()){
        qDebug() << "INSERT INTO Automobiles_Table fail "<< AddNewAuto.lastError().text();
    }

    // Get Last RowID
    QSqlQuery query(MyData.CarsDB);
        query.prepare("SELECT last_insert_rowid()");
        if(!query.exec())
        {
            qDebug() << "SELECT last_insert_rowid() "<< AddNewAuto.lastError().text();
        }
        else {
            m_strSelectedCarID = query.lastInsertId().toString();
             qDebug() << "m_strSelectedCarID   "<< m_strSelectedCarID;
             ClearAllFields();
        }
     MyData.CloseConnection();
}


void NewAuto::FillComboMarki()
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
    ui->Combo_NewAuto_Marka->setModel(MyModel);

    MyData.CloseConnection();

}

bool NewAuto::CheckSelected(QString SelectedString)
{
    if(( (int)SelectedString.size() < 2 ) || (SelectedString == "Select") || SelectedString == "")
    {
        qDebug() << "CheckSelected  FAIL SelectedString " << SelectedString;
        return false;
    }
    return true;
}


void NewAuto::DeActivateField(NewAuto::NewAutoFields Field)
{
    switch (Field)
    {
    case NewAuto::eModel :
    {
        ClearAllFields();
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
        ui->Combo_NewAuto_Model->setEnabled(true);

        ui->Combo_NewAuto_Year->setCurrentIndex(0);
        ui->Combo_NewAuto_Year->setEnabled(true);

        ui->Combo_NewAuto_Fuel->setCurrentIndex(0);
        ui->Combo_NewAuto_Fuel->setEnabled(true);

        ui->Combo_NewAuto_Type->setCurrentIndex(0);
        ui->Combo_NewAuto_Type->setEnabled(true);

        ui->LText_NewAutoRegNumber->clear();
        ui->LText_NewAutoRegNumber->setEnabled(true);

        ui->LText_NewAutoVIN->clear();
        ui->LText_NewAutoVIN->setEnabled(true);

        ui->Button_AddNewAuto->setEnabled(true);
        break;
    }

    default:
        qDebug() << "Activate UnknownField";
        break;
    }
}

void NewAuto::FillComboModeli(int MarkaIndex)
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
    ui->Combo_NewAuto_Model->setModel(MyModel);
    MyData.CloseConnection();

    if(ui->Combo_NewAuto_Model->count() == 1)
    {
        ActivateField(NewAuto::eYear);
    }

}

void NewAuto::on_Combo_NewAuto_Marka_currentIndexChanged(int index)
{
    if(CheckSelected(ui->Combo_NewAuto_Marka->currentText()))  {
      ActivateField(NewAuto::eModel);
      FillComboModeli(index);

    }
    else {
        DeActivateField(NewAuto::eModel);
    }
}

void NewAuto::on_Combo_NewAuto_Model_currentIndexChanged(int index)
{

    if(CheckSelected(ui->Combo_NewAuto_Model->currentText()) && index !=0)  {
      ActivateField(NewAuto::eYear);
    }
}
