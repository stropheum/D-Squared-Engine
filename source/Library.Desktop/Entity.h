#pragma once
#include "Attributed.h"
#include "Sector.h"

namespace Library
{
	class Entity :
		public Attributed
	{
	public:
		Entity();
		~Entity();

		std::string name();
		void setName(const std::string& name);
		Sector* getSector();
		void setSector(const Sector& sector);
		void update();
	};
}
