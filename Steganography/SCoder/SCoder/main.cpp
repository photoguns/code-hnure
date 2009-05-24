#include "scoder.h"

int main()
{
    //Create a BMP image container
    Container* container = GetWaveContainer("1.wav");

    //Create LSB coder
    Coder* coder = GetLSBSoundCoder();

    //Create PRS key
    Key* key = GetQuantKey("Shut your eyes and see", Key::STRING);

    //Hide message into container
    coder->SetMessage(container, "Shut seeasdasdasSS", key);

    container->Save("2.wav");
    container->Open("2.wav");

    //Get message from container
    std::string message = coder->GetMessage(container, key);

    // Cleanup memory
    delete container;
    delete coder;
    delete key;

    return 0;
}