#pragma once
#include "TypeState.h"

namespace Library
{
	class FloatState :
		public TypeState
	{
	public:
		explicit FloatState(Datum* const context);

		Datum& operator=(const float& rhs) override;

		void setSize(std::uint32_t size) override;
		void reserve(std::uint32_t capacity) override;
		void clear() override;
		void setFromString(const std::string& value, const std::uint32_t& index) override;
		void setStorage(const Datum& rhs) override;
		void setStorage(float* data, std::uint32_t size) override;
	};
}

