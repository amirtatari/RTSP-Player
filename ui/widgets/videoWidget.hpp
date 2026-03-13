#pragma once

#include <string>
#include <QWidget>
#include <QString>

class VideoWidget : public QWidget
{
    Q_OBJECT

public:
    // CTOR
    explicit VideoWidget(int width, int height, 
                        const QString &name, QWidget *parentPtr = nullptr);

    VideoWidget(const VideoWidget &rhs) = delete;
    VideoWidget &operator=(const VideoWidget &rhs) = delete; 
    VideoWidget(VideoWidget &&rhs) = delete;                
    VideoWidget &operator=(VideoWidget &&rhs) = delete;      
};