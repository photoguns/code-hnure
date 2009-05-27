#ifndef _QUANTCODER_H_
#define _QUANTCODER_H_

////////////////////////////////////////////////////////////////////////////////

#include "lsbcoder.h"
#include "quantkey.h"

////////////////////////////////////////////////////////////////////////////////


/** C++ class for stegano -coding -encoding based on "quantization" algorithm
*
*
*  @author  Roman Pasechnik
*  @since   Apr 04th, 2009
*  @updated May 24th, 2009
*
*/
class QuantCoder: public LSBCoder
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    QuantCoder();


    /** Destructor */
    virtual ~QuantCoder();


    /** Puts the message into container */
    virtual void SetMessage ( Container* _container,
                              const std::string& message,
                              const Key* _key );


    /** Gets the message from container */
    virtual std::string GetMessage ( const Container* _container,
                                     const Key* _key );

////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** Special handling in this coder */
    virtual bool SetBit( bool _bit );


    /** Special handling in this coder */
    virtual bool GetBit( bool* _bit );


    /** Gets nearest brightness position in quantization table with equal bit */
    int GetNearestDifference( int _difference, bool _bit );


    /** Quant Key */
    std::bitset<QuantKey::quantizationTableSize> m_Key;


    /** Previous byte value */
    unsigned char m_PrevByte;


////////////////////////////////////////////////////////////////////////////////
};

#endif //_QUANTCODER_H_
