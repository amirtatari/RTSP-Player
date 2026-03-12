#include "mainwindow.hpp"
#include "backend/stateMachine/stateMachine.hpp"

#include <QApplication>
#include <gst/gst.h>
#include <X11/Xlib.h>

int main(int argc, char *argv[])
{
    XInitThreads();
    gst_init(&argc, &argv);
    try
    {
        QApplication app(argc, argv);

        MainWindow mainWindow;
        
        // create state machine and connect the signal and slots
        StateMachine sm {&mainWindow, &app};
        QObject::connect(&mainWindow, &MainWindow::sendEvent, 
                        &sm, &StateMachine::eventReceived);

        mainWindow.show();
        return app.exec();
    } 
    catch(const std::exception& exp)
    {   
        return -1;
    }
    gst_deinit();
    return 0;
}
