#include "videoWidget.hpp"
#include <stdexcept>

void VideoWidget::changeSize(int x, int y, int width, int height)
{
    setGeometry(QRect{x, y, width, height});
}