#include <QtGui/QApplication>
#include "mainwindow.h"
#include "scoder.h"
#include "wizard.h"

int main(int argc, char *argv[])
{
    ////Create a container
    //Container* container = GetBMPContainer("1.bmp");

    ////Create coder
    //Coder* coder = GetQuantCoder();

    ////Create key
    //Key* key = GetQuantKey("On Air:  Acues - Existrance 14 on AH.FM 23-05-2009 [REPLAY]", Key::STRING);

    ////Hide message into container
    //coder->SetMessage(container, "Ashley Wallbridge Feat Meighan Nealon - My Blood (TyDi Remix)", key);

    //container->Save("2.bmp");
    //container->Open("2.bmp");

    ////Get message from container
    //std::string message = coder->GetMessage(container, key);

    //// Cleanup memory
    //delete container;
    //delete coder;
    //delete key;

    QApplication a(argc, argv);
    SCoderWizard w;
    w.show();
    return a.exec();
}
