#include "mainwindow.h"
#include <QApplication>
#include "QtCore"
#include "QDir"
#include "qdebug.h"
#include <QTextStream>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

// Menu - open file
//        QString test = QDir::currentPath();

    const char* Msg= "TESDTTESDTSTSTST";
//    qDebug() << " Current Path ->   " << test;
//    qDebug() << " applicationFilePath Path ->   " << QCoreApplication::applicationFilePath();

    QFile some_file("/home/default/Gosheto/CarServ/test.txt");
        if(!some_file.open(QIODevice::WriteOnly)){
            qDebug() << "Unable to open file";
        } else {
            qDebug() << "File open successfully";
        }

        QTextStream stream( &some_file );
        some_file.write(Msg, qstrlen(Msg) );
        stream << " alal asdl \n asdlalsda lwsdlaw ";
        some_file.close();
    w.show();

    return a.exec();
}





