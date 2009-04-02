#include <iostream>
#include "scoder.h"


int main()
{
    std::cout << "Hello Stego!" << std::endl;

    //Create a BMP image container
    Container* container = new BMPContainer("Image.bmp");

    //Create LSB coder
    Coder* coder = new BlockCoder();

    //Create PRS key
    Key* key = new BlockKey("Key", Key::STRING);

    //Hide message into container
    coder->HideMessage(container, "Message", key);

    //Get message from container
    std::string message = coder->GetMessage(container, key);

    delete container;
    delete coder;
    delete key;
    return 0;
}