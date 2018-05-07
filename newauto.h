#ifndef NEWAUTO_H
#define NEWAUTO_H

#include <QDialog>

namespace Ui {
class NewAuto;
}

class NewAuto : public QDialog
{
    Q_OBJECT

public:
    explicit NewAuto(QWidget *parent = 0);
    ~NewAuto();

private:
    Ui::NewAuto *ui;
};

#endif // NEWAUTO_H
