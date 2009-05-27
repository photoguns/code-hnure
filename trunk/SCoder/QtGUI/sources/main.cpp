#include <QtGui/QApplication>
#include "scoderwizard.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SCoderWizard w;
    w.show();
    return a.exec();
}
