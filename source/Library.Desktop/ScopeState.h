#pragma once
#include "TypeState.h"

namespace Library
{
	class Scope;
	class ScopeState :
		public TypeState
	{
	public:
		explicit ScopeState(Datum* context);

		Datum& operator=(Scope* const rhs) override;
		/// Sets the number of elements in the array
		/// @param size: The new number of elements in the array
		void setSize(std::uint32_t size) override;
		/// Reserves capacity for the specified number of elements in the array
		/// @Param: The new potential number of elements in the array
		void reserve(std::uint32_t capacity) override;
	};
}