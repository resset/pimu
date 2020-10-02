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
}

Window::~Window()
{
    delete ui;
}

