#include "pch.h"
#include "TestSharedData.h"
#include "RTTI.h"

namespace Library
{
//	RTTI_DEFINITIONS(TestSharedData)

	TestSharedData::TestSharedData():
		SharedData()
	{
	}

	XmlParseMaster::SharedData* TestSharedData::clone()
	{
		return this;
	}

	std::string TestSharedData::ToString() const
	{
		return "Test Shared Data";
	}

	bool TestSharedData::Equals(const Library::RTTI* rhs) const
	{
//		if (dynamic_cast<const Library::XmlParseMaster::SharedData*>(this) == rhs)
//		{
//			return true;
//		}

		const SharedData* data = rhs->As<XmlParseMaster::SharedData>();
		bool result = false;

//		if (data != nullptr)
//		{
//			result = (this == rhs);
//		}

		return result;
	}
}

