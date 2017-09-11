#include "pch.h"
#include "Sector.h"


using namespace std;

namespace Library
{
	RTTI_DEFINITIONS(Sector)

		Sector::Sector()
	{
		(*this)["Name"].SetStorage(&mName, 1);
		(*this)["Entities"].SetType(DatumType::Scope);
	}

	string Sector::Name() const
	{
		return mName;
	}

	void Sector::SetName(const string& name)
	{
		(*this)["Name"] = name;
	}

	Datum& Sector::Entities()
	{
		return (*this)["Entities"];
	}

	Entity* Sector::CreateEntity(const string& className, const string& instanceName)
	{
		Entity* instance = Factory<Entity>::Create(className);
		assert(instance != nullptr);
		instance->SetName(instanceName);
		Adopt(*instance, "Entities");
		return instance;
	}

	void Sector::SetWorld(World& world)
	{
		world.Adopt(*this, mName);
	}

	World& Sector::GetWorld()
	{
		if (GetParent() == nullptr)
		{
			throw exception("Parent is null");
		}
		assert(GetParent()->Is(World::TypeIdClass()));
		return *GetParent()->As<World>();
	}

	void Sector::Update(WorldState& worldState)
	{
		worldState.sector = this;

		for (uint32_t i = 0; i < Entities().Size(); i++)
		{
			assert(Entities()[i].Is(Entity::TypeIdClass()));
			Entities()[i].As<Entity>()->Update(worldState);
		}

		worldState.sector = nullptr;
	}
}
