#ifndef COMMON_PLAYERINFORMATION_H
#define COMMON_PLAYERINFORMATION_H

#include <vector>

namespace Common
{
	class PlayerInformation
	{
	public:
		PlayerInformation();
        ~PlayerInformation();
        void setBombCounter(unsigned int amount);
        unsigned int getBombCounter() const;        
        void setRangeCounter(unsigned int amount);
        unsigned int getRangeCounter() const;
        void setSpeedCounter(double amount);
        unsigned int getSpeedCounter() const;
        void setPlayerId(unsigned int id);
        unsigned int getPlayerId() const;
    
    private:
		unsigned int m_bombCounter;
		unsigned int m_rangeCounter;
        unsigned int m_speedCounter;
        unsigned int m_playerId;
	};
}


#endif
