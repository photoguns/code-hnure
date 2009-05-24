////////////////////////////////////////////////////////////////////////////////

#include "blockcoder.h"
#include "bmpcontainer.h"
#include "blockkey.h"

////////////////////////////////////////////////////////////////////////////////


BlockCoder::BlockCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


BlockCoder::~BlockCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


void BlockCoder::SetMessage( Container* _container,
                             const std::string& _message, const Key* _key )
{
    // Must be Block key
    if ( _key->IsBlockKey() )
    {
        const BlockKey* key = static_cast<const BlockKey*>(_key);

        // Must be BMP container
        if ( _container->IsBMPContainer() )
        {
            BMPContainer* container = static_cast<BMPContainer*>(_container);

            // Reset data
            m_CurrBlock = 0;

            // Hard coded key length
            const size_t keyLength = 16;

            // Get Block key
            m_Key = key->GetBlockKey(keyLength);

            // Hide message
            LSBCoder::SetMessage(_container, _message);
        }
    }
}


////////////////////////////////////////////////////////////////////////////////


std::string BlockCoder::GetMessage( const Container* _container,
                                    const Key* _key )
{
    // Must be Block key
    if ( _key->IsBlockKey() )
    {
        const BlockKey* key = static_cast<const BlockKey*>(_key);

        // Must be BMP container
        if ( _container->IsBMPContainer() )
        {
            const BMPContainer* container = static_cast<const BMPContainer*>(_container);

            // Reset data
            m_CurrBlock = 0;

            // Hard coded key length
            const size_t keyLength = 16;

            // Get Block key
            m_Key = key->GetBlockKey(keyLength);

            // Get message
            return LSBCoder::GetMessage(_container);
        }
    }

    // Fail
    return "";
}


////////////////////////////////////////////////////////////////////////////////


bool BlockCoder::SetBit( bool _bit )
{
    // Parity bit - sum of all LSBs in a block
    bool parityBit = false;

    // Last byte in a block
    unsigned char byte = 0;

    for (int i = 0; i < m_Key[m_CurrBlock]; ++i)
    {
        // Get pixel byte
        if ( !GetByte(&byte) )
            return false;

        if ( byte % 2 )
            parityBit = !parityBit;
    }

    // Invert LSB
    if (_bit != parityBit)
    {
        // Get copy of byte
        unsigned char copy = byte;

        // Reset LSB
        byte &= 254;

        // Invert LSB and OR with original
        byte |= (~copy & 1);

        // Write modified byte
        SetByte(byte);
    }

    // Prepare next block for next bit
    m_CurrBlock = ++m_CurrBlock % m_Key.size();

    // Bit has been written
    return true;
}


////////////////////////////////////////////////////////////////////////////////


bool BlockCoder::GetBit( bool* _bit )
{
    // Parity bit - sum of all LSBs in a block
    *_bit = false;

    for (int i = 0; i < m_Key[m_CurrBlock]; ++i)
    {
        // Byte in a block
        unsigned char byte;

        // Get pixel byte
        if ( !GetByte(&byte) )
            return false;

        if ( byte % 2 )
            *_bit = !(*_bit);
    }

    // Prepare next block for next bit
    m_CurrBlock = ++m_CurrBlock % m_Key.size();

    // Bit has been read
    return true;
}


////////////////////////////////////////////////////////////////////////////////
