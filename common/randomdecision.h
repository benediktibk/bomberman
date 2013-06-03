#ifndef COMMON_RANDOMDECISION_H
#define COMMON_RANDOMDECISION_H

namespace Common
{
class RandomDecision
{
public:
	RandomDecision(double possibilityForTrue);

	bool decide() const;

private:
	double m_possibilityForTrue;
};
}

#endif
