#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addrepair.h"

/**Autos */
#include "carsdatabase.h"
#include "showallcars.h"
#include "newauto.h"
#include "removechangeauto.h"


/**Clients */
#include "newclient.h"
#include "removeclient.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    AddRepair           *m_Repairs;

    /**Autos */
    ShowAllcars         *m_ShowAllAutos;
    NewAuto             *m_NewAuto;
    RemoveChangeAuto    *m_DelEdtiAuto;

    /**Clients  */
    NewClient           *m_NewClient;
    RemoveClient        *m_RemoveClient;


    void LoadDesignView();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Button_Search_clicked();
    void on_Button_OpenRepairs_clicked();

    void RestoreMainForm();
    void CenterForm();

    void on_Exit_clicked();
    void on_ShowAllAutos_triggered();
    void on_AddNewAuto_triggered();
    void on_EditDeleteAuto_triggered();
    void on_DeleteClient_triggered();
    void on_AddNewClient_triggered();
    void on_EditClient_triggered();
};

#endif // MAINWINDOW_H
