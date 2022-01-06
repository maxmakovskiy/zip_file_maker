#include <QApplication>
#include "zipper_window.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    ZipperWindow* wind = new ZipperWindow;
    wind->show();

    return app.exec();
}

