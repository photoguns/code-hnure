////////////////////////////////////////////////////////////////////////////////

#include "lsbsoundcoder.h"
#include <cassert>

////////////////////////////////////////////////////////////////////////////////


LSBSoundCoder::LSBSoundCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


LSBSoundCoder::~LSBSoundCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


std::string LSBSoundCoder::GetMessage( const Container* _container, const Key* _key )
{
    // Must be a BMP container
    if ( _container->IsWaveContainer() )
    {
        // Get container
        const WAVContainer* container = 
            static_cast<const WAVContainer*>(_container);

        // Setup Wave container
        SetupContainer(container);

        // Get message length first
        unsigned long messageLength = GetMessageLength();

        // Get message text
        return GetMessageText(messageLength);
    }

    // Error, not a Wave container
    return "";
}


////////////////////////////////////////////////////////////////////////////////


void LSBSoundCoder::SetMessage( Container* _container, const std::string& _message, 
                                const Key* _key )
{
    // Must be BMP container
    if ( _container->IsWaveContainer() )
    {
        // Get container
        const WAVContainer* container = 
            static_cast<const WAVContainer*>(_container);

        // Setup Wave container
        SetupContainer(container);

        //Hide message length first
        SetMessageLength( _message.length() );

        // Hide message text
        SetMessageText(_message);
    }
}


////////////////////////////////////////////////////////////////////////////////


void LSBSoundCoder::SetupContainer( const WAVContainer* _container )
{
    // Set current container
    SetContainer(_container);
}


////////////////////////////////////////////////////////////////////////////////


const WAVContainer* LSBSoundCoder::GetContainer() const
{
    return static_cast<const WAVContainer*>(m_Container);
}


////////////////////////////////////////////////////////////////////////////////


WAVContainer* LSBSoundCoder::GetContainer()
{
    return m_Container;
}


////////////////////////////////////////////////////////////////////////////////


void LSBSoundCoder::SetContainer( const WAVContainer* _container )
{
    m_Container = const_cast<WAVContainer*>(_container);
    m_CurrSamplePosition = 100;
}


////////////////////////////////////////////////////////////////////////////////


unsigned long LSBSoundCoder::GetMessageLength()
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


void LSBSoundCoder::SetMessageLength( size_t _length )
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


std::string LSBSoundCoder::GetMessageText( size_t _length )
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


void LSBSoundCoder::SetMessageText( const std::string& _message )
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


bool LSBSoundCoder::GetBit( bool* _bit )
{
    if ( m_CurrSamplePosition < m_Container->Size() )
    {
        short sample = m_Container->GetSample(m_CurrSamplePosition);
        if (sample % 2)
            *_bit = true;
        else
            *_bit = false;

        ++m_CurrSamplePosition;
        return true;
    }
    else
        return false;
}


////////////////////////////////////////////////////////////////////////////////


bool LSBSoundCoder::SetBit( bool _bit )
{
    if ( m_CurrSamplePosition < m_Container->Size() )
    {
        short sample = m_Container->GetSample(m_CurrSamplePosition);

        if ( _bit && (sample % 2 == 0) )
            sample += 1;
        else if ( !_bit && (sample % 2 != 0) )
            sample -= 1;

        m_Container->SetSample(m_CurrSamplePosition, sample);
        ++m_CurrSamplePosition;

        return true;
    }
    else
        return false;
}


////////////////////////////////////////////////////////////////////////////////
