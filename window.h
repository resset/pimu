#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::Window *ui;
    void menuPopulateSerialPorts();
};
#endif // WINDOW_H
