#ifndef CARSDATABASE_H
#define CARSDATABASE_H

#include <QtSql>
#include <QString>
#include <QDebug>
#include <QApplication>
#include <QFile>

class CarsDatabase
{
private:
    QString m_CurrDataName;
public:
    CarsDatabase();
    QSqlDatabase CarsDB;

    bool OpenConnection(QString DataBaseName);
    QString GetDataBasePath(QString DataBaseName);
    QString GetReousrcesPath();
    void CloseConnection();

};

#endif // CARSDATABASE_H
