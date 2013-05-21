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

private:
	bool m_upKeyPressed;
	bool m_downKeyPressed;
};
}

#endif
