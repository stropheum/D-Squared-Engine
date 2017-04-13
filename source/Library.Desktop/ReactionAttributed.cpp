#include "pch.h"
#include "ReactionAttributed.h"


namespace Library
{
	ReactionAttributed::ReactionAttributed()
	{
		(*this)["Subtype"].setType(DatumType::String);
	}

	ReactionAttributed::~ReactionAttributed()
	{
	}

	void ReactionAttributed::notify(const EventPublisher& event)
	{
		//TODO: implement notify method for reaction attributed
		UNREFERENCED_PARAMETER(event);
	}
}
