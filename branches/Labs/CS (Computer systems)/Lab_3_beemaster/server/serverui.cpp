////////////////////////////////////////////////////////////////////////////////

#include <QtGui>
#include "serverui.h"
#include "ui_serverui.h"

////////////////////////////////////////////////////////////////////////////////


ServerUI::ServerUI(QWidget *parent)
: QMainWindow(parent), m_UI(new Ui::ServerUI), m_Image("image.bmp")
{
    // Setup GUI
    m_UI->setupUi(this);

    // Display picture
    m_UI->m_Label->setPixmap( QPixmap::fromImage(m_Image) );

    // Send image to server
    m_Server.SetImage(&m_Image);

    connect(&m_Server, SIGNAL(ImageChanged()), this, SLOT(RefreshImage()));

    // Start server
    if ( !m_Server.listen(QHostAddress::LocalHost, 27027) )
    {
        QMessageBox::critical(this, tr("Server"),
                              tr("Unable to start the server: %1.")
                              .arg(m_Server.errorString()));
         close();
     }
}


////////////////////////////////////////////////////////////////////////////////


ServerUI::~ServerUI()
{
    delete m_UI;
}


////////////////////////////////////////////////////////////////////////////////


void ServerUI::RefreshImage()
{
    // Set new image
    m_UI->m_Label->setPixmap(QPixmap::fromImage(m_Image));
}


////////////////////////////////////////////////////////////////////////////////
