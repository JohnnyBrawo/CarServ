#include "printformat.h"
#include "ui_printformat.h"
#include <qdebug.h>

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
    if(CurrField)CurrField->setText(QString::number(m_list.at(3)));
}

void PrintFormat::ReadRepairs()
{
    QRegExp tagExp("\n");
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
        pos = 0;

        // Get Repair name and Go on
        if((pos = RepairsList.at(i).indexOf("Repair name:", pos)) != -1){
            QStringList myStringList = RepairsList.at(i).split(':');
            m_strRepairDescr = "lineEdit_" + QString::number(repair_num) + "_Descr";
            QLineEdit * CurrField =  this->findChild<QLineEdit *>(m_strRepairDescr);
            if(CurrField)CurrField->setText(myStringList.at(1));
            continue;
        }

        pos = 0;
        while ((pos = rx.indexIn(RepairsList.at(i), pos)) != -1) {
            m_list << rx.cap(1).toInt();
            pos += rx.matchedLength();
        }
        if(!m_list.isEmpty()){
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

              qDebug() << " value(1) " <<EditClientsQry.value(1).toString();
              qDebug() << " value(2) " <<EditClientsQry.value(2).toString();
              qDebug() << " value(3) " <<EditClientsQry.value(3).toString();
              qDebug() << " value(4) " <<EditClientsQry.value(4).toString();
              qDebug() << " value(5) " <<EditClientsQry.value(5).toString();

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
    this->show();

}


