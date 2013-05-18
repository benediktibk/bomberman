#include "inputstate.h"

using namespace Common;

InputState::InputState() :
	m_upKeyPressed(false)
{ }

void InputState::setUpKeyPressed()
{
	m_upKeyPressed = true;
}

void InputState::setUpKeyNotPressed()
{
	m_upKeyPressed = false;
}

bool InputState::isUpKeyPressed() const
{
	return m_upKeyPressed;
}
