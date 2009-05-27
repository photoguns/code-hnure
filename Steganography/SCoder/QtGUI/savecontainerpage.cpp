////////////////////////////////////////////////////////////////////////////////

#include "savecontainerpage.h"

////////////////////////////////////////////////////////////////////////////////

#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLineEdit>
#include <cassert>

#include "scoderwizard.h"

////////////////////////////////////////////////////////////////////////////////


SaveContainerPage::SaveContainerPage( QWidget* _parent /* = NULL */ )
: QWizardPage(_parent)
{
    // Set title
    setTitle(tr("Save container"));
    setSubTitle(tr("\nChose where to save container after modification"));

    // Create save file button
    m_Save = new QPushButton(tr("&Browse..."));
    m_Save->setMaximumSize(100,30);

    // Create line edit displaying save file path
    m_Path = new QLineEdit;
    m_Path->setReadOnly(true);

    // Setup layout
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_Save);
    layout->addWidget(m_Path);
    setLayout(layout);

    // Connect signals to slots
    connect( m_Save, SIGNAL( clicked() ), this, SLOT( SaveFile() ) );

    // Register field with save file name
    registerField("SaveFileName*", m_Path);
}


////////////////////////////////////////////////////////////////////////////////


SaveContainerPage::~SaveContainerPage()
{
}


////////////////////////////////////////////////////////////////////////////////


bool SaveContainerPage::validatePage()
{
    if ( field("OpenFileName") == field("SaveFileName") )
    {
        QMessageBox box(QMessageBox::Warning, tr("Error"),
            tr("Please, specify another path for saving file."),
            QMessageBox::Ok, this);
        
        box.exec();
        
        return false;
    }

    // Exit
    return true;
}


////////////////////////////////////////////////////////////////////////////////

void SaveContainerPage::SaveFile()
{
    QString filter;
    switch ( static_cast<ContainerType>( field("ContainerType").toInt() ) )
    {
    case IMAGE:
        filter = tr("Images (*.bmp)");
        break;
    case SOUND:
        filter = tr("Sounds (*.wav)");
        break;
    default:
        assert(0);
    }


    // Show open file dialog
    QString path = QFileDialog::getSaveFileName( this, tr("Save as..."),
                                                 QString(), filter );

    // Display file name
    if (!path.isEmpty())
        setField("SaveFileName", path);
}


////////////////////////////////////////////////////////////////////////////////


int SaveContainerPage::nextId() const
{
    return SCoderWizard::HIDE_PAGE;
}


////////////////////////////////////////////////////////////////////////////////
