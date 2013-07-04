#ifndef GAMEENGINE_ROUTERGRIDFIELDDECIDER_H
#define GAMEENGINE_ROUTERGRIDFIELDDECIDER_H

namespace GameEngine
{
	class RouterGridField;

	class RouterGridFieldDecider
	{
	public:
		virtual bool decide(const RouterGridField &field, const RouterGridField &previousField, bool previousFieldValid) const = 0;

		virtual ~RouterGridFieldDecider() { }
	};
}

#endif
