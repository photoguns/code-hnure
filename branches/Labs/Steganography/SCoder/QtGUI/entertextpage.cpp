////////////////////////////////////////////////////////////////////////////////

#include "entertextpage.h"
#include "wizard.h"

#include <cassert>
#include <QString>
#include <QTextEdit>

////////////////////////////////////////////////////////////////////////////////


EnterTextPage::EnterTextPage( QWidget* _parent /* = NULL */ )
: TextPage(_parent)
{
    setTitle(tr("Enter Text"));
}


////////////////////////////////////////////////////////////////////////////////


EnterTextPage::~EnterTextPage()
{
}


////////////////////////////////////////////////////////////////////////////////


int EnterTextPage::nextId() const
{
    // Get wizard
    SCoderWizard* aWizard = static_cast<SCoderWizard*>( wizard() );

    // Hide message
    switch ( aWizard->GetContainerType() )
    {
        // Hide message in image
    case SCoderWizard::IMAGE:
        return SCoderWizard::IMAGE_ALGORITHM;

        // Hide message in sound
    case SCoderWizard::SOUND:
        SCoderWizard::SOUND_ALGORITHM;

        // Fail..
    default:
        assert(0);
        return 0;
    }
}


////////////////////////////////////////////////////////////////////////////////


std::string EnterTextPage::getText() const
{
    return m_Text->toPlainText().toStdString();
}


////////////////////////////////////////////////////////////////////////////////
