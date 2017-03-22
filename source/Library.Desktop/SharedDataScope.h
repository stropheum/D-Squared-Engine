#pragma once
#include "XmlParseMaster.h"


namespace Library
{
	class SharedDataScope :
		public XmlParseMaster::SharedData
	{
	public:
		SharedDataScope();
		~SharedDataScope();
		SharedData* clone() override;

		/// RTTI ToString representation of the shared data class
		/// @Return: A string representation of the class name
		std::string ToString() const override;

		/// RTTI Equals comparison
		/// @Param rhs: The RTTI object being compared against
		/// @Return: True if the objects are shared data and identical pointers
		bool Equals(const RTTI* rhs) const override;

		Scope* mScope;
	};
}

