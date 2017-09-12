#pragma once
#include "TypeState.h"

namespace Library
{
	class Scope;
	class ScopeState :
		public TypeState
	{
	public:

#pragma region Construction/Copy/Assignment

		explicit ScopeState(Datum* context);

		ScopeState(const ScopeState& rhs) = delete;

		ScopeState& operator=(const ScopeState& rhs) = delete;

		ScopeState(ScopeState&& rhs) = delete;

		ScopeState& operator=(ScopeState&& rhs) = delete;

#pragma endregion

		/**
		 * Comparison operator for Datum objects
		 * @Param rhs: The Datum object being compared against
		 * @Return: True if Type, Size, and each element of the Datum objects are equivalent. False otherwise
		 * @Exception: THrown if called from this context
		 */
		bool operator==(const Datum& rhs) override;
		
		/**
		 * Assignment operator for scope. Performs a deep copy of all scopes within it
		 * @Param rhs: The Scope object being copied
		 * @Return: A reference to the newly copied Datum object
		 */
		Datum& operator=(Scope* const rhs) override;
		
		/**
		 * Sets the number of elements in the array
		 * @param Size: The new number of elements in the array
		 */
		void SetSize(const std::uint32_t& size) override;
		
		/**
		 * Reserves Capacity for the specified number of elements in the array
		 * @Param: The new potential number of elements in the array
		 */
		void Reserve(const std::uint32_t& capacity) override;
	};
}