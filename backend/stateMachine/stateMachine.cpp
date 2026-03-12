#include "stateMachine.hpp"

StateMachine::StateMachine(MainWindow* window, QObject* parent) noexcept
  : QObject{parent}
  , m_currentState{std::make_unique<Idle>()}
  , m_windowPtr{window}{}

void StateMachine::eventReceived(Event event)
{
  auto newState {m_currentState->getNextState(event)};
  if (newState)
  {
    m_currentState = std::move(newState);
    m_currentState->onEvent(m_windowPtr);
  }
}