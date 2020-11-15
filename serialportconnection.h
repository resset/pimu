#ifndef SERIALPORTCONNECTION_H
#define SERIALPORTCONNECTION_H

#include <QSerialPort>

#include "ui_window.h"
#include "serialport.h"
#include "serialportreader.h"

class SerialPortConnection : public QObject
{
    Q_OBJECT

public:
    SerialPortConnection(Ui::Window *ui);
    ~SerialPortConnection();

public slots:
    void connectTo();
    void disconnect();

signals:
    void statusChanged(QString status);

private:
    QList<SerialPort> getSerialPorts();
    void updateSerialPortsUi();

    Ui::Window *ui;
    QList<QAction*> serialPortActionList;
    QSerialPort *serialPort;
    SerialPortReader *serialPortReader = nullptr;
};

#endif // SERIALPORTCONNECTION_H
