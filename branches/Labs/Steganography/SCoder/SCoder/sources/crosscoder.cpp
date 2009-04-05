////////////////////////////////////////////////////////////////////////////////

#include "crosscoder.h"
#include "bmpcontainer.h"

////////////////////////////////////////////////////////////////////////////////


CrossCoder::CrossCoder()
{
    m_Radius = 2;
}


////////////////////////////////////////////////////////////////////////////////


CrossCoder::~CrossCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


void CrossCoder::SetupContainer( const BMPContainer* _container )
{
    LSBCoder::SetupContainer(_container);

    int height = _container->TellHeight();
    SetCurrPixelPosition(height - 1, m_Radius);
    m_BaseHeight = height - 1;
    m_BaseWidth = m_Radius;
}

bool CrossCoder::SetBit( bool _bit )
{
    if ( !JumpToNextPixel() )
        return false;
 
    RGBApixel pixel = GetCurrPixel();
    double lambda = 0.2989 * pixel.Red +
                    0.58662 * pixel.Green +
                    0.11448 * pixel.Blue;

    // Ratio
    const double u = 0.2;

    if (_bit)
        pixel.Blue = pixel.Blue + static_cast<unsigned char>(u * lambda);
    else
        pixel.Blue = pixel.Blue - static_cast<unsigned char>(u * lambda);

    // Save pixel
    SetCurrPixel(pixel);

    // Bit has been written
    return true;
}


////////////////////////////////////////////////////////////////////////////////


bool CrossCoder::GetBit( bool* _bit )
{
    if ( !JumpToNextPixel() )
        return false;

    int currHeight, currWidth;
    GetCurrPixelPosition(&currHeight, &currWidth);

    int commonBrightness = 0;
    for (int i = currHeight - m_Radius; i < currHeight; ++i)
    {
        RGBApixel pixel = GetContainer()->GetPixel(i, currWidth);
        commonBrightness += pixel.Blue;
    }
    for (int i = currHeight + m_Radius; i > currHeight; --i)
    {
        RGBApixel pixel = GetContainer()->GetPixel(i, currWidth);
        commonBrightness += pixel.Blue;
    }
    for (int i = currWidth - m_Radius; i < currWidth; ++i)
    {
        RGBApixel pixel = GetContainer()->GetPixel(currHeight, i);
        commonBrightness += pixel.Blue;
    }
    for (int i = currWidth + m_Radius; i > currWidth; --i)
    {
        RGBApixel pixel = GetContainer()->GetPixel(currHeight, i);
        commonBrightness += pixel.Blue;
    }


    *_bit = GetCurrPixel().Blue > commonBrightness / (4 * m_Radius);

    // Bit has been read
    return true;
}


////////////////////////////////////////////////////////////////////////////////


bool CrossCoder::JumpToNextPixel()
{
    // Get container
    const BMPContainer* container = GetContainer();
    int height = container->TellHeight();
    int width = container->TellWidth();

    int currHeight, currWidth;
    GetCurrPixelPosition(&currHeight, &currWidth);

    if ( IsInside(height, width, ++currHeight, ++currWidth) )
    {
        SetCurrPixelPosition(currHeight, currWidth);
    }
    else if ( IsInside(height, width, 
                       m_BaseHeight - m_Radius - 1, m_BaseWidth) )
    {
        m_BaseHeight -= m_Radius + 1;
        SetCurrPixelPosition(m_BaseHeight, m_BaseWidth);
    }
    else if ( IsInside(height, width,
                       m_BaseHeight, m_BaseWidth + m_Radius + 1) )
    {
        m_BaseWidth += m_Radius + 1;
        SetCurrPixelPosition(m_BaseHeight, m_BaseWidth);
    }
    else
        return false;
     

    return true;
}


////////////////////////////////////////////////////////////////////////////////


bool CrossCoder::IsInside( int _height, int _width, int _currHeight, int _currWidth )
{
    return ! (_currHeight - m_Radius < 0 ||
              _currWidth - m_Radius  < 0 ||
              _currHeight + m_Radius > _height ||
              _currWidth + m_Radius >= _width );
}