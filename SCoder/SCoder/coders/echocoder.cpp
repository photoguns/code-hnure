////////////////////////////////////////////////////////////////////////////////

#include "echocoder.h"
#include "echokey.h"

////////////////////////////////////////////////////////////////////////////////


EchoCoder::EchoCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


EchoCoder::~EchoCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


void EchoCoder::SetMessage( Container* _container, const std::string& _message, 
                            const Key* _key )
{
    // Must be a echo key
    if ( _key->IsEchoKey() )
    {
        // Get echo key
        const EchoKey* key = static_cast<const EchoKey*>(_key);

        // Get offsets
        std::pair<int, int> offsets = key->GetEchoKey();

        m_EchoFirstOffset = offsets.first;
        m_EchoSecondOffset = offsets.second;

        // Hide message using echo algorithm
        LSBSoundCoder::SetMessage(_container, _message);
    }
}


////////////////////////////////////////////////////////////////////////////////


std::string EchoCoder::GetMessage( const Container* _container, const Key* _key )
{
    // Must be a echo key
    if ( _key->IsEchoKey() )
    {
        // Get echo key
        const EchoKey* key = static_cast<const EchoKey*>(_key);

        // Get offsets
        std::pair<int, int> offsets = key->GetEchoKey();

        m_EchoFirstOffset = offsets.first;
        m_EchoSecondOffset = offsets.second;

        // Hide message using echo algorithm
        return LSBSoundCoder::GetMessage(_container);
    }

    // Not a PRI key
    return "";
}


////////////////////////////////////////////////////////////////////////////////


void EchoCoder::SetupContainer( const WAVContainer* _container )
{
    LSBSoundCoder::SetupContainer(_container);

    // Skip 100 samples
    for (int i = 0; i < 100; ++i)
        if ( !JumpToNextSample() )
            return;
}


////////////////////////////////////////////////////////////////////////////////


bool EchoCoder::GetBit( bool* _bit )
{
    // Go to echo 1
    for (int i = 0; i < m_EchoFirstOffset; ++i)
    {
        if ( !JumpToNextSample() )
            // Bit has not been read
            return false;
    }

    // First echo
    short echo_1_value = GetCurrSample();

    // Go to echo 2
    for (int i = 0; i < m_EchoSecondOffset; ++i)
    {
        if ( !JumpToNextSample() )
            // Bit has not been read
            return false;
    }

    // Second echo
    short echo_2_value = GetCurrSample();

    // If echo 1 > echo 2 -- bit == 1;
    *_bit = echo_2_value > echo_1_value;

    // Bit has been read
    return true;
}


////////////////////////////////////////////////////////////////////////////////


bool EchoCoder::SetBit( bool _bit )
{
    // Go to echo 1
    for (int i = 0; i < m_EchoFirstOffset; ++i)
    {
        if ( !JumpToNextSample() )
            // Bit has not been written
            return false;
    }

    // Get first echo
    short sample1 = GetCurrSample();

    // Go to echo 2
    for (int i = 0; i < m_EchoSecondOffset; ++i)
    {
        if ( !JumpToNextSample() )
            // Bit has not been written
            return false;
    }

    // If bit == 1 - increase second echo
    if (_bit)
        WriteEcho(sample1, true);
    else
        // If bit == 0 - decrease second echo
        WriteEcho(sample1, false);

    // Bit not been written
    return true;
}


////////////////////////////////////////////////////////////////////////////////


void EchoCoder::WriteEcho( short _sample, bool _greater )
{
    // Current sample
    short currSample = GetCurrSample();

    // Modify second echo
    if (_greater)
    {
        while (currSample <= _sample &&
            currSample != std::numeric_limits<short>::max() )
            currSample++;
    }
    else
    {
        while (currSample >= _sample &&
            currSample != std::numeric_limits<short>::min() )
            currSample--;
    }

    // Set it
    SetCurrSample(currSample);
}


////////////////////////////////////////////////////////////////////////////////

