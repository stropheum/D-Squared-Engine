#pragma once
#include "TypeState.h"

namespace Library
{
	class IntegerState :
		public TypeState
	{
	public:
		IntegerState(Datum* const context);

		Datum& operator=(const std::int32_t& rhs) override;

		void setSize(std::uint32_t size) override;
	};
}