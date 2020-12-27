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

private:
    Ui::PrintFormat *ui;
};

#endif // PRINTFORMAT_H
