#pragma once
#include "TypeState.h"

namespace Library
{
	class PointerState :
		public TypeState
	{
	public:
		PointerState(Datum* const context);
		~PointerState();

		Datum& operator=(Library::RTTI* const& rhs) override;

		void setSize(std::uint32_t size) override;
		void reserve(std::uint32_t capacity) override;
		void clear() override;
		void setFromString(const std::string& value, const std::uint32_t& index) override;
		void setStorage(const Datum& rhs) override;
	};
}
