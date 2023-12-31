#ifndef COMMON_COMPARE_H
#define COMMON_COMPARE_H

namespace Common
{
class Compare
{
public:
    Compare(double epsilon);

    bool isFuzzyEqual(double value1, double value2);
    bool isFuzzyGreater(double value1, double value2);
    bool isFuzzySmaller(double value1, double value2);
    bool isStrictFuzzyGreater(double value1, double value2);
    bool isStrictFuzzySmaller(double value1, double value2);

private:
     double m_epsilon;
};
}
#endif // COMPARE_H
