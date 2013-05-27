#include "uniqueidcreator.h"
#include <algorithm>
#include <assert.h>

using namespace Common;

UniqueIdCreator::UniqueIdCreator()
{ }

void UniqueIdCreator::removeId(unsigned int id)
{
    assert(count(m_idList.begin(), m_idList.end(), id) == 1);
    List::<iterator> index;
    index=std::find(m_idList.begin(),m_idList.end(),id);
    m_idList.remove(index);
}

unsigned int UniqueIdCreator::getId()
{
    unsigned int id;
    if(m_idList.size()==0)
    {
        id=0;
        m_idList.push_back(id);
    }
    else
    {   id=m_idList.back()+1;
        m_idList.push_back(id);
    }
    sort(m_idList.begin(),m_idList.end());
    return id;
}
