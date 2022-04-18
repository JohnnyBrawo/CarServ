#include "carsdatabase.h"

CarsDatabase::CarsDatabase()
{
    GetWorkingPath();
}


void CarsDatabase::GetWorkingPath()
{
    QString testPath = QApplication::applicationDirPath();
    testPath.append("/DataBase/");
//    qDebug() << " applicationDirPath " << testPath;
// qDebug() << "QSysInfo::productType() " << QSysInfo::productType();
// qDebug() << "testPath " << testPath;

//    if(QSysInfo::productType() == "debian"){
//        int position = testPath.indexOf("/build");
//        if(position != (-1)){
//            testPath.truncate(position);
//            testPath.append("/CarServ/DataBase/");
//        }else {
//            qDebug() << " Cannot find BUILD name in project path for LINUX";
//        }
//    }else if(QSysInfo::productType() == "windows"){
//        int position = testPath.indexOf("/build");
//        if(position!=(-1)){
//            testPath.truncate(position);
//            testPath.append("/CarServ/DataBase/");
//        }else {
//            qDebug() << " Cannot find BUILD name in project path  for Windows ";
//        }
//    }

//    qDebug() << " Final Path " << testPath;
    m_WorkPath = testPath;
}


QString  CarsDatabase::GetDataBasePath(QString DataBaseName)
{
    m_CurrDataName = m_WorkPath + DataBaseName;

//            qDebug() << "GetDataBasePath DataBaseName: " << DataBaseName;
//            qDebug() << "GetDataBasePath m_CurrDataName: " << m_CurrDataName;
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
        return true;
    }
}

void CarsDatabase::RemoveConnection()
{
    CarsDB.removeDatabase(QSqlDatabase::defaultConnection);
}

void CarsDatabase::CloseConnection()
{
    CarsDB.close();
//
}
