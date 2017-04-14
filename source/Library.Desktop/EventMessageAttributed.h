#pragma once
#include "Attributed.h"


namespace Library
{
	class EventMessageAttributed final:
		public Attributed
	{
		class World;

	public:
		EventMessageAttributed();
		~EventMessageAttributed() = default;

		const std::string& getSubtype() const;
		void setSubType(const std::string& subtype);

		World* getWorld() const;
		void setWorld(World* const world);

	private:
		std::string mSubtype;
		World* mWorld;
	};
}