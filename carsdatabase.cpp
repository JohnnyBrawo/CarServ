#include "carsdatabase.h"

CarsDatabase::CarsDatabase()
{

}

QString  CarsDatabase::GetReousrcesPath()
{
//    QString testPath = QApplication::applicationDirPath();
//    int position = testPath.indexOf("build");
//    int position2 = testPath.indexOf("/");

// qDebug() << "GetReousrcesPath BUILD PATH NOT FOUND   testPath    "<< testPath;
//    if(position != (-1)){
//        testPath.truncate(position);
//        if(position2 != (-1)){
//            testPath.append("CarServ/Images/");
//        }
//        else {
//            testPath.append("CarServ\\Images\\");
//        }
//    }
//    else {
//        qDebug() << " GetReousrcesPath BUILD PATH NOT FOUND   ";
//    }
    return "/home/default/Gosheto/CarServ/DataBase/";
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
        qDebug() << "GetDataBasePath BUILD PATH NOT FOUND   testPath    "<< testPath << "  DataBaseName  "<<DataBaseName;;
    }
// @ TODO   make this smart !!
// Windows
//    m_CurrDataName = "C:\\Users\\BUFU\\Projects\\DATA_BASE\\" + DataBaseName;b
// Linux
    m_CurrDataName = "/home/default/Gosheto/CarServ/DataBase/"+ DataBaseName;
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
