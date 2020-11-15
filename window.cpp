#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);

    statusLabel = new QLabel();
    ui->statusbar->addWidget(statusLabel);
    statusLabel->setText("Ready to connect");

    ui->menu_Connect_to->setIcon(QIcon::fromTheme("network-connect"));

    sp = new SerialPortConnection(ui);

    connect(ui->actionExit, &QAction::triggered, this, &Window::closeWindow);

    connect(ui->openGLCanvas, SIGNAL(xRotationChanged(int)), ui->xSlider, SLOT(setValue(int)));
    connect(ui->openGLCanvas, SIGNAL(yRotationChanged(int)), ui->ySlider, SLOT(setValue(int)));
    connect(ui->openGLCanvas, SIGNAL(zRotationChanged(int)), ui->zSlider, SLOT(setValue(int)));

    connect(sp->serialParser, SIGNAL(xRotDataArrived(int)), ui->openGLCanvas, SLOT(setXRotation(int)));
    connect(sp->serialParser, SIGNAL(yRotDataArrived(int)), ui->openGLCanvas, SLOT(setYRotation(int)));
    connect(sp->serialParser, SIGNAL(zRotDataArrived(int)), ui->openGLCanvas, SLOT(setZRotation(int)));

    connect(sp, SIGNAL(statusChanged(QString)), this, SLOT(setStatus(QString)));
}

Window::~Window()
{
    delete ui;
}

void Window::closeEvent(QCloseEvent *event)
{
    (void)event;
    qDebug("close event");
    closeWindow();
}

void Window::closeWindow()
{
    qDebug("app closed");
    ui->openGLCanvas->cleanup();
    QApplication::quit();
}

void Window::setStatus(QString status)
{
    statusLabel->setText(status);
}
