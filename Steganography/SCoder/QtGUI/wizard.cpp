////////////////////////////////////////////////////////////////////////////////

#include "wizard.h"

////////////////////////////////////////////////////////////////////////////////

#include "intropage.h"
#include "opencontainerpage.h"
#include "entertextpage.h"
#include "viewtextpage.h"
#include "imagealgorithm.h"
#include "soundalgorithm.h"
#include "enterkeypage.h"
#include "savecontainerpage.h"

////////////////////////////////////////////////////////////////////////////////


SCoderWizard::SCoderWizard( QWidget* _parent /* = NULL */ )
: QWizard(_parent)
{
    setPage(INTRO_PAGE,          new IntroPage);
    setPage(OPEN_CONTAINER_PAGE, new OpenContainerPage);
    setPage(ENTER_TEXT_PAGE,     new EnterTextPage);
    setPage(VIEW_TEXT_PAGE,      new ViewTextPage);
    setPage(IMAGE_ALGORITHM,     new ImageAlgorithm);
    setPage(SOUND_ALGORITHM,     new SoundAlgorithm);
    setPage(ENTER_KEY_PAGE,      new EnterKeyPage);
    setPage(SAVE_CONTAINER_PAGE, new SaveContainerPage);

    setStartId(INTRO_PAGE);
    setWindowTitle(tr("SCoder Wizard"));
}


////////////////////////////////////////////////////////////////////////////////


SCoderWizard::~SCoderWizard()
{
}


////////////////////////////////////////////////////////////////////////////////


SCoderWizard::ContainerType SCoderWizard::GetContainerType() const
{
    OpenContainerPage* openPage = static_cast<OpenContainerPage*>( page(INTRO_PAGE) );
    return openPage->IsImageContainer() ? Containers::IMAGE : Containers::SOUND;
}


////////////////////////////////////////////////////////////////////////////////


bool SCoderWizard::IsHideMessageMode() const
{
    IntroPage* introPage = static_cast<IntroPage*>( page(INTRO_PAGE) );
    return introPage->IsHideMessageMode();
}


////////////////////////////////////////////////////////////////////////////////

std::string SCoderWizard::GetOpenFileName() const
{
    OpenContainerPage* openPage = static_cast<OpenContainerPage*>( page(INTRO_PAGE) );
    return openPage->GetFileName();
}

////////////////////////////////////////////////////////////////////////////////


void SCoderWizard::Process()
{
    Container* container = NULL;
    switch ( GetContainerType() )
    {
        // Image container
    case Containers::IMAGE:
        container = GetBMPContainer( GetOpenFileName() );
        break;

        // Sound container
    case Containers::SOUND:
        container = GetWAVContainer( GetOpenFileName() );
        break;

        //Problem
    default:
        assert(0);
        break;
    }

    Coder* coder = NULL;

}


////////////////////////////////////////////////////////////////////////////////