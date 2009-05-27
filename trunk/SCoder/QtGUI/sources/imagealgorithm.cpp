////////////////////////////////////////////////////////////////////////////////

#include "imagealgorithm.h"

////////////////////////////////////////////////////////////////////////////////

#include <QRadioButton>
#include <QVBoxLayout>
#include <QVariant>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////


ImageAlgorithm::ImageAlgorithm( QWidget* _parent /* = NULL */ )
: ChooseAlgorithmPage(_parent)
{
    // Create radio buttons
    m_LSB      = new QRadioButton(tr("&Least Significant Bit"));
    m_PRI      = new QRadioButton(tr("&Pseudo-random interval"));
    m_PRS      = new QRadioButton(tr("&Pseudo-random &substitution"));
    m_Block    = new QRadioButton(tr("&Blocking"));
    m_Quant    = new QRadioButton(tr("&Quantization"));
    m_Cross    = new QRadioButton(tr("&Cross"));
    m_KochZhao = new QRadioButton(tr("&Koch-Zhao"));

    // Set LSB default algoruthm
    m_LSB->setChecked(true);

    // Setup layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_LSB);
    layout->addWidget(m_PRI);
    layout->addWidget(m_PRS);
    layout->addWidget(m_Block);
    layout->addWidget(m_Quant);
    layout->addWidget(m_Cross);
    layout->addWidget(m_KochZhao);
    setLayout(layout);
}


////////////////////////////////////////////////////////////////////////////////


ImageAlgorithm::~ImageAlgorithm()
{
}


////////////////////////////////////////////////////////////////////////////////


bool ImageAlgorithm::NeedsKey() const
{
    // Get coder type
    CoderType coderType = static_cast<CoderType>( field("CoderType").toInt() );

    // Only LSB and CROSS algorithms do not need key
    return coderType != LSB && coderType != CROSS;
}


////////////////////////////////////////////////////////////////////////////////


bool ImageAlgorithm::validatePage()
{
    CoderType coderType = INVALID;

    // Determine coder type
    if ( m_LSB->isChecked() )
        coderType = LSB;
    else if (m_PRS->isChecked() )
        coderType = PRS;
    else if (m_PRI->isChecked() )
        coderType = PRI;
    else if (m_Block->isChecked() )
        coderType = BLOCK;
    else if (m_Quant->isChecked() )
        coderType = QUANT;
    else if (m_Block->isChecked() )
        coderType = BLOCK;
    else if (m_Cross->isChecked() )
        coderType = CROSS;
    else if (m_KochZhao->isChecked() )
        coderType = KOCHZHAO;

    assert(coderType != INVALID);

    // Set coder type field
    setField("CoderType", static_cast<int>(coderType) );

    // Go to next page
    return true;
}


////////////////////////////////////////////////////////////////////////////////
