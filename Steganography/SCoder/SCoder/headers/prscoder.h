#ifndef _PRSCODER_H_
#define _PRSCODER_H_

////////////////////////////////////////////////////////////////////////////////

#ifndef _CODER_H_
#include "coder.h"
#endif

////////////////////////////////////////////////////////////////////////////////


/** C++ class for stegano -coding -encoding based on PRS algorithm
*
*
*  @author  Roman Pasechnik
*  @since   March 25th, 2009
*  @updated March 25th, 2009
*
*/
class PRSCoder: public Coder
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    PRSCoder();


    /** Destructor */
    virtual ~PRSCoder();


    /** Puts the message into container */
    virtual void Encrypt ( const std::string& message,
                           Container* _container,
                           const Key* _key );


    /** Gets the message from container */
    virtual std::string Decrypt ( const Container* _container,
                                  const Key* _key );

////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////
};

#endif

