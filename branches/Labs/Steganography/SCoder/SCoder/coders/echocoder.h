#ifndef _ECHOCODER_H_
#define _ECHOCODER_H_

////////////////////////////////////////////////////////////////////////////////

#include "lsbsoundcoder.h"

////////////////////////////////////////////////////////////////////////////////


/** C++ class for stegano -coding -encoding based on echo algorithm
*   Use it with some sound container
*
*  @author  Roman Pasechnik
*  @since   May 23rd, 2009
*  @updated May 23rd, 2009
*
*/
class EchoCoder: public LSBSoundCoder
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    EchoCoder();


    /** Destructor */
    virtual ~EchoCoder();


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


    /** Special handling */
    virtual void SetupContainer( const WAVContainer* _container );


    /** Reads bit from container */
    virtual bool GetBit( bool* _bit );


    /** Writes bit in container */
    virtual bool SetBit( bool _bit );


    /** Writes echo of sample in container */
    void WriteEcho( short _sample, bool _greater );


    /** First echo offset [samples] */
    int m_EchoFirstOffset;


    /** Second echo offset [samples] */
    int m_EchoSecondOffset;


////////////////////////////////////////////////////////////////////////////////
};

#endif //_ECHOCODER_H_
