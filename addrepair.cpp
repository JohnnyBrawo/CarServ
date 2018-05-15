#include "addrepair.h"
#include "ui_addrepair.h"

AddRepair::AddRepair(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddRepair)
{
    ui->setupUi(this);
    ui->RepairList->setAutoScroll(true);
    ui->RepairList->setPalette(QColor(255,255,225,255));
}

AddRepair::~AddRepair()
{
    delete ui;

}

void AddRepair::on_Button_ExitRepair_clicked()
{
    emit CloseNewRepairForm();
    this->hide();
}

void AddRepair::on_Button_InsertRepair_clicked()
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

void AddRepair::on_Button_DeleteRepair_clicked()
{
    //Delete selected item from the listWidget
       delete ui->RepairList->currentItem ();
}

void AddRepair::on_pushButton_clicked()
{
//  Trqbva da nameri nomera na kolata w bazata. Move da ima "Случаен клиент" отметка, за такива ,които не са редовни в сервиза.
//  Drugiq variant e da se zarezda forma za tyrsene na weche nalichen klient
//
}
