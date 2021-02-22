#include "carsdatabase.h"

CarsDatabase::CarsDatabase()
{
    GetWorkingPath();
}


void CarsDatabase::GetWorkingPath()
{
    QString testPath = QApplication::applicationDirPath();

    if(QSysInfo::productType() == "debian"){
        int position = testPath.indexOf("/build");
        testPath.truncate(position);
        testPath.append("/CarServ/DataBase/");
    }else if(QSysInfo::productType() == "Win32"){
        int position = testPath.indexOf("\\build");
        testPath.truncate(position);
        testPath.append("\\CarServ\\DataBase\\");
    }
    m_WorkPath = testPath;
}


QString  CarsDatabase::GetDataBasePath(QString DataBaseName)
{
    m_CurrDataName = m_WorkPath + DataBaseName;

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

void CarsDatabase::CloseConnection()
{
    CarsDB.close();
    CarsDB.removeDatabase(QSqlDatabase::defaultConnection);
}
