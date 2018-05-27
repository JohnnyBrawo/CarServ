#include "searchform.h"
#include "ui_searchform.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include "QDate"
#include "QDateTime"

SearchForm::SearchForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchForm)
{
    ui->setupUi(this);
    setWindowTitle("Search");
    CenterForm();
}

SearchForm::~SearchForm()
{
    delete ui;
}

void SearchForm::OpenClearWindow()
{
    ui->Combo_SearchAuto->setCurrentIndex(0);
    ui->Combo_Search_Klient->setCurrentIndex(0);
    ui->Combo_Search_RegNumber->setCurrentIndex(0);


    QDate CurrentDate= QDate::currentDate();

    ui->LText_SearchFROMdate->setText(CurrentDate.toString("dd.MM.yyyy"));
    ui->LText_SearchTOdate->setText(CurrentDate.toString("dd.MM.yyyy"));

    this->show();
}


void SearchForm::CenterForm()
{
    setFixedSize(geometry().width(), geometry().height());
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-width()*0.5, center.y()-height()*0.5);
}

void SearchForm::on_Button_Search_Back_clicked()
{
    emit CloseSearchForm();
    hide();
}

void SearchForm::on_pushButton_clicked()
{

}
