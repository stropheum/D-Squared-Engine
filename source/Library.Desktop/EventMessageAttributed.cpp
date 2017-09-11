#include "pch.h"
#include "EventMessageAttributed.h"


namespace Library
{
	EventMessageAttributed::EventMessageAttributed() :
		mSubtype(""), mWorldState(nullptr)
	{}

	const std::string& EventMessageAttributed::GetSubtype() const
	{
		return mSubtype;
	}

	void EventMessageAttributed::SetSubtype(const std::string& subtype)
	{
		mSubtype = subtype;
	}

	WorldState* EventMessageAttributed::GetWorldState() const
	{
		return mWorldState;
	}

	void EventMessageAttributed::SetWorldState(WorldState& worldState)
	{
		mWorldState = &worldState;
	}
}
