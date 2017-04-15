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
		(*this)["Subtype"] = "";
		(*this)["Delay"].setType(DatumType::Integer);
		(*this)["Delay"] = 0;

		mPrescribedAttributes.pushBack(
			Signature("Subtype", DatumType::String, 1u, static_cast<std::string*>(nullptr)));
		mPrescribedAttributes.pushBack(
			Signature("Delay", DatumType::Integer, 1u, static_cast<std::int32_t*>(nullptr)));
	}

	void ActionEvent::update(WorldState& worldState)
	{
		EventMessageAttributed ema;
		ema.setWorldState(worldState);
		ema.setSubtype(getSubtype());

		for (auto iter = begin(); iter != end(); ++iter)
		{
			if (isAuxiliaryAttribute((*iter).first))
			{
				Datum& auxDatum = ema.append((*iter).first);
				auxDatum = (*iter).second;
			}
		}

		Event<EventMessageAttributed>* event = new Event<EventMessageAttributed>(ema, true);
		auto& delay = (*this)["Delay"].get<std::int32_t>(0);
		worldState.world->getEventQueue().enqueue(*event, worldState.getGameTime(), milliseconds(delay));
	}

	std::string ActionEvent::getSubtype()
	{
		return (*this)["Subtype"].get<std::string>(0);
	}

	void ActionEvent::setSubtype(const std::string& subtype)
	{
		(*this)["Subtype"] = subtype;
	}

	const std::int32_t& ActionEvent::getDelay()
	{
		return (*this)["Delay"].get<std::int32_t>(0);
	}

	void ActionEvent::setDelay(const std::int32_t delay)
	{
		(*this)["Delay"] = delay;
	}
}
