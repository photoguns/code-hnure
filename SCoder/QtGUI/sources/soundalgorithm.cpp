////////////////////////////////////////////////////////////////////////////////

#include "soundalgorithm.h"

#include <QRadioButton>
#include <QVBoxLayout>
#include <QVariant>

#include <cassert>

////////////////////////////////////////////////////////////////////////////////


SoundAlgorithm::SoundAlgorithm( QWidget* _parent /* = NULL */ )
: ChooseAlgorithmPage(_parent)
{
    // Setup radio buttons
    m_LSBSound = new QRadioButton(tr("&Least Significant Bit"));
    m_Echo     = new QRadioButton(tr("&Echo"));

    // Default algorithm
    m_LSBSound->setChecked(true);

    // Setup layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_LSBSound);
    layout->addWidget(m_Echo);
    setLayout(layout);
}


////////////////////////////////////////////////////////////////////////////////


SoundAlgorithm::~SoundAlgorithm()
{
}


////////////////////////////////////////////////////////////////////////////////


bool SoundAlgorithm::NeedsKey() const
{
    // Get coder type
    CoderType coderType = static_cast<CoderType>( field("CoderType").toInt() );
    
    // LSB algorithm does not need a key
    return coderType != LSBSOUND;
}


////////////////////////////////////////////////////////////////////////////////


bool SoundAlgorithm::validatePage()
{
    CoderType coderType = INVALID;

    // Determine coder type
    if ( m_LSBSound->isChecked() )
        coderType = LSBSOUND;
    else if (m_Echo->isChecked() )
        coderType = ECHO;

    assert(coderType != INVALID);

    // Set coder type field
    setField("CoderType", static_cast<int>(coderType) );

    // Go to next page
    return true;
}


////////////////////////////////////////////////////////////////////////////////
