#include "gstPlayer.hpp"

#include <gst/video/videooverlay.h>

GstPlayer::GstPlayer(QObject* parent) 
  : QObject{parent} 
  {}

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
  m_bus.reset();
  m_error.reset();
  m_message.reset();
  m_windowId = 0;
}

bool GstPlayer::playStream(const std::string& pipeline, WId windowId) 
{
  if (m_playerElem)
    stop();

  m_windowId = windowId;

  // check the input variables
  if (pipeline.empty()) 
  {
    emit errorOccurred("Empty pipeline description");
    return false;
  }

  // initialize the player element using the description
  GError* err{nullptr};
  m_playerElem.reset(gst_parse_launch(pipeline.c_str(), &err));
  if (err) 
  {
    const QString errorMsg {QString("Failed to parse pipeline: %1").arg(err->message)};
    emit errorOccurred(errorMsg);
    g_error_free(err);
    return false;
  }

  if (!m_playerElem) 
  {
    emit errorOccurred("Failed to create pipeline (unknown error)");
    return false;
  }

  // setup bus watch and sync handler
  m_bus.reset(gst_element_get_bus(m_playerElem.get()));
  gst_bus_set_sync_handler(m_bus.get(), syncBusCallback, this, nullptr);
  gst_bus_add_watch(m_bus.get(), busCallback, this);

  // set player element state to playing
  GstStateChangeReturn ret{gst_element_set_state(m_playerElem.get(), GST_STATE_PLAYING)};

  if (ret == GST_STATE_CHANGE_FAILURE) 
  {
    emit errorOccurred("Failed to set pipeline to PLAYING state");
    return false;
  }
  return true;
}

bool GstPlayer::init()
{
  return gst_init_check(nullptr, nullptr, nullptr);
}

GstBusSyncReply GstPlayer::syncBusCallback(GstBus* bus, GstMessage* msg, gpointer data)
{
  if (gst_is_video_overlay_prepare_window_handle_message(msg))
  {
    auto* self {static_cast<GstPlayer*>(data)};
    if (self->m_windowId != 0) 
      gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(GST_MESSAGE_SRC(msg)), 
                                                            self->m_windowId);
  }

  return GST_BUS_PASS;
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
      emit self->errorOccurred(errorMsg);
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
      emit self->errorOccurred(warningMsg);
      g_error_free(err);
      g_free(debug);
      break;
    }
    case GST_MESSAGE_EOS:
      emit self->eosReached();
      break;
    case GST_MESSAGE_STATE_CHANGED: 
    {
      if (GST_MESSAGE_SRC(msg) == GST_OBJECT(self->m_playerElem.get())) 
      {
        GstState oldState, newState, pendingState;
        gst_message_parse_state_changed(msg, &oldState, &newState, &pendingState);
        emit self->stateChanged(QString::fromStdString(gst_element_state_get_name(newState)));
      }
      break;
    }
    default:
      break;
  }
  
  return TRUE;
}
