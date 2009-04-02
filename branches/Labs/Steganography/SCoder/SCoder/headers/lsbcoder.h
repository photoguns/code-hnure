#ifndef _LSBCODER_H_
#define _LSBCODER_H_

////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <bitset>
#include <limits>
#include "coder.h"
#include "bmpcontainer.h"

class BMPContainer;
////////////////////////////////////////////////////////////////////////////////


/** C++ class for stegano -coding -encoding based on LSB algorithm
*
*
*  @author  Roman Pasechnik
*  @since   Mar 25th, 2009
*  @updated Apr 02th, 2009
*
*/
class LSBCoder: public Coder
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
	LSBCoder();


    /** Destructor */
	virtual ~LSBCoder();


    /** Puts the message into container */
    virtual void HideMessage ( Container* _container,
                               const std::string& message,
                               const Key* _key = NULL );


    /** Gets the message from container */
    virtual std::string GetMessage ( const Container* _container,
                                     const Key* _key = NULL );


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** Quantity of bits in char and size_t types */
    enum
    {
        bitsInChar = std::numeric_limits<char>::digits,
        bitsInSizeT = std::numeric_limits<size_t>::digits
    };


    /** Utility type: bitset for one char */
    typedef std::bitset<bitsInChar> CharBitset;


    /** Utility type: vector of CharBitsets */
    typedef std::vector<CharBitset> BinaryString;


    /** Utility type: bitset for one size_t */
    typedef std::bitset<bitsInSizeT> SizeTBitset;


    /** Current pixel */
    RGBApixel m_Pixel;


    /** Current pixel coordinates */
    int m_CurrHeight;
    int m_CurrWidth;


    /** RGB */
    enum Colour
    {
        Red,
        Green,
        Blue
    };


    /** Current color in current pixel */
    Colour m_Colour;


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** Clear data from previous operations */
    void Reset();


    /** Writes message length to container */
    void HideMessageLength ( BMPContainer* _container, size_t _length );


    /** Writes message to container */
    void HideMessageText ( BMPContainer* _container, const std::string& _message );


    /** Gets message length from container */
    unsigned long GetMessageLength ( const BMPContainer* _container );


    /** Gets message from container */
    std::string GetMessageText ( const BMPContainer* _container, size_t _length );


    /** Reads bit from container */
    virtual bool ReadBit ( const BMPContainer* _container, bool& _bit );


    /** Writes bit in container */
    virtual bool WriteBit ( BMPContainer* _container, bool _bit );


////////////////////////////////////////////////////////////////////////////////

protected:

////////////////////////////////////////////////////////////////////////////////


    /** Returns next pixel to take bytes from */
    virtual bool GetNextPixel ( const BMPContainer* _container, RGBApixel& _pixel);


    /** Returns next byte to write in */
    bool GetNextByte ( const BMPContainer* _container, unsigned char& _byte );


    /** Returns next byte to write in */
    void SetByte ( BMPContainer* _container, unsigned char _byte );


////////////////////////////////////////////////////////////////////////////////
};

#endif //_LSBCODER_H_
