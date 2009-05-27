#ifndef _WAVECONTAINER_H_
#define _WAVECONTAINER_H_

////////////////////////////////////////////////////////////////////////////////

#include "container.h"
#include "sndfile.hh"

#include <vector>

////////////////////////////////////////////////////////////////////////////////


/** C++ class - WAV sound container
*
*
*  @author  Roman Pasechnik
*  @since   May 22th, 2009
*  @updated May 22th, 2009
*
*/
class WAVContainer : public Container
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    WAVContainer ( const std::string& _fileName );


    /** Destructor */
    virtual ~WAVContainer();


    /** Tells if this container is Wave container */
    virtual bool IsWaveContainer() const { return true; }


    /** Loads container from file */
    virtual bool Open( const std::string& _path );


    /** Saves container to file */
    virtual bool Save( const std::string& _path );


    /** Tells BMP image height in pixels */
    size_t Size() const;


    /** Gets BMP image pixel with coordinates (i, j) */
    short GetSample( size_t _position ) const;


    /** Sets BMP image pixel with coordinates (i, j) */
    void SetSample( size_t _position, short _sample );


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** Wave frames */
    short* m_Frames;

    /** Wave frames count */
    size_t m_FramesCount;

    /** Wave file properties */
    int m_Format;
    int m_Channels;
    int m_SampleRate;


////////////////////////////////////////////////////////////////////////////////
};


#endif //_WAVECONTAINER_H_