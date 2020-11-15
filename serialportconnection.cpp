#include <QSerialPortInfo>

#include "serialportconnection.h"

SerialPortConnection::SerialPortConnection(Ui::Window * ui) {
    this->ui = ui;

    this->serialPort = new QSerialPort();

    updateSerialPortsUi();

    connect(ui->actionDisconnect, SIGNAL(triggered(bool)), this, SLOT(disconnect()));
}

SerialPortConnection::~SerialPortConnection() {
    delete serialPort;
    if (serialPortReader != nullptr) {
        delete serialPortReader;
    }
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
    // Remove old actions
    ui->menu_Connect_to->clear();
    serialPortActionList.clear();

    // Get current list
    QList<SerialPort> sp = getSerialPorts();

    // Create new actions
    for (QList<SerialPort>::iterator i = sp.begin();
         i != sp.end();
         ++i)
    {
        QAction *qa = new QAction(i->systemLocation + " (SN: " + i->serialNumber + ")");
        qa->setCheckable(true);
        qa->setData(i->systemLocation);
        serialPortActionList.append(qa);

        connect(serialPortActionList.last(), &QAction::triggered, this, &SerialPortConnection::connectTo);

        ui->menu_Connect_to->addAction(serialPortActionList.last());
    }
}

void SerialPortConnection::connectTo()
{
    QString serialPortName;

    for (QList<QAction*>::iterator i = serialPortActionList.begin();
         i != serialPortActionList.end();
         ++i)
    {
        if ((*i)->isChecked()) {
            serialPortName = (*i)->data().toString();
        }
        (*i)->setEnabled(false);
    }

    serialPort->setPortName(serialPortName);
    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (!serialPort->open(QIODevice::ReadWrite)) {
        ui->actionDisconnect->setEnabled(false);
        updateSerialPortsUi();
        emit statusChanged(QString("Failed to open port %1, error: %2")
                           .arg(serialPortName)
                           .arg(serialPort->errorString()));
    } else {
        serialPortReader = new SerialPortReader(serialPort);

        ui->actionDisconnect->setEnabled(true);
        emit statusChanged("Connected to " + serialPortName);
    }
}

void SerialPortConnection::disconnect()
{
    if (serialPort->isOpen()) {
        serialPort->close();
        delete serialPortReader;
        ui->actionDisconnect->setEnabled(false);
        updateSerialPortsUi();
        emit statusChanged("Disconnected");
    }
}
