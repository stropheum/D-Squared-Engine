#include "pch.h"
#include "SharedDataScope.h"
#include "Scope.h"


namespace Library
{
	SharedDataScope::SharedDataScope():
		SharedData(), mScope(nullptr)
	{
	}

	SharedDataScope::~SharedDataScope()
	{
		delete mScope;
	}

	XmlParseMaster::SharedData* SharedDataScope::clone()
	{
		SharedDataScope* clone = new SharedDataScope();
		clone->mScope = mScope;
		return clone;
	}

	/// RTTI ToString representation of the shared data class
	/// @Return: A string representation of the class name
	std::string SharedDataScope::ToString() const
	{
		return "Shared Data Scope";
	}

	/// RTTI Equals comparison
	/// @Param rhs: The RTTI object being compared against
	/// @Return: True if the objects are shared data and identical pointers
	bool SharedDataScope::Equals(const RTTI* rhs) const
	{
		if (this == rhs) { return true; }
		const SharedDataScope* data = rhs->As<SharedDataScope>();
		return (data != nullptr) && (mScope == data->mScope);
	}
}
