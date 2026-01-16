#include "stateMachine.hpp"

StateMachine::StateMachine(MainWindow* window, QWidget* parent)
  : QWidget{parent}
  , m_windowPtr{window}
  , m_state{std::make_unique<Idle>()}
{}

void StateMachine::changeState(Event event)
{
  // get the new state
  std::unique_ptr<AbsState> newState {getNewState(event)};

  // act on the event
  newState->onEvent(m_windowPtr);

  // store the state
  m_state = std::move(newState);
}

std::unique_ptr<AbsState> StateMachine::getNewState(Event event)
{
  switch(event)
  {
    case Event::PLAY:
      return std::make_unique<VideoPlaying>();
    case Event::STOP:
      return std::make_unique<VideoStopped>();
    default:
      return std::make_unique<Idle>();
  }
}