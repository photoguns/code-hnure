#ifndef _CROSSCODER_H_
#define _CROSSCODER_H_

////////////////////////////////////////////////////////////////////////////////

#include "lsbcoder.h"

////////////////////////////////////////////////////////////////////////////////


/** C++ class for stegano -coding -encoding based on cross algorithm
*
*
*  @author  Roman Pasechnik
*  @since   Apr 04th, 2009
*  @updated May 24th, 2009
*
*/
class CrossCoder: public LSBCoder
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    CrossCoder();


    /** Destructor */
    virtual ~CrossCoder();


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


    /** Checks if (_currHeight, _currWidth) is inside area (0.._height, 0.._width) */
    bool IsInside( int _height, int _width, int _currHeight, int _currWidth );


////////////////////////////////////////////////////////////////////////////////


    // Cross radius
    int m_Radius;

    // Some variables needed to move wisely through container 
    // (I don't exactly remember why I need this.. f..k!)
    //          [Hint: Always comment code, even if it is very simple ))]
    // It seems they are pointing to a center of a cross
    int m_BaseHeight;
    int m_BaseWidth;


////////////////////////////////////////////////////////////////////////////////
};

#endif //_CROSSCODER_H_
