#include "newrepair.h"
#include "ui_newrepair.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include <qdebug.h>
#include <QtWidgets>
#include <QKeyEvent>

NewRepair::NewRepair(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRepair),
    m_Client(new NewClient()),
    m_Auto(new NewAuto())
{
    ui->setupUi(this);
}

NewRepair::~NewRepair()
{
    delete ui;
    delete m_Client;
    delete m_Auto;
}


void NewRepair::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-static_cast<int>(width()*0.5), center.y()-static_cast<int>(height()*0.5) );
}

void NewRepair::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
            on_Button_CancelNewRepair_clicked();
    }
    else{
            QDialog::keyPressEvent(event);
    }
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
    AutoInfoDone = false;
    ClientInfoDone = false;
}

bool NewRepair::CheckRecordInformation(){

    QString EmptyFields = "";

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
    return true;
}


bool NewRepair::CheckRecordObligatory(){

    if(!CheckSelected(ui->Combo_NewRepair_Marka->currentText()) ||
       !CheckSelected(ui->LText_NewRepairAutoRegNumber->text()) ||
       !CheckSelected(ui->LText_NewRepairKlientName->text()) ||
       !CheckSelected(ui->LText_NewRepairKlientPhone->text())){

        QMessageBox::information(this,"Ops!","Missing fields ( * ).");
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

    if(!ClientInfoDone){
        if(m_Client->AddClentInfo(ui->LText_NewRepairKlientName->text(),ui->LText_NewRepairKlientPhone->text())){
            ClientInfoDone = true;
        }else{
            return;
        }
    }

    if(!AutoInfoDone && ClientInfoDone){

            if (m_Auto->AddCarInfo(ui->LText_NewRepairAutoRegNumber->text(),
                                   ui->Combo_NewRepair_Marka->currentText(),
                                   ui->Combo_NewRepair_Model->currentText(),
                                   ui->Combo_NewRepair_Year->currentText(),
                                   ui->Combo_NewRepair_Fuel->currentText(),
                                   ui->LText_NewRepairAutoMillage->text()) ){
             m_Client->SetNewRepairRegNumber(ui->LText_NewRepairAutoRegNumber->text());
             m_Client->RecordCarToClient();
             AutoInfoDone = true;
            }
            else{
                qDebug() <<" Car info failed ";
            }
        }

 if(ClientInfoDone && AutoInfoDone){
    on_Button_CancelNewRepair_clicked();
 }
}


void NewRepair::FillComboMarki()
{
   MyData.OpenConnection("Marki.sqlite");

   QSqlQueryModel * MyModel = new QSqlQueryModel();

   QSqlQuery ShowMakriQry(MyData.CarsDB);
   ShowMakriQry.prepare("SELECT Marki FROM AutoMarki_Table");

   if(! ShowMakriQry.exec()){
       qDebug() << "ShowMakriQry.Exec() SELECT Model_Name FROM AutoMarki_Table fail "<< ShowMakriQry.lastError().text();
   }

   MyModel->setQuery(ShowMakriQry);
   ui->Combo_NewRepair_Marka->setModel(MyModel);
   ui->Combo_NewRepair_Marka->setMaxVisibleItems(10);
   ui->Combo_NewRepair_Marka->setStyleSheet("combobox-popup: 0;");

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

    MyData.OpenConnection("All_Models.sqlite");
    QSqlQueryModel *MyModel = new QSqlQueryModel();
    QSqlQuery ShowModelQry(MyData.CarsDB);

    ShowModelQry.prepare("SELECT Model_Name FROM All_Models_Table WHERE Model_ID='"+QString::number(MarkaIndex)+"' ");


    if(! ShowModelQry.exec()){
        qDebug() << "ShowModelQry.Exec() SELECT Model_Name FROM All_Models_Table fail "<< ShowModelQry.lastError().text();
    }

    MyModel->setQuery(ShowModelQry);
    ui->Combo_NewRepair_Model->setModel(MyModel);
    ui->Combo_NewRepair_Model->setMaxVisibleItems(10);
    ui->Combo_NewRepair_Model->setStyleSheet("combobox-popup: 0;");

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

void NewRepair::on_LText_NewRepairAutoRegNumber_editingFinished()
{
    ui->LText_NewRepairAutoRegNumber->setText(ui->LText_NewRepairAutoRegNumber->text().replace(" ",""));
    ui->LText_NewRepairAutoRegNumber->setText(ui->LText_NewRepairAutoRegNumber->text().toUpper());
}

void NewRepair::on_LText_NewRepairKlientName_editingFinished()
{
    ui->LText_NewRepairKlientName->setText(ui->LText_NewRepairKlientName->text().trimmed());
}

void NewRepair::on_LText_NewRepairKlientPhone_editingFinished()
{
    ui->LText_NewRepairKlientPhone->setText(ui->LText_NewRepairKlientPhone->text().replace(" ",""));
}

void NewRepair::on_LText_NewRepairAutoMillage_editingFinished()
{
    ui->LText_NewRepairAutoMillage->setText(ui->LText_NewRepairAutoMillage->text().replace(" ",""));
}
