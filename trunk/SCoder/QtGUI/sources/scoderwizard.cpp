////////////////////////////////////////////////////////////////////////////////

#include "scoderwizard.h"

////////////////////////////////////////////////////////////////////////////////

#include "intropage.h"
#include "opencontainerpage.h"
#include "entertextpage.h"
#include "viewtextpage.h"
#include "imagealgorithm.h"
#include "soundalgorithm.h"
#include "enterkeypage.h"
#include "savecontainerpage.h"
#include "hidepage.h"

#include <QVariant>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////


SCoderWizard::SCoderWizard( QWidget* _parent /* = NULL */ )
: QWizard(_parent)
{
    // Set Wizard window title
    setWindowTitle(tr("SCoder Wizard"));

    // Yo yo yo check this out
    setWizardStyle(ClassicStyle);

    // Add pages
    setPage(INTRO_PAGE,          new IntroPage);
    setPage(OPEN_CONTAINER_PAGE, new OpenContainerPage);
    setPage(ENTER_TEXT_PAGE,     new EnterTextPage);
    setPage(IMAGE_ALGORITHM,     new ImageAlgorithm);
    setPage(SOUND_ALGORITHM,     new SoundAlgorithm);
    setPage(ENTER_KEY_PAGE,      new EnterKeyPage);
    setPage(SAVE_CONTAINER_PAGE, new SaveContainerPage);
    setPage(VIEW_TEXT_PAGE,      new ViewTextPage);
    setPage(HIDE_PAGE,           new HidePage);

    // Set start page
    setStartId(INTRO_PAGE);
}


////////////////////////////////////////////////////////////////////////////////


SCoderWizard::~SCoderWizard()
{
}


////////////////////////////////////////////////////////////////////////////////


ContainerType SCoderWizard::GetContainerType() const
{
    return static_cast<ContainerType>( field("ContainerType").toInt() );
}


////////////////////////////////////////////////////////////////////////////////


bool SCoderWizard::IsHideMessageMode() const
{
    return field("IsHideMessageMode").toBool();
}


////////////////////////////////////////////////////////////////////////////////

std::string SCoderWizard::GetOpenFileName() const
{
    return field("OpenFileName").toString().toStdString();
}


////////////////////////////////////////////////////////////////////////////////


std::string SCoderWizard::GetSaveFileName() const
{
    return field("SaveFileName").toString().toStdString();
}


////////////////////////////////////////////////////////////////////////////////


std::string SCoderWizard::GetText() const
{
    return field("Text").toString().toStdString();
}


////////////////////////////////////////////////////////////////////////////////


void SCoderWizard::SetText( std::string _text )
{
    setField("Text", QString::fromStdString(_text) );
}


////////////////////////////////////////////////////////////////////////////////


std::string SCoderWizard::GetKeyText() const
{
    return field("Key").toString().toStdString();
}


////////////////////////////////////////////////////////////////////////////////


CoderType SCoderWizard::GetCoderType() const
{
    return static_cast<CoderType>( field("CoderType").toInt() );
}


////////////////////////////////////////////////////////////////////////////////


void SCoderWizard::Process()
{
    // Get container
    Container* container = GetContainer ( GetContainerType(), GetOpenFileName() );

    // Get coder
    Coder* coder = GetCoder( GetCoderType() );

    // Get key
    Key* key = GetKey( GetCoderType(), GetKeyText(), Key::STRING);

    if ( IsHideMessageMode() )
    {
        // Hide and save
        coder->SetMessage(container, GetText(), key);
        container->Save( GetSaveFileName() );
    }
    else
    {
        // Reveal
        SetText ( coder->GetMessage(container, key) );
    }
}


////////////////////////////////////////////////////////////////////////////////

