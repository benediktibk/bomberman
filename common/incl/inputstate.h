#ifndef COMMON_INPUTSTATE_H
#define COMMON_INPUTSTATE_H

namespace Common
{
class InputState
{
public:
	InputState();

	void setUpKeyPressed();
	void setUpKeyNotPressed();
	bool isUpKeyPressed() const;
	void setDownKeyPressed();
	void setDownKeyNotPressed();
	bool isDownKeyPressed() const;
	void setLeftKeyPressed();
	void setLeftKeyNotPressed();
	bool isLeftKeyPressed() const;
	void setRightKeyPressed();
	void setRightKeyNotPressed();
	bool isRightKeyPressed() const;
	void setSpaceKeyPressed();
	void setSpaceKeyNotPressed();
	bool isSpaceKeyPressed() const;

private:
	bool m_upKeyPressed;
	bool m_downKeyPressed;
	bool m_leftKeyPressed;
	bool m_rightKeyPressed;
	bool m_spaceKeyPressed;
};
}

#endif
