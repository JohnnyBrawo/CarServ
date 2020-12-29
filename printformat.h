#ifndef PRINTFORMAT_H
#define PRINTFORMAT_H

#include <QDialog>

namespace Ui {
class PrintFormat;
}

class PrintFormat : public QDialog
{
    Q_OBJECT

public:
    explicit PrintFormat(QWidget *parent = nullptr);
    ~PrintFormat();

private slots:
    void on_B_PrintCancel_clicked();

private:
    Ui::PrintFormat *ui;

signals:
    void ClosePrintForm();

private slots:
    void OpenPrintForm();

};

#endif // PRINTFORMAT_H
