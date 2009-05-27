////////////////////////////////////////////////////////////////////////////////

#include "viewtextpage.h"

////////////////////////////////////////////////////////////////////////////////

#include <QString>
#include <QTextEdit>

#include "scoderwizard.h"

////////////////////////////////////////////////////////////////////////////////


ViewTextPage::ViewTextPage( QWidget* _parent /* = NULL */ )
: TextPage(_parent)
{
    // Set title
    setTitle(tr("Text"));
    setSubTitle(tr("\nVoila! It works, isn't it?"));

    // Can not edit text in get text mode
    m_Text->setReadOnly(true);
}


////////////////////////////////////////////////////////////////////////////////


void ViewTextPage::initializePage()
{
    // Get wizard
    SCoderWizard* aWizard = static_cast<SCoderWizard*>( wizard() );

    // Get text from container
    aWizard->Process();

    // Display it
    m_Text->document()->setPlainText( field("Text").toString() );
}


////////////////////////////////////////////////////////////////////////////////


ViewTextPage::~ViewTextPage()
{
}


////////////////////////////////////////////////////////////////////////////////


int ViewTextPage::nextId() const
{
    return -1;
}


////////////////////////////////////////////////////////////////////////////////
