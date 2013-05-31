#include "inputstate.h"

using namespace Common;

InputState::InputState() :
	m_upKeyPressed(false),
	m_downKeyPressed(false),
	m_leftKeyPressed(false),
	m_rightKeyPressed(false),
	m_spaceKeyPressed(false)
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

void InputState::setLeftKeyPressed()
{
	m_leftKeyPressed = true;
}

void InputState::setLeftKeyNotPressed()
{
	m_leftKeyPressed = false;
}

bool InputState::isLeftKeyPressed() const
{
	return m_leftKeyPressed;
}

void InputState::setRightKeyPressed()
{
	m_rightKeyPressed = true;
}

void InputState::setRightKeyNotPressed()
{
	m_rightKeyPressed = false;
}

bool InputState::isRightKeyPressed() const
{
	return m_rightKeyPressed;
}

void InputState::setSpaceKeyPressed()
{
	m_spaceKeyPressed = true;
}

void InputState::setSpaceKeyNotPressed()
{
	m_spaceKeyPressed = false;
}

bool InputState::isSpaceKeyPressed() const
{
	return m_spaceKeyPressed;
}

bool InputState::isMovementButtonPressed() const
{
	return m_rightKeyPressed || m_leftKeyPressed || m_upKeyPressed || m_downKeyPressed;
}

bool InputState::isMoreThanOneMovementButtonPressed() const
{
	unsigned int pressedButtons = 0;

	if (isUpKeyPressed())
		++pressedButtons;
	if (isDownKeyPressed())
		++pressedButtons;
	if (isLeftKeyPressed())
		++pressedButtons;
	if (isRightKeyPressed())
		++pressedButtons;

	return pressedButtons > 1;
}
