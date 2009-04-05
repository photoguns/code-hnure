////////////////////////////////////////////////////////////////////////////////

#include "blockcoder.h"
#include "bmpcontainer.h"
#include "blockkey.h"

////////////////////////////////////////////////////////////////////////////////


BlockCoder::BlockCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


BlockCoder::~BlockCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


void BlockCoder::SetMessage( Container* _container,
                              const std::string& _message, const Key* _key )
{
    // Must be Block key
    if ( _key->IsBlockKey() )
    {
        const BlockKey* key = static_cast<const BlockKey*>(_key);

        // Must be BMP container
        if ( _container->IsBMPContainer() )
        {
            BMPContainer* container = static_cast<BMPContainer*>(_container);

            // Reset data
            m_CurrBlock = 0;

            //// Get container dimensions
            //const int height = container->TellHeight();
            //const int width = container->TellWidth();

            // Hard coded key length
            const size_t keyLength = 16;

            // Get Block key
            m_Key = key->GetBlockKey(keyLength);

            // Hide message
            LSBCoder::SetMessage(_container, _message);
        }
    }
}


////////////////////////////////////////////////////////////////////////////////


std::string BlockCoder::GetMessage( const Container* _container,
                                    const Key* _key )
{
    // Must be Block key
    if ( _key->IsBlockKey() )
    {
        const BlockKey* key = static_cast<const BlockKey*>(_key);

        // Must be BMP container
        if ( _container->IsBMPContainer() )
        {
            const BMPContainer* container = static_cast<const BMPContainer*>(_container);

            // Reset data
            m_CurrBlock = 0;

            //// Get container dimensions
            //const int height = container->TellHeight();
            //const int width = container->TellWidth();

            // Hard coded key length
            const size_t keyLength = 16;

            // Get Block key
            m_Key = key->GetBlockKey(keyLength);

            // Get message
            return LSBCoder::GetMessage(_container);
        }
    }

    // Fail
    return "";
}


////////////////////////////////////////////////////////////////////////////////


bool BlockCoder::WriteBit( BMPContainer* _container, bool _bit )
{
    //// Get next block
    //const BlockKey::Block& block = m_Key[m_CurrBlock];

    //// Last pixel in a block
    //RGBApixel pixel;

    //// Count even bit of block
    //for (size_t i = 0; i < block.size(); ++i)
    //{
    //    // Get block pixel
    //    pixel = _container->GetPixel(block[i].first, block[i].second);

    //    if ( PixelEvenBit(pixel) )
    //        evenBit = !evenBit;
    //}

    //// Invert LSB
    //if (_bit != evenBit)
    //{
    //    std::bitset<std::numeric_limits<unsigned char>::digits> byte(pixel.Red);
    //    byte[0] = !byte[0];
    //    pixel.Red = static_cast<unsigned char>( byte.to_ulong() );

    //    // Write modified pixel
    //    _container->SetPixel(block.back().first, block.back().second, pixel);
    //}

    // Even bit
    bool evenBit = false;

    // Last byte in a block
    unsigned char byte;

    for (int i = 0; i < m_Key[m_CurrBlock]; ++i)
    {
        // Get pixel byte
        if ( !GetByte(&byte) )
            return false;

        if ( byte % 2 )
            evenBit = !evenBit;
    }

    // Invert LSB
    if (_bit != evenBit)
    {
        std::bitset<std::numeric_limits<unsigned char>::digits> bits(byte);
        bits[0] = !bits[0];
        byte = static_cast<unsigned char>( bits.to_ulong() );

        // Write modified byte
        SetByte(byte);
    }

    // Prepare next block for next bit
    m_CurrBlock = ++m_CurrBlock % m_Key.size();

    // Bit has been written
    return true;
}


////////////////////////////////////////////////////////////////////////////////


bool BlockCoder::ReadBit( const BMPContainer* _container, bool& _bit )
{
    //// Get next block
    //const BlockKey::Block& block = m_Key[m_CurrBlock];

    //// Even bit
    //_bit = false;

    //// Count even bit of block
    //for (size_t i = 0; i < block.size(); ++i)
    //{
    //    // Get block pixel
    //    RGBApixel pixel = _container->GetPixel(block[i].first,
    //                                           block[i].second);

    //    if ( PixelEvenBit(pixel) )
    //        _bit = !_bit;
    //}

    // Even bit
    _bit = false;

    for (int i = 0; i < m_Key[m_CurrBlock]; ++i)
    {
        // Byte in a block
        unsigned char byte;

        // Get pixel byte
        if ( !GetByte(&byte) )
            return false;

        if ( byte % 2 )
            _bit = !_bit;
    }

    // Prepare next block for next bit
    m_CurrBlock = ++m_CurrBlock % m_Key.size();

    // Bit has been read
    return true;
}


////////////////////////////////////////////////////////////////////////////////


//bool BlockCoder::PixelEvenBit( const RGBApixel& pixel ) const
//{
//    if ( (pixel.Red + pixel.Green + pixel.Blue) % 2 )
//        return true;
//    else
//        return false;
//}


////////////////////////////////////////////////////////////////////////////////
