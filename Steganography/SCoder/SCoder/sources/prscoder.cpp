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


void PRSCoder::HideMessage ( Container* _container, const std::string& _message, 
                             const Key* _key )
{
    if ( _key->IsPRSKey() )
    {
        const PRSKey* key = static_cast<const PRSKey*>(_key);
        LSBCoder::HideMessage(_container, key->ApplyPRSKey(_message));
    }
}


////////////////////////////////////////////////////////////////////////////////


std::string PRSCoder::GetMessage ( const Container* _container, const Key* _key )
{
    if ( _key->IsPRSKey() )
    {
        const PRSKey* key = static_cast<const PRSKey*>(_key);
        return key->ApplyPRSKey(LSBCoder::GetMessage(_container) );
    }

    // Not a PRS key
    return "";
}


////////////////////////////////////////////////////////////////////////////////
