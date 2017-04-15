#include "pch.h"
#include "EventMessageAttributed.h"


namespace Library
{
	EventMessageAttributed::EventMessageAttributed() :
		mSubtype(""), mWorldState(nullptr)
	{}

	const std::string& EventMessageAttributed::getSubtype() const
	{
		return mSubtype;
	}

	void EventMessageAttributed::setSubtype(const std::string& subtype)
	{
		mSubtype = subtype;
	}

	WorldState* EventMessageAttributed::getWorldState() const
	{
		return mWorldState;
	}

	void EventMessageAttributed::setWorldState(WorldState& worldState)
	{
		mWorldState = &worldState;
	}
}
