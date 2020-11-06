#ifndef SERIALPORTCONNECTION_H
#define SERIALPORTCONNECTION_H

#include "ui_window.h"
#include "serialport.h"

class SerialPortConnection : public QObject
{
    Q_OBJECT

public:
    SerialPortConnection(Ui::Window *ui);

public slots:
    void connectTo();
    void disconnect();

private:
    QList<SerialPort> getSerialPorts();
    void updateSerialPortsUi();

    Ui::Window *ui;
    QList<QAction*> serialPortActionList;
    bool connected;
};

#endif // SERIALPORTCONNECTION_H
