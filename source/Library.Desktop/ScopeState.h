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

		/// Comparison operator for Datum objects
		/// @Param rhs: The Datum object being compared against
		/// @Return: True if type, size, and each element of the Datum objects are equivalent. False otherwise
		/// @Exception: THrown if called from this context
		bool operator==(const Datum& rhs) override;
		/// Assignment operator for scope. Performs a deep copy of all scopes within it
		/// @Param rhs: The Scope object being copied
		/// @Return: A reference to the newly copied Datum object
		Datum& operator=(Scope* const rhs) override;
		/// Sets the number of elements in the array
		/// @param size: The new number of elements in the array
		void setSize(std::uint32_t size) override;
		/// Reserves capacity for the specified number of elements in the array
		/// @Param: The new potential number of elements in the array
		void reserve(std::uint32_t capacity) override;
	};
}