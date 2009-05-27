////////////////////////////////////////////////////////////////////////////////

#include "hidepage.h"

////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include "scoderwizard.h"

////////////////////////////////////////////////////////////////////////////////


HidePage::HidePage( QWidget* _parent /* = NULL */ )
: QWizardPage(_parent)
{
    // Set title
    setTitle(tr("Now you can hide it!"));
    setSubTitle(tr("\nPress 'Hide' button to inject the text"));

    // Create open file button
    m_Go = new QPushButton(tr("&Hide"));
    m_Go->setMaximumSize(100,30);

    // Create line edit for displaying filename
    m_Done = new QLabel;

    // Setup layout
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_Go);
    layout->addWidget(m_Done);

    setLayout(layout);

    // Connect signal to slot
    connect( m_Go, SIGNAL( clicked() ), this, SLOT( Hide() ) );
}


////////////////////////////////////////////////////////////////////////////////


HidePage::~HidePage()
{
}


////////////////////////////////////////////////////////////////////////////////


int HidePage::nextId() const
{
  return -1;
}


////////////////////////////////////////////////////////////////////////////////


void HidePage::Hide()
{
    // Get wizard
    SCoderWizard* aWizard = static_cast<SCoderWizard*>( wizard() );
    
    // Do it!
    aWizard->Process();

    //Display status
    m_Done->setText("Done! Modified container successfully saved to\n" +
                    field("SaveFileName").toString() );

}


////////////////////////////////////////////////////////////////////////////////


void HidePage::cleanupPage()
{
    m_Done->clear();
}


////////////////////////////////////////////////////////////////////////////////
