#include "dpremainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("DITA-Preprocessor");
    QCoreApplication::setApplicationVersion("1.0");

    QApplication a(argc, argv);


    Settings::getInstance(QCoreApplication::arguments());

    DPreMainWindow w;
    w.show();
    return a.exec();
}
