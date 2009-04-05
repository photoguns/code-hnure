#ifndef _LSBCODER_H_
#define _LSBCODER_H_

////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <bitset>
#include <limits>

#include "coder.h"
#include "bmpcontainer.h"

////////////////////////////////////////////////////////////////////////////////


/** C++ class for stegano -coding -encoding based on LSB algorithm
*
*
*  @author  Roman Pasechnik
*  @since   Mar 25th, 2009
*  @updated Apr 04th, 2009
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
    virtual void SetMessage ( Container* _container,
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
        bitsInChar = std::numeric_limits<unsigned char>::digits,
        bitsInSizeT = std::numeric_limits<size_t>::digits
    };

    
    /** Utility type: bitset for one char */
    typedef std::bitset<bitsInChar> CharBitset;


    /** Utility type: vector of CharBitsets */
    typedef std::vector<CharBitset> BinaryString;


    /** Utility type: bitset for one size_t */
    typedef std::bitset<bitsInSizeT> SizeTBitset;


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** Set current container */
    void SetContainer( const BMPContainer* _container );


    /** Gets message length from container */
    unsigned long GetMessageLength();


    /** Writes message length to container */
    void SetMessageLength( size_t _length );


    /** Gets message from container */
    std::string GetMessageText( size_t _length );


    /** Writes message to container */
    void SetMessageText( const std::string& _message );


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////

    
    /** RGB */
    enum Colour
    {
        Red,
        Green,
        Blue
    };


    /** Reads bit from container */
    virtual bool GetBit( bool* _bit );


    /** Writes bit in container */
    virtual bool SetBit( bool _bit );


    /** Sets current pixels current colour */
    Colour GetCurrColour() const;


    /** Sets current pixels current colour */
    void SetCurrColour( Colour _colour );


////////////////////////////////////////////////////////////////////////////////

protected:

////////////////////////////////////////////////////////////////////////////////


    /** Setup the container */
    virtual void SetupContainer( const BMPContainer* _container );


	/** Get current container for read */
	const BMPContainer* GetContainer() const;


	/** Get current container for write */
	BMPContainer* GetContainer();


    /** Set current coordinates for next pixel */
    virtual bool JumpToNextPixel();


    /** Gets current image pixel */
    RGBApixel GetCurrPixel() const;


    /** Sets current image pixel */
    void SetCurrPixel( const RGBApixel& _pixel );


	/** Gets image current height and width */
	void GetCurrPixelPosition( int* _i, int* _j ) const;


    /** Sets image current height and width */
    bool SetCurrPixelPosition( int _i, int _j );


    /** Reads byte from current pixel */
    bool GetByte( unsigned char* _byte );


    /** Writes byte to current pixel */
    void SetByte( unsigned char _byte );


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** Current container */
    BMPContainer* m_Container;


    /** Current pixel coordinates */
    int m_CurrHeight;
    int m_CurrWidth;


    /** Current color in current pixel */
    Colour m_Colour;


////////////////////////////////////////////////////////////////////////////////
};

#endif //_LSBCODER_H_
