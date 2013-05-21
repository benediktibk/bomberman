#include "inputstate.h"

using namespace Common;

InputState::InputState() :
	m_upKeyPressed(false),
	m_downKeyPressed(false)
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

void InputState::setDownKeyPressed()
{
	m_downKeyPressed = true;
}

void InputState::setDownKeyNotPressed()
{
	m_downKeyPressed = false;
}

bool InputState::isDownKeyPressed() const
{
	return m_downKeyPressed;
}
