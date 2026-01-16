#pragma once

#include <string>
#include <QWidget>
#include <QString>

class VideoWidget : public QWidget
{
    Q_OBJECT

public:
    // CTOR
    explicit VideoWidget(int x, int y, int width, int height, const QString &name,
                          QWidget *parentPtr = nullptr) noexcept
        : QWidget{parentPtr}
    {
        // set the size and location of the widget
        setGeometry(QRect{x, y, width, height});

        // set the object name
        setObjectName(name);

        // set the color
        setStyleSheet("background-color : black");
    }

    VideoWidget(const VideoWidget &rhs) = delete;
    VideoWidget &operator=(const VideoWidget &rhs) = delete; 
    VideoWidget(VideoWidget &&rhs) = delete;                
    VideoWidget &operator=(VideoWidget &&rhs) = delete;      

    // changes the size of the widget
    void changeSize(int x, int y, int width, int height);
};