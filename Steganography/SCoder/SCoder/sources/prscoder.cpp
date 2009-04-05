////////////////////////////////////////////////////////////////////////////////

#include "prscoder.h"
#include "prskey.h"

////////////////////////////////////////////////////////////////////////////////


PRSCoder::PRSCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


PRSCoder::~PRSCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


void PRSCoder::SetMessage ( Container* _container, const std::string& _message, 
                             const Key* _key )
{
    // Must be a PRS key
    if ( _key->IsPRSKey() )
    {
        const PRSKey* key = static_cast<const PRSKey*>(_key);

        // Apply PRS key on message and hide it using LSB algorithm
        LSBCoder::SetMessage( _container, key->ApplyPRSKey(_message) );
    }
}


////////////////////////////////////////////////////////////////////////////////


std::string PRSCoder::GetMessage ( const Container* _container, const Key* _key )
{
    // Must be a PRS key
    if ( _key->IsPRSKey() )
    {
        const PRSKey* key = static_cast<const PRSKey*>(_key);

        // Get message using LSB algorithm and apply PRS key
        return key->ApplyPRSKey(LSBCoder::GetMessage(_container) );
    }

    // Not a PRS key
    return "";
}


////////////////////////////////////////////////////////////////////////////////
