#ifndef NEWREPAIR_H
#define NEWREPAIR_H

#include <QDialog>

namespace Ui {
class NewRepair;
}

class NewRepair : public QDialog
{
    Q_OBJECT

public:
    explicit NewRepair(QWidget *parent = 0);
    ~NewRepair();

private:
    Ui::NewRepair *ui;
};

#endif // NEWREPAIR_H
