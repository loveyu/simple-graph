#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QTextCodec *xcodec = QTextCodec::codecForLocale() ;
    QString exeDir = xcodec->toUnicode( QByteArray(argv[0]) ) ;
    QString BKE_CURRENT_DIR = QFileInfo( exeDir ).path() ;
    QApplication::setLibraryPaths( QApplication::libraryPaths() << BKE_CURRENT_DIR) ;

    QApplication a(argc, argv);
    QTranslator appTranslator;

    appTranslator.load("zh_CN");
    a.installTranslator(&appTranslator);

    MainWindow w;
    w.show();

    return a.exec();
}
