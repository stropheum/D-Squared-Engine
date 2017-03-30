#pragma once
#include "Attributed.h"

namespace Library
{
	class Sector :
		public Attributed
	{
	public:
		Sector();
		~Sector();

		std::string name();
		void setName(const std::string& name);
	};
}

