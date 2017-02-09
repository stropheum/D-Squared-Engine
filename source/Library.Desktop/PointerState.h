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
	};
}
