#include "addrepair.h"
#include "ui_addrepair.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include "qdebug.h"

AddRepair::AddRepair(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddRepair)
{
    ui->setupUi(this);
    setWindowTitle("Repair Dictionary");
    SetInitialDesign();
    CenterForm();
    InsertRepair();
    m_bChecked = false;
}

AddRepair::~AddRepair()
{
    delete ui;

}

void AddRepair::SetRandomDesign()
{
    ui->LText_RandomClient->setVisible(true);
    ui->LText_RandClientName->setVisible(true);
    ui->Combo_RepairAutoRegNumber->setVisible(false);
    ui->L_RandClientName->setVisible(true);
    ui->L_CarRegNumber->setText("Въведете Региострационен Номер  :   ");
    ui->Button_Search->setText("Добави");
}

void AddRepair::SetInitialDesign()
{
    ui->Check_RandomClient->setChecked(false);
    ui->LText_RandomClient->setVisible(false);
    ui->LText_RandClientName->setVisible(false);
    ui->Combo_RepairAutoRegNumber->setVisible(true);
    ui->L_CarRegNumber->setText("Изберете Региострационен Номер  :   ");
    ui->L_RandClientName->setVisible(false);
    ui->Button_Search->setText("Въведи");
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

       //Making sure that the listWidgetItem has the same size as the TheNewRepairItem
       listWidgetItem->setSizeHint (m_newRepair->sizeHint ());

       //Finally adding the itemWidget to the list
       ui->RepairList->setItemWidget (listWidgetItem, m_newRepair);
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

void AddRepair::on_Button_RecordRepairs_clicked()
{
    int count = ui->RepairList->count();
    // Record to DATABASE
    // Then clear all fields
    for(int i=0; i< count; i++)
    {
        delete ui->RepairList->item(0);
    }

    // Return to MainForm
    on_Button_ExitRepair_clicked();
}

void AddRepair::OpenClearWindow()
{
    SetInitialDesign();
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
