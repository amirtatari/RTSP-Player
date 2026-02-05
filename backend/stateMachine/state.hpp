#pragma once

#include "../backend/gstreamer/gstPlayer.hpp"

class MainWindow;     // forward declaration

class AbsState
{
public:
  virtual void onEvent(MainWindow* window, GstPlayer& player) = 0;
  virtual ~AbsState() = default;
};

class VideoPlaying : public AbsState
{
public:
  void onEvent(MainWindow* window, GstPlayer& player) override;
};

class VideoStopped : public AbsState
{
public:
  void onEvent(MainWindow* window, GstPlayer& player) override;
};

class Idle : public AbsState
{
public:
  void onEvent(MainWindow* window, GstPlayer& player) override;
};