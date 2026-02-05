#pragma once

#include "state.hpp"

#include <memory>

/**
 * @brief defines different types of events
 */
enum class Event{PLAY, STOP, IDLE};

class MainWindow;

/**
 * @brief manages states and events
 */
class StateMachine : public QObject
{
  Q_OBJECT

  std::unique_ptr<AbsState> m_state;
  MainWindow* m_windowPtr;
  GstPlayer m_gstPlayer;

  /**
   * @brief gets the New State
   * @param event incoming event
   * @return std::unique_ptr<AbsState> 
   */

  std::unique_ptr<AbsState> getNewState(Event event);

public:
  explicit StateMachine(MainWindow* window, QObject* parent = nullptr) noexcept;
  GstPlayer& getPlayer() { return m_gstPlayer; }

public slots:
  /**
   * @brief changes the current state using incoming event and act on the event
   * @param event incoming event
   */
  void changeState(Event event);
};