#include "pch.h"
#include "EventMessageAttributed.h"


namespace Library
{
	EventMessageAttributed::EventMessageAttributed() :
		mSubtype(""), mWorld(nullptr)
	{}

	const std::string& EventMessageAttributed::getSubtype() const
	{
		return mSubtype;
	}

	void EventMessageAttributed::setSubType(const std::string& subtype)
	{
		mSubtype = subtype;
	}

	EventMessageAttributed::World* EventMessageAttributed::getWorld() const
	{
		return mWorld;
	}

	void EventMessageAttributed::setWorld(World* const world)
	{
		mWorld = world;
	}
}
