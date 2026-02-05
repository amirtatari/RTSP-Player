#include "mainwindow.hpp"

#include <QApplication>
#include <gst/gst.h>
#include <X11/Xlib.h>

int main(int argc, char *argv[])
{
    XInitThreads();
    gst_init(&argc, &argv);
    try
    {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    } 
    catch(const std::exception& exp)
    {   
        return -1;
    }
    gst_deinit();
    return 0;
}
