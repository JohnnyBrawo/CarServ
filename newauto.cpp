#include "newauto.h"
#include "ui_newauto.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include <qdebug.h>
#include <QtWidgets>

// Must have Automobile database here

NewAuto::NewAuto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAuto)
{
    ui->setupUi(this);
    m_strSelectedCarReg = "None";
    CenterForm();
    setWindowTitle("New Auto");

    ui->Combo_NewAuto_Model->setMaxVisibleItems(10);
    ui->Combo_NewAuto_Model->setStyleSheet("combobox-popup: 0;");

    ui->Combo_NewAuto_Marka->setMaxVisibleItems(10);
    ui->Combo_NewAuto_Marka->setStyleSheet("combobox-popup: 0;");

    ui->Combo_NewAuto_Year->setMaxVisibleItems(10);
    ui->Combo_NewAuto_Year->setStyleSheet("combobox-popup: 0;");
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
    move(center.x()-static_cast<int>(width()*0.5), center.y()-static_cast<int>(height()*0.5) );
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
//    QMessageBox::StandardButton UserReply;

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

    return true;
}


bool NewAuto::CheckRecordObligatory(){

    if(!CheckSelected(ui->Combo_NewAuto_Marka->currentText()) || !CheckSelected(ui->LText_NewAutoRegNumber->text()) ){

        QMessageBox::information(this,"Attention!","Missing information in some fields( * ).");
         return false;
     }

    return true;
}

void NewAuto::on_Button_AddNewAuto_clicked()
{
    if(!CheckRecordObligatory()){
        return;
    }
    if(!CheckRecordInformation())
    {
         qDebug() << "INSERT Rejected because of empty fields ";
        return;
    }

    if(!AddCarInfo(ui->LText_NewAutoRegNumber->text(), ui->Combo_NewAuto_Marka->currentText(), ui->Combo_NewAuto_Model->currentText(),
                  ui->Combo_NewAuto_Year->currentText(), ui->Combo_NewAuto_Fuel->currentText(), ui->LText_NewAutoVIN->text(), ui->Combo_NewAuto_Type->currentText()))
    {
         ClearAllFields();
    }else {
        emit on_Button_CancelNewAuto_clicked();
    }
}


void NewAuto::FillComboMarki()
{

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
    if((static_cast<int>(SelectedString.size()) < 2 ) || (SelectedString == "Select") || SelectedString == "")
    {
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

bool NewAuto::AutoExsist(QString RegNum)
{
    MyData.OpenConnection("Automobiles.sqlite");
    QSqlQuery ShowModelQry(MyData.CarsDB);
    bool m_bfound = false;
    ShowModelQry.prepare("SELECT Auto_RegNumber FROM Automobiles_Table WHERE Auto_RegNumber='"+RegNum+"' ");

    if(ShowModelQry.exec()){
       if(ShowModelQry.next()){
           m_bfound = true;
       }
    }else{
          qDebug() << " AutoExsist Ima problem s cheteneto ot bazata ";
    }

    MyData.CloseConnection();
    return m_bfound;
}


bool NewAuto::AddCarInfo(QString RegNumber, QString AutoMarka, QString AutoModel, QString AutoYear,
                         QString AutoFuel, QString AutoVIN, QString AutoType)
{
    if (AutoExsist(RegNumber)) {
       QMessageBox::information(this,"Error!","There is automobile with this registration !! ");
       return false;
    }
    qDebug() << " NewAuto::AddCarInfo : " <<
                " RegNumber " << RegNumber<<
                " AutoMarka " << AutoMarka<<
                " AutoModel " << AutoModel<<
                " AutoYear " << AutoYear<<
                " AutoFuel " << AutoFuel<<
                " AutoVIN " << AutoVIN<<
                " AutoType " << AutoType ;

    MyData.OpenConnection("Automobiles.sqlite");
    qDebug() << " zapchwame INSERT INTO Automobiles_Table ";
    QSqlQuery AddNewAuto(MyData.CarsDB);
    AddNewAuto.prepare("INSERT INTO Automobiles_Table(Auto_RegNumber, Auto_Marka, Auto_Model, Auto_Year, Auto_Fuel, Auto_VIN, Auto_Type) "
                       "VALUES(:Auto_RegNumber, :Auto_Marka, :Auto_Model, :Auto_Year, :Auto_Fuel, :Auto_VIN, :Auto_Type)");

    AddNewAuto.bindValue(":Auto_RegNumber",RegNumber);
    AddNewAuto.bindValue(":Auto_Marka",AutoMarka);
    AddNewAuto.bindValue(":Auto_Model",AutoModel);
    AddNewAuto.bindValue(":Auto_Year",AutoYear);
    AddNewAuto.bindValue(":Auto_Fuel",AutoFuel);
    AddNewAuto.bindValue(":Auto_VIN",AutoVIN);
    AddNewAuto.bindValue(":Auto_Type",AutoType);

    m_strSelectedCarReg = ui->LText_NewAutoRegNumber->text();
    if(!AddNewAuto.exec()){
        qDebug() << "INSERT INTO Automobiles_Table fail "<< AddNewAuto.lastError().text();
        MyData.CloseConnection();
        return false;
    }

    MyData.CloseConnection();
    return true;
}

void NewAuto::on_LText_NewAutoRegNumber_editingFinished()
{
    ui->LText_NewAutoRegNumber->setText(ui->LText_NewAutoRegNumber->text().replace(" ",""));
    ui->LText_NewAutoRegNumber->setText(ui->LText_NewAutoRegNumber->text().toUpper());
}

void NewAuto::on_LText_NewAutoVIN_editingFinished()
{
    ui->LText_NewAutoVIN->setText(ui->LText_NewAutoVIN->text().replace(" ",""));
}
