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
            testPath.append("CarServ/DataBase/");
        }
        else {
            testPath.append("CarServ\\DataBase\\");
        }
    }
    else {
        qDebug() << " BUILD PATH NOT FOUND   ";
    }
// @ TODO   make this smart !!
    m_CurrDataName = "C:\\Users\\BUFU\\Projects\\DATA_BASE\\" + DataBaseName;

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
