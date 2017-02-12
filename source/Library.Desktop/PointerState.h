#pragma once
#include "TypeState.h"

namespace Library
{
	class PointerState :
		public TypeState
	{
	public:
		explicit PointerState(Datum* const context);

		Datum& operator=(Library::RTTI* const& rhs) override;

		void setSize(std::uint32_t size) override;
		void reserve(std::uint32_t capacity) override;
		void clear() override;
		void setFromString(const std::string& value, const std::uint32_t& index) override;
		void setStorage(const Datum& rhs) override;
		void setStorage(Library::RTTI** data, std::uint32_t size) override;
		std::string toString(std::uint32_t index = 0) override;
	};
}
