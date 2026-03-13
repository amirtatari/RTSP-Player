#include "gstPlayer.hpp"
#include "../../ui/mainwindow.hpp"

#include <gst/video/videooverlay.h>

GstPlayer::GstPlayer(const std::string& pipeline, 
            long long unsigned int windowId, 
            MainWindow* mwptr,
            QObject* parent) noexcept
  : QObject{parent}
  , m_pipeline{pipeline}
  , m_playerElem{nullptr}
  , m_sinkElem{nullptr}
  , m_bus{nullptr}
  , m_windowId{windowId}
  {
    connect(this, &GstPlayer::sendMessage, mwptr, &MainWindow::handleMessage);
  }

GstPlayer::~GstPlayer() 
{ 
  stop(); 
}

void GstPlayer::stop() 
{
  if (m_playerElem == nullptr)
    return;

  // stop the player element set its state to null
  gst_element_set_state(m_playerElem.get(), GST_STATE_NULL);

  // memory cleanup
  if (m_bus)
  {
    gst_bus_set_sync_handler(m_bus.get(), nullptr, nullptr, nullptr);
    gst_bus_remove_watch(m_bus.get());
  }
  
  m_playerElem.reset();
  m_sinkElem.reset();
  m_bus.reset();
  m_windowId = 0;
}

bool GstPlayer::playStream() 
{
  if (m_playerElem)
    stop();

  // check the input variables
  if (m_pipeline.empty()) 
    return false;

  // initialize the player element using the description
  GError* err{nullptr};
  m_playerElem.reset(gst_parse_launch(m_pipeline.c_str(), &err));

  if (!m_playerElem) 
    return false;

  // set window handle for overlay
  gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(m_sinkElem.get()), m_windowId);

  // set player element state to playing
  GstStateChangeReturn ret{gst_element_set_state(m_playerElem.get(), GST_STATE_PLAYING)};

  if (ret == GST_STATE_CHANGE_FAILURE) 
    return false;

  m_bus.reset(gst_element_get_bus(m_playerElem.get()));

  // add a watch for messages on the bus
  [[maybe_unused]]const unsigned int busId {gst_bus_add_watch(m_bus.get(), busCallback, this)};

  // Wait until error or EOS
  [[maybe_unused]] GstMessage* message {
    gst_bus_timed_pop_filtered(m_bus.get(), 0,
    (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_WARNING | GST_MESSAGE_EOS | GST_MESSAGE_PROGRESS))};

  return true;
}

gboolean GstPlayer::busCallback(GstBus* bus, GstMessage* msg, gpointer data)
{
  auto* self {static_cast<GstPlayer*>(data)};
  switch (GST_MESSAGE_TYPE(msg)) {
    case GST_MESSAGE_ERROR: 
    {
      GError* err {nullptr};
      gchar* debug {nullptr};
      gst_message_parse_error(msg, &err, &debug);
      const QString errorMsg {QString("GStreamer error from %1: %2")
                             .arg(GST_OBJECT_NAME(msg->src))
                             .arg(err->message)};
      emit self->sendMessage(errorMsg);
      g_error_free(err);
      g_free(debug);
      break;
    }
    case GST_MESSAGE_WARNING: 
    {
      GError* err {nullptr};
      gchar* debug {nullptr};
      gst_message_parse_warning(msg, &err, &debug);
      const QString warningMsg {QString("GStreamer warning from %1: %2")
                             .arg(GST_OBJECT_NAME(msg->src))
                             .arg(err->message)};
      emit self->sendMessage(warningMsg);
      g_error_free(err);
      g_free(debug);
      break;
    }
    case GST_MESSAGE_EOS:
      break;

    case GST_MESSAGE_STATE_CHANGED: 
    {
      if (GST_MESSAGE_SRC(msg) == GST_OBJECT(self->m_playerElem.get())) 
      {
        GstState oldState, newState, pendingState;
        gst_message_parse_state_changed(msg, &oldState, &newState, &pendingState);
        emit self->sendMessage(QString::fromStdString(gst_element_state_get_name(newState)));
      }
      break;
    }
    default:
      break;
  }
  
  return TRUE;
}
