#ifndef LEVELDEFINITION_H
#define LEVELDEFINITION_H

namespace Common
{

class LevelDefinition
{
public:
    enum ObjectType
    {
        ObjectTypePlayer,
        ObjectTypeSolidWall,
        ObjectTypeLooseWall
    };

    LevelDefinition();

    //ObjectType getObjectTypeAtPosition(unsigned int position);

private:
    unsigned int m_width;
    unsigned int m_height;
    ObjectType m_obejectType;
};
}

#endif // LEVELDEFINITION_H
