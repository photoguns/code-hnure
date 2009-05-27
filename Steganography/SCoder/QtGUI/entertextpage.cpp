////////////////////////////////////////////////////////////////////////////////

#include "entertextpage.h"

////////////////////////////////////////////////////////////////////////////////

#include <cassert>

#include "scoderwizard.h"

////////////////////////////////////////////////////////////////////////////////


EnterTextPage::EnterTextPage( QWidget* _parent /* = NULL */ )
: TextPage(_parent)
{
    // Set title
    setTitle(tr("Enter Text"));
    setSubTitle(tr("\nYou can type or paste the text which will be injected into container"));
}


////////////////////////////////////////////////////////////////////////////////


EnterTextPage::~EnterTextPage()
{
}


////////////////////////////////////////////////////////////////////////////////


int EnterTextPage::nextId() const
{
    // Hide message
    switch ( static_cast<ContainerType>( field("ContainerType").toInt() ) )
    {
        // Hide message in image
    case IMAGE:
        return SCoderWizard::IMAGE_ALGORITHM;

        // Hide message in sound
    case SOUND:
        return SCoderWizard::SOUND_ALGORITHM;

        // Fail..
    default:
        assert(0);
        return 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
