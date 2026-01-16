#pragma once

#include <string>
#include <memory>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>

struct GstObjectDeleter {
  void operator()(gpointer ptr) const {
    if (ptr)
      gst_object_unref(ptr);
  }
};

struct GErrorDeleter {
  void operator()(GError* ptr) const {
    if (ptr)
      g_error_free(ptr);
  }
};

struct GstMessageDeleter {
  void operator()(GstMessage* ptr) const {
    if (ptr)
      gst_message_unref(ptr);
  }
};

class GstPlayer
{
  std::unique_ptr<GstElement, GstObjectDeleter> m_playerElem;
  std::unique_ptr<GstBus, GstObjectDeleter> m_bus;
  std::unique_ptr<GstMessage, GstMessageDeleter> m_message;
  std::unique_ptr<GError, GErrorDeleter> m_error;

public:
  bool playStream(const std::string& pipeline, unsigned int windowId);
  void stop();
  bool init();
};