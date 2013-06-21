#ifndef GAMEENGINE_ROUTERGRIDFIELDDECIDER_H
#define GAMEENGINE_ROUTERGRIDFIELDDECIDER_H

namespace GameEngine
{
	class RouterGridField;

	class RouterGridFieldDecider
	{
	public:
		virtual bool decide(const RouterGridField &field) const = 0;

		virtual ~RouterGridFieldDecider() { }
	};
}

#endif
