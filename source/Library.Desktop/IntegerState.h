#pragma once
#include "TypeState.h"

namespace Library
{
	class IntegerState :
		public TypeState
	{
	public:
		explicit IntegerState(Datum* const context);

		Datum& operator=(const std::int32_t& rhs) override;

		void setSize(std::uint32_t size) override;
		void reserve(std::uint32_t capacity) override;
		void clear() override;
		void setFromString(const std::string& value, const std::uint32_t& index) override;
		void setStorage(const Datum& rhs) override;
		void setStorage(std::int32_t* data, std::uint32_t size) override;
		std::string toString(std::uint32_t index = 0) override;
	};
}