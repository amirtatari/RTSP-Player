#pragma once

#include <string>
#include <memory>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <QObject>

class MainWindow;

struct GstObjectDeleter 
{
  void operator()(gpointer ptr) const 
  {
    if (ptr)
      gst_object_unref(ptr);
  }
};

class GstPlayer : public QObject
{
  Q_OBJECT
  const std::string m_pipeline; 
  std::unique_ptr<GstElement, GstObjectDeleter> m_playerElem;
  std::unique_ptr<GstElement, GstObjectDeleter> m_sinkElem;
  std::unique_ptr<GstBus, GstObjectDeleter> m_bus;

  long long unsigned int m_windowId;

  static gboolean busCallback(GstBus* bus, GstMessage* msg, gpointer data);

public:
  explicit GstPlayer(const std::string& pipeline, long long unsigned int windowId, 
                    MainWindow* mwptr,  
                    QObject* parent = nullptr) noexcept;
  ~GstPlayer();

  bool playStream();
  void stop();

signals:
  void sendMessage(const QString& message);
};