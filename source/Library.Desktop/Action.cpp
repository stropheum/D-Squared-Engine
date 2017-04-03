#include "pch.h"
#include "Action.h"


namespace Library
{
	RTTI_DEFINITIONS(Action)

	Action::Action()
	{
	}

	std::string Action::name() const
	{
		return mName;
	}

	void Action::setName(const std::string& name)
	{
		mName = name;
	}
}
