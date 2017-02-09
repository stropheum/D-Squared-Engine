#pragma once
#include "TypeState.h"

namespace Library
{
	class FloatState :
		public TypeState
	{
	public:
		FloatState(Datum* const context);
		~FloatState();

		Datum& operator=(const float& rhs) override;

		void setSize(std::uint32_t size) override;
		void reserve(std::uint32_t capacity) override;
	};
}

