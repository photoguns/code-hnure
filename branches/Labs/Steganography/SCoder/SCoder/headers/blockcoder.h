#ifndef _BLOCKCODER_H_
#define _BLOCKCODER_H_

////////////////////////////////////////////////////////////////////////////////

#ifndef _CODER_H_
#include "coder.h"
#endif

////////////////////////////////////////////////////////////////////////////////


/** C++ class for stegano -coding -encoding based on block algorithm
*
*
*  @author  Roman Pasechnik
*  @since   March 25th, 2009
*  @updated March 25th, 2009
*
*/
class BlockCoder: public Coder
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    BlockCoder();


    /** Destructor */
    virtual ~BlockCoder();


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

#endif //_BLOCKCODER_H_
