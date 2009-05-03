#include <QtGui/QApplication>
#include "serverui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ServerUI server;
    server.show();
    return app.exec();
}
