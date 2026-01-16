#include "state.hpp"
#include "mainwindow.hpp"

inline std::string createPipeline(const std::string &url)
{
  const std::string rtspsrc {"rtspsrc location=" + url};
  const std::string latency {" latency=100 !"};
  const std::string mimeType {" application/x-rtp, media=video, clock-rate=90000, payload=96 !"};
  const std::string rtpJitter {" rtpjitterbuffer name=jitterbuffer !"};
  const std::string depay {" rtph264depay ! h264parse !"};
  const std::string decode {" avdec_h264 !"};
  const std::string videoScale {" videoconvert ! videoscale ! video/x-raw,width=800,height=600 !"};
  const std::string sink {" ximagesink name=video_sink sync=false"};
  return rtspsrc + latency + mimeType + rtpJitter + depay + decode + videoScale + sink;
}

void VideoPlaying::onEvent(MainWindow* window)
{
  const QString text{window->getUrl()};
  const std::string pipeline {createPipeline(text.toStdString())};

  m_gstPlayer.playStream(pipeline, window->getVideoWidget().winId());
}

void VideoStopped::onEvent(MainWindow* window)
{
  // TODO
}

void Idle::onEvent(MainWindow* window)
{
  // TODO
}