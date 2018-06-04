#include "removechangeauto.h"
#include "ui_removechangeauto.h"
#include "carsdatabase.h"
#include <QtWidgets>

RemoveChangeAuto::RemoveChangeAuto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveChangeAuto),
    m_SelectedRegNumber("")
{
    ui->setupUi(this);

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
    CarsDatabase MyData;
    MyData.OpenConnection("Automobiles.sqlite");
    QSqlQueryModel * MyModel = new QSqlQueryModel();
    QSqlQuery ShowModelQry(MyData.CarsDB);

    ShowModelQry.prepare("SELECT Auto_RegNumber FROM Automobiles_Table ");


    if(! ShowModelQry.exec()){
        qDebug() << "ShowModelQry.Exec() SELECT Auto_RegNumber FROM Automobiles_Table Fail "<< endl;
    }

    MyModel->setQuery(ShowModelQry);
    ui->Combo_DelChangeAutoRegs->setModel(MyModel);
    MyData.CloseConnection();
}


void RemoveChangeAuto::on_Combo_DelChangeAutoRegs_currentIndexChanged(const QString &arg1)
{
    CarsDatabase MyData;
    MyData.OpenConnection("Automobiles.sqlite");
    QSqlQuery ShowModelQry(MyData.CarsDB);

    m_SelectedRegNumber = arg1;

    ShowModelQry.prepare("SELECT * FROM Automobiles_Table WHERE Auto_RegNumber='"+arg1+"' ");


    if(!ShowModelQry.exec()){
        qDebug() << "ShowModelQry.Exec() SELECT Auto_RegNumber FROM Automobiles_Table Fail "<< endl;
    }else {
        while (ShowModelQry.next()) {
            ui->LText_DelChangeMarka->setText(ShowModelQry.value(2).toString());
            ui->LText_DelChangeModel->setText(ShowModelQry.value(3).toString());
            ui->LText_DelChangeYear->setText(ShowModelQry.value(4).toString());
            ui->LText_DelChangeFuel->setText(ShowModelQry.value(5).toString());
            ui->LText_DelChangeRegNumber->setText(ShowModelQry.value(6).toString());
            ui->LText_DelChangeVIN->setText(ShowModelQry.value(7).toString());
            ui->LText_DelChangeType->setText(ShowModelQry.value(8).toString());

            /// Record selected AutoID - attach it to the New client
            m_iAutoID = ShowModelQry.value(0).toInt();
        }



    }


    MyData.CloseConnection();
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
    hide();
    emit CloseDeletePage();
}
