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
		(*this)["Subtype"].SetType(DatumType::String);
		(*this)["Subtype"] = "";
		(*this)["Delay"].SetType(DatumType::Integer);
		(*this)["Delay"] = 0;

		mPrescribedAttributes.PushBack(
			Signature("Subtype", DatumType::String, 1u, static_cast<std::string*>(nullptr)));
		mPrescribedAttributes.PushBack(
			Signature("Delay", DatumType::Integer, 1u, static_cast<std::int32_t*>(nullptr)));
	}

	void ActionEvent::Update(WorldState& worldState)
	{
		EventMessageAttributed ema;
		ema.SetWorldState(worldState);
		ema.SetSubtype(GetSubtype());

		for (auto iter = Begin(); iter != End(); ++iter)
		{
			if (IsAuxiliaryAttribute((*iter).first))
			{
				Datum& auxDatum = ema.Append((*iter).first);
				auxDatum = (*iter).second;
			}
		}

		Event<EventMessageAttributed>* event = new Event<EventMessageAttributed>(ema, true);
		auto& delay = (*this)["Delay"].Get<std::int32_t>(0);
		worldState.world->GetEventQueue().Enqueue(*event, worldState.GetGameTime(), milliseconds(delay));
	}

	std::string ActionEvent::GetSubtype()
	{
		return (*this)["Subtype"].Get<std::string>(0);
	}

	void ActionEvent::SetSubtype(const std::string& subtype)
	{
		(*this)["Subtype"] = subtype;
	}

	const std::int32_t& ActionEvent::GetDelay()
	{
		return (*this)["Delay"].Get<std::int32_t>(0);
	}

	void ActionEvent::SetDelay(const std::int32_t delay)
	{
		(*this)["Delay"] = delay;
	}
}
