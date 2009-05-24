////////////////////////////////////////////////////////////////////////////////

#include "kochzhaocoder.h"
#include "bmpcontainer.h"

////////////////////////////////////////////////////////////////////////////////


KochZhaoCoder::KochZhaoCoder()
:m_Threshold(253)
{
}


////////////////////////////////////////////////////////////////////////////////


KochZhaoCoder::~KochZhaoCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


void KochZhaoCoder::SetupContainer( const BMPContainer* _container )
{
    LSBCoder::SetupContainer(_container);
    SetCurrPixelPosition(-8, 0);
}


////////////////////////////////////////////////////////////////////////////////


bool KochZhaoCoder::SetBit( bool _bit )
{
    if ( !JumpToNextPixel() )
        return false;

    // Build coefficient table
    BuildCoefficientTable();

    // Set diff
    SetDifference(_bit);

    // Build colour table
    ReverseTransform();

    // Bit has been written
    return true;
}


////////////////////////////////////////////////////////////////////////////////


bool KochZhaoCoder::GetBit( bool* _bit )
{
    if ( !JumpToNextPixel() )
        return false;

    BuildCoefficientTable();

    *_bit = GetDifference();

    // Bit has been read
    return true;
}


////////////////////////////////////////////////////////////////////////////////


bool KochZhaoCoder::JumpToNextPixel()
{
    // Get container
    const BMPContainer* container = GetContainer();
    int height = container->TellHeight();
    int width = container->TellWidth();

    int currHeight, currWidth;
    GetCurrPixelPosition(&currHeight, &currWidth);
    
    // Move right
    currHeight += 8;
    if (currHeight + 8 > height)
    {
        currHeight = 0;

        // Move down
        currWidth += 8;
        if (currWidth + 8 > width)
            
            // Nowhere to move. Stop.
            return false;
    }

    SetCurrPixelPosition(currHeight, currWidth);
    return true;
}


////////////////////////////////////////////////////////////////////////////////


void KochZhaoCoder::BuildCoefficientTable()
{
    for (int u = 0; u < 8; ++u)
        for (int v = 0; v < 8; ++v)
            m_FourierCoefficients[u][v] = Sigma(u) * Sigma(v) * Sum(u, v);
}


////////////////////////////////////////////////////////////////////////////////


void KochZhaoCoder::ReverseTransform()
{
    int height, width;
    GetCurrPixelPosition(&height, &width);
    
    double result;

    for (int x = 0; x < 8; ++x)
        for (int y = 0; y < 8; ++y)
        {
            RGBApixel pixel = GetContainer()->GetPixel(height + x, width + y);
            result = Sum2(x, y);
            if (result > 255)
                result = 255;
            else if (result < 0)
                result = 0;

            pixel.Red = static_cast<unsigned char>(result);
            GetContainer()->SetPixel(height + x, width + y, pixel);
        }
}


////////////////////////////////////////////////////////////////////////////////


double KochZhaoCoder::Sigma(int _u)
{
    return _u == 0 ? 0.35355339056 : 0.5;
}


////////////////////////////////////////////////////////////////////////////////


double KochZhaoCoder::Sum(int _u, int _v)
{
    int height, width;
    GetCurrPixelPosition(&height, &width);

    double sum = 0;

    for (int x = 0; x < 8; ++x)
        for (int y = 0; y < 8; ++y)
        {
            double colour = GetContainer()->GetPixel(x + height, y + width).Red;
            double cos1 = cos( 3.1415926535 *
                               static_cast<double>(_u) *
                               static_cast<double>(2 * x + 1) / 16.0 );
            double cos2 = cos( 3.14159265 *
                               static_cast<double>(_v) *
                               static_cast<double>(2 * y + 1) / 16.0 );
            sum += colour * cos1 * cos2;
        }
            
            

    return sum;
}


////////////////////////////////////////////////////////////////////////////////


double KochZhaoCoder::Sum2(int _x, int _y)
{
    double sum = 0;

    for (int u = 0; u < 8; ++u)
        for (int v = 0; v < 8; ++v)
        {
            double cos1 = cos( 3.1415926535 *
                               static_cast<double>(u) *
                               static_cast<double>(2 * _x + 1) / 16.0 );
            double cos2 = cos( 3.1415926535 *
                               static_cast<double>(v) *
                               static_cast<double>(2 * _y + 1) / 16.0 );
            sum += Sigma(u) * Sigma(v) * m_FourierCoefficients[u][v] * cos1 * cos2;
        }

    return sum;
}


////////////////////////////////////////////////////////////////////////////////


void KochZhaoCoder::SetDifference(bool _bit)
{
    double& c1 = m_FourierCoefficients[2][2];
    double& c2 = m_FourierCoefficients[2][3];

    if (_bit)
    {
        while (abs(c1) - abs(c2) >= -m_Threshold)
        {
            if (c1 < 0)
                ++c1;
            else
                --c1;

            if (c2 < 0 && c2 > -255)
                --c2;
            else if (c2 >= 0 && c2 < 255)
                ++c2;
        }
    }
    else
    {
        while (abs(c1) - abs(c2) <= m_Threshold)
        {
            if (c1 > 0 && c1 < 255)
                ++c1;
            else if (c1 <= 0 && c1 > -255)
                --c1;

            if (c2 > 0)
                --c2;
            else
                ++c2;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////


bool KochZhaoCoder::GetDifference()
{
    double& c1 = m_FourierCoefficients[2][2];
    double& c2 = m_FourierCoefficients[2][3];
    return abs(c1) < abs(c2);
}


////////////////////////////////////////////////////////////////////////////////
