#ifndef _LSBSOUNDCODER_H_
#define _LSBSOUNDCODER_H_

////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <bitset>
#include <limits>

#include "coder.h"
#include "wavcontainer.h"

////////////////////////////////////////////////////////////////////////////////


/** C++ class for stegano -coding -encoding based on LSB algorithm
*
*
*  @author  Roman Pasechnik
*  @since   Mar 25th, 2009
*  @updated Apr 04th, 2009
*
*/
class LSBSoundCoder: public Coder
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    LSBSoundCoder();


    /** Destructor */
    virtual ~LSBSoundCoder();


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
    void SetContainer( const WAVContainer* _container );


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


    /** Reads bit from container */
    virtual bool GetBit( bool* _bit );


    /** Writes bit in container */
    virtual bool SetBit( bool _bit );


////////////////////////////////////////////////////////////////////////////////

protected:

////////////////////////////////////////////////////////////////////////////////


    /** Setup the container */
    virtual void SetupContainer( const WAVContainer* _container );


    /** Get current container for read */
    const WAVContainer* GetContainer() const;


    /** Get current container for write */
    WAVContainer* GetContainer();


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** Current container */
    WAVContainer* m_Container;

    size_t m_CurrSamplePosition;


////////////////////////////////////////////////////////////////////////////////
};

#endif //_LSBSOUNDCODER_H_
