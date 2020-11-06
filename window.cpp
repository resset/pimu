#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);

    connect(ui->actionExit, &QAction::triggered, this, &Window::closeWindow);

    connect(ui->openGLCanvas, SIGNAL(xRotationChanged(int)), ui->xSlider, SLOT(setValue(int)));
    connect(ui->openGLCanvas, SIGNAL(yRotationChanged(int)), ui->ySlider, SLOT(setValue(int)));
    connect(ui->openGLCanvas, SIGNAL(zRotationChanged(int)), ui->zSlider, SLOT(setValue(int)));

    this->sp = new SerialPortConnection(ui);
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
