#ifndef FINDAUTO_H
#define FINDAUTO_H

#include <QDialog>

namespace Ui {
class FindAuto;
}

class FindAuto : public QDialog
{
    Q_OBJECT    

private:
    Ui::FindAuto *ui;
    void CenterForm();

public:
    explicit FindAuto(QWidget *parent = 0);
    ~FindAuto();

signals:
    void CloseAddAutoForm();

private slots:
    void on_Button_FindAutoDone_clicked();
    void on_Button_FindAutoCancel_clicked();
    void OpenClearWindow();


};

#endif // FINDAUTO_H
