////////////////////////////////////////////////////////////////////////////////

#include "pricoder.h"
#include "prikey.h"

////////////////////////////////////////////////////////////////////////////////


PRICoder::PRICoder()
{
}


////////////////////////////////////////////////////////////////////////////////


PRICoder::~PRICoder()
{
}


////////////////////////////////////////////////////////////////////////////////


void PRICoder::SetMessage( Container* _container, const std::string& _message, 
                           const Key* _key )
{
    // Must be a PRI key
    if ( _key->IsPRIKey() )
    {
        // Reset data
        m_CurrKeyIdx = -1;

        const size_t keyLength = 16;
        const PRIKey* key = static_cast<const PRIKey*>(_key);
        
        // Get key of keyLength intervals
        m_Key = key->GetPRIKey(keyLength);

        // Hide message using LSB algorithm
        LSBCoder::SetMessage(_container, _message);
    }
}


////////////////////////////////////////////////////////////////////////////////


std::string PRICoder::GetMessage( const Container* _container, const Key* _key )
{
    // Must be PRI key
    if ( _key->IsPRIKey() )
    {
        // Reset data
        m_CurrKeyIdx = -1;

        const size_t keyLength = 16;
        const PRIKey* key = static_cast<const PRIKey*>(_key);
        m_Key = key->GetPRIKey(keyLength);

        // Get message using LSB algorithm
        return LSBCoder::GetMessage(_container);
    }

    // Not a PRI key
    return "";
}


////////////////////////////////////////////////////////////////////////////////


bool PRICoder::JumpToNextPixel()
{
    // Get next interval in key
    m_CurrKeyIdx = ++m_CurrKeyIdx % m_Key.size();

    // Continue getting next pixels just like in LSB algorithm
    for (int i = 0; i < m_Key[m_CurrKeyIdx]; ++i)
        if ( !LSBCoder::JumpToNextPixel() )
            // No pixels left
            return false;

    // Next pixel is OK
    return true;
}


////////////////////////////////////////////////////////////////////////////////
