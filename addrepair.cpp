#include "addrepair.h"
#include "ui_addrepair.h"
#include "qapplication.h"
#include "qdesktopwidget.h"

AddRepair::AddRepair(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddRepair)
{
    ui->setupUi(this);
    CenterForm();
    InsertRepair();
}

AddRepair::~AddRepair()
{
    delete ui;

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

}
