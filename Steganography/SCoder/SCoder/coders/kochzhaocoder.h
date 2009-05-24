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


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** Setup the container */
    virtual void SetupContainer( const BMPContainer* _container );


    /** Special handling for cross algorithm */
    virtual bool SetBit( bool _bit );


    /** Special handling for cross algorithm */
    virtual bool GetBit( bool* _bit );


    /** Special handling for cross algorithm */
    virtual bool JumpToNextPixel();


    /** Build Fourier coefficient table */
    void BuildCoefficientTable();


    /** Build Fourier coefficient table */
    void ReverseTransform();


    /** Set difference between two pixels */
    void SetDifference(bool _bit);


    /** Get difference between two pixels */
    bool GetDifference();


    double Sigma(int _u);
    double Sum(int _u, int _v);
    double Sum2(int _x, int _y);


////////////////////////////////////////////////////////////////////////////////


    /** JPEG compression threshold */
    const int m_Threshold;


    /** Fourier coefficients of a piece of image 8x8 */
    double m_FourierCoefficients[8][8];

    /** Fourier coefficients of a piece of image 8x8 */
    double m_Restored[8][8];


////////////////////////////////////////////////////////////////////////////////
};

#endif //_KOCHZHAOCODER_H_
