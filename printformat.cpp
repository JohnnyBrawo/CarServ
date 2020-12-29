#include "printformat.h"
#include "ui_printformat.h"

PrintFormat::PrintFormat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrintFormat)
{
    ui->setupUi(this);
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

void PrintFormat::OpenPrintForm()
{
    this->show();
}


