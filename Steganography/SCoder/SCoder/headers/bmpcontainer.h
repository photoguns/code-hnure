#ifndef _BMPCONTAINER_H_
#define _BMPCONTAINER_H_

////////////////////////////////////////////////////////////////////////////////

#include "container.h"
#include "EasyBMP.h"

////////////////////////////////////////////////////////////////////////////////


/** C++ class - BMP image container
*    
*
*  @author  Roman Pasechnik
*  @since   March 25th, 2009
*  @updated March 25th, 2009
*
*/
class BMPContainer : public Container
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    BMPContainer ( const std::string& _fileName );


    /** Tells if this container is BMP container */
    virtual bool IsBMPContainer() const { return true; }


    /** Tells BMP image width in pixels */
    int TellWidth() const;


    /** Tells BMP image height in pixels */
    int TellHeight() const;


    /** Gets BMP image pixel with coordinates (i, j) */
    RGBApixel GetPixel ( int _i, int _j ) const;


    /** Sets BMP image pixel with coordinates (i, j) */
    void SetPixel (int _i, int _j, const RGBApixel& _pixel);


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** BMP Image */
    BMP m_Image;


////////////////////////////////////////////////////////////////////////////////
};


#endif //_BMPCONTAINER_H_