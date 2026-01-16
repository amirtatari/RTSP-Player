#pragma once

#include "state.hpp"

#include <QWidget>
#include <memory>

/**
 * @brief defines different types of events
 */
enum class Event{PLAY, STOP, IDLE};

/**
 * @brief manages states and events
 */
class StateMachine : public QWidget
{
  Q_OBJECT

  std::unique_ptr<AbsState> m_state;
  MainWindow* m_windowPtr;

  /**
   * @brief gets the New State
   * @param event incoming event
   * @return std::unique_ptr<AbsState> 
   */
  std::unique_ptr<AbsState> getNewState(Event event);
public:
  explicit StateMachine(MainWindow* window, QWidget* parent = nullptr);

public slots:
  /**
   * @brief changes the current state using incoming event and act on the event
   * @param event incoming event
   */
  void changeState(Event event);
};