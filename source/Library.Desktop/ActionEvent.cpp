#include "pch.h"
#include "ActionEvent.h"
#include "Signature.h"


using namespace std;
using namespace chrono;

namespace Library
{
	ActionEvent::ActionEvent()
	{
		(*this)["Subtype"].SetType(DatumType::String);
		(*this)["Subtype"] = "";
		(*this)["Delay"].SetType(DatumType::Integer);
		(*this)["Delay"] = 0;

		mPrescribedAttributes.PushBack(
			Signature("Subtype", DatumType::String, 1u, static_cast<string*>(nullptr)));
		mPrescribedAttributes.PushBack(
			Signature("Delay", DatumType::Integer, 1u, static_cast<int32_t*>(nullptr)));
	}

	void ActionEvent::Update(WorldState& worldState)
	{
		EventMessageAttributed ema;
		ema.SetWorldState(worldState);
		ema.SetSubtype(GetSubtype());

		for (auto iter = begin(); iter != end(); ++iter)
		{
			if (IsAuxiliaryAttribute((*iter).first))
			{
				Datum& auxDatum = ema.Append((*iter).first);
				auxDatum = (*iter).second;
			}
		}

		Event<EventMessageAttributed>* event = new Event<EventMessageAttributed>(ema, true);
		auto& delay = (*this)["Delay"].Get<int32_t>(0);
		worldState.world->GetEventQueue().Enqueue(*event, worldState.GetGameTime(), milliseconds(delay));
	}

	string ActionEvent::GetSubtype()
	{
		return (*this)["Subtype"].Get<string>(0);
	}

	void ActionEvent::SetSubtype(const string& subtype)
	{
		(*this)["Subtype"] = subtype;
	}

	const int32_t& ActionEvent::GetDelay()
	{
		return (*this)["Delay"].Get<int32_t>(0);
	}

	void ActionEvent::SetDelay(const int32_t& delay)
	{
		(*this)["Delay"] = delay;
	}
}
