////////////////////////////////////////////////////////////////////////////////

#include "quantcoder.h"
#include "quantkey.h"

////////////////////////////////////////////////////////////////////////////////


QuantCoder::QuantCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


QuantCoder::~QuantCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


void QuantCoder::SetMessage ( Container* _container, const std::string& _message, 
                               const Key* _key )
{
    // Must be a Quant key
    if ( _key->IsQuantKey() )
    {
        const QuantKey* key = static_cast<const QuantKey*>(_key);

        // Get key
        m_Key = key->GetQuantKey();

        // Reset data;
        m_PrevByte = 0;

        // Hide message
        LSBCoder::SetMessage(_container, _message);
    }
}


////////////////////////////////////////////////////////////////////////////////


std::string QuantCoder::GetMessage ( const Container* _container, const Key* _key )
{
    // Must be a Quant key
    if ( _key->IsQuantKey() )
    {
        const QuantKey* key = static_cast<const QuantKey*>(_key);

        // Get key
        m_Key = key->GetQuantKey();

        // Reset data;
        m_PrevByte = 0;

        // Get message
        return LSBCoder::GetMessage(_container);
    }

    // Not a Quant key
    return "";
}


////////////////////////////////////////////////////////////////////////////////


bool QuantCoder::WriteBit( BMPContainer* _container, bool _bit )
{
    // Get next byte for writing
    unsigned char byte;
    if ( !GetByte(&byte) )
        // Bit has not been written
        return false;

    // Brightness difference
    int difference = static_cast<int>(byte) -
                     static_cast<int>(m_PrevByte) + 255;

    // If bit from quantization table is equal to bit which is being written
    if ( m_Key[difference] == _bit )
    {
        // Update previous byte
        m_PrevByte = byte;

        // Do not do anything
        return true;
    }
    else
    {
        // Increase/decrease position until bits are equal
        int newDiff = GetNearestDifference(difference, _bit);

        // Write bit to byte
        byte = static_cast<unsigned char>
                    (static_cast<int>(byte) + newDiff - difference);

        // Write byte to pixel
        SetByte(byte);

        // Update previous byte
        m_PrevByte = byte;

        // Bit has been successfully written
        return true;
    }
}


////////////////////////////////////////////////////////////////////////////////


int QuantCoder::GetNearestDifference( int _difference, bool _bit )
{
    // Difference after
    int diffAfter = _difference + 1;

    // Difference before
    int diffBefore = _difference - 1;

    while ( diffAfter + m_PrevByte < QuantKey::quantizationTableSize ||
            diffBefore + m_PrevByte >= 0 )
    {
        if ( m_Key[diffAfter] == _bit )
            return diffAfter;
        if ( m_Key[diffBefore] == _bit )
            return diffBefore;

        ++diffAfter;
        --diffBefore;
    }

    // Fail
    return _difference;
}


////////////////////////////////////////////////////////////////////////////////


bool QuantCoder::ReadBit( const BMPContainer* _container, bool& _bit )
{
    // Byte
    unsigned char byte;

    // Fetch byte
    if ( !GetByte(&byte) )
        return false;

    // Read its value from quantization table
    _bit = m_Key[static_cast<int>(byte) - static_cast<int>(m_PrevByte) + 255];

    // Update previous byte
    m_PrevByte = byte;

    // Read is OK
    return true;
}


////////////////////////////////////////////////////////////////////////////////
