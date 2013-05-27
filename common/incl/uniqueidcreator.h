#ifndef UNIQUEIDCREATOR_H
#define UNIQUEIDCREATOR_H

#include <list>


namespace Common
{
class UniqueIdCreator
{
public:
    UniqueIdCreator();
    void removeId(unsigned int id);
    unsigned int  getId();

private:
    std::list<unsigned int> m_idList;
};
}

#endif
