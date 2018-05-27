#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newauto.h"
#include "addrepair.h"
#include "newclient.h"
#include "searchform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    NewClient   *m_NewClient;
    AddRepair   *m_NewRepair;
    NewAuto     *m_NewAuto;
    SearchForm  *m_SearchForm;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Button_Search_clicked();
    void on_Button_AddNewAuto_clicked();
    void on_Button_AddNewClient_clicked();
    void on_Button_AddNewRepair_clicked();

    void RestoreMainForm();
    void CenterForm();

};

#endif // MAINWINDOW_H
