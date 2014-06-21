#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load( "trans", "C:/Users/Applemoon/Desktop/C++/PicCutter" );
    a.installTranslator( &translator );

    MainWindow w;
    w.showMaximized();

    return a.exec();
}


/*
-запись по Enter
-выход по Escape
-не выделять малые участки
*/
