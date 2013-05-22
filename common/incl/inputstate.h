#ifndef INPUTSTATE_H
#define INPUTSTATE_H

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

private:
	bool m_upKeyPressed;
	bool m_downKeyPressed;
    bool m_leftKeyPressed;
    bool m_rightKeyPressed;
};
}

#endif
