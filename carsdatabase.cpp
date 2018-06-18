#include "carsdatabase.h"

CarsDatabase::CarsDatabase()
{

}

QString  CarsDatabase::GetReousrcesPath()
{
    QString testPath = QApplication::applicationDirPath();
    int position = testPath.indexOf("build");
    int position2 = testPath.indexOf("/");


    if(position != (-1)){
            testPath.truncate(position);
            if(position2 != (-1)){
                testPath.append("CarServ/Images/");
            }
            else {
                qDebug() << "WINDOWS ";
                testPath.append("CarServ\\Images\\");
            }
    }
    else {
         qDebug() << " BUILD PATH NOT FOUND   ";
    }
    return testPath;
}

QString  CarsDatabase::GetDataBasePath(QString DataBaseName)
{
    QString testPath = QApplication::applicationDirPath();
    int position = testPath.indexOf("build");
    int position2 = testPath.indexOf("/");


    if(position != (-1)){
            testPath.truncate(position);
            if(position2 != (-1)){
//                qDebug() << "LINUX ";
                testPath.append("CarServ/DataBase/");
            }
            else {
                qDebug() << "WINDOWS ";
                testPath.append("CarServ\\DataBase\\");
            }
    }
    else {
         qDebug() << " BUILD PATH NOT FOUND   ";
    }

    m_CurrDataName = testPath + DataBaseName;

    return m_CurrDataName;
}

bool CarsDatabase::OpenConnection(QString DataBaseName)
{

    CarsDB = QSqlDatabase::addDatabase("QSQLITE","CarsConnection");
    CarsDB.setDatabaseName(GetDataBasePath(DataBaseName));

    if(!CarsDB.open())
    {
        qDebug() << " Can not open database : " << m_CurrDataName;
        return false;
    }else
     {
//        qDebug() << " Connected to database : " << m_CurrDataName;
        return true;
    }
}

void CarsDatabase::CloseConnection()
{
    CarsDB.close();
    CarsDB.removeDatabase(QSqlDatabase::defaultConnection);
}
