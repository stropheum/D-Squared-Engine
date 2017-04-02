#include "pch.h"
#include "Sector.h"
#include "Entity.h"
#include "World.h"


namespace Library
{
	RTTI_DEFINITIONS(Sector)

		Sector::Sector()
	{
		(*this)["Name"].setStorage(&mName, 1);
		(*this)["Entities"].setType(DatumType::Scope);
	}

	std::string Sector::name() const
	{
		return mName;
	}

	void Sector::setName(const std::string& name)
	{
		(*this)["Name"] = name;
	}

	Datum& Sector::entities()
	{
		return (*this)["Entities"];
	}

	Entity* Sector::createEntity(const std::string& className, const std::string& instanceName)
	{
		Entity* instance = Factory<Entity>::create(className);
		assert(instance != nullptr);
		instance->setName(instanceName);
		adopt(*instance, "Entities");
		return instance;
	}

	void Sector::setWorld(World& world)
	{
		world.adopt(*this, mName);
	}

	World& Sector::getWorld()
	{
		if (getParent() == nullptr)
		{
			throw std::exception("Parent is null");
		}
		assert(getParent()->Is(World::TypeIdClass()));
		return *getParent()->As<World>();
	}

	void Sector::update(WorldState& worldState)
	{
		for (std::uint32_t i = 0; i < entities().size(); i++)
		{
			assert(entities()[i].Is(Entity::TypeIdClass()));
			entities()[i].As<Entity>()->update(worldState);
		}
	}
}
