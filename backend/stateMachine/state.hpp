#pragma once

#include "../backend/gstreamer/gstPlayer.hpp"

class MainWindow;     // forward declaration

class AbsState
{
protected:
  GstPlayer m_gstPlayer;
public:
  virtual void onEvent(MainWindow* window) = 0;
  virtual ~AbsState() = default;
};

class VideoPlaying : public AbsState
{
public:
  void onEvent(MainWindow* window);
};

class VideoStopped : public AbsState
{
public:
  void onEvent(MainWindow* window);
};

class Idle : public AbsState
{
public:
  void onEvent(MainWindow* window);
};