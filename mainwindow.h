#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addrepair.h"
#include "newclient.h"
#include "searchform.h"
#include "carsform.h"
#include "carsdatabase.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    NewClient   *m_Clients;
    AddRepair   *m_Repairs;
    CarsForm    *m_Autos;
    SearchForm  *m_Search;
    CarsDatabase   *m_BasePath;
    void LoadDesignView();


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Button_Search_clicked();
    void on_Button_OpenAutoForm_clicked();
    void on_Button_OpenClents_clicked();
    void on_Button_OpenRepairs_clicked();

    void RestoreMainForm();
    void CenterForm();

};

#endif // MAINWINDOW_H
