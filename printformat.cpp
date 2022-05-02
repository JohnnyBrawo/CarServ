#include "printformat.h"
#include "QDate"
#include "QDateTime"
#include "ui_printformat.h"
#include <qdebug.h>
#include <QPixmap>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QSysInfo>
#include <QFileInfo>
#include <QtWidgets>
#include <QKeyEvent>

PrintFormat::PrintFormat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrintFormat)
{
    ui->setupUi(this);
    CenterForm();
    m_strRepairs = "";
    m_strClientRegNumber="";
}

void PrintFormat::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-static_cast<int>(width()*0.5), center.y()-static_cast<int>(height()*0.5) );
}

PrintFormat::~PrintFormat()
{
    delete ui;
}

void PrintFormat::on_B_PrintCancel_clicked()
{
    CurrentPageToShow = 0;
    PagesToShow = 0;
    emit ClosePrintForm();
    hide();
}

void PrintFormat::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
            on_B_PrintCancel_clicked();
    }
    else{
            QDialog::keyPressEvent(event);
    }
}

void PrintFormat::FillAutoData()
{
    MyData.OpenConnection("Automobiles.sqlite");
    QSqlQuery EditAutoQry(MyData.CarsDB);

    EditAutoQry.prepare("SELECT * FROM Automobiles_Table WHERE Auto_RegNumber='"+m_strClientRegNumber+"' ");

    if(!EditAutoQry.exec()){
        qDebug() << "EditAutoQry.Exec() SELECT Auto_RegNumber FROM Automobiles_Table Fail "<< EditAutoQry.lastError().text();
    }else {
        /// Fill all automobiles with speciffic ClientID or Auto_Reg Number
        if (EditAutoQry.next()) {
            ui->T_AutoRegNumber->setText(m_strClientRegNumber);
            ui->T_AutoMarka->setText(EditAutoQry.value(3).toString());
            ui->T_AutoModel->setText(EditAutoQry.value(4).toString());
            ui->T_AutoVIN->setText(EditAutoQry.value(7).toString());
            ui->T_AutoMilage->setText(EditAutoQry.value(9).toString());

        }else {
            /// Fill all automobiles with No cliet assigned
            qDebug() << " Autos Not Found !  ";
        }
    }

    MyData.CloseConnection();

}

void PrintFormat::FillRepairData(int RepairNum, bool IncludeTaxes)
{
    QLineEdit * CurrField;
    m_strRepairNumber.clear();
    m_strRepairCnt="";
    m_strRepairSPrice="";
    m_strRepairTotal="";

//    qDebug() << " RepairNum "<<RepairNum;
//    qDebug() << " CurrentPageToShow "<<CurrentPageToShow;
//        qDebug() << " CurrentPageToShow "<<CurrentPageToShow*15 + RepairNum;

    m_strRepairNumber = "lineEdit_" + QString::number(RepairNum) + "_NUM";
    CurrField =  this->findChild<QLineEdit *>(m_strRepairNumber);
    if(CurrField)CurrField->setText(QString::number(RepairNum + CurrentPageToShow*15));

    m_strRepairCnt  = "lineEdit_" + QString::number(RepairNum) + "_CNT";
    CurrField =  this->findChild<QLineEdit *>(m_strRepairCnt);
    if(CurrField)CurrField->setText(QString::number(m_list.at(0)));

    m_strRepairSPrice  = "lineEdit_" + QString::number(RepairNum) + "_SPrice";
    CurrField =  this->findChild<QLineEdit *>(m_strRepairSPrice);
    if(CurrField)CurrField->setText(QString::number(m_list.at(1)));

    if(IncludeTaxes){
        m_strRepairTotal  = "lineEdit_" + QString::number(RepairNum) + "_Total_DDS";
    }else {
        m_strRepairTotal  = "lineEdit_" + QString::number(RepairNum) + "_Total_No_DDS";
    }
    CurrField =  this->findChild<QLineEdit *>(m_strRepairTotal);
    if(CurrField)CurrField->setText(QString::number(m_list.at(2)));
}

void PrintFormat::ReadRepairs()
{
    QRegExp tagExp("\n");
    QStringList RepairsList = m_strRepairs.split(tagExp);
//    ui->T_DateRepair->setText(RepairsList.at(1));
    QRegExp rx("(-?\\d+(?:[\\.,]\\d+(?:e\\d+)?)?)");

//    qDebug() << "<ReadRepairs RepairsList.length()"<<RepairsList.length();
    int pos = 0;
    int repair_num = 1;
    for(int i=0;i<RepairsList.length();i++){
        bool bTaxes = false;
        // Get Repair date and go on
        if(RepairsList.at(i) == "Date : "){
            ui->T_DateRepair->setText(RepairsList.at(i+1));
            i++;
            continue;
        }

        //Meet repairs devider - increase count and go on
        if(RepairsList.at(i) == "==================="){

//             qDebug() << " 111 ReadRepairs repair_num  "<<repair_num;
            FillRepairData(repair_num, false);
            repair_num ++;
            continue;
        }

         //Meet repairs end. Next is Total payment only
        if((RepairsList.at(i).indexOf("Total Price", 0)) != -1){
//              qDebug()<<" Exit repairs " ;
               break;
          }

        m_list.clear();
        // Get Repair name and Go on
        if((RepairsList.at(i).indexOf("Repair name:", 0)) != -1){
            QStringList myStringList = RepairsList.at(i).split(':');
            m_strRepairDescr = "lineEdit_" + QString::number(repair_num) + "_Descr";
            QLineEdit * CurrField =  this->findChild<QLineEdit *>(m_strRepairDescr);
            if(CurrField)CurrField->setText(myStringList.at(1));
            continue;
        }

        pos = 0;
        if((RepairsList.at(i).indexOf("Taxes included", 0)) != -1){
            bTaxes = true;
        }

        while ((pos = rx.indexIn(RepairsList.at(i), pos)) != -1) {
            m_list << rx.cap(1).toDouble();
            pos += rx.matchedLength();
        }

//        qDebug() << " m_list "<<m_list.isEmpty();
        /** Nothing to record - go to next line */
        if(m_list.isEmpty()){
            i++;
            continue;
        }

        double TotalValueDDS = m_list.at(2) + m_list.at(2)/5;

        m_list << TotalValueDDS;

//        qDebug() << " m_list "<<m_list<< " Taxes "<<bTaxes;
        if(!m_list.isEmpty()){
//            qDebug() << " 2222 ReadRepairs repair_num  "<<repair_num;
            FillRepairData(repair_num, bTaxes);
            EnableDDSCheck(repair_num);
        }
    }
}


void PrintFormat::FillClientData()
{
    MyData.OpenConnection("Clients.sqlite");
    QSqlQuery EditClientsQry(MyData.CarsDB);
    EditClientsQry.prepare("SELECT * FROM Clients_Table WHERE ClientName='"+m_strClient_Name+"' ");

    if(! EditClientsQry.exec()){
        qDebug() << "ShowClientsQry.Exec() SELECT ClientName FROM Clients_Table fail "<< EditClientsQry.lastError().text();
    }else {
         while (EditClientsQry.next()) {
            ui->T_KlientName->setText(EditClientsQry.value(1).toString());
            ui->T_KlientCity->setText(EditClientsQry.value(2).toString());
            ui->T_KlientFirm->setText(EditClientsQry.value(3).toString());
            ui->T_KlientPhone->setText(EditClientsQry.value(4).toString());
            ui->T_KlientAdress->setText(EditClientsQry.value(5).toString());
         }
    }

    MyData.CloseConnection();
}

void PrintFormat::SetPagesPrintView()
{
    ClearAllFields();
    ui->B_NextPage->setVisible(CurrentPageToShow<=strRepairTextOnPage.size()-1?true:false);
    ui->B_PreviousPage->setVisible(CurrentPageToShow>=0?true:false);
    ui->L_PageNumber->setVisible(true);
    ui->L_PageNumber->setText(QString::number(CurrentPageToShow+1));
    m_strRepairs = strRepairTextOnPage.at(CurrentPageToShow);
    ReadRepairs();
}

void PrintFormat::SetStandardPrintView()
{
    ui->B_NextPage->setVisible(false);
    ui->B_PreviousPage->setVisible(false);
    ui->L_PageNumber->setVisible(false);
}


void PrintFormat::OpenPrintForm()
{
//    qDebug() << " PrintFormat::OpenPrintForm() ENTER  ";

    ui->L_TotalWorkCost->setVisible(false);
    ui->L_TotalWorkCostValue->setVisible(false);
    ui->B_NextPage->setVisible(false);

    FillAutoData();
    FillClientData();
    HideAllDDSChecks();

    /** Set print Pages View */
    if(PagesToShow > 0){
        SetPagesPrintView();
    }
    else  /** Set Standard Print View */
    {
        SetStandardPrintView();
        ReadRepairs();
    }

    QDate CurrentDate= QDate::currentDate();
    ui->T_Data->setText(CurrentDate.toString("dd.MM.yyyy"));
    ui->lineEdit_TotalPay_Value->setText(QString::number(m_TotalRepairCost));
    if(m_bTaxesIncluded){
        ui->lineEdit_DDS_CostValue->setText(QString::number(m_TotalRepairCost/5));
        ui->lineEdit_TotalRepairCost_Value->setText(QString::number(m_TotalRepairCost - (m_TotalRepairCost/5) ));
    }else{
        ui->lineEdit_DDS_CostValue->setText("-");
        ui->lineEdit_TotalRepairCost_Value->setText(QString::number(m_TotalRepairCost ));
    }

    this->show();

}

QString PrintFormat::GetWorkingPath()
{
    // Format Output filename - date and time in case of multiple repairs in one day fo same car
    QLocale testLocale = QLocale(QLocale::English, QLocale::UnitedStates);
    QString CurrentDate = testLocale.toString(QDate::currentDate(),"dd.MM.yyyy");
    QString ScreenShotPath = QApplication::applicationDirPath();
    ScreenShotPath.append("/Repairs/" + m_strClient_Name + "/" + CurrentDate + "/");
    QDir::root().mkpath(ScreenShotPath);
    return ScreenShotPath;
}

void PrintFormat::HideAllDDSChecks()
{
    /** Hide All chackBoxes for Print View */
    QString strCheckBox_Name = "";
    QCheckBox * CurrField;
    for(int CheckBoxNum = 0; CheckBoxNum < 16; CheckBoxNum ++){
        strCheckBox_Name = "Check_DDS_" + QString::number(CheckBoxNum);
        CurrField =  this->findChild<QCheckBox *>(strCheckBox_Name);
        if(CurrField)CurrField->setVisible(false);
    }
    /*********************************************/
}


void PrintFormat::EnableDDSCheck(unsigned short CheckIndex)
{
    /** Hide All chackBoxes for Print View */
    QString strCheckBox_Name = "Check_DDS_" + QString::number(CheckIndex);
    QCheckBox * CurrField;
    CurrField =  this->findChild<QCheckBox *>(strCheckBox_Name);
    if(CurrField)CurrField->setVisible(true);
    /*********************************************/
}


void PrintFormat::on_B_PrintDocument_clicked()
{
    for(int i=0; i <PagesToShow;i++){
        on_B_PreviousPage_clicked();
    }

    m_bPrintingDone = true;
    for(int Page=0; Page <PagesToShow; Page++){

        ui->B_PrintCancel->setVisible(false);
        ui->B_PrintDocument->setVisible(false);
        ui->B_NextPage->setVisible(false);
        ui->B_PreviousPage->setVisible(false);
        ui->L_PageNumber->setVisible(false);

        HideAllDDSChecks();

        ui->L_AutoMarka->setFocus();

        auto active_window = qApp->activeWindow();
        if (active_window) //could be null if your app doesn't have focus
        {
            QPixmap pixmap(active_window->size());
            active_window->render(&pixmap);

            // Format Output filename - date and time in case of multiple repairs in one day fo same car
            QLocale testLocale = QLocale(QLocale::English, QLocale::UnitedStates);
            QString CurrentTime = testLocale.toString(QDateTime::currentDateTime(), "dddd_dd_MMMM_yyyy_hh_mm_ss");
            ui->B_PrintCancel->setVisible(true);
            ui->B_PrintDocument->setVisible(true);
            if(!pixmap.save(GetWorkingPath() + m_strClientRegNumber + "_" + CurrentTime + "_PAGE_" + QString::number(Page) + ".png"))
            {
                m_bPrintingDone = false;
//                qDebug() << " Something Wrong with SnapShot ! ";
            }
        }
        on_B_NextPage_clicked();
    }
    QMessageBox::information(this,"Success!","Print Page is saved for printing!");
    m_bPrintingDone = true;
    on_B_PrintCancel_clicked();
}

void PrintFormat::on_B_NextPage_clicked()
{
//     qDebug() << " NextPage_clicked ";
    if((CurrentPageToShow + 1) == strRepairTextOnPage.size() ) return;
    CurrentPageToShow++;
    SetPagesPrintView();
}

void PrintFormat::on_B_PreviousPage_clicked()
{
//    qDebug() << " PreviousPage_clicked ";
    if(CurrentPageToShow == 0) return;
    CurrentPageToShow--;
    SetPagesPrintView();
}

void PrintFormat::ClearAllFields()
{
    HideAllDDSChecks();
    QLineEdit * CurrField;
    QString m_strItemName("");

    for(int CheckBoxNum = 1; CheckBoxNum < 16; CheckBoxNum ++){
//      qDebug() << " RepairNum "<<CheckBoxNum;
      m_strItemName = "lineEdit_" + QString::number(CheckBoxNum) + "_Descr";
      CurrField =  this->findChild<QLineEdit *>(m_strItemName);
      if(CurrField)CurrField->setText("");

      m_strItemName = "lineEdit_" + QString::number(CheckBoxNum) + "_NUM";
      CurrField =  this->findChild<QLineEdit *>(m_strItemName);
      if(CurrField)CurrField->setText("");

      m_strItemName  = "lineEdit_" + QString::number(CheckBoxNum) + "_CNT";
      CurrField =  this->findChild<QLineEdit *>(m_strItemName);
      if(CurrField)CurrField->setText("");

      m_strItemName  = "lineEdit_" + QString::number(CheckBoxNum) + "_SPrice";
      CurrField =  this->findChild<QLineEdit *>(m_strItemName);
      if(CurrField)CurrField->setText("");

      m_strItemName  = "lineEdit_" + QString::number(CheckBoxNum) + "_Total_No_DDS";
      CurrField =  this->findChild<QLineEdit *>(m_strItemName);
      if(CurrField)CurrField->setText("");
    }
}
