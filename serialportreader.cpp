#include "serialportreader.h"

#include <QCoreApplication>
#include <QDebug>

SerialPortReader::SerialPortReader(QSerialPort *serialPort, QObject *parent) :
    QObject(parent),
    m_serialPort(serialPort),
    m_standardOutput(stdout)
{
    m_serialPort->readAll();

    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortReader::handleReadyRead);
    connect(m_serialPort, &QSerialPort::errorOccurred, this, &SerialPortReader::handleError);
}

SerialPortReader::~SerialPortReader() {
}

void SerialPortReader::handleReadyRead()
{
    if (m_serialPort->canReadLine()) {
        QByteArray line = m_serialPort->readLine(1000);
        m_readData.append(line);
        //m_standardOutput << line;
        qDebug(line.data());
    }
}

void SerialPortReader::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        m_standardOutput << QString("An I/O error occurred while reading "
                                    "the data from port %1, error: %2")
                            .arg(m_serialPort->portName())
                            .arg(m_serialPort->errorString())
                         << "\n";
    }
}
