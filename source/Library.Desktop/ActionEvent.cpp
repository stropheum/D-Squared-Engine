#include "pch.h"
#include "ActionEvent.h"


namespace Library
{
	ActionEvent::ActionEvent()
	{
		(*this)["Subtype"].setType(DatumType::String);
		(*this)["Delay"].setType(DatumType::Integer);
	}

	void ActionEvent::update(WorldState& worldState)
	{
		UNREFERENCED_PARAMETER(worldState);
		// TODO: Create an attributed event, assign its world and subtype, copy all aux params into the event and queue it with the given delay
	}
}
