#include <QSerialPortInfo>

#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);

    connect(ui->openGLCanvas, SIGNAL(xRotationChanged(int)), ui->xSlider, SLOT(setValue(int)));
    connect(ui->openGLCanvas, SIGNAL(yRotationChanged(int)), ui->ySlider, SLOT(setValue(int)));
    connect(ui->openGLCanvas, SIGNAL(zRotationChanged(int)), ui->zSlider, SLOT(setValue(int)));

    menuPopulateSerialPorts();
    ui->statusbar->showMessage(tr("Ready, please connect"));
}

Window::~Window()
{
    delete ui;
}

void Window::closeEvent(QCloseEvent *event)
{
    qDebug("exit");
}

void Window::menuPopulateSerialPorts()
{
    //Port: ttyUSB0
    //Location: /dev/ttyUSB0
    //Description: FT230X Basic UART
    //Manufacturer: FTDI
    //Serial number: D307O726
    //Vendor Identifier: 403
    //Product Identifier: 6015
    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    const QString blankString = "N/A";
    QString serialNumber;
    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        serialNumber = serialPortInfo.serialNumber();
        ui->menu_Connect_to->addAction(serialPortInfo.systemLocation() + " (" + (!serialNumber.isEmpty() ? serialNumber : blankString) + ")");
    }
}
