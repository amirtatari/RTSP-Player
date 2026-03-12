#pragma once

#include "state.hpp"

#include <memory>

class MainWindow;

/**
 * @brief manages states and events
 */
class StateMachine : public QObject
{
  Q_OBJECT

  std::unique_ptr<AbsState> m_currentState;
  MainWindow* m_windowPtr;

public:
  explicit StateMachine(MainWindow* window, QObject* parent = nullptr) noexcept;

public slots:
  /**
   * @brief changes the current state using incoming event and act on the event
   * @param event incoming event
   */
  void eventReceived(Event event);
};