#pragma once
#include "TypeState.h"

namespace Library
{
	class ScopeState :
		public TypeState
	{
	public:
		explicit ScopeState(Datum* context);
		~ScopeState();

		bool operator==(const Datum& rhs) override;
		Datum& operator=(Scope* const rhs) override;
		/// Sets the number of elements in the array
		/// @param size: The new number of elements in the array
		void setSize(std::uint32_t size) override;
		/// Reserves capacity for the specified number of elements in the array
		/// @Param: The new potential number of elements in the array
		void reserve(std::uint32_t capacity) override;
		/// Clears the value of all elements in the array without changing capacity
		void clear() override;
		/// Parses a string value and assigns the specified index of the array to its value
		/// @Param value: The string value being parsed
		/// @Param index: The index of the array being assigned to
		void setFromString(const std::string& value, const std::uint32_t& index) override;
		/// Sets external storage on copy
		/// @Param rhs: The Datum object that the storage reference is being taken from
		void setStorage(const Datum& rhs) override;
		/// Sets the external storage to the specified pointer
		/// @Param data: The external storage being utilized
		/// @Pram size: The number of elements in the external storage
		/// @Exception: Thrown if attempting to reassign datum type, or if local memory is already used
		void setStorage(Scope** data, std::uint32_t size) override;
	};
}