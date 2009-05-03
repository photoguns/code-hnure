#include "serverthread.h"
#include <cassert>

////////////////////////////////////////////////////////////////////////////////


ServerThread::ServerThread( int _socketDescriptor,
                            int _imageHeight,
                            int _imageWidth,
                            QVector<int>* _colour,
                            QVector<int>* _mask,
                            QObject* _parent )
: QThread(_parent),
m_SocketDescriptor(_socketDescriptor),
m_ImageHeight(_imageHeight),
m_ImageWidth(_imageWidth),
m_Colour(_colour),
m_Mask(_mask)
{
}


////////////////////////////////////////////////////////////////////////////////


void ServerThread::run()
{
    // Setup TCP socket
    QTcpSocket socket;
    socket.setSocketDescriptor(m_SocketDescriptor);

    // Send image to client
    WriteColour(&socket);

    // Wait for client responce
    socket.waitForReadyRead();

    // Receive modified image from client
    ReadColour(&socket);
}


////////////////////////////////////////////////////////////////////////////////


void ServerThread::WriteColour(QTcpSocket* _socket)
{
    QDataStream out(_socket);

    // Send mask to client
    out << *m_Mask;

    // Send image to client
    out << m_ImageHeight;
    out << m_ImageWidth;

    out << *m_Colour;
}


////////////////////////////////////////////////////////////////////////////////


void ServerThread::ReadColour(QTcpSocket* _socket)
{
    QDataStream in(_socket);

    int colourSize;
    in >> colourSize;

    // Receive image from client
    for (int i = 0; i < colourSize; ++i)
    {
        if ( !_socket->bytesAvailable() )
            _socket->waitForReadyRead();
        in >> (*m_Colour)[i];
    }
    assert(m_Colour->size() == m_ImageHeight * m_ImageWidth);

    // Disconnect
    _socket->disconnectFromHost();
}


////////////////////////////////////////////////////////////////////////////////
