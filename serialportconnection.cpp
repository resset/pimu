#include <QSerialPortInfo>

#include "serialportconnection.h"

SerialPortConnection::SerialPortConnection(Ui::Window * ui) {
    this->ui = ui;
    this->connected = false;

    updateSerialPortsUi();

    connect(ui->actionDisconnect, &QAction::triggered, this, &SerialPortConnection::disconnect);

    ui->statusbar->showMessage("Ready to connect");
}

QList<SerialPort> SerialPortConnection::getSerialPorts()
{
    QList<SerialPort> serialPortList;

    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    const QString blankString = "N/A";
    QString description;
    QString manufacturer;
    QString serialNumber;

    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        description = serialPortInfo.description();
        manufacturer = serialPortInfo.manufacturer();
        serialNumber = serialPortInfo.serialNumber();

        SerialPort *sp = new SerialPort();
        sp->portName = serialPortInfo.portName();
        sp->systemLocation = serialPortInfo.systemLocation();
        sp->description = (!description.isEmpty() ? description : blankString);
        sp->manufacturer = (!manufacturer.isEmpty() ? manufacturer : blankString);
        sp->serialNumber = (!serialNumber.isEmpty() ? serialNumber : blankString);
        sp->vendorIdentifier = (serialPortInfo.hasVendorIdentifier()
                                ? QByteArray::number(serialPortInfo.vendorIdentifier(), 16)
                                : blankString);
        sp->productIdentifier = (serialPortInfo.hasProductIdentifier()
                                 ? QByteArray::number(serialPortInfo.productIdentifier(), 16)
                                 : blankString);
        serialPortList.append(*sp);
    }

    return serialPortList;
}

void SerialPortConnection::updateSerialPortsUi()
{
    //Port: ttyUSB0
    //Location: /dev/ttyUSB0
    //Description: FT230X Basic UART
    //Manufacturer: FTDI
    //Serial number: D307O726
    //Vendor Identifier: 403
    //Product Identifier: 6015

    // Remove old actions
    ui->menu_Connect_to->clear();
    serialPortActionList.clear();

    // Get current list
    QList<SerialPort> sp = getSerialPorts();

    // Create new actions
    QList<SerialPort>::iterator i;
    for (i = sp.begin(); i != sp.end(); ++i) {
        QAction *qa = new QAction(i->systemLocation + " (SN: " + i->serialNumber + ")");
        qa->setCheckable(true);
        serialPortActionList.append(qa);

        connect(serialPortActionList.last(), &QAction::triggered, this, &SerialPortConnection::connectTo);
        ui->menu_Connect_to->addAction(serialPortActionList.last());
    }
}

void SerialPortConnection::connectTo()
{
    QList<QAction*>::iterator i;
    for (i = serialPortActionList.begin(); i != serialPortActionList.end(); ++i) {
        (*i)->setEnabled(false);
    }

    ui->actionDisconnect->setEnabled(true);
    ui->statusbar->showMessage("Connected to <TODO>");
}

void SerialPortConnection::disconnect()
{
    ui->actionDisconnect->setEnabled(false);
    updateSerialPortsUi();
    ui->statusbar->showMessage("Disconnected");
}
