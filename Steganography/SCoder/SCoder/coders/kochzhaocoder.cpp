////////////////////////////////////////////////////////////////////////////////

#include "kochzhaocoder.h"
#include "bmpcontainer.h"
#include "kochzhaokey.h"

#define _USE_MATH_DEFINES
#include "math.h"

////////////////////////////////////////////////////////////////////////////////


KochZhaoCoder::KochZhaoCoder()
//Increase this parameter if text is not recognized properly
//May be increased up to 255
:m_Threshold(160),
m_C1(NULL),
m_C2(NULL)
{
}


////////////////////////////////////////////////////////////////////////////////


KochZhaoCoder::~KochZhaoCoder()
{
}


////////////////////////////////////////////////////////////////////////////////


void KochZhaoCoder::SetMessage( Container* _container,
                               const std::string& _message, 
                               const Key* _key )
{
    // Must be a Koch-Zhao key
    if ( _key->IsKochZhaoKey() )
    {
        const KochZhaoKey* key = static_cast<const KochZhaoKey*>(_key);

        // Get key -- two coordinates of Fourier coefficients in table
        KochZhaoKey::TwoCoords coords = key->GetKochZhaoKey(TABLESIZE);

        m_C1 = &m_FourierCoefficients[coords.first.first][coords.first.second];
        m_C2 = &m_FourierCoefficients[coords.second.first][coords.second.second];

        // Hide message using LSB algorithm
        LSBCoder::SetMessage(_container, _message);
    }
}


////////////////////////////////////////////////////////////////////////////////


std::string KochZhaoCoder::GetMessage( const Container* _container, const Key* _key )
{
    // Must be a Koch-Zhao key
    if ( _key->IsKochZhaoKey() )
    {
        const KochZhaoKey* key = static_cast<const KochZhaoKey*>(_key);

        // Get key -- two coordinates of Fourier coefficients in table
        KochZhaoKey::TwoCoords coords = key->GetKochZhaoKey(TABLESIZE);

        m_C1 = &m_FourierCoefficients[coords.first.first][coords.first.second];
        m_C2 = &m_FourierCoefficients[coords.second.first][coords.second.second];

        // Get message using LSB algorithm
        return LSBCoder::GetMessage(_container);
    }

    // Not a PRI key
    return "";
}
////////////////////////////////////////////////////////////////////////////////


void KochZhaoCoder::SetupContainer( const BMPContainer* _container )
{
    LSBCoder::SetupContainer(_container);

    //Begin from upper left corner
    SetCurrPixelPosition(-TABLESIZE, 0);
}


////////////////////////////////////////////////////////////////////////////////


bool KochZhaoCoder::SetBit( bool _bit )
{
    if ( !JumpToNextPixel() )
        return false;

    // Build coefficient table
    ForvardFourierTransform();

    // Set difference between two coefficients
    SetDifference(_bit);

    // Build colour table
    ReverseFourierTransform();

    // Bit has been written
    return true;
}


////////////////////////////////////////////////////////////////////////////////


bool KochZhaoCoder::GetBit( bool* _bit )
{
    if ( !JumpToNextPixel() )
        return false;

    // Build coefficient table
    ForvardFourierTransform();

    // Get difference between two coefficients
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
    currHeight += TABLESIZE;
    if (currHeight + TABLESIZE > height)
    {
        currHeight = 0;

        // Move down
        currWidth += TABLESIZE;
        if (currWidth + TABLESIZE > width)

            // Nowhere to move. Stop.
            return false;
    }

    SetCurrPixelPosition(currHeight, currWidth);
    return true;
}


////////////////////////////////////////////////////////////////////////////////


void KochZhaoCoder::ForvardFourierTransform()
{
    // Fucking math! I hate it =)
    for (int u = 0; u < TABLESIZE; ++u)
        for (int v = 0; v < TABLESIZE; ++v)
            m_FourierCoefficients[u][v] = Sigma(u) * Sigma(v) * SumForvard(u, v);
}


////////////////////////////////////////////////////////////////////////////////


void KochZhaoCoder::ReverseFourierTransform()
{
    int height, width;
    GetCurrPixelPosition(&height, &width);

    double result;

    for (int x = 0; x < TABLESIZE; ++x)
        for (int y = 0; y < TABLESIZE; ++y)
        {
            // Get pixel
            RGBApixel pixel = GetContainer()->GetPixel(height + x, width + y);

            // Get red colour from modified table
            result = SumReverse(x, y);

            // Normalize result
            if (result > 255)
                result = 255;
            else if (result < 0)
                result = 0;

            pixel.Red = static_cast<unsigned char>(result);

            // Set modified pixel
            GetContainer()->SetPixel(height + x, width + y, pixel);
        }
}


////////////////////////////////////////////////////////////////////////////////


double KochZhaoCoder::Sigma(int _u)
{
    // Magic comes here
    return _u == 0 ? 0.35355339056 : 0.5;
}


////////////////////////////////////////////////////////////////////////////////


double KochZhaoCoder::SumForvard(int _u, int _v)
{
    // Get current pixel position
    int height, width;
    GetCurrPixelPosition(&height, &width);

    double sum = 0;

    // Maaaaaagic, its everywhere
    for (int x = 0; x < TABLESIZE; ++x)
        for (int y = 0; y < TABLESIZE; ++y)
        {
            double colour = GetContainer()->GetPixel(x + height, y + width).Red;
            double cos1 = cos( M_PI *
                static_cast<double>(_u) *
                static_cast<double>(2 * x + 1) / static_cast<double>(TABLESIZE * 2) );
            double cos2 = cos( M_PI *
                static_cast<double>(_v) *
                static_cast<double>(2 * y + 1) / static_cast<double>(TABLESIZE * 2) );
            sum += colour * cos1 * cos2;
        }

        return sum;
}


////////////////////////////////////////////////////////////////////////////////


double KochZhaoCoder::SumReverse(int _x, int _y)
{
    double sum = 0;

    for (int u = 0; u < TABLESIZE; ++u)
        for (int v = 0; v < TABLESIZE; ++v)
        {
            double cos1 = cos( M_PI *
                static_cast<double>(u) *
                static_cast<double>(2 * _x + 1) / static_cast<double>(TABLESIZE * 2) );
            double cos2 = cos( M_PI *
                static_cast<double>(v) *
                static_cast<double>(2 * _y + 1) / static_cast<double>(TABLESIZE * 2) );
            sum += Sigma(u) * Sigma(v) * m_FourierCoefficients[u][v] * cos1 * cos2;
        }

        return sum;
}


////////////////////////////////////////////////////////////////////////////////


void KochZhaoCoder::SetDifference(bool _bit)
{
    // Hell manipulation with numbers
    if (_bit)
    {
        // Difference between these two coefficients 
        // must not be greater than -m_Threshold
        // this case will hide bit, which value is 1
        while (abs(*m_C1) - abs(*m_C2) >= -m_Threshold)
        {
            if (*m_C1 < 0)
                ++*m_C1;
            else
                --*m_C1;

            if (*m_C2 < 0 && *m_C2 > -255)
                --*m_C2;
            else if (*m_C2 >= 0 && *m_C2 < 255)
                ++*m_C2;
        }
    }
    else
    {
        // Difference between these two coefficients 
        // must not be smaller than -m_Threshold
        // this case will hide bit, which value is 0
        while (abs(*m_C1) - abs(*m_C2) <= m_Threshold)
        {
            if (*m_C1 > 0 && *m_C1 < 255)
                ++*m_C1;
            else if (*m_C1 <= 0 && *m_C1 > -255)
                --*m_C1;

            if (*m_C2 > 0)
                --*m_C2;
            else
                ++*m_C2;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////


bool KochZhaoCoder::GetDifference()
{
    return abs(*m_C1) < abs(*m_C2);
}


////////////////////////////////////////////////////////////////////////////////
