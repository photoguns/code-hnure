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

#include <cassert>

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


ContainerType SCoderWizard::GetContainerType() const
{
    OpenContainerPage* openPage = static_cast<OpenContainerPage*>( page(INTRO_PAGE) );
    return openPage->IsImageContainer() ? IMAGE : SOUND;
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
    OpenContainerPage* openPage = static_cast<OpenContainerPage*>( page(OPEN_CONTAINER_PAGE) );
    return openPage->GetFileName();
}


////////////////////////////////////////////////////////////////////////////////


std::string SCoderWizard::GetSaveFileName() const
{
    SaveContainerPage* savePage = static_cast<SaveContainerPage*>( page(SAVE_CONTAINER_PAGE) );
    return savePage->GetFileName();
}


////////////////////////////////////////////////////////////////////////////////


std::string SCoderWizard::GetText() const
{
    const EnterTextPage* enterTextPage = static_cast<const EnterTextPage*>( page(ENTER_TEXT_PAGE) );
    return enterTextPage->GetText();
}


////////////////////////////////////////////////////////////////////////////////


void SCoderWizard::SetText( std::string _text )
{
    ViewTextPage* viewTextPage = static_cast<ViewTextPage*>( page(VIEW_TEXT_PAGE) );
    return viewTextPage->SetText(_text);
}


////////////////////////////////////////////////////////////////////////////////


std::string SCoderWizard::GetKey() const
{
    EnterKeyPage* keyPage = static_cast<EnterKeyPage*>( page(ENTER_KEY_PAGE) );
    return keyPage->GetKey();
}


////////////////////////////////////////////////////////////////////////////////


CoderType SCoderWizard::GetCoderType() const
{
    switch ( GetContainerType() )
    {
        // Image container
    case IMAGE:
        {
            SoundAlgorithm* soundPage = static_cast<SoundAlgorithm*>( page(SOUND_ALGORITHM) );
            return soundPage->GetCoderType();
        }

        // Sound container
    case SOUND:
        {
            ImageAlgorithm* imagePage = static_cast<ImageAlgorithm*>( page(IMAGE_ALGORITHM) );
            return imagePage->GetCoderType();
        }
        //Problem
    default:
        assert(0);
        return INVALID;
    }
}


////////////////////////////////////////////////////////////////////////////////


void SCoderWizard::Process()
{
    Container* container = NULL;
    switch ( GetContainerType() )
    {
        // Image container
    case IMAGE:
        container = GetBMPContainer( GetOpenFileName() );
        break;

        // Sound container
    case SOUND:
        container = GetWAVContainer( GetOpenFileName() );
        break;

        //Problem
    default:
        assert(0);
        break;
    }

    Coder* coder = NULL;
    Key* key = NULL;

    switch ( GetCoderType() )
    {
    case LSB:
        coder = GetLSBCoder();
        break;
    case PRS:
        coder = GetPRSCoder();
        key = GetPRSKey(GetKey(), Key::FILE);
        break;
    case PRI:
        coder = GetPRICoder();
        key = GetPRIKey(GetKey(), Key::FILE);
        break;
    case BLOCK:
        coder = GetBlockCoder();
        key = GetBlockKey(GetKey(), Key::FILE);
        break;
    case QUANT:
        coder = GetQuantCoder();
        key = GetQuantKey(GetKey(), Key::FILE);
        break;
    case CROSS:
        coder = GetCrossCoder();
        break;
    case KOCHZHAO:
        coder = GetKochZhaoCoder();
        key = GetKochZhaoKey(GetKey(), Key::FILE);
    case LSBSOUND:
        coder = GetLSBSoundCoder();
        break;
    case ECHO:
        coder = GetEchoCoder();
        break;
    }

    if ( IsHideMessageMode() )
    {
        coder->SetMessage(container, GetText(), key);
        container->Save( GetSaveFileName() );
    }
    else
    {
        SetText ( coder->GetMessage(container, key) );
    }
}


////////////////////////////////////////////////////////////////////////////////

