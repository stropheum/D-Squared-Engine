#include "pch.h"
#include "TestSharedData.h"
#include "RTTI.h"

namespace Library
{
	RTTI_DEFINITIONS(TestSharedData)

	TestSharedData::TestSharedData():
		SharedData(), mValue(0)
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
		if (dynamic_cast<const Library::RTTI*>(this) == rhs)
		{
			return true;
		}

		TestSharedData* data = rhs->As<TestSharedData>();
		bool result = false;

		if (data != nullptr)
		{
			result = (mValue == data->mValue);
		}

		return result;
	}
}

