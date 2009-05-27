////////////////////////////////////////////////////////////////////////////////

#include "opencontainerpage.h"

////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLineEdit>

#include "scoderwizard.h"

////////////////////////////////////////////////////////////////////////////////


OpenContainerPage::OpenContainerPage( QWidget* _parent /* = NULL */ )
: QWizardPage(_parent)
{
    // Set title
    setTitle(tr("Open container"));
    setSubTitle(tr("You can open a BMP image or a WAV sound file.\n" \
                   "Note: only 24-bit images and 16-bit audio files are supported!"));

    // Create open file button
    m_Open = new QPushButton(tr("&Browse..."));
    m_Open->setMaximumSize(100,30);

    // Create line edit for displaying filename
    m_FileName = new QLineEdit;
    m_FileName->setReadOnly(true);

    // Setup layout
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_Open);
    layout->addWidget(m_FileName);

    setLayout(layout);

    registerField("OpenFileName*", m_FileName);
    registerField("ContainerType", this);

    // Connect signal to slot
    connect( m_Open, SIGNAL( clicked() ), this, SLOT( OpenFile() ) );
}


////////////////////////////////////////////////////////////////////////////////


OpenContainerPage::~OpenContainerPage()
{
}


////////////////////////////////////////////////////////////////////////////////


int OpenContainerPage::nextId() const
{
    // If hide mode -- go to enter text page
    if ( field("IsHideMessageMode").toBool() )
        return SCoderWizard::ENTER_TEXT_PAGE;
    else
    {
        // Chose algorithm
        switch ( static_cast<ContainerType>( field("ContainerType").toInt() ) )
        {
        case IMAGE:
            return SCoderWizard::IMAGE_ALGORITHM;
        case SOUND:
            return SCoderWizard::SOUND_ALGORITHM;
        default:
            assert(0);
            return 0;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////


void OpenContainerPage::OpenFile()
{
    // Show open file dialog
    QString fn = QFileDialog::getOpenFileName(this,
                                              tr("Open File..."),
                                              QString(),
                                              tr("Images, Sounds (*.bmp *.wav)") );
    
    // Display file name
    if (!fn.isEmpty())
    {
        // Set container type
        if ( fn.endsWith(".bmp", Qt::CaseInsensitive) )
            setField("ContainerType", static_cast<int>(IMAGE) );
        else if ( fn.endsWith(".wav", Qt::CaseInsensitive) )
            setField("ContainerType", static_cast<int>(SOUND) );

        // Set file name
        m_FileName->setText(fn);
    }
}


////////////////////////////////////////////////////////////////////////////////
