#ifndef SERIALPORTREADER_H
#define SERIALPORTREADER_H

#include <QSerialPort>
#include <QByteArray>

class SerialPortReader : public QObject
{
    Q_OBJECT

public:
    explicit SerialPortReader(QSerialPort *serialPort, QObject *parent = nullptr);
    ~SerialPortReader();

private slots:
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);

signals:
    void packetReceived(QByteArray packet);

private:
    QSerialPort *m_serialPort = nullptr;
    QByteArray m_readData;
};

#endif // SERIALPORTREADER_H
