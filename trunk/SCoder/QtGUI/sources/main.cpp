#include <QtGui/QApplication>
#include <QTranslator>
#include "scoderwizard.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("scoder_ru");

    a.installTranslator(&translator);

    SCoderWizard w;
    w.show();
    return a.exec();
}
