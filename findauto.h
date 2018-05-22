#ifndef FINDAUTO_H
#define FINDAUTO_H

#include <QDialog>

namespace Ui {
class FindAuto;
}

class FindAuto : public QDialog
{
    Q_OBJECT

public:
    explicit FindAuto(QWidget *parent = 0);
    ~FindAuto();

private:
    Ui::FindAuto *ui;
};

#endif // FINDAUTO_H
