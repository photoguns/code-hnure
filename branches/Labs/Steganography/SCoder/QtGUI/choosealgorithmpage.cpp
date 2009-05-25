////////////////////////////////////////////////////////////////////////////////

#include "choosealgorithmpage.h"
#include "wizard.h"

////////////////////////////////////////////////////////////////////////////////


ChooseAlgorithmPage::ChooseAlgorithmPage( QWidget* _parent /* = NULL */ )
: QWizardPage(_parent)
{
    setTitle(tr("Choose algorithm"));
}


////////////////////////////////////////////////////////////////////////////////


ChooseAlgorithmPage::~ChooseAlgorithmPage()
{
}


////////////////////////////////////////////////////////////////////////////////


int ChooseAlgorithmPage::nextId() const
{
    // Get wizard
    SCoderWizard* aWizard = static_cast<SCoderWizard*>( wizard() );

    return NeedsKey() ?
        SCoderWizard::ENTER_KEY_PAGE :
        ( aWizard->IsHideMessageMode() ?
             SCoderWizard::SAVE_CONTAINER_PAGE :
             SCoderWizard::VIEW_TEXT_PAGE );
}


////////////////////////////////////////////////////////////////////////////////
