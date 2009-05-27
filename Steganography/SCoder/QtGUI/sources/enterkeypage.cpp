////////////////////////////////////////////////////////////////////////////////

#include "enterkeypage.h"

////////////////////////////////////////////////////////////////////////////////

#include <QLineEdit>
#include <QVBoxLayout>
#include <QVariant>

#include "scoderwizard.h"

////////////////////////////////////////////////////////////////////////////////


EnterKeyPage::EnterKeyPage( QWidget* _parent /* = NULL */ )
: QWizardPage(_parent)
{
    // Set title
    setTitle(tr("Enter key"));
    setSubTitle(tr("\nThe algorithm you have chosen needs key. Please, enter it"));

    // Create line edit
    m_Key = new QLineEdit;

    // Setup layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_Key);
    setLayout(layout);

    // Create key field
    registerField("Key*", m_Key);
}


////////////////////////////////////////////////////////////////////////////////


EnterKeyPage::~EnterKeyPage()
{
}


////////////////////////////////////////////////////////////////////////////////


int EnterKeyPage::nextId() const
{
    return field("IsHideMessageMode").toBool() ?
        SCoderWizard::SAVE_CONTAINER_PAGE :
        SCoderWizard::VIEW_TEXT_PAGE;
}


////////////////////////////////////////////////////////////////////////////////
