////////////////////////////////////////////////////////////////////////////////

#include "soundalgorithm.h"

#include <QRadioButton>
#include <QVBoxLayout>

#include <cassert>

////////////////////////////////////////////////////////////////////////////////


SoundAlgorithm::SoundAlgorithm( QWidget* _parent /* = NULL */ )
: ChooseAlgorithmPage(_parent)
{
    m_LSBSound = new QRadioButton(tr("&LSB Sound"));
    m_Echo     = new QRadioButton(tr("&Echo Sound"));

    m_LSBSound->setChecked(true);
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
    return m_Echo->isChecked();
}


////////////////////////////////////////////////////////////////////////////////


CoderType SoundAlgorithm::GetCoderType() const
{
    if ( m_Echo->isChecked() )
        return ECHO;
    else if (m_LSBSound->isChecked() )
        return LSBSOUND;
    else
    {
        assert(0);
        return INVALID;
    }
}


////////////////////////////////////////////////////////////////////////////////
