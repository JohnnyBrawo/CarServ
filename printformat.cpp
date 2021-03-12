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

PrintFormat::PrintFormat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrintFormat)
{
    ui->setupUi(this);
    m_strRepairs = "";
    m_strClientRegNumber="";
}

PrintFormat::~PrintFormat()
{
    delete ui;
}

void PrintFormat::on_B_PrintCancel_clicked()
{
    emit ClosePrintForm();
    hide();
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

        }else {
            /// Fill all automobiles with No cliet assigned
            qDebug() << " Autos Not Found !  ";
        }
    }

    MyData.CloseConnection();

}

void PrintFormat::FillRepairData(int RepairNum)
{
    QLineEdit * CurrField;
    m_strRepairNumber.clear();
    m_strRepairCnt="";
    m_strRepairSPrice="";
    m_strRepairTotal="";

    m_strRepairNumber = "lineEdit_" + QString::number(RepairNum) + "_NUM";
    CurrField =  this->findChild<QLineEdit *>(m_strRepairNumber);
    if(CurrField)CurrField->setText(QString::number(RepairNum));

    m_strRepairCnt  = "lineEdit_" + QString::number(RepairNum) + "_CNT";
    CurrField =  this->findChild<QLineEdit *>(m_strRepairCnt);
    if(CurrField)CurrField->setText(QString::number(m_list.at(0)));

    m_strRepairSPrice  = "lineEdit_" + QString::number(RepairNum) + "_SPrice";
    CurrField =  this->findChild<QLineEdit *>(m_strRepairSPrice);
    if(CurrField)CurrField->setText(QString::number(m_list.at(1)));

    m_strRepairTotal  = "lineEdit_" + QString::number(RepairNum) + "_Total";
    CurrField =  this->findChild<QLineEdit *>(m_strRepairTotal);
    if(CurrField)CurrField->setText(QString::number(m_list.at(2)));
}

void PrintFormat::ReadRepairs()
{
    QRegExp tagExp("\n");
      qDebug() << " ReadRepairs  "<<m_strRepairs;
    QStringList RepairsList = m_strRepairs.split(tagExp);
    ui->T_DateRepair->setText(RepairsList.at(1));
    QRegExp rx("(-?\\d+(?:[\\.,]\\d+(?:e\\d+)?)?)");


    int pos = 0;
    int repair_num = 1;
    for(int i=0;i<RepairsList.length();i++){

        // Get Repair date and go on
        if(RepairsList.at(i) == "Date : "){
            ui->T_DateRepair->setText(RepairsList.at(i+1));
            i++;
            continue;
        }

        //Meet repairs devider - increase count and go on
        if(RepairsList.at(i) == "==================="){
            FillRepairData(repair_num);
            repair_num ++;
            continue;
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
        while ((pos = rx.indexIn(RepairsList.at(i), pos)) != -1) {
            m_list << rx.cap(1).toDouble();
            pos += rx.matchedLength();
        }
        if(!m_list.isEmpty()){
             qDebug() << " Repair numbers  "<< m_list;
            FillRepairData(repair_num);
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

void PrintFormat::OpenPrintForm()
{
    FillAutoData();
    FillClientData();
    ReadRepairs();
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
    QString ScreenShotPath = QApplication::applicationDirPath();
    ScreenShotPath.append("/Repairs/" + m_strClient_Name + "/");
//    if(QSysInfo::productType() == "debian"){
//        int position = ScreenShotPath.indexOf("/build");
//        ScreenShotPath.truncate(position);
//        ScreenShotPath.append("/Repairs/" + m_strClient_Name + "/");
//    }else if(QSysInfo::productType() == "windows"){
//        int position = ScreenShotPath.indexOf("/build");
//        ScreenShotPath.truncate(position);
//        ScreenShotPath.append("/Repairs/" + m_strClient_Name + "/");
//    }

    QDir::root().mkpath(ScreenShotPath);
    return ScreenShotPath;
}


void PrintFormat::on_B_PrintDocument_clicked()
{
    m_bPrintingDone = false;
    ui->B_PrintCancel->setVisible(false);
    ui->B_PrintDocument->setVisible(false);

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
        if(pixmap.save(GetWorkingPath() + m_strClientRegNumber + "_" + CurrentTime + ".png"))
        {
            QMessageBox::information(this,"Success!","Print Page is saved for printing!");
            m_bPrintingDone = true;
            on_B_PrintCancel_clicked();
        }
        else
        {
            m_bPrintingDone = false;
            qDebug() << " Something Wrong with SnapShot ! ";
        }
    }
}
