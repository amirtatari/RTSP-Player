#pragma once

#include "../backend/gstreamer/gstPlayer.hpp"
#include "event.hpp"

class MainWindow;     // forward declaration

class AbsState
{
protected:
  std::unique_ptr<GstPlayer> m_playerPtr;
public:
  explicit AbsState() noexcept;
   virtual ~AbsState() = default;
  
  // get the next state
  virtual std::unique_ptr<AbsState> getNextState(Event event) = 0;
  
  // on event action 
  virtual void onEvent(MainWindow* window) = 0;
};

class VideoPlaying : public AbsState
{
public:
  std::unique_ptr<AbsState> getNextState(Event event);
  void onEvent(MainWindow* window);
};

class VideoStopped : public AbsState
{
public:
  std::unique_ptr<AbsState> getNextState(Event event);
  void onEvent(MainWindow* window);
};

class Idle : public AbsState
{
public:
  std::unique_ptr<AbsState> getNextState(Event event);
  void onEvent(MainWindow* window);
};