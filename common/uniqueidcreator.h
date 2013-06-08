#ifndef COMMON_UNIQUEIDCREATOR_H
#define COMMON_UNIQUEIDCREATOR_H

#include <list>
#include <stddef.h>

namespace Common
{
	class UniqueIdCreator
	{
	public:
		UniqueIdCreator();

		void removeId(unsigned int id);
		unsigned int getId();
		size_t getIDCount() const;

	private:
		std::list<unsigned int> m_idList;
	};
}

#endif
