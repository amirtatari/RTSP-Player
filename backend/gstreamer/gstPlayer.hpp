#pragma once

#include <string>
#include <memory>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <QObject>
#include <QWidget>
#include <QString>

struct GstObjectDeleter 
{
  void operator()(gpointer ptr) const 
  {
    if (ptr)
      gst_object_unref(ptr);
  }
};

struct GErrorDeleter 
{
  void operator()(GError* ptr) const 
  {
    if (ptr)
      g_error_free(ptr);
  }
};

struct GstMessageDeleter 
{
  void operator()(GstMessage* ptr) const 
  {
    if (ptr)
      gst_message_unref(ptr);
  }
};

class GstPlayer : public QObject
{
  Q_OBJECT

  std::unique_ptr<GstElement, GstObjectDeleter> m_playerElem;
  std::unique_ptr<GstBus, GstObjectDeleter> m_bus;
  std::unique_ptr<GstMessage, GstMessageDeleter> m_message;
  std::unique_ptr<GError, GErrorDeleter> m_error;
  WId m_windowId{0};

  static gboolean busCallback(GstBus* bus, GstMessage* msg, gpointer data);
  static GstBusSyncReply syncBusCallback(GstBus* bus, GstMessage* msg, gpointer data);

public:
  explicit GstPlayer(QObject* parent = nullptr);
  ~GstPlayer();

  bool playStream(const std::string& pipeline, WId windowId);
  void stop();
  bool init();

signals:
  void errorOccurred(const QString& message);
  void stateChanged(const QString& state);
  void eosReached();
};