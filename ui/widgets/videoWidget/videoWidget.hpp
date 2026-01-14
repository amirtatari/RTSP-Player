#pragma once

#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <string>
#include <QWidget>
#include <iostream>

class PlayerWidget : public QWidget 
{
    Q_OBJECT

    GstElement* m_playerElem;
    GstBus* m_bus;
    GstMessage* m_message;
    GError* m_error;

public:
    // CTOR
    explicit PlayerWidget(int x, int y, int widthm, int height, const QString& name, QWidget* parentPtr = nullptr) noexcept :
        QWidget{parentPtr},
        m_playerElem{nullptr}, 
        m_bus{nullptr},
        m_error{nullptr},
        m_message{nullptr}
    {
        // set the size and location of the widget
        setGeometry(QRect{x, y, widthm, height});

        // set the object name
        setObjectName(name);

        // set the color
        setStyleSheet("background-color : black");
    }

    PlayerWidget(const PlayerWidget& rhs) = delete;  // copy ctor deleted
    PlayerWidget& operator=(const PlayerWidget& rhs) = delete;  // copy assignment operator deleted
    PlayerWidget(PlayerWidget&& rhs) = delete;  // move ctor deleted
    PlayerWidget& operator=(PlayerWidget&& rhs) = delete;   // move assignment operator deleted

    // DTOR
    ~PlayerWidget() 
    { 
        stop(); 
    }

    // Create elements and play PlayerWidget
    void play(const QString& description);

    // Stops the player and Cleans up the memory
    void stop();

    // changes the size of the widget
    void changeSize(int x, int y, int width, int height);
};