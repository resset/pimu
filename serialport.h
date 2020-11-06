#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QString>

class SerialPort
{
public:
    SerialPort();

    QString portName;
    QString systemLocation;
    QString description;
    QString manufacturer;
    QString serialNumber;
    QString vendorIdentifier;
    QString productIdentifier;
    bool beingUsed;
};

#endif // SERIALPORT_H
