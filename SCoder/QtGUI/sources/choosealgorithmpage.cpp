////////////////////////////////////////////////////////////////////////////////

#include "choosealgorithmpage.h"
#include "scoderwizard.h"

#include <QVariant>

////////////////////////////////////////////////////////////////////////////////


ChooseAlgorithmPage::ChooseAlgorithmPage( QWidget* _parent /* = NULL */ )
: QWizardPage(_parent)
{
    // Set title
    setTitle(tr("Choose algorithm"));
    setSubTitle(tr("\nThis one will be used to hide text into container in specific way"));

    // Register field representing coder type
    registerField("CoderType", this);
}


////////////////////////////////////////////////////////////////////////////////


ChooseAlgorithmPage::~ChooseAlgorithmPage()
{
}


////////////////////////////////////////////////////////////////////////////////


int ChooseAlgorithmPage::nextId() const
{
    if ( NeedsKey() )
        return SCoderWizard::ENTER_KEY_PAGE;
    else
    {
        if ( field("IsHideMessageMode").toBool() )
            return SCoderWizard::SAVE_CONTAINER_PAGE;
        else
            return SCoderWizard::VIEW_TEXT_PAGE;
    }
}


////////////////////////////////////////////////////////////////////////////////
