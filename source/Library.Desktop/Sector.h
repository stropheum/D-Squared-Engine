#pragma once
#include "Attributed.h"
#include "Factory.h"


namespace Library
{
	class Sector final :
		public Attributed
	{
		RTTI_DECLARATIONS(Sector, Attributed)

	public:
		Sector();
		~Sector() = default;

		Sector(const Sector& rhs) = delete;
		Sector* operator=(const Sector& rhs) = delete;

		Sector(Sector&& rhs) = delete;
		Sector* operator=(Sector&& rhs) = delete;

		std::string name() const;
		void setName(const std::string& name);
		Datum& entities();
		class Entity* createEntity(const std::string& className, const std::string& instanceName);

	private:
		std::string mName;
	};

	ConcreteFactory(Attributed, Sector)
}

