#include "server.h"
#include "serverthread.h"


////////////////////////////////////////////////////////////////////////////////


Server::Server(QObject* _parent)
:QTcpServer(_parent), m_ConnectedClients(0)
{
    // Create mask for image
    m_Mask.push_back(1);
    m_Mask.push_back(4);
    m_Mask.push_back(1);
    m_Mask.push_back(-3);
    m_Mask.push_back(-1);
    m_Mask.push_back(-3);
    m_Mask.push_back(3);
    m_Mask.push_back(-2);
    m_Mask.push_back(1);
}


////////////////////////////////////////////////////////////////////////////////


void Server::SetImage(QImage* _image)
{
    // Set current image
    m_Image = _image;

    // Fetch colours
    for (int i = 0; i < m_Image->width(); ++i)
        for (int j = 0; j < m_Image->height(); ++j)
        {
            QRgb pixel = m_Image->pixel(i,j);
            m_Red.push_back( qRed(pixel) );
            m_Green.push_back( qGreen(pixel) );
            m_Blue.push_back( qBlue(pixel) );
        }
}


////////////////////////////////////////////////////////////////////////////////


void Server::ViewMaskedImage()
{
    // Fetch colours
    for (int i = 0; i < m_Image->width(); ++i)
        for (int j = 0; j < m_Image->height(); ++j)
        {
            QRgb pixel = qRgb( m_Red  [i * m_Image->height() + j],
                               m_Green[i * m_Image->height() + j],
                               m_Blue [i * m_Image->height() + j] );
            m_Image->setPixel(i,j, pixel);
        }

    // Send signal to GUI
    emit(ImageChanged());
}


////////////////////////////////////////////////////////////////////////////////


void Server::incomingConnection(int socketDescriptor)
{
    // Increase clients counter
    ++m_ConnectedClients;

    QVector<int>* colour = NULL;

    // First client processes red colour,
    // second processes green and third - blue
    switch (m_ConnectedClients)
    {
    case 1:
        colour = &m_Red;
        break;

    case 2:
        colour = &m_Green;
        break;

    case 3:
        colour = &m_Blue;
        break;

    default:
        break;
    }

    // Each colour is processed in separate thread
    if (colour)
    {
        // Start new thread
        ServerThread* thread = new ServerThread( socketDescriptor,
                                                 m_Image->height(),
                                                 m_Image->width(),
                                                 colour, &m_Mask, this );

        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), this, SLOT(ViewMaskedImage()));

        thread->start();
    }
}


////////////////////////////////////////////////////////////////////////////////
