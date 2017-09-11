#include "pch.h"
#include "TestSharedData.h"

namespace Library
{
	RTTI_DEFINITIONS(TestSharedData)

	TestSharedData::TestSharedData():
		SharedData(), mName(""), mHealth(0), mMana(0)
	{
	}

	XmlParseMaster::SharedData* TestSharedData::Clone()
	{
		TestSharedData* clone = new TestSharedData();
		clone->mName = mName;
		clone->mHealth = mHealth;
		clone->mMana = mMana;
		return clone;
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
			result =
				(mName == data->mName) &&
				(mHealth == data->mHealth) &&
				(mMana == data->mMana);
		}

		return result;
	}
}

