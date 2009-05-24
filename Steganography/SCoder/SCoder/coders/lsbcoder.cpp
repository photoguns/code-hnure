////////////////////////////////////////////////////////////////////////////////

#include "lsbcoder.h"

////////////////////////////////////////////////////////////////////////////////


LSBCoder::LSBCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


LSBCoder::~LSBCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


std::string LSBCoder::GetMessage( const Container* _container, const Key* _key )
{
    // Must be a BMP container
    if ( _container->IsBMPContainer() )
    {
        // Get container
        const BMPContainer* container = 
            static_cast<const BMPContainer*>(_container);

        // Setup BMP container
        SetupContainer(container);

        // Get message length first
        unsigned long messageLength = GetMessageLength();

        // Get message text
        return GetMessageText(messageLength);
    }

    // Error, not a BMP container
    return "";
}


////////////////////////////////////////////////////////////////////////////////


void LSBCoder::SetMessage( Container* _container, const std::string& _message, 
                           const Key* _key )
{
    // Must be BMP container
    if ( _container->IsBMPContainer() )
    {
        // Get container
        const BMPContainer* container = 
            static_cast<const BMPContainer*>(_container);

        // Setup BMP container
        SetupContainer(container);

        //Hide message length first
        SetMessageLength( _message.length() );

        // Hide message text
        SetMessageText(_message);
    }
}


////////////////////////////////////////////////////////////////////////////////


void LSBCoder::SetupContainer( const BMPContainer* _container )
{
    // Set current container
    SetContainer(_container);

    // Set default colour and position
    SetCurrColour(Red);
    SetCurrPixelPosition(-1,0);
}


////////////////////////////////////////////////////////////////////////////////


const BMPContainer* LSBCoder::GetContainer() const
{
    return static_cast<const BMPContainer*>(m_Container);
}


////////////////////////////////////////////////////////////////////////////////


BMPContainer* LSBCoder::GetContainer()
{
    return m_Container;
}


////////////////////////////////////////////////////////////////////////////////


void LSBCoder::SetContainer( const BMPContainer* _container )
{
    m_Container = const_cast<BMPContainer*>(_container);
}


////////////////////////////////////////////////////////////////////////////////


unsigned long LSBCoder::GetMessageLength()
{
    // Binary message size
    SizeTBitset messageLength;

    // Read message length
    for (size_t bitsRead = 0; bitsRead < bitsInSizeT; ++bitsRead)
    {
        // Bit
        bool bit;

        // If no space left to read bits - break
        if ( !GetBit(&bit) )
            break;

        // Save bit
        messageLength[bitsRead] = bit;
    }

    // Return message length
    return messageLength.to_ulong();
}


////////////////////////////////////////////////////////////////////////////////


void LSBCoder::SetMessageLength( size_t _length )
{
    // Prepare message length for hiding - convert it to binary
    SizeTBitset length(_length);

    // Write all the bits
    for (size_t bitsWritten = 0; bitsWritten < bitsInSizeT; ++bitsWritten)
    {
        // If no space left to write bits - break
        if ( !SetBit( length[bitsWritten] ) )
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////


std::string LSBCoder::GetMessageText( size_t _length )
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
        if ( !GetBit(&bit) )
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


void LSBCoder::SetMessageText( const std::string& _message )
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
        if ( !SetBit( message[bitsWritten / bitsInChar]
                             [bitsWritten % bitsInChar] ) )
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////


bool LSBCoder::GetBit( bool* _bit )
{
    // Byte
    unsigned char byte;

    // Get next byte
    if ( !GetByte(&byte) )
        return false;

    // Read its LSB
    *_bit = byte & 1;

    // Read is OK
    return true;
}


////////////////////////////////////////////////////////////////////////////////


bool LSBCoder::SetBit( bool _bit )
{
    // Get next byte for writing
    unsigned char byte;

    if ( !GetByte(&byte) )
        // Bit has not been written
        return false;

    // Max byte
    unsigned char maxByte = std::numeric_limits<unsigned char>::max() - 1;
    unsigned char bit = _bit;

    // Write bit to byte
    byte &= bit | maxByte;
    byte |= bit;

    // Write pixel
    SetByte(byte);

    // Bit has been successfully written
    return true;
}


////////////////////////////////////////////////////////////////////////////////


bool LSBCoder::GetByte( unsigned char* _byte )
{
    
    // Which color to choose?
    switch ( GetCurrColour() )
    {
    case Red:
        // Take a new pixel
        if ( !JumpToNextPixel() )
            return false;

        // Green
        SetCurrColour(Green);
        *_byte = GetCurrPixel().Green; 
        break;
    
    case Green:
        // Blue
        SetCurrColour(Blue);
        *_byte = GetCurrPixel().Blue; 
        break;
    
    case Blue:
        // Red
        SetCurrColour(Red);
        *_byte = GetCurrPixel().Red; 
        break;
    }

    return true;
}


////////////////////////////////////////////////////////////////////////////////


void LSBCoder::SetByte( unsigned char _byte )
{
    RGBApixel pixel = GetCurrPixel();

    switch ( GetCurrColour() )
    {
    case Red:
        // Save in red
        pixel.Red = _byte;
        break;

    case Green:
        // Save in green
        pixel.Green = _byte;
        break;

    case Blue:
        // Save in blue
        pixel.Blue = _byte;
        break;
    }

    // Save pixel
    SetCurrPixel(pixel);
}


////////////////////////////////////////////////////////////////////////////////


bool LSBCoder::JumpToNextPixel()
{
    // Get container dimensions
    const int height = GetContainer()->TellHeight();
    const int width = GetContainer()->TellWidth();

    int currHeight, currWidth;
    GetCurrPixelPosition(&currHeight, &currWidth);

    // Lowest pixel in a column
    if ( ++currHeight == height )
    {
        // Jump to highest pixel
        currHeight = 0;
        ++currWidth;

        // Rightmost pixel
        if (currWidth == width)

            //No pixels left
            return false;
    }

    // Jump to next pixel
    SetCurrPixelPosition(currHeight, currWidth);

    // Next pixel is OK
    return true;
}


////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////


RGBApixel LSBCoder::GetCurrPixel() const
{
    return GetContainer()->GetPixel(m_CurrHeight, m_CurrWidth);
}


////////////////////////////////////////////////////////////////////////////////


void LSBCoder::SetCurrPixel( const RGBApixel& _pixel )
{
    GetContainer()->SetPixel(m_CurrHeight, m_CurrWidth, _pixel);
}


////////////////////////////////////////////////////////////////////////////////


void LSBCoder::GetCurrPixelPosition( int* _i, int* _j ) const
{
    *_i = m_CurrHeight;
    *_j = m_CurrWidth;
}


////////////////////////////////////////////////////////////////////////////////


bool LSBCoder::SetCurrPixelPosition( int _i, int _j )
{
    if ( _i < m_Container->TellHeight() && _j < m_Container->TellWidth() )
    {
        m_CurrHeight = _i;
        m_CurrWidth = _j;
        return true;
    }
    else
        return false;
}


////////////////////////////////////////////////////////////////////////////////


LSBCoder::Colour LSBCoder::GetCurrColour() const
{
    return m_Colour;
}


////////////////////////////////////////////////////////////////////////////////


void LSBCoder::SetCurrColour( Colour _colour )
{
    m_Colour = _colour;
}


////////////////////////////////////////////////////////////////////////////////
