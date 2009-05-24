#ifndef _BLOCKCODER_H_
#define _BLOCKCODER_H_

////////////////////////////////////////////////////////////////////////////////

#include "lsbcoder.h"

////////////////////////////////////////////////////////////////////////////////


/** C++ class for stegano -coding -encoding based on block algorithm
*
*
*  @author  Roman Pasechnik
*  @since   Mar 25th, 2009
*  @updated May 24th, 2009
*
*/
class BlockCoder: public LSBCoder
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    BlockCoder();


    /** Destructor */
    virtual ~BlockCoder();


    /** Puts the message into container */
    virtual void SetMessage( Container* _container,
                             const std::string& _message,
                             const Key* _key );


    /** Gets the message from container */
    virtual std::string GetMessage( const Container* _container,
                                    const Key* _key );


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** Special handling for Block algorithm */
    virtual bool SetBit( bool _bit );


    /** Special handling for Block algorithm */
    virtual bool GetBit( bool* _bit );


////////////////////////////////////////////////////////////////////////////////


    /** Block Key */
    std::vector<int> m_Key;


    /** Current area in PRS Key */
    size_t m_CurrBlock;


////////////////////////////////////////////////////////////////////////////////
};

#endif //_BLOCKCODER_H_
