#include "state.hpp"
#include "mainwindow.hpp"

AbsState::AbsState() noexcept
  : m_playerPtr{nullptr} {}

inline std::string createPipeline(const std::string &url)
{
  const std::string rtspsrc {"rtspsrc location=" + url};
  const std::string latency {" latency=100 !"};
  const std::string mimeType {
    " application/x-rtp, media=video, clock-rate=90000, payload=96 !"};
  const std::string rtpJitter {" rtpjitterbuffer name=jitterbuffer !"};
  const std::string depay {" rtph264depay ! h264parse !"};
  const std::string decode {" avdec_h264 !"};
  const std::string videoScale {
    " videoconvert ! videoscale ! video/x-raw,width=800,height=600 !"};
  const std::string sink {" ximagesink name=video_sink sync=false"};
  return rtspsrc + latency + mimeType + rtpJitter + depay + 
          decode + videoScale + sink;
}

std::unique_ptr<AbsState> VideoPlaying::getNextState(Event event)
{
  // TODO 
  return nullptr;
}

std::unique_ptr<AbsState> VideoStopped::getNextState(Event event)
{
  // TODO 
  return nullptr;
}

std::unique_ptr<AbsState> Idle::getNextState(Event event)
{
  switch(event)
  {
    case Event::PLAYING:
      return std::make_unique<VideoPlaying>();
    case Event::STOP:
      return std::make_unique<VideoStopped>();
    default:
      return std::make_unique<Idle>();
  }
  // TODO 
  return nullptr;
}

void VideoPlaying::onEvent(MainWindow* window)
{
  const QString text{window->getUrl()};
  const std::string pipeline {createPipeline(text.toStdString())};
  m_playerPtr.reset();
  m_playerPtr = std::make_unique<GstPlayer>(pipeline, window->getVideoWidget().winId());
  bool res {m_playerPtr->playStream()};
}

void VideoStopped::onEvent(MainWindow* window)
{
  m_playerPtr->stop();
}

void Idle::onEvent(MainWindow* window)
{
  //player.stop();
}