////////////////////////////////////////////////////////////////////////////////

#include "opencontainerpage.h"
#include "wizard.h"
#include <cassert>

#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLabel>

////////////////////////////////////////////////////////////////////////////////


OpenContainerPage::OpenContainerPage( QWidget* _parent /* = NULL */ )
: QWizardPage(_parent)
{
    setTitle(tr("Open container"));

    // Create open file button
    m_Open = new QPushButton(tr("&Browse..."));
    m_Open->setMaximumSize(100,30);

    m_FileName = new QLabel;

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_Open);
    layout->addWidget(m_FileName);

    setLayout(layout);

    connect( m_Open, SIGNAL( clicked() ), this, SLOT( OpenFile() ) );
}


////////////////////////////////////////////////////////////////////////////////


OpenContainerPage::~OpenContainerPage()
{
}


////////////////////////////////////////////////////////////////////////////////


int OpenContainerPage::nextId() const
{
    // Get wizard
    SCoderWizard* aWizard = static_cast<SCoderWizard*>( wizard() );

    // Hide message
    if ( aWizard->IsHideMessageMode() )
        return  SCoderWizard::ENTER_TEXT_PAGE;
    else
    {
        // Get message
        switch ( aWizard->GetContainerType() )
        {
            // Get message from image
        case SCoderWizard::IMAGE:
            return SCoderWizard::IMAGE_ALGORITHM;

            // Get message from sound
        case SCoderWizard::SOUND:
            SCoderWizard::SOUND_ALGORITHM;
        
            // Fail..
        default:
            assert(0);
            return 0;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////


bool OpenContainerPage::IsImageContainer() const
{
    return true;
}


////////////////////////////////////////////////////////////////////////////////


void OpenContainerPage::OpenFile()
{
    // Show open file dialog
    QString fn = QFileDialog::getOpenFileName(this, tr("Open File..."),
        QString(), tr("Images (*.bmp);;Sounds (*.wav)"));

    // Display file name
    if (!fn.isEmpty())
        m_FileName->setText(fn);
}


////////////////////////////////////////////////////////////////////////////////


std::string OpenContainerPage::GetFileName() const
{
    return m_FileName->text().toStdString();
}


////////////////////////////////////////////////////////////////////////////////
