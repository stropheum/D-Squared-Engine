#pragma once
#include "XmlParseMaster.h"
#include "RTTI.h"

namespace Library
{
	class TestSharedData :
		public XmlParseMaster::SharedData
	{
		RTTI_DECLARATIONS(TestSharedData, XmlParseMaster::SharedData)
	public:
		TestSharedData();
		virtual ~TestSharedData() = default;

		XmlParseMaster::SharedData* clone() override;

		std::string ToString() const override;

		bool Equals(const Library::RTTI* rhs) const override;

		int mValue;
	};
}



