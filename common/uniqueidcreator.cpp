#include "uniqueidcreator.h"
#include <algorithm>
#include <assert.h>

using namespace Common;
using namespace std;

UniqueIdCreator::UniqueIdCreator()
{ }

void UniqueIdCreator::removeId(unsigned int id)
{
	assert(count(m_idList.begin(), m_idList.end(), id) == 1);
	list<unsigned int>::iterator index = find(m_idList.begin(), m_idList.end(), id);
	assert(index != m_idList.end());
	m_idList.erase(index);
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
	m_idList.sort();
	return id;
}

size_t UniqueIdCreator::getIDCount() const
{
	return m_idList.size();
}
