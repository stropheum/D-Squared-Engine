#include "pch.h"
#include "ActionEvent.h"
#include "EventMessageAttributed.h"
#include "WorldState.h"
#include "World.h"
#include "Event.h"
#include "GameTime.h"


using namespace std::chrono;

namespace Library
{
	ActionEvent::ActionEvent()
	{
		(*this)["Subtype"].setType(DatumType::String);
		(*this)["Delay"].setType(DatumType::Integer);
		(*this)["Delay"] = 0;
	}

	void ActionEvent::update(WorldState& worldState)
	{
		EventMessageAttributed ema;
		ema.setWorldState(worldState);

		auto auxAttributes = getAuxilliaryAttributes();
		for (auto iter = auxAttributes.begin(); iter != auxAttributes.end(); ++iter)
		{
			Datum& auxDatum = ema.appendAuxiliaryAttribute((*iter).first);
			auxDatum = (*iter).second;
		}

		Event<EventMessageAttributed> event(ema, true);
		auto delay = (*this)["Delay"].get<std::int32_t>();
		worldState.world->getEventQueue().enqueue(event, worldState.getGameTime(), milliseconds(delay));
	}
}
