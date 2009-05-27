#include "scoder.h"

int main()
{
    //Create a container
    Container* container = GetContainer(SOUND, "1.wav");

    //Create coder
    Coder* coder = GetCoder(ECHO);

    //Create key
    Key* key = GetKey(ECHO, "On", Key::STRING);

    //Hide message into container
    coder->SetMessage(container, "dsddddddddddddddddddddddddddddddddddd", key);

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