#include "videoWidget.hpp"
#include <stdexcept>

void PlayerWidget::stop()
{
    using std::cout;

    // return if the player element is nullptr
    if(m_playerElem == nullptr)
    {
        return;
    }

    // stop the player element set its state to null
    GstStateChangeReturn ret = gst_element_set_state(m_playerElem, GST_STATE_PAUSED);
    ret = gst_element_set_state(m_playerElem, GST_STATE_NULL);

    // rmemory cleanup
    if(m_playerElem != nullptr)
    {
        g_object_unref(m_playerElem);
        m_playerElem = nullptr;
    }

    if(m_bus != nullptr)
    {
        g_object_unref(m_bus);
        m_bus = nullptr;
    }

    if(m_error != nullptr)
    {
        g_object_unref(m_error);
        m_error = nullptr;
    }

    if(m_message != nullptr)
    {
        g_object_unref(m_message);
        m_message = nullptr;
    }
}

void PlayerWidget::play(const QString& description){
    using std::invalid_argument;

    if(m_playerElem != nullptr)
    {
        std::cout << "PlayerWidget::play: player is already playing!\n";
        return;
    }

    // check the input variables
    if(description.isEmpty())
    {
        throw invalid_argument("PlayerWidget::play: description is empty!");    
    }

    // intialize the player element using the description
    m_playerElem = gst_parse_launch(description.toStdString().c_str(), &m_error);
    if(m_playerElem == nullptr)
    {
        throw invalid_argument("PlayerWidget::play: could not parse the description!" + std::string{m_error->message});
    }

    // get the sink element & set video overlay
    GstElement* video_sink = gst_bin_get_by_interface(GST_BIN(m_playerElem), GST_TYPE_VIDEO_OVERLAY);
    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(video_sink), winId());

    std::cout << "PlayerWidget::play: playing stream ...!\n";

    // set player element state to playing
    GstStateChangeReturn ret = gst_element_set_state(m_playerElem, GST_STATE_PLAYING);
    
    if(ret == GST_STATE_CHANGE_FAILURE)
    {
        std::cerr << "PlayerWidget::play: ERROR: cannot play the stream!\n";

        // stop the player and free the memory
        stop();
    }
}

void PlayerWidget::changeSize(int x, int y, int width, int height)
{
    setGeometry(QRect{x, y, width, height});
}