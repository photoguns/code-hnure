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
*  @since   Mar 25th, 2009
*  @updated Mar 25th, 2009
*
*/
class BMPContainer : public Container
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    BMPContainer ( const std::string& _fileName );


    /** Destructor */
    virtual ~BMPContainer();


    /** Tells if this container is BMP container */
    virtual bool IsBMPContainer() const { return true; }


    /** Loads container from file */
    virtual bool Open( const std::string& _path );


    /** Saves container to file */
    virtual bool Save( const std::string& _path );


    /** Tells BMP image height in pixels */
    int TellHeight() const;


    /** Tells BMP image width in pixels */
    int TellWidth() const;


    /** Gets BMP image pixel with coordinates (i, j) */
    RGBApixel GetPixel( int _width, int _height ) const;


    /** Sets BMP image pixel with coordinates (i, j) */
    void SetPixel( int _width, int _height, const RGBApixel& _pixel );


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** BMP Image */
    BMP m_Image;


////////////////////////////////////////////////////////////////////////////////
};


#endif //_BMPCONTAINER_H_