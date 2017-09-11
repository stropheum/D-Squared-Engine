#include "pch.h"
#include "Action.h"


namespace Library
{
	RTTI_DEFINITIONS(Action)

	Action::Action()
	{
	}

	std::string Action::Name() const
	{
		return mName;
	}

	void Action::SetName(const std::string& name)
	{
		mName = name;
	}
}
