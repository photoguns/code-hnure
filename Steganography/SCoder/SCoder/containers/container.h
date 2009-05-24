#ifndef _CONTAINER_H_
#define _CONTAINER_H_

////////////////////////////////////////////////////////////////////////////////

#include <string>

////////////////////////////////////////////////////////////////////////////////


/** C++ interface class for containers (BMP images,...)
*    
*
*  @author  Roman Pasechnik
*  @since   Mar 25th, 2009
*  @updated Mar 25th, 2009
*
*/
class Container
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    Container();


    /** Destructor */
    virtual ~Container();


    /** Tells if this container is BMP container */
    virtual bool IsBMPContainer() const { return false; }


    /** Tells if this container is Wave container */
    virtual bool IsWaveContainer() const { return false; }


    /** Loads container from file */
    virtual bool Open( const std::string& _path ) = 0;


    /** Saves container to file */
    virtual bool Save( const std::string& _path ) = 0;


////////////////////////////////////////////////////////////////////////////////

};


////////////////////////////////////////////////////////////////////////////////

#endif //_CONTAINER_H_
