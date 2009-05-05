#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

////////////////////////////////////////////////////////////////////////////////

#include <QVector>
#include <QThread>
#include <QTcpSocket>

////////////////////////////////////////////////////////////////////////////////

class ServerThread : public QThread
{
////////////////////////////////////////////////////////////////////////////////

    Q_OBJECT

////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    ServerThread( int _socketDescriptor,
                  int _imageHeight,
                  int _imageWidth,
                  QVector<int>* _image,
                  QVector<int>* _mask,
                  QObject* _parent = NULL );


////////////////////////////////////////////////////////////////////////////////
/** QTread interface implementation */
////////////////////////////////////////////////////////////////////////////////


    /** Here the thread starts */
    void run();


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** Send one colour of image to client */
    void WriteColour(QTcpSocket* _socket);


    /** Read modified colour from client */
    void ReadColour(QTcpSocket* _socket);


////////////////////////////////////////////////////////////////////////////////


    /** TCP socket descriptor */
    int m_SocketDescriptor;


    /** Image height */
    int m_ImageHeight;


    /** Image width */
    int m_ImageWidth;


    /** Image in one colour */
    QVector<int>* m_Colour;


    /** Mask (3x3) */
    QVector<int>* m_Mask;


////////////////////////////////////////////////////////////////////////////////
};


#endif // SERVERTHREAD_H
