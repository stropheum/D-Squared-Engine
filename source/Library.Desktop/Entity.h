#pragma once
#include "Attributed.h"
#include "Sector.h"
#include "Factory.h"


namespace Library
{
	class Entity :
		public Attributed
	{
		RTTI_DECLARATIONS(Entity, Attributed)

	public:
		Entity();
		~Entity() = default;

		Entity* operator=(const Entity& rhs) = delete;
		Entity(const Entity& rhs) = delete;

		Entity* operator=(Entity&& rhs) = delete;
		Entity(Entity&& rhs) = delete;

		std::string name() const;
		void setName(const std::string& name);
		Sector* getSector();
		void setSector(Sector& sector);
		void update(class WorldState& worldState);

	private:
		std::string mName;
	};

	ConcreteFactory(Scope, Entity)										
}
