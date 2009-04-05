#include "scoder.h"

int main()
{
    //Create a BMP image container
    Container* container = GetBMPContainer("Image.bmp");

    //Create LSB coder
    Coder* coder = GetQuantCoder();

    //Create PRS key
    Key* key = GetQuantKey("Shut your eyes and see", Key::STRING);

    //Hide message into container
    coder->SetMessage(container, "Shut your mouth and talk to me", key);

    //Get message from container
    std::string message = coder->GetMessage(container, key);

    // Cleanup memory
    delete container;
    delete coder;
    delete key;

    return 0;
}