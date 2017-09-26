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
		/// Constuctor for Test Shared Data
		TestSharedData();

		/// Destructor for Test Shared Data. No memory is allocated in this class so destruction is defaulted
		virtual ~TestSharedData() = default;

		/// Clones and instantiates a new copy of this object with matching state
		/// @Return: A pointer to the freshly cloned Test Shared Data object
		XmlParseMaster::SharedData* Clone() override;

		/// RTTI ToString method
		/// @Return: The string representation of the Test Shared Data class Type
		std::string ToString() const override;

		/// RTTI Equals method
		/// @Param rhs: The RTTI object being compared against
		/// @Return: True if the two RTTI objects are equivalent
		bool Equals(const Library::RTTI* rhs) const override;

		std::string mName; /// The Player's Name
		std::int32_t mHealth; /// The Player's health
		std::int32_t mMana; /// The Player's mana
	};
}



