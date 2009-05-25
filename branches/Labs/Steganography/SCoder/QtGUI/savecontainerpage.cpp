////////////////////////////////////////////////////////////////////////////////

#include "savecontainerpage.h"
#include "wizard.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLabel>

////////////////////////////////////////////////////////////////////////////////


SaveContainerPage::SaveContainerPage( QWidget* _parent /* = NULL */ )
: QWizardPage(_parent)
{
    setTitle(tr("Save container"));

    // Create save file button
    m_Save = new QPushButton(tr("&Browse..."));
    m_Save->setMaximumSize(100,30);

    m_Done = new QLabel;

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_Save);
    layout->addWidget(m_Done);

    setLayout(layout);

    connect( m_Save, SIGNAL( clicked() ), this, SLOT( SaveFile() ) );
}


////////////////////////////////////////////////////////////////////////////////


SaveContainerPage::~SaveContainerPage()
{
}


////////////////////////////////////////////////////////////////////////////////


void SaveContainerPage::SaveFile()
{
    m_Done->clear();

    // Show open file dialog
    m_FileName = QFileDialog::getSaveFileName(this, tr("Save as..."),
        QString(), tr("Images (*.bmp);;Sounds (*.wav)"));

    // Display file name
    if (!m_FileName.isEmpty())
    {
        // Get wizard
        SCoderWizard* aWizard = static_cast<SCoderWizard*>( wizard() );
        aWizard->Process();

        m_Done->setText(tr("Done!"));
    }
}


////////////////////////////////////////////////////////////////////////////////


std::string SaveContainerPage::GetFileName() const
{
    return m_FileName.toStdString();
}


////////////////////////////////////////////////////////////////////////////////
