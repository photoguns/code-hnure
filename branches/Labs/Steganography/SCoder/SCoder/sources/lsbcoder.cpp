////////////////////////////////////////////////////////////////////////////////

#include "lsbcoder.h"
#include "bmpcontainer.h"

////////////////////////////////////////////////////////////////////////////////


LSBCoder::LSBCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


LSBCoder::~LSBCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


void LSBCoder::HideMessage ( Container* _container, const std::string& _message, 
                             const Key* _key )
{
    // Must be BMP container
    if ( _container->IsBMPContainer() )
    {
        // Clear data
        Reset();

        // Get container
        BMPContainer* container = static_cast<BMPContainer*>(_container);

        //Hide message length first
        HideMessageLength ( container, _message.length() );

        // Hide message text
        HideMessageText (container, _message);
    }
}


////////////////////////////////////////////////////////////////////////////////


std::string LSBCoder::GetMessage ( const Container* _container, const Key* _key )
{
    // Must be BMP container
    if ( _container->IsBMPContainer() )
    {
        // Clear data
        Reset();

        // Get container
        const BMPContainer* container = 
            static_cast<const BMPContainer*>(_container);

        // Get message length first
        unsigned long messageLength = GetMessageLength(container);

        // Get message text
        return GetMessageText(container, messageLength);
    }

    // Error, not a BMP container
    return "";
}


////////////////////////////////////////////////////////////////////////////////


void LSBCoder::Reset()
{
    m_CurrHeight = -1;
    m_CurrWidth = 0;
    m_Colour = Red;
}


////////////////////////////////////////////////////////////////////////////////


void LSBCoder::HideMessageLength ( BMPContainer* _container, size_t _length )
{
    // Prepare message length for hiding - convert it to binary
    SizeTBitset length(_length);

    // Write all the bits
    for (size_t bitsWritten = 0; bitsWritten < bitsInSizeT; ++bitsWritten)
    {
        // If no space left to write bits - break
        if ( !WriteBit(_container, length[bitsWritten]) )
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////


void LSBCoder::HideMessageText ( BMPContainer* _container, const std::string& _message )
{
    // Prepare message for hiding - convert it to binary
    BinaryString message;

    // Convert message to binary
    for (size_t byteN = 0; byteN < _message.length(); ++byteN)

        // Save each letter
        message.push_back(_message[byteN]);

    // Get container dimensions
    const size_t bitsInMessage = _message.size() * bitsInChar;

    // Hide message
    for (size_t bitsWritten = 0; bitsWritten < bitsInMessage; ++bitsWritten)
    {
        // If no space left to write bits - break
        if ( !WriteBit(_container, message[bitsWritten / bitsInChar]
                                          [bitsWritten % bitsInChar]) )
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////


unsigned long LSBCoder::GetMessageLength ( const BMPContainer* _container )
{
    // Binary message size
    SizeTBitset messageLength;

    // Read message length
    for (size_t bitsRead = 0; bitsRead < bitsInSizeT; ++bitsRead)
    {
        // Bit
        bool bit;

        // If no space left to read bits - break
        if ( !ReadBit(_container, bit) )
            break;

        // Save bit
        messageLength[bitsRead] = bit;
    }

    // Return message length
    return messageLength.to_ulong();
}


////////////////////////////////////////////////////////////////////////////////


std::string LSBCoder::GetMessageText ( const BMPContainer* _container,
                                       size_t _length )
{
    // Binary message
    BinaryString message;

    size_t bitsInMessage = _length * bitsInChar;

    // Read message 
    for (size_t bitsRead = 0; bitsRead < bitsInMessage; ++bitsRead )
    {
        // Add new char to message to write bits in
        if (bitsRead % bitsInChar == 0)
            message.push_back( CharBitset() );

        // Bit
        bool bit;

        // If no space left to read bits - break
        if ( !ReadBit(_container, bit) )
            break;

        // Save bit
        message.back()[bitsRead % bitsInChar] = bit;
    }

    // Result string
    std::string str;

    // Convert from binary to char
    for (size_t i = 0; i < message.size(); ++i)
        str += static_cast<char>( message[i].to_ulong() );

    return str;
}


////////////////////////////////////////////////////////////////////////////////


bool LSBCoder::WriteBit( BMPContainer* _container, bool _bit )
{
    // Get next byte for writing
    unsigned char byte;
    if ( !GetNextByte(_container, byte) )
        // Bit has not been written
        return false;

    // Max byte
    unsigned char maxByte = std::numeric_limits<unsigned char>::max();

    // Write bit
    byte &= static_cast<unsigned char>(_bit) | (maxByte - 1);

    // Write pixel
    SetByte(_container, byte);

    // Bit has been successfully written
    return true;
}


////////////////////////////////////////////////////////////////////////////////


bool LSBCoder::GetNextByte ( const BMPContainer* _container, unsigned char& _byte )
{
    // Which color to choose?
    switch (m_Colour)
    {
    case Red:
        // Take a new pixel
        if ( !GetNextPixel(_container, m_Pixel) )
            return false;

        // Green
        m_Colour = Green;
        _byte = m_Pixel.Green; 
        break;
    
    case Green:
        // Blue
        m_Colour = Blue;
        _byte = m_Pixel.Blue; 
        break;
    
    case Blue:
        // Red
        m_Colour = Red;
        _byte = m_Pixel.Red; 
        break;
    }

    return true;
}


////////////////////////////////////////////////////////////////////////////////


void LSBCoder::SetByte ( BMPContainer* _container, unsigned char _byte )
{
    switch (m_Colour)
    {
    case Red:
        // Save in red
        m_Pixel.Red = _byte;
        break;

    case Green:
        // Save in green
        m_Pixel.Green = _byte;
        break;

    case Blue:
        // Save in blue
        m_Pixel.Blue = _byte;
        break;
    }

    // Save pixel
    _container->SetPixel(m_CurrHeight, m_CurrWidth, m_Pixel);
}


////////////////////////////////////////////////////////////////////////////////


bool LSBCoder::GetNextPixel ( const BMPContainer* _container, RGBApixel& _pixel)
{
    // Get container dimensions
    const int height = _container->TellHeight();
    const int width = _container->TellWidth();

    // Lowest pixel in a column
    if ( ++m_CurrHeight == height )
    {
        // Jump to highest pixel
        m_CurrHeight = 0;
        ++m_CurrWidth;

        // Rightmost pixel
        if (m_CurrWidth == width)

            //No pixels left
            return false;
    }

    // Get next pixel
    _pixel = _container->GetPixel(m_CurrHeight, m_CurrWidth);

    // Next pixel is OK
    return true;
}


////////////////////////////////////////////////////////////////////////////////


bool LSBCoder::ReadBit ( const BMPContainer* _container, bool& _bit )
{
    // Byte
    unsigned char byte;

    // Get next byte
    if ( !GetNextByte(_container, byte) )
        return false;

    // Read its LSB
    _bit = byte & 1;

    // Read is OK
    return true;
}


////////////////////////////////////////////////////////////////////////////////
