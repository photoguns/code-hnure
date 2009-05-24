#ifndef _KOCHZHAOCODER_H_
#define _KOCHZHAOCODER_H_

////////////////////////////////////////////////////////////////////////////////

#include "lsbcoder.h"

////////////////////////////////////////////////////////////////////////////////


/** C++ class for stegano -coding -encoding based on Koch-Zhao algorithm
*
*
*  @author  Roman Pasechnik
*  @since   May 16th, 2009
*  @updated May 16th, 2009
*
*/
class KochZhaoCoder: public LSBCoder
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    KochZhaoCoder();


    /** Destructor */
    virtual ~KochZhaoCoder();


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


    /** Setup the container */
    virtual void SetupContainer( const BMPContainer* _container );


    /** Special handling for Koch-Zhao algorithm */
    virtual bool SetBit( bool _bit );


    /** Special handling for Koch-Zhao algorithm */
    virtual bool GetBit( bool* _bit );


    /** Special handling for Koch-Zhao algorithm */
    virtual bool JumpToNextPixel();


    /** Build Fourier coefficient table */
    void ForvardFourierTransform();


    /** Build image from Fourier coefficient table */
    void ReverseFourierTransform();


    /** Set difference between two pixels in middle frequency area */
    void SetDifference( bool _bit );


    /** Get difference between two pixels in middle frequency area */
    bool GetDifference();


    /** RTFM of Koch-Zhao */
    double Sigma( int _u );


    /** Utility function for forvard fourier transform */
    double SumForvard( int _u, int _v );


    /** Utility function for reverse fourier transform */
    double SumReverse( int _x, int _y );


////////////////////////////////////////////////////////////////////////////////


    /** JPEG compression threshold */
    const int m_Threshold;


    /** Fourier table size */
    enum { TABLESIZE = 8 };


    /** Fourier coefficients of a piece of image 8x8 */
    double m_FourierCoefficients[TABLESIZE][TABLESIZE];


    /** Two Fourier coefficients where the bit is hidden */
    double& m_C1;
    double& m_C2;


////////////////////////////////////////////////////////////////////////////////
};

#endif //_KOCHZHAOCODER_H_
