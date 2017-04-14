#pragma once
#include "Attributed.h"


namespace Library
{
	class WorldState;

	class EventMessageAttributed final:
		public Attributed
	{
	public:
		EventMessageAttributed();
		~EventMessageAttributed() = default;

		const std::string& getSubtype() const;
		void setSubType(const std::string& subtype);

		WorldState* getWorldState() const;
		void setWorldState(WorldState& worldState);

	private:
		std::string mSubtype;
		WorldState* mWorldState;
	};
}