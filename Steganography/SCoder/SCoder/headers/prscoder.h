#ifndef _PRSCODER_H_
#define _PRSCODER_H_

////////////////////////////////////////////////////////////////////////////////

#include "lsbcoder.h"

////////////////////////////////////////////////////////////////////////////////


/** C++ class for stegano -coding -encoding based on 
"pseudorandom interval" algorithm
*
*
*  @author  Roman Pasechnik
*  @since   March 25th, 2009
*  @updated March 25th, 2009
*
*/
class PRSCoder: public LSBCoder
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    PRSCoder();


    /** Destructor */
    virtual ~PRSCoder();


    /** Puts the message into container */
    virtual void HideMessage ( Container* _container,
                               const std::string& message,
                               const Key* _key );


    /** Gets the message from container */
    virtual std::string GetMessage ( const Container* _container,
                                     const Key* _key );


////////////////////////////////////////////////////////////////////////////////
};

#endif //_PRSCODER_H_
