#include "removechangeauto.h"
#include "ui_removechangeauto.h"
#include "carsdatabase.h"
#include <QtWidgets>

RemoveChangeAuto::RemoveChangeAuto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveChangeAuto),
    m_SelectedRegNumber(""),
    m_SelectedClientName("")
{
    ui->setupUi(this);
    m_strAutoID = "None";
    /** Need to refill car table information. Made for double refill table on text change in combos */
    m_bRefillTable=true;

 //   connect(ui->LText_DelChangeRegNumber, SIGNAL(textChanged(const QString &)), this, SLOT(HandleNewText(const QString &)));
}

RemoveChangeAuto::~RemoveChangeAuto()
{
    delete ui;
}

void RemoveChangeAuto::SetUnactiveFields()
{

    //  Enable fields one after other
    ui->LText_DelChangeFuel->setEnabled(false);
    ui->LText_DelChangeMarka->setEnabled(false);
    ui->LText_DelChangeModel->setEnabled(false);
    ui->LText_DelChangeRegNumber->setEnabled(false);
    ui->LText_DelChangeType->setEnabled(false);
    ui->LText_DelChangeVIN->setEnabled(false);
    ui->LText_DelChangeYear->setEnabled(false);

    ui->Button_Record->setVisible(false);
    ui->Button_DeleteAuto->setVisible(false);
    ui->L_ChangeClientName->setVisible(false);
    ui->Combo_DelChangeClientName->setVisible(false);

    ui->L_ChangeAutoMain->setText("Добавяне на автомобил");
}

//void RemoveChangeAuto::HandleNewText(const QString &)
//{
   // Обработва event при натиснат бутон в конкретното поле! Яко.
//}

void RemoveChangeAuto::ClearAllFields()
{
    //  Enable fields one after other
    ui->LText_DelChangeFuel->setText("");
    ui->LText_DelChangeMarka->setText("");
    ui->LText_DelChangeModel->setText("");
    ui->LText_DelChangeRegNumber->setText("");
    ui->LText_DelChangeType->setText("");
    ui->LText_DelChangeVIN->setText("");
    ui->LText_DelChangeYear->setText("");
    ui->Combo_DelChangeAutoRegs->setCurrentIndex(-1);

}

void RemoveChangeAuto::OpenClearEditWindow()
{
    show();
    ui->Button_Add->setVisible(false);
    FillPage();
}

void RemoveChangeAuto::OpenClearWindow()
{
    show();
    ClearAllFields();
    FillPage();
    SetUnactiveFields();

}


void RemoveChangeAuto::FillPage()
{
//    CarsDatabase MyData;
//    MyData.OpenConnection("Automobiles.sqlite");
//    QSqlQueryModel * MyModel = new QSqlQueryModel();
//    QSqlQuery EditAutoQry(MyData.CarsDB);

//    EditAutoQry.prepare("SELECT Auto_RegNumber FROM Automobiles_Table ");


//    if(! EditAutoQry.exec()){
//        qDebug() << "EditAutoQry.Exec() SELECT Auto_RegNumber FROM Automobiles_Table Fail "<< endl;
//    }

//    MyModel->setQuery(EditAutoQry);
//    ui->Combo_DelChangeAutoRegs->setModel(MyModel);
//    MyData.CloseConnection();

    qDebug() << " Fill reg numbers combo box  ";
    FillRegCombo();
    qDebug() << " Fill Clients name combo box  ";
    FillClientNameCombo();
}

void RemoveChangeAuto::FillRegCombo()
{
    CarsDatabase MyData;
    MyData.OpenConnection("Automobiles.sqlite");
    QSqlQueryModel * MyModel = new QSqlQueryModel();
    QSqlQuery EditAutoQry(MyData.CarsDB);

    EditAutoQry.prepare("SELECT Auto_RegNumber FROM Automobiles_Table ");

    if(! EditAutoQry.exec()){
        qDebug() << "EditAutoQry.Exec() SELECT Auto_RegNumber FROM Automobiles_Table Fail "<< endl;
    }
    MyModel->setQuery(EditAutoQry);
    ui->Combo_DelChangeAutoRegs->setModel(MyModel);


//    QSqlQuery ClientIDQry(MyData.CarsDB);
//    ClientIDQry.prepare("SELECT CLIENT_ID FROM Automobiles_Table WHERE Auto_RegNumber='"+m_SelectedRegNumber+"' ");

//    if(! ClientIDQry.exec()){
//        qDebug() << "EditAutoQry.Exec() SELECT Auto_RegNumber FROM Automobiles_Table Fail "<< endl;
//    }else {
//        m_SelectedClientName = ClientIDQry.value(0).toString();
//    }

    MyData.CloseConnection();
}

void RemoveChangeAuto::FillClientNameCombo()
{
    CarsDatabase MyData;
    MyData.OpenConnection("Clients.sqlite");
    QSqlQueryModel * MyModel = new QSqlQueryModel();
    QSqlQuery EditAutoQry(MyData.CarsDB);

    EditAutoQry.prepare("SELECT ClientName FROM Clients_Table ");


    if(! EditAutoQry.exec()){
        qDebug() << "EditAutoQry.Exec() SELECT ClientName FROM Clients_Table Fail "<< endl;
    }

    MyModel->setQuery(EditAutoQry);
    ui->Combo_DelChangeClientName->setModel(MyModel);
    MyData.CloseConnection();
}

void RemoveChangeAuto::on_Combo_DelChangeAutoRegs_currentIndexChanged(const QString &arg1)
{
    if(!m_bRefillTable){
        m_bRefillTable = true;
        return;
    }
    CarsDatabase MyData;
    MyData.OpenConnection("Automobiles.sqlite");
    QSqlQuery EditAutoQry(MyData.CarsDB);

    m_SelectedRegNumber = arg1;

    EditAutoQry.prepare("SELECT * FROM Automobiles_Table WHERE Auto_RegNumber='"+arg1+"' ");


    if(!EditAutoQry.exec()){
        qDebug() << "EditAutoQry.Exec() SELECT Auto_RegNumber FROM Automobiles_Table Fail "<< endl;
    }else {
        while (EditAutoQry.next()) {
             m_SelectedClientName = EditAutoQry.value(1).toString();
            ui->LText_DelChangeMarka->setText(EditAutoQry.value(2).toString());
            ui->LText_DelChangeModel->setText(EditAutoQry.value(3).toString());
            ui->LText_DelChangeYear->setText(EditAutoQry.value(4).toString());
            ui->LText_DelChangeFuel->setText(EditAutoQry.value(5).toString());
            ui->LText_DelChangeRegNumber->setText(EditAutoQry.value(6).toString());
            ui->LText_DelChangeVIN->setText(EditAutoQry.value(7).toString());
            ui->LText_DelChangeType->setText(EditAutoQry.value(8).toString());

            /// Record selected AutoID - attach it to the New client
            m_strAutoID = EditAutoQry.value(0).toString();
        }
    }
    MyData.CloseConnection();

    if(!m_SelectedClientName.isEmpty())
    {
        m_bRefillTable = false;
        ui->Combo_DelChangeClientName->setCurrentIndex(m_SelectedClientName.toInt()-1);
    }
}

void RemoveChangeAuto::ShowAllFieldsText()
{
        qDebug() << " ui->LText_DelChangeMarka->text "  << ui->LText_DelChangeMarka->text();
        qDebug() << " ui->LText_DelChangeModel->text "  << ui->LText_DelChangeModel->text();
        qDebug() << " ui->LText_DelChangeType->text "  << ui->LText_DelChangeType->text();
        qDebug() << " ui->LText_DelChangeYear->text "  << ui->LText_DelChangeYear->text();
        qDebug() << " ui->LText_DelChangeFuel->text "  << ui->LText_DelChangeFuel->text();
        qDebug() << " ui->LText_DelChangeRegNumber->text "  << ui->LText_DelChangeRegNumber->text();
        qDebug() << " ui->LText_DelChangeVIN->text "  << ui->LText_DelChangeVIN->text();
}

void RemoveChangeAuto::on_Button_Record_clicked()
{
    CarsDatabase MyData;
    MyData.OpenConnection("Automobiles.sqlite");

    qDebug() << " m_SelectedRegNumber   " << m_SelectedRegNumber << "Changed " << ui->LText_DelChangeRegNumber->text();
    QSqlQuery AddNewAuto(MyData.CarsDB);
    AddNewAuto.prepare("UPDATE Automobiles_Table set AutoMarka='"+ui->LText_DelChangeMarka->text()+"', AutoModel='"+ui->LText_DelChangeModel->text()+"', AutoYear='"+ui->LText_DelChangeYear->text()+"', AutoFuel='"+ui->LText_DelChangeFuel->text()+"', Auto_RegNumber='"+ui->LText_DelChangeRegNumber->text()+"', AutoVIN='"+ui->LText_DelChangeVIN->text()+"', AutoType='"+ui->LText_DelChangeType->text()+"' WHERE Auto_RegNumber='"+m_SelectedRegNumber+"' ");

    if(!AddNewAuto.exec()){
        qDebug() << "UPDATE Automobiles_Table fail "<< endl;
    }

    // Update Current Changes
    m_SelectedRegNumber = ui->LText_DelChangeRegNumber->text();
    MyData.CloseConnection();
    ClearAllFields();
    FillPage();
}

void RemoveChangeAuto::on_Button_DeleteAuto_clicked()
{
    CarsDatabase MyData;
    MyData.OpenConnection("Automobiles.sqlite");

    qDebug() << " m_SelectedRegNumber   " << m_SelectedRegNumber << "Changed " << ui->LText_DelChangeRegNumber->text();
    QSqlQuery AddNewAuto(MyData.CarsDB);
    AddNewAuto.prepare("DELETE FROM Automobiles_Table WHERE Auto_RegNumber='"+m_SelectedRegNumber+"' ");

     QMessageBox::StandardButton UserReply;
     UserReply =  QMessageBox::question(this,"Внимавай ! ", "Автомобил с регистрационен номер : \n " + ui->LText_DelChangeRegNumber->text() + " \n ще бъде изтрит!! \n Да продължа ли ?",QMessageBox::Yes | QMessageBox::No);
     if(UserReply == QMessageBox::Yes){
         if(!AddNewAuto.exec()){
             qDebug() << "DELETE FROM Automobiles_Table WHERE Auto_RegNumber FAIL "<< endl;
         }

         // Update Current Changes
         m_SelectedRegNumber = ui->LText_DelChangeRegNumber->text();
         MyData.CloseConnection();
         ClearAllFields();
         FillPage();
     }
}

void RemoveChangeAuto::on_Button_Add_clicked()
{
    hide();
    emit CloseDeletePage();
}


void RemoveChangeAuto::on_Button_Back_clicked()
{
    m_strAutoID = "None";
    hide();
    emit CloseDeletePage();
}

void RemoveChangeAuto::on_Combo_DelChangeClientName_currentIndexChanged(const QString &arg1)
{
     qDebug() << "on_Combo_DelChangeClientName_currentIndexChanged "<< arg1;
    if(!m_bRefillTable)
    {
        m_bRefillTable = true;
        /** No need to refill table now*/
        return;
    }

//    m_bRefillTable = false;
    CarsDatabase MyData;
    MyData.OpenConnection("Automobiles.sqlite");
    QSqlQuery EditAutoQry(MyData.CarsDB);

    /**Must be +1 !!! it starts from 1 not 0 !!*/
      m_SelectedClientName = QString::number(ui->Combo_DelChangeClientName->currentIndex()+1);
qDebug() << "m_SelectedClientName "<< m_SelectedClientName;
   if(!EditAutoQry.prepare("SELECT * FROM Automobiles_Table WHERE CLIENT_ID='"+m_SelectedClientName+"' "))
   {
        qDebug() << "m_SelectedClientName  " << m_SelectedClientName << " Not found ";
   }


    if(!EditAutoQry.exec()){
        qDebug() << "EditAutoQry.Exec() SELECT Client ID  FROM Automobiles_Table Fail "<< endl;
    }else {
        if(EditAutoQry.next()) {
            ui->LText_DelChangeMarka->setText(EditAutoQry.value(2).toString());
            ui->LText_DelChangeModel->setText(EditAutoQry.value(3).toString());
            ui->LText_DelChangeYear->setText(EditAutoQry.value(4).toString());
            ui->LText_DelChangeFuel->setText(EditAutoQry.value(5).toString());
            ui->LText_DelChangeRegNumber->setText(EditAutoQry.value(6).toString());
            ui->LText_DelChangeVIN->setText(EditAutoQry.value(7).toString());
            ui->LText_DelChangeType->setText(EditAutoQry.value(8).toString());

            /// Record selected AutoID - attach it to the New client
            m_strAutoID = EditAutoQry.value(0).toString();
            m_bRefillTable = false;
            on_Combo_DelChangeAutoRegs_currentIndexChanged(EditAutoQry.value(6).toString());

            }
        else {
                ClearAllFields();
            }
        }
    MyData.CloseConnection();

}
