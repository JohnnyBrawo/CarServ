#include "mainwindow.h"
#include <QApplication>
#include "QtCore"
#include "QDir"
#include "qdebug.h"
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


        QString test = QDir::currentPath();
        QFileInfo exec_fileinfo(argv[0]);
        qDebug() << "Executable is in" << exec_fileinfo.absolutePath();

    const char* Msg= "TESDTTESDTSTSTST";
    qDebug() << " Current Path ->   " << test;
    QFile some_file("/home/default/Gosheto/CarServ/test.txt");
        if(!some_file.open(QIODevice::WriteOnly)){
            qDebug() << "Unable to open file";
        } else {
            qDebug() << "File open successfully";
        }

        QTextStream stream( &some_file );
        some_file.write(Msg, qstrlen(Msg) );
        stream << " alal asdl asdlalsda lwsdlaw ";
        some_file.close();
    w.show();

    return a.exec();
}




