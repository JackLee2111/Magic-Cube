#include <QGuiApplication>
#include "window.h"
#include "setwindow.h"
#include "show2d.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    //QGuiApplication app(argc, argv);
    app.setApplicationName("dg");

    // Set OpenGL Version information
    // Note: This format must be set before show() is called.

    SetWindow w;
    w.show();
    // Set the window up
    return app.exec();
}
