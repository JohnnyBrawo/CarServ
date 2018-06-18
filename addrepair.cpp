#include "addrepair.h"
#include "ui_addrepair.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include "qdebug.h"
#include "QDate"
#include "QDateTime"
#include "carsdatabase.h"
#include <QtWidgets>

AddRepair::AddRepair(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddRepair)
{
    ui->setupUi(this);
    setWindowTitle("Repair Dictionary");
    CenterForm();
    m_bChecked = false;
    m_strSelCarNumber.clear();
    m_vRepairItem.clear();
    RepairsNumber = 0;
}

AddRepair::~AddRepair()
{
    delete ui;

}

void AddRepair::SetRandomDesign()
{
    QDate CurrentDate= QDate::currentDate();

    ui->LText_RepairDate->setText(CurrentDate.toString("dd.MM.yyyy"));

    ui->LText_RandomClient->setVisible(true);
    ui->LText_RandClientName->setVisible(true);
    ui->Combo_RepairAutoRegNumber->setVisible(false);
    ui->L_RandClientName->setVisible(true);
    ui->L_CarRegNumber->setText("Въведете Региострационен Номер  :   ");
    ui->Button_Search->setText("Добави");

}

void AddRepair::FillPage()
{
    CarsDatabase MyData;
    MyData.OpenConnection("Automobiles.sqlite");
    QSqlQueryModel * MyModel = new QSqlQueryModel();
    QSqlQuery ShowModelQry(MyData.CarsDB);

    ShowModelQry.prepare("SELECT Auto_RegNumber FROM Automobiles_Table ");


    if(! ShowModelQry.exec()){
        qDebug() << "ShowModelQry.Exec() SELECT Auto_RegNumber FROM Automobiles_Table Fail "<< ShowModelQry.lastError().text();
    }

    MyModel->setQuery(ShowModelQry);

    ui->Combo_RepairAutoRegNumber->setModel(MyModel);
    MyData.CloseConnection();
}

void AddRepair::SetInitialDesign()
{
    QDate CurrentDate= QDate::currentDate();

    ui->LText_RepairDate->setText(CurrentDate.toString("dd.MM.yyyy"));
    ui->Check_RandomClient->setChecked(false);
    ui->LText_RandomClient->setVisible(false);
    ui->LText_RandClientName->setVisible(false);
    ui->Combo_RepairAutoRegNumber->setVisible(true);
    ui->L_CarRegNumber->setText("Изберете Региострационен Номер  :   ");
    ui->L_RandClientName->setVisible(false);
    ui->Button_Search->setText("Въведи");
    FillPage();
}

void AddRepair::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-width()*0.5, center.y()-height()*0.5);
}

void AddRepair::on_Button_ExitRepair_clicked()
{
    emit CloseNewRepairForm();
    ClearAllinputs();
    SetInitialDesign();
    this->hide();
}

void AddRepair::InsertRepair()
{


    //Creating a new list widget item whose parent is the listwidget itself
       QListWidgetItem *listWidgetItem = new QListWidgetItem(ui->RepairList);

       //Adding the item to the listwidget
       ui->RepairList->addItem (listWidgetItem);

       //Creating an object of the designed widget which is to be added to the listwidget
       NewRepairItem *m_newRepair = new NewRepairItem;

//       m_vRepairItem.push_back(m_newRepair);

       //Making sure that the listWidgetItem has the same size as the TheNewRepairItem
       listWidgetItem->setSizeHint (m_newRepair->sizeHint ());

       //Finally adding the itemWidget to the list
       ui->RepairList->setItemWidget (listWidgetItem, m_newRepair);
       RepairsNumber ++;

//       listWidgetItem = ui->RepairList->currentItem();
//       m_newRepair = (NewRepairItem*)(ui->RepairList->itemWidget(listWidgetItem));
//       m_vRepairItem.push_back(m_newRepair);
}

void AddRepair::on_Button_InsertRepair_clicked()
{
   InsertRepair();
}

void AddRepair::on_Button_DeleteRepair_clicked()
{
    //Delete selected item from the listWidget
       delete ui->RepairList->currentItem ();
}

void AddRepair::ClearAllinputs()
{
    int count = ui->RepairList->count();

    // Then clear all fields
    for(int i=0; i< count; i++)
    {
        delete ui->RepairList->item(0);
    }

}

bool AddRepair::CheckRecordInformation()
{
//    QMessageBox::StandardButton UserReply;
    QListWidgetItem *  listWidgetItem;
    NewRepairItem * m_newRepair;

    CarsDatabase MyData;
    MyData.OpenConnection("Repairs.sqlite");

    for(int i=0; i< ui->RepairList->count(); i++)
    {
        listWidgetItem = ui->RepairList->item(i);
        m_newRepair = (NewRepairItem*)(ui->RepairList->itemWidget(listWidgetItem));
        if(m_newRepair->GetRepairDescrText().isEmpty() && m_newRepair->GetRepairQuantityText().isEmpty() && m_newRepair->GetRepairSinglePriceText().isEmpty() && m_newRepair->GetRepairValueText().isEmpty())
        {
            QMessageBox::information(this,"Празни полета!","Празните полета няма да бъдат записани.");
//            if(UserReply == QMessageBox::No){
//                return false;
//            }
        }
    }

    return true;
}

void AddRepair::on_Button_RecordRepairs_clicked()
{
    // Record to DATABASE
    RecordRepair();
    ClearAllinputs();
    // Return to MainForm
    on_Button_ExitRepair_clicked();
}

void AddRepair::RecordRepair()
{
    /// Check for correct input information

    QListWidgetItem *  listWidgetItem;
    NewRepairItem * m_newRepair;

    CarsDatabase MyData;
    MyData.OpenConnection("Repairs.sqlite");

    for(int i=0; i< ui->RepairList->count(); i++)
    {
        if(!CheckRecordInformation())
        {
             qDebug() << "RecordRepair Rejected because of empty fields ";
            continue;
        }

        listWidgetItem = ui->RepairList->item(i);
        m_newRepair = (NewRepairItem*)(ui->RepairList->itemWidget(listWidgetItem));

    ////// Record all repairs for this car

    QSqlQuery AddNewAuto(MyData.CarsDB);
    AddNewAuto.prepare("INSERT INTO Repair_Table(RepairName, RepairQuantity, RepairSinglePrice, RepairValue, RepairTotal, RepairDate, RepairCarRegNumber) "
                       "VALUES(:RepairName, :RepairQuantity, :RepairSinglePrice, :RepairValue, :RepairTotal, :RepairDate, :RepairCarRegNumber)");

    AddNewAuto.bindValue(":RepairName",m_newRepair->GetRepairDescrText());
    AddNewAuto.bindValue(":RepairQuantity",m_newRepair->GetRepairQuantityText());
    AddNewAuto.bindValue(":RepairSinglePrice",m_newRepair->GetRepairSinglePriceText());
    AddNewAuto.bindValue(":RepairValue",m_newRepair->GetRepairValueText());
    AddNewAuto.bindValue(":RepairTotal",ui->LText_TotalPrice->text());
    AddNewAuto.bindValue(":RepairDate",ui->LText_RepairDate->text());
    AddNewAuto.bindValue(":RepairCarRegNumber",m_strSelCarNumber);

    if(!AddNewAuto.exec()){
        qDebug() << "INSERT INTO Repair_Table fail "<< AddNewAuto.lastError().text();
    }
  }
    MyData.CloseConnection();
    ClearAllinputs();
    OpenClearWindow();
}

void AddRepair::OpenClearWindow()
{
    SetInitialDesign();
    InsertRepair();
    this->show();
}


void AddRepair::on_Check_RandomClient_clicked(bool checked)
{
    m_bChecked = checked;
    if(!checked)
    {
        SetInitialDesign();
    }else
    {
        SetRandomDesign();
    }

}
void AddRepair::on_Button_Search_clicked()
{
    if (m_bChecked)
    {
        qDebug() << " Добавяме колата в базата на колите";
    }
}

void AddRepair::on_Combo_RepairAutoRegNumber_currentIndexChanged(const QString &arg1)
{
    m_strSelCarNumber = arg1;
}
