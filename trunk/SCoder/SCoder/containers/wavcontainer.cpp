////////////////////////////////////////////////////////////////////////////////

#include "wavcontainer.h"
#include <cassert>

////////////////////////////////////////////////////////////////////////////////


WAVContainer::WAVContainer( const std::string& _fileName )
:m_Frames(NULL), m_FramesCount(0), m_Format(0), m_Channels(0), m_SampleRate(0)
{
    // Open file
    Open(_fileName);
}


////////////////////////////////////////////////////////////////////////////////


WAVContainer::~WAVContainer()
{
    // Cleanup
    if (m_Frames)
        delete m_Frames;
}


////////////////////////////////////////////////////////////////////////////////


bool WAVContainer::Open( const std::string& _path )
{
    // Open file
    SndfileHandle file(_path, SFM_READ);

    // Support only WAV files with bit rate 16
    if ( (file.format() == static_cast<int>(SF_FORMAT_WAV | SF_FORMAT_PCM_16)) &&
         (file.frames() != 0) )
    {
        // Save file properties
        m_Format = file.format();
        m_Channels = file.channels();
        m_SampleRate = file.samplerate();

        // Cleanup
        if (m_Frames)
            delete[] m_Frames;

        // Alloc memory for data
        m_FramesCount = static_cast<size_t>( file.frames() * m_Channels );
        m_Frames = new short[m_FramesCount];

        // Read all frames
        if ( m_FramesCount == file.read(reinterpret_cast<short*>(m_Frames), m_FramesCount) )

            // Everything is OK
            return true;
    }

    // Shit happens
    assert(0);
    return false;
}


////////////////////////////////////////////////////////////////////////////////


bool WAVContainer::Save( const std::string& _path )
{
    // Create file for writing
    SndfileHandle file(_path, SFM_WRITE, m_Format, m_Channels, m_SampleRate);

    // Write
    if ( m_FramesCount == file.write(reinterpret_cast<short*>(m_Frames), m_FramesCount) )

        // Everything is OK
        return true;

    else
    {
        // Shit happens
        assert(0);
        return false;
    }
}


////////////////////////////////////////////////////////////////////////////////


size_t WAVContainer::Size() const
{
    return m_FramesCount;
}


////////////////////////////////////////////////////////////////////////////////


short WAVContainer::GetSample( size_t _position ) const
{
    assert (_position < m_FramesCount);
    return m_Frames[_position];
}


////////////////////////////////////////////////////////////////////////////////


void WAVContainer::SetSample( size_t _position, short _sample )
{
    assert (_position < m_FramesCount);
    m_Frames[_position] = _sample;
}


////////////////////////////////////////////////////////////////////////////////
