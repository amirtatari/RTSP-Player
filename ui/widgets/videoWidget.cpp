#include "videoWidget.hpp"

VideoWidget::VideoWidget(int x, int y, int width, int height, 
                            const QString &name, QWidget *parentPtr)
    : QWidget{parentPtr}
    {
        // allow the widget to be styled via stylesheets
        setAttribute(Qt::WA_StyledBackground);

        // set the size and location hints for the layout
        setMinimumSize(width, height);
        
        // set the object name and change the background color to black
        setObjectName(name);
        setStyleSheet(QString("#%1 { background-color: black; }").arg(name));
    }