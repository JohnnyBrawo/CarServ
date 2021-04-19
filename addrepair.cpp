#include "addrepair.h"
#include "ui_addrepair.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include "qdebug.h"
#include "QDate"
#include "QDateTime"
#include <QtWidgets>

AddRepair::AddRepair(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddRepair),
    m_uiRepairsNumber(0),
    m_uiSubMenuNumber(0),
    m_dTotalCost(0.0),
    m_NewRepairForm(new NewRepair())
{
    ui->setupUi(this);
    setWindowTitle("Repair Dictionary");
    CenterForm();
    m_strSelCarNumber.clear();
    m_vRepairItem.clear();
    m_vMenusAndSubmebus.clear();


    ui->Combo_RepairAutoRegNumber->setMaxVisibleItems(10);
    ui->Combo_RepairAutoRegNumber->setStyleSheet("combobox-popup: 0;");

    QObject::connect(ui->Button_NewClientRepair, SIGNAL(clicked()), m_NewRepairForm, SLOT(OpenNewRepairWindow()));
    QObject::connect(m_NewRepairForm, SIGNAL(CloseNewRepairForm()), this, SLOT(RestoreAutoRepairForm()));
}

AddRepair::~AddRepair()
{
    delete ui;
}


void AddRepair::FillPage()
{
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

    ui->Combo_RepairAutoRegNumber->setVisible(true);
    ui->L_CarRegNumber->setText("Изберете Региострационен Номер  :   ");
    ui->Button_Search->setText("Въведи");

// @ TODO DElete repeair is not working !!!
    ui->Button_Search->setEnabled(true);
    ui->Combo_RepairAutoRegNumber->setEnabled(true);
    ui->Button_DeleteRepair->setEnabled(false);
    ui->Button_InsertRepair->setEnabled(false);
    ui->Button_RecordRepairs->setEnabled(false);
    ui->Button_InsertSubMenu->setEnabled(false);
    ui->Button_TotalCostCalc->setEnabled(false);
    ui->LText_TotalPrice->setEnabled(false);
    ui->LText_TotalPrice->setText("");
    ui->L_KlientName->setText("");

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
        ui->Button_DeleteRepair->setEnabled(true);
        ui->Button_InsertSubMenu->setEnabled(true);
        m_uiSubMenuNumber = 0;
    }else if(m_uiRepairsNumber>0){
        m_vMenusAndSubmebus[m_uiRepairsNumber-1]++;
        m_uiSubMenuNumber ++;
    }

    m_newRepair->SetRepairIndex(m_uiRepairsNumber,m_uiSubMenuNumber);
    //Finally adding the itemWidget to the list
    ui->RepairList->setItemWidget (listInsertItem, m_newRepair);

}

void AddRepair::on_Button_InsertRepair_clicked()
{
    InsertRepair(false);
}

void AddRepair::on_Button_DeleteRepair_clicked()
{
    QMessageBox::StandardButton UserReply;

    NewRepairItem * m_currentRepair;
    QListWidgetItem *  listDeleteItem;
    listDeleteItem = ui->RepairList->currentItem();

    if(listDeleteItem == nullptr) {
        QMessageBox::information(this,"Attention!","Select repair first  !");
        return;
    }

    ui->RepairList->selectedItems();

    m_currentRepair = static_cast<NewRepairItem*>(ui->RepairList->itemWidget(listDeleteItem));

    //Delete selected item from the listWidget
    qDebug() << " GetRepairIndexText   " << m_currentRepair->GetRepairIndexText();
    QString str = m_currentRepair->GetRepairIndexText();
    QStringList list1 = str.split('.');
    int SubmenuStartIndex = QString(list1.first()).toInt();

     if(m_vMenusAndSubmebus.at(SubmenuStartIndex-1) > 0){
         UserReply= QMessageBox::question(this,"Attention!","All fields will be deleted !",QMessageBox::Ok|QMessageBox::Cancel);
         if(UserReply == QMessageBox::Cancel){
             return;
         }else {
             QListWidgetItem *  listItem;
             unsigned int Cnt = m_vMenusAndSubmebus.at(SubmenuStartIndex-1);
             for(unsigned int i=0,currItem=SubmenuStartIndex; i< Cnt; i++)
             {
                  listItem = ui->RepairList->item(currItem);
                  delete listItem;
                  m_vMenusAndSubmebus[SubmenuStartIndex-1]--;
             }
         }
     }

    delete listDeleteItem;
    m_vMenusAndSubmebus.removeAt(SubmenuStartIndex-1);
     m_uiRepairsNumber--;
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

    ui->LText_TotalPrice->setText("");
    ui->CheckBox_DDS->setChecked(false);
    m_uiSubMenuNumber = 0;
    m_uiRepairsNumber = 0;
    m_dTotalCost = 0.0;
}

bool AddRepair::CheckRecordInformation()
{
    QListWidgetItem *  listItemData;
    NewRepairItem * m_newRepair;
    bool CheckResults = true;


    for(int i=0; i< ui->RepairList->count(); i++)
    {
        listItemData = ui->RepairList->item(i);
        m_newRepair = static_cast<NewRepairItem*>(ui->RepairList->itemWidget(listItemData));

        if( (m_newRepair->GetRepairDescrText().isEmpty() || m_newRepair->GetRepairDescrText() == "0") ||
            ( m_newRepair->GetRepairQuantityText().isEmpty() || m_newRepair->GetRepairQuantityText() == "0") ||
            ( m_newRepair->GetRepairSinglePriceText().isEmpty() || m_newRepair->GetRepairSinglePriceText() == "0") ||
            ( m_newRepair->GetRepairValueText().isEmpty() || m_newRepair->GetRepairValueText() == "0") )
        {
                CheckResults = false;
        }
    }

    if(!CheckResults){
        QMessageBox::information(this,"Attention!","There is 0 or missing value in some fields. Record Fail  !");
            return false;
    }

    return true;
}

void AddRepair::on_Button_RecordRepairs_clicked()
{
    // Record to DATABASE
    RecordRepair();
    if(m_bRecordSuccess ){
        ClearAllinputs();
        // Return to MainForm
        on_Button_ExitRepair_clicked();
    }
     m_bRecordSuccess = true;
}

void AddRepair::RecordRepair()
{
    /// Check for correct input information

    QListWidgetItem *  listItemData;
    NewRepairItem * m_newRepair;

    if(!CheckRecordInformation()){
        m_bRecordSuccess = false;
        return;
    }

    MyData.OpenConnection("Repairs.sqlite");

    for(int i=0; i< ui->RepairList->count(); i++)
    {
        listItemData = ui->RepairList->item(i);
        m_newRepair = static_cast<NewRepairItem*>(ui->RepairList->itemWidget(listItemData));

        ////// Record all repairs for this car

        QSqlQuery AddNewAuto(MyData.CarsDB);
        AddNewAuto.prepare("INSERT INTO Repair_Table(RepairName, RepairQuantity, RepairSinglePrice, RepairValue, RepairTotal, RepairDate, RepairCarRegNumber, DDS) "
                           "VALUES(:RepairName, :RepairQuantity, :RepairSinglePrice, :RepairValue, :RepairTotal, :RepairDate, :RepairCarRegNumber, :DDS )");

        AddNewAuto.bindValue(":RepairName",m_newRepair->GetRepairDescrText());
        AddNewAuto.bindValue(":RepairQuantity",m_newRepair->GetRepairQuantityText());
        AddNewAuto.bindValue(":RepairSinglePrice",m_newRepair->GetRepairSinglePriceText());
        AddNewAuto.bindValue(":RepairValue",m_newRepair->GetRepairValueText());
        AddNewAuto.bindValue(":RepairTotal",ui->LText_TotalPrice->text());
        AddNewAuto.bindValue(":RepairDate",ui->LText_RepairDate->text());
        AddNewAuto.bindValue(":RepairCarRegNumber",m_strSelCarNumber);
        AddNewAuto.bindValue(":DDS", ui->CheckBox_DDS->isChecked());

        if(!AddNewAuto.exec()){
            qDebug() << "INSERT INTO Repair_Table fail "<< AddNewAuto.lastError().text();
        }
    }

    m_bRecordSuccess = true;
    MyData.CloseConnection();
    ClearAllinputs();
    OpenClearWindow();
}

void AddRepair::OpenClearWindow()
{
    SetInitialDesign();
    this->show();
}

void AddRepair::on_Button_Search_clicked()
{
    InsertRepair(false);

    ui->Button_DeleteRepair->setEnabled(false);
    ui->Button_InsertRepair->setEnabled(true);
    ui->Button_RecordRepairs->setEnabled(true);
    ui->Button_InsertSubMenu->setEnabled(true);

    ui->Button_TotalCostCalc->setEnabled(true);
    ui->LText_TotalPrice->setEnabled(true);
    ui->Combo_RepairAutoRegNumber->setEnabled(false);
    ui->Button_Search->setEnabled(false);
    ui->LText_RepairDate->setEnabled(false);
}

void AddRepair::on_Combo_RepairAutoRegNumber_currentIndexChanged(const QString &arg1)
{
    m_strSelCarNumber = arg1;
    SetKlientName(m_strSelCarNumber);
}

void AddRepair::SetKlientName(QString CarNumber){

    int ClientID = 0;
    MyData.OpenConnection("Automobiles.sqlite");
    QSqlQuery ShowModelQry(MyData.CarsDB);
    ShowModelQry.prepare("SELECT CLIENT_ID FROM Automobiles_Table WHERE Auto_RegNumber='"+CarNumber+"' ");

    if(! ShowModelQry.exec()){
        qDebug() << "ShowModelQry.Exec() SELECT Auto_RegNumber FROM Automobiles_Table Fail "<< ShowModelQry.lastError().text();
    }else {
        if(ShowModelQry.next()){
            ClientID = ShowModelQry.value(0).toInt();
        }
    }
    MyData.CloseConnection();

    MyData.OpenConnection("Clients.sqlite");
    QSqlQuery ShowClentQry(MyData.CarsDB);
    ShowClentQry.prepare("SELECT ClientName FROM Clients_Table WHERE PR_ID='"+QString::number(ClientID)+"' ");

    if(! ShowClentQry.exec()){
        qDebug() << "ShowClentQry.Exec() SELECT ClientName FROM Clients_Table Fail "<< ShowModelQry.lastError().text();
    }else {
        if(ShowClentQry.next()){
            ui->L_KlientName->setText(ShowClentQry.value(0).toString());
        }
    }
    MyData.CloseConnection();

}

void AddRepair::on_Button_InsertSubMenu_clicked()
{
    InsertRepair(true);
}


void AddRepair::on_Button_TotalCostCalc_clicked()
{
    QListWidgetItem *  listItemData;
    NewRepairItem * m_CurrentRepair;
    double totalCost = 0.0;

    for(int i=0; i< ui->RepairList->count(); i++)
    {
        listItemData = ui->RepairList->item(i);
        m_CurrentRepair = static_cast<NewRepairItem*>(ui->RepairList->itemWidget(listItemData));
        if( m_CurrentRepair->GetRepairValueText()=="0" && !m_CurrentRepair->GetRepairDescrText().isEmpty() ){
            double CalcValue = 0.0;
            CalcValue = m_CurrentRepair->GetRepairQuantityText().toDouble() * m_CurrentRepair->GetRepairSinglePriceText().toDouble();
            if(CalcValue == 0.0){
                m_CurrentRepair->SetRepairValueText(QString::number(0));
            }else {
                m_CurrentRepair->SetRepairValueText(QString::number(CalcValue, 'f', 2));
            }
        }
    }


    for(int i=0; i< ui->RepairList->count(); i++)
    {
        listItemData = ui->RepairList->item(i);
        m_CurrentRepair = static_cast<NewRepairItem*>(ui->RepairList->itemWidget(listItemData));

        if(!m_CurrentRepair->GetRepairDescrText().isEmpty()){
            totalCost += m_CurrentRepair->GetRepairValueText().toDouble();
        }
        else{
            qDebug() << " Skip total price ";
        }
    }

    m_dTotalCost = totalCost;
    if(ui->CheckBox_DDS->isChecked()){
        totalCost = totalCost + (totalCost/5);
    }

    if(totalCost == 0.00){
        ui->LText_TotalPrice->setText(QString::number(0));
    }
    else {
        ui->LText_TotalPrice->setText(QString::number(totalCost, 'f',2));
    }
}

void AddRepair::on_Button_NewClientRepair_clicked()
{
    this->hide();
    SetInitialDesign();
}

void AddRepair::RestoreAutoRepairForm()
{
    this->show();
    SetInitialDesign();
}


void AddRepair::on_CheckBox_DDS_stateChanged(int arg1)
{
   if(!ui->LText_TotalPrice->text().isEmpty() && ui->LText_TotalPrice->text().toDouble()!=0.0)
   {
       double TotalPrice = m_dTotalCost;
           if(arg1==2) {
               TotalPrice = TotalPrice + (TotalPrice/5);
           }
           ui->LText_TotalPrice->setText(QString::number(TotalPrice, 'f',2));
    }
    qDebug() << " on_checkBox_clicked " << arg1;
}
