#ifndef _CODER_H_
#define _CODER_H_

////////////////////////////////////////////////////////////////////////////////

#include <string>

////////////////////////////////////////////////////////////////////////////////

class Container;
class Key;

////////////////////////////////////////////////////////////////////////////////


/** C++ interface class for stegano -coding -encoding
*    
*
*  @author  Roman Pasechnik
*  @since   March 25th, 2009
*  @updated March 25th, 2009
*
*/
class Coder
{

////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
	Coder();


    /** Destructor */
    virtual ~Coder();


    /** Puts the message into container */
    virtual void SetMessage ( Container* _container,
                              const std::string& _message,
                              const Key* _key = NULL ) = 0;


    /** Gets the message from container */
    virtual std::string GetMessage ( const Container* _container,
                                     const Key* _key = NULL ) = 0;


////////////////////////////////////////////////////////////////////////////////
};

#endif //_CODER_H_
