#ifndef _LSBCODER_H_
#define _LSBCODER_H_

////////////////////////////////////////////////////////////////////////////////

#ifndef _CODER_H_
#include "coder.h"
#endif

////////////////////////////////////////////////////////////////////////////////


/** C++ class for stegano -coding -encoding based on LSB algorithm
*
*
*  @author  Roman Pasechnik
*  @since   March 25th, 2009
*  @updated March 25th, 2009
*
*/
class LSB: public Coder
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
	LSB();


    /** Destructor */
	virtual ~LSB();


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

#endif //_LSBCODER_H_
