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

private:
	bool m_upKeyPressed;
};
}

#endif
