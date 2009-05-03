#include <QtNetwork>
#include <QtDebug>
#include <cassert>
#include "client.h"


////////////////////////////////////////////////////////////////////////////////


Client::Client(QObject* _parent)
    :QObject(_parent)
{
    // Create new tcp socket
    m_TcpSocket = new QTcpSocket(this);

    // Connect to server
    m_TcpSocket->connectToHost(QHostAddress::LocalHost, 27027);

    // Process image when data received
    connect( m_TcpSocket, SIGNAL(readyRead()), this, SLOT(ProcessImage()));
}


////////////////////////////////////////////////////////////////////////////////


Client::~Client()
{
    // Cleanup memory
    if (m_TcpSocket)
        delete m_TcpSocket;
}

////////////////////////////////////////////////////////////////////////////////


void Client::ProcessImage()
{
    // Receive image from server
    ReadImage();

    // Put mask on image
    MaskImage();

    // Send image back to server
    WriteImage();

    // Exit program
    delete m_TcpSocket;
    m_TcpSocket = NULL;
    exit(0);
}


////////////////////////////////////////////////////////////////////////////////


void Client::ReadImage()
{
    // Input stream
    QDataStream in(m_TcpSocket);

    // Read mask
    in >> m_Mask;

    // Read image dimensions
    in >> m_ImageHeight;
    in >> m_ImageWidth;

    int imageSize;
    in >> imageSize;

    m_Image.resize(imageSize);
    for (int i = 0; i < imageSize; ++i)
    {
        // Wait for bytes if they are not avaliable
        if (!m_TcpSocket->bytesAvailable())
            m_TcpSocket->waitForReadyRead();
        in >> m_Image[i];
    }
}


////////////////////////////////////////////////////////////////////////////////


void Client::MaskImage()
{
    // Copy image
    QVector<int> newImage(m_Image);

    // Mask copy of image
    for (int x = 1; x < m_ImageWidth - 1; ++x)
        for (int y = 1; y < m_ImageHeight - 1; ++y)
        {
            int newColour =

                    m_Image[(x - 1) * m_ImageHeight + y - 1] * m_Mask[0] +
                    m_Image[(x    ) * m_ImageHeight + y - 1] * m_Mask[1] +
                    m_Image[(x + 1) * m_ImageHeight + y - 1] * m_Mask[2] +

                    m_Image[(x - 1) * m_ImageHeight + y] * m_Mask[3] +
                    m_Image[(x    ) * m_ImageHeight + y] * m_Mask[4] +
                    m_Image[(x + 1) * m_ImageHeight + y] * m_Mask[5] +

                    m_Image[(x - 1) * m_ImageHeight + y + 1] * m_Mask[6] +
                    m_Image[(x    ) * m_ImageHeight + y + 1] * m_Mask[7] +
                    m_Image[(x + 1) * m_ImageHeight + y + 1] * m_Mask[8];

            if (newColour < 0)
                newColour = 0;
            else if (newColour > 255)
                newColour = 255;

            newImage[x * m_ImageHeight + y] = newColour;
        }

    // Refresh image
    m_Image = newImage;
}


////////////////////////////////////////////////////////////////////////////////


void Client::WriteImage()
{
    // Setup output stream
    QDataStream out(m_TcpSocket);

    // Send modified image
    out << m_Image;

    m_TcpSocket->waitForBytesWritten();
    m_TcpSocket->waitForDisconnected();
}


////////////////////////////////////////////////////////////////////////////////
