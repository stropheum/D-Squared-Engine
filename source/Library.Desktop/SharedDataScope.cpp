#include "pch.h"
#include "SharedDataScope.h"


using namespace std;

namespace Library
{
	RTTI_DEFINITIONS(SharedDataScope)

	SharedDataScope::SharedDataScope() :
		SharedData(), mScope(nullptr)
	{
	}

	SharedDataScope::~SharedDataScope()
	{
		delete mScope;
	}

	XmlParseMaster::SharedData* SharedDataScope::Clone()
	{
		SharedDataScope* clone = new SharedDataScope();
		if (mScope != nullptr)
		{
			clone->mScope = new Scope(*mScope);
		}
		return clone;
	}

	string SharedDataScope::ToString() const
	{
		return "Shared Data Scope";
	}

	bool SharedDataScope::Equals(const RTTI* rhs) const
	{
		if (this == rhs) { return true; }
		if (rhs == nullptr) { return false; }
		SharedDataScope* data = rhs->As<SharedDataScope>();
		if (data == nullptr) { return false; }
		return
			(mScope == data->mScope) ||
			(mScope != nullptr) && 
			(data->mScope != nullptr) &&
			(*mScope == *data->mScope);
	}
}
