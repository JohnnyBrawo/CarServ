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
    ui(new Ui::AddRepair),
    m_uiRepairsNumber(0),
    m_uiSubMenuNumber(0)
{
    ui->setupUi(this);
    setWindowTitle("Repair Dictionary");
    CenterForm();
//    m_bChecked = false;
    m_strSelCarNumber.clear();
    m_vRepairItem.clear();
    m_vMenusAndSubmebus.clear();

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
/** Bez toq buton zasega **/
    ui->Check_RandomClient->setChecked(false);
    ui->Check_RandomClient->setVisible(false);


    ui->LText_RandomClient->setVisible(false);
    ui->LText_RandClientName->setVisible(false);
    ui->Combo_RepairAutoRegNumber->setVisible(true);
    ui->L_CarRegNumber->setText("Изберете Региострационен Номер  :   ");
    ui->L_RandClientName->setVisible(false);
    ui->Button_Search->setText("Въведи");

    ui->Button_Search->setEnabled(true);
    ui->Combo_RepairAutoRegNumber->setEnabled(true);
    ui->Button_DeleteRepair->setEnabled(false);
    ui->Button_InsertRepair->setEnabled(false);
    ui->Button_RecordRepairs->setEnabled(false);
    FillPage();
}

void AddRepair::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-static_cast<int>(width()*0.5), center.y()-static_cast<int>(height()*0.5) );
}

void AddRepair::on_Button_ExitRepair_clicked()
{
    emit CloseNewRepairForm();
    ClearAllinputs();
    SetInitialDesign();
    this->hide();
}

void AddRepair::InsertRepair(bool SubMenu)
{

    qDebug() << " INSERT  ";

    //Creating a new list widget item whose parent is the listwidget itself
    QListWidgetItem *listInsertItem = new QListWidgetItem(ui->RepairList);

    //Adding the item to the listwidget
    ui->RepairList->addItem (listInsertItem);

    //Creating an object of the designed widget which is to be added to the listwidget
    NewRepairItem *m_newRepair = new NewRepairItem;

    //Making sure that the listInsertItem has the same size as the TheNewRepairItem
    listInsertItem->setSizeHint (m_newRepair->sizeHint ());

    if(!SubMenu){
        m_uiRepairsNumber ++;
        m_vMenusAndSubmebus.push_back(0);
        m_uiSubMenuNumber = 0;
    }else if(m_uiRepairsNumber>0){
        m_vMenusAndSubmebus[m_uiRepairsNumber-1]++;
        m_uiSubMenuNumber ++;
    }

    m_newRepair->SetRepairIndex(m_uiRepairsNumber,m_uiSubMenuNumber);
    //Finally adding the itemWidget to the list
    ui->RepairList->setItemWidget (listInsertItem, m_newRepair);

//    if(m_uiRepairsNumber > 0)
//    {
//        ui->Button_InsertSubMenu->setEnabled(false); //Da Nqma podmeniuta, a wseki remont da si e otdelen za sebe si
//        ui->Button_InsertSubMenu->setVisible(false);
//        ui->Button_DeleteRepair->setEnabled(true);
//    }

    //ListAllMenus();
}

void AddRepair::on_Button_InsertRepair_clicked()
{
    InsertRepair(false);
}

void AddRepair::on_Button_DeleteRepair_clicked()
{
    qDebug() << " DELETE  ";
    QMessageBox::StandardButton UserReply;
    //ListAllMenus();

    NewRepairItem * m_currentRepair;
    QListWidgetItem *  listDeleteItem;
    listDeleteItem = ui->RepairList->currentItem();

    m_currentRepair = static_cast<NewRepairItem*>(ui->RepairList->itemWidget(listDeleteItem));





    //Delete selected item from the listWidget
    qDebug() << " GetRepairIndexText   " << m_currentRepair->GetRepairIndexText();
    QString str = m_currentRepair->GetRepairIndexText();
    QStringList list1 = str.split('.');
//     qDebug() << " GetRepairIndexText  to LIST " << list1;
     int SubmenuStartIndex = QString(list1.first()).toInt();

     if(m_vMenusAndSubmebus.at(SubmenuStartIndex-1) > 0){
         UserReply= QMessageBox::question(this,"Внимание!","Всички подточки ще бъдат изтрити!",QMessageBox::Ok|QMessageBox::Cancel);
         if(UserReply == QMessageBox::Cancel){
             return;
         }else {
             QListWidgetItem *  listItem;
//             NewRepairItem * m_cu;

             unsigned int Cnt = m_vMenusAndSubmebus.at(SubmenuStartIndex-1);
             for(unsigned int i=0,currItem=SubmenuStartIndex; i< Cnt; i++)
             {
                  listItem = ui->RepairList->item(currItem);
//                  m_cu = static_cast<NewRepairItem*>(ui->RepairList->itemWidget(listItem));
       //           qDebug() << " GetRepairDescrText " << m_cu->GetRepairDescrText();
                  delete listItem;
                  m_vMenusAndSubmebus[SubmenuStartIndex-1]--;
             }
             qDebug() << " SUBMENU DELETE FINISH ";
           //  ListAllMenus();
         }
     }

    delete listDeleteItem;
     // qDebug() << " removeAt index  " << SubmenuStartIndex-1;
     // qDebug() << " m_vMenusAndSubmebus.at(SubmenuStartIndex-1) " <<m_vMenusAndSubmebus.at(SubmenuStartIndex-1);
      m_vMenusAndSubmebus.removeAt(SubmenuStartIndex-1);
    //ListAllMenus();
    ReFillRepairIndexes();

}


void AddRepair::ReFillRepairIndexes()
{
    unsigned int count = static_cast<unsigned int>(ui->RepairList->count());
    NewRepairItem * m_currentRepair;
    QListWidgetItem *  listItem;

    unsigned int CurrentSub=0, CurrMenu = 0;
    // Then clear all fields
    for(unsigned int i=0; i< count; i++)
    {

         listItem = ui->RepairList->item(i);
         m_currentRepair = static_cast<NewRepairItem*>(ui->RepairList->itemWidget(listItem));

         if( m_currentRepair->IsFieldSubmenu()){
             CurrentSub ++;
             m_currentRepair->SetRepairIndex(CurrMenu,CurrentSub);
         }else{
             CurrentSub = 0;
             CurrMenu =i+1;
             m_currentRepair->SetRepairIndex(i+1);
         }
    }

    if(ui->RepairList->count() < 1){
        ui->Button_InsertSubMenu->setEnabled(false);
        ui->Button_DeleteRepair->setEnabled(false);
        m_uiRepairsNumber =0;
    }
}

void AddRepair::ListAllMenus()
{
     qDebug() << "\n\n ListAllMenus";
    for(int i=0; i< m_vMenusAndSubmebus.size(); i++)
    {
         qDebug() << " Field :  " << i << " have    :   " << m_vMenusAndSubmebus.at(i) << " submebus. ";
    }
}

void AddRepair::ClearAllinputs()
{
    int count = ui->RepairList->count();

    // Then clear all fields
    for(int i=0; i< count; i++)
    {
        delete ui->RepairList->item(0);
    }

    m_uiSubMenuNumber = 0;
    m_uiRepairsNumber = 0;
}

bool AddRepair::CheckRecordInformation()
{
    //    QMessageBox::StandardButton UserReply;
    QListWidgetItem *  listRecordItem;
    NewRepairItem * m_newRepair;

    CarsDatabase MyData;
    MyData.OpenConnection("Repairs.sqlite");

    for(int i=0; i< ui->RepairList->count(); i++)
    {
        listRecordItem = ui->RepairList->item(i);
        m_newRepair = static_cast<NewRepairItem*>(ui->RepairList->itemWidget(listRecordItem));
        if(m_newRepair->GetRepairDescrText().isEmpty() && m_newRepair->GetRepairQuantityText().isEmpty() && m_newRepair->GetRepairSinglePriceText().isEmpty() && m_newRepair->GetRepairValueText().isEmpty())
        {
            QMessageBox::information(this,"Празни полета!","Празните полета няма да бъдат записани.");
            //            if(UserReply == QMessageBox::No){
            //                return false;
            //            }
        }
    }
    MyData.CloseConnection();
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

    QListWidgetItem *  listItemData;
    NewRepairItem * m_newRepair;

    CarsDatabase MyData;
    MyData.OpenConnection("Repairs.sqlite");

    for(int i=0; i< ui->RepairList->count(); i++)
    {
//        if(!CheckRecordInformation())
//        {
//            qDebug() << "RecordRepair Rejected because of empty fields ";
//            continue;
//        }

        listItemData = ui->RepairList->item(i);
        m_newRepair = static_cast<NewRepairItem*>(ui->RepairList->itemWidget(listItemData));

        if(m_newRepair->GetRepairDescrText().isEmpty() && m_newRepair->GetRepairQuantityText().isEmpty() && m_newRepair->GetRepairSinglePriceText().isEmpty() && m_newRepair->GetRepairValueText().isEmpty())
        {
//            QMessageBox::information(this,"Празни полета!","Празните полета няма да бъдат записани.");
            //            if(UserReply == QMessageBox::No){
            //                return false;
            //            }
            qDebug() << "Ima prazni poleta - Continue ";
            continue;
        }

        qDebug() << " Записваме !  ";
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


    this->show();
}


//void AddRepair::on_Check_RandomClient_clicked(bool checked)
//{
//    m_bChecked = checked;
//    if(!checked)
//    {
//        SetInitialDesign();
//    }else
//    {
//        SetRandomDesign();
//    }

//}

void AddRepair::on_Button_Search_clicked()
{
//    if (m_bChecked)
//    {
//        qDebug() << " Добавяме колата в базата на колите";
//    }

//    SetInitialDesign();
    for(unsigned int i=0; i< 10; i++)
    {
        InsertRepair(false);
    }

    ui->Button_DeleteRepair->setEnabled(true);
    ui->Button_InsertRepair->setEnabled(true);
    ui->Button_RecordRepairs->setEnabled(true);

    ui->Combo_RepairAutoRegNumber->setEnabled(false);
    ui->Button_Search->setEnabled(false);
    ui->LText_RepairDate->setEnabled(false);

//    ui->RepairList->item(0)->
//            ui->RepairList->setCursor()
}

void AddRepair::on_Combo_RepairAutoRegNumber_currentIndexChanged(const QString &arg1)
{
    m_strSelCarNumber = arg1;
    qDebug() << " Резет на всичко до момента или СЪобщение ?! " << m_strSelCarNumber;
}

void AddRepair::on_Button_InsertSubMenu_clicked()
{
    InsertRepair(true);
}

void AddRepair::on_RepairList_clicked()
{
     qDebug() << " on_RepairList_clicked";
}
