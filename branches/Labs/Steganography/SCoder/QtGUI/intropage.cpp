////////////////////////////////////////////////////////////////////////////////

#include "intropage.h"

////////////////////////////////////////////////////////////////////////////////

#include <QRadioButton>
#include <QVBoxLayout>

#include "scoderwizard.h"

////////////////////////////////////////////////////////////////////////////////


IntroPage::IntroPage( QWidget* _parent /* = NULL */ )
: QWizardPage(_parent)
{
    // Set title
    setTitle(tr("Hello user!"));
    setSubTitle(tr("\nPlease, make your choice"));

    // Setup radio buttons
    m_HideMessage = new QRadioButton(tr("&Hide message"));
    m_GetMessage = new QRadioButton(tr("&Get message"));
    m_HideMessage->setChecked(true);

    // Setup layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_HideMessage);
    layout->addWidget(m_GetMessage);
    setLayout(layout);

    // Register field to save mode in which program will work
    registerField("IsHideMessageMode", m_HideMessage);
}


////////////////////////////////////////////////////////////////////////////////


IntroPage::~IntroPage()
{
}


////////////////////////////////////////////////////////////////////////////////


int IntroPage::nextId() const
{
    // Next is open container page
    return SCoderWizard::OPEN_CONTAINER_PAGE;
}


////////////////////////////////////////////////////////////////////////////////


bool IntroPage::validatePage()
{
    setField( "IsHideMessageMode", m_HideMessage->isChecked() );
    return true;
}


////////////////////////////////////////////////////////////////////////////////
