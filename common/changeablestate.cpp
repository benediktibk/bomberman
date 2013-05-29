#include "changeablestate.h"

using namespace Common;

ChangeableState::ChangeableState() :
	m_changed(true)
{ }

ChangeableState::~ChangeableState()
{ }

void ChangeableState::setChanged()
{
	m_changed = true;
}

bool ChangeableState::hasChanged()
{
	return m_changed;
}

void ChangeableState::resetChanged()
{
	m_changed = false;
}