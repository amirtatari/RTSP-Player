#include "gstPlayer.hpp"

void GstPlayer::stop() {
  // return if the player element is nullptr
  if (m_playerElem == nullptr)
    return;

  // stop the player element set its state to null
  gst_element_set_state(m_playerElem.get(), GST_STATE_PAUSED);
  gst_element_set_state(m_playerElem.get(), GST_STATE_NULL);

  // memory cleanup
  m_playerElem.reset();
  m_bus.reset();
  m_error.reset();
  m_message.reset();
}

bool GstPlayer::playStream(const std::string& pipeline, unsigned int windowId) {
  if (m_playerElem) {
    return false;
  }

  // check the input variables
  if (pipeline.empty()) {
    return false;
  }

  // initialize the player element using the description
  GError* err{nullptr};
  m_playerElem.reset(gst_parse_launch(pipeline.c_str(), &err));
  m_error.reset(err);

  if (!m_playerElem) {
    return false;
  }

  // get the sink element & set video overlay
  std::unique_ptr<GstElement, GstObjectDeleter> videoSink{
      gst_bin_get_by_interface(GST_BIN(m_playerElem.get()), GST_TYPE_VIDEO_OVERLAY)};

  if (videoSink) {
    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(videoSink.get()), windowId);
  }

  // set player element state to playing
  GstStateChangeReturn ret{gst_element_set_state(m_playerElem.get(), GST_STATE_PLAYING)};

  if (ret == GST_STATE_CHANGE_FAILURE) {
    stop();
    return false;
  }

  return true;
}

bool GstPlayer::init()
{
  return gst_init_check(nullptr, nullptr, nullptr);
}
