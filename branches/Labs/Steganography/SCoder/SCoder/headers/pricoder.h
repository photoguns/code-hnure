#ifndef _PRICODER_H_
#define _PRICODER_H_

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
class PRICoder: public LSBCoder
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    PRICoder();


    /** Destructor */
    virtual ~PRICoder();


    /** Puts the message into container */
    virtual void HideMessage ( Container* _container,
                               const std::string& message,
                               const Key* _key );


    /** Gets the message from container */
    virtual std::string GetMessage ( const Container* _container,
                                     const Key* _key );

////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** Special next pixel handling in this coder */
    virtual bool GetNextPixel( const BMPContainer* _container, RGBApixel& _pixel );


    /** PRI Key */
    std::vector<int> m_Key;


    /** Current interval in PRI Key */
    int m_CurrKeyIdx;


////////////////////////////////////////////////////////////////////////////////
};

#endif //_PRICODER_H_
