#ifndef CARSDATABASE_H
#define CARSDATABASE_H

#include <QtSql>
#include <QString>
#include <QDebug>
#include <QApplication>
#include <QFile>
#include <QSysInfo>

class CarsDatabase
{
private:
    QString m_CurrDataName;
    QString m_WorkPath;
    QString m_osType;
public:
    CarsDatabase();
    QSqlDatabase CarsDB;

    void GetWorkingPath();
    bool OpenConnection(QString DataBaseName);
    QString GetDataBasePath(QString DataBaseName);
    void CloseConnection();
    void SetProjectWotkPath(QString Path){m_WorkPath = Path;}
    void SetOSType(QString OSType) {m_osType=OSType;}
    void RemoveConnection();

};

#endif // CARSDATABASE_H
