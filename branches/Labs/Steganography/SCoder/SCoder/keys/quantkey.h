#ifndef _QUANTKEY_H_
#define _QUANTKEY_H_

////////////////////////////////////////////////////////////////////////////////

#include <bitset>
#include "key.h"


/** C++ class for keys generation for Quantization algorithm
*
*
*  @author  Roman Pasechnik
*  @since   Apr 04th, 2009
*  @updated Apr 04th, 2009
*
*/
class QuantKey : public Key
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    QuantKey( const std::string& _string, Key::KeyType _type );


    /** Destructor */
    ~QuantKey();


    /** Tells if this key is Quant key */
    virtual bool IsQuantKey() const { return true; }


    /** Size of quantization table */
    enum
    {
        quantizationTableSize = 511
    };


    /** Get Quant Key */
    std::bitset<quantizationTableSize> GetQuantKey() const;


////////////////////////////////////////////////////////////////////////////////
};

#endif
