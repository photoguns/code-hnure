////////////////////////////////////////////////////////////////////////////////

#include "intropage.h"
#include "wizard.h"

#include <QRadioButton>
#include <QVBoxLayout>

////////////////////////////////////////////////////////////////////////////////


IntroPage::IntroPage( QWidget* _parent /* = NULL */ )
: QWizardPage(_parent)
{
    setTitle(tr("Hello SCoder!"));

    m_HideMessage = new QRadioButton(tr("&Hide message"));
    m_GetMessage = new QRadioButton(tr("&Get message"));
    m_HideMessage->setChecked(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_HideMessage);
    layout->addWidget(m_GetMessage);
    setLayout(layout);
}


////////////////////////////////////////////////////////////////////////////////


IntroPage::~IntroPage()
{
}


////////////////////////////////////////////////////////////////////////////////


int IntroPage::nextId() const
{
    return SCoderWizard::OPEN_CONTAINER_PAGE;
}


////////////////////////////////////////////////////////////////////////////////


bool IntroPage::IsHideMessageMode() const
{
    return m_HideMessage->isChecked();
}


////////////////////////////////////////////////////////////////////////////////
