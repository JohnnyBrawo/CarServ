#ifndef CARSDATABASE_H
#define CARSDATABASE_H

#include <QtSql>
#include <QString>
#include <QDebug>

class CarsDatabase
{
private:
    QString m_CurrDataName;
public:
    CarsDatabase();
    QSqlDatabase CarsDB;

    bool OpenConnection(QString DataBaseName)
    {
        m_CurrDataName = "/home/default/Gosheto/CarServ/DataBase/" + DataBaseName;
        CarsDB = QSqlDatabase::addDatabase("QSQLITE","CarsConnection");
        CarsDB.setDatabaseName(m_CurrDataName);

        if(!CarsDB.open())
        {
            qDebug() << " Can not open database : " << m_CurrDataName;
            return false;
        }else
         {
            qDebug() << " Connected to database : " << m_CurrDataName;
            return true;
        }
    }

    void CloseConnection()
    {
        CarsDB.close();
        CarsDB.removeDatabase(QSqlDatabase::defaultConnection);
    }
};

#endif // CARSDATABASE_H
