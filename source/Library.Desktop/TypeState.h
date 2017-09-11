#pragma once
#include "Datum.h"

namespace Library
{
	class Scope;
	
	/// Parent class for all potential Type states
	/// All methods throw exceptions from this context because a generic TypeState should be considered invalid
	/// Valid states will override the methods considered valid to their state and the rest will still throw exceptions
	class TypeState
	{
	public:
		virtual ~TypeState() = default;
		
		/// Comparison operator for Datum objects
		/// @Param rhs: The Datum object being compared against
		/// @Return: True if Type, Size, and each element of the Datum objects are equivalent. False otherwise
		/// @Exception: THrown if called from this context
		virtual bool operator==(const Datum& rhs);
		
		/// Assignment operator
		/// @Param rhs: The value being assigned to the first element of the array
		/// @Exception: Thrown if called from this context
		virtual Datum& operator=(const std::int32_t& rhs);
		
		/// Assignment operator
		/// @Param rhs: The value being assigned to the first element of the array
		/// @Exception: Thrown if called from this context
		virtual Datum& operator=(const float& rhs);
		
		/// Assignment operator
		/// @Param rhs: The value being assigned to the first element of the array
		/// @Exception: Thrown if called from this context
		virtual Datum& operator=(const glm::vec4& rhs);
		
		/// Assignment operator
		/// @Param rhs: The value being assigned to the first element of the array
		/// @Exception: Thrown if called from this context
		virtual Datum& operator=(const glm::mat4& rhs);
		
		/// Assignment operator
		/// @Param rhs: The value being assigned to the first element of the array
		/// @Exception: THrown if called from this context
		virtual Datum& operator=(Scope* const rhs);
		
		/// Assignment operator
		/// @Param rhs: The value being assigned to the first element of the array
		/// @Exception: Thrown if called from this context
		virtual Datum& operator=(const std::string& rhs);
		
		/// Assignment operator
		/// @Param rhs: The value being assigned to the first element of the array
		/// @Exception: Thrown if called from this context
		virtual Datum& operator=(Library::RTTI* const& rhs);

		/// Sets the number of elements in the array
		/// @param Size: The new number of elements in the array
		virtual void SetSize(std::uint32_t size)=0;
		
		/// Reserves Capacity for the specified number of elements in the array
		/// @Param: The new potential number of elements in the array
		virtual void Reserve(std::uint32_t capacity)=0;
		
		/// Clears all values in the array without changing Capacity
		virtual void Clear();
		
		/// Parses a string value and assigns the specified index of the array to its value
		/// @Param value: The string value being parsed
		/// @Param index: The index of the array being assigned to
		virtual void SetFromString(const std::string& value, const std::uint32_t& index);
		
		/// Sets the external storage of the Datum object being copied
		/// @Param rhs: The datum object which stores the reference to the external storage
		virtual void SetStorage(const Datum& rhs);
		
		/// Sets the external storage of the specified integer array
		/// @Param data: The external storage array
		/// @Param Size: The Size of the array
		/// @Exception: Thrown if called from this context
		virtual void SetStorage(std::int32_t* data, std::uint32_t size);
		
		/// Sets the external storage of the specified float array
		/// @Param data: The external storage array
		/// @Param Size: The Size of the array
		/// @Exception: Thrown if called from this context
		virtual void SetStorage(float* data, std::uint32_t size);
		
		/// Sets the external storage of the specified vector array
		/// @Param data: The external storage array
		/// @Param Size: The Size of the array
		/// @Exception: Thrown if called from this context
		virtual void SetStorage(glm::vec4* data, std::uint32_t size);
		
		/// Sets the external storage of the specified matrix array
		/// @Param data: The external storage array
		/// @Param Size: The Size of the array
		/// @Exception: Thrown if called from this context
		virtual void SetStorage(glm::mat4* data, std::uint32_t size);
		
		/// Sets the external storage to the specified pointer
		/// @Param data: The external storage being utilized
		/// @Pram Size: The number of elements in the external storage
		/// @Exception: Thrown if attempting to reassign datum Type, or if local memory is already used
		virtual void SetStorage(Scope** data, std::uint32_t size);
		
		/// Sets the external storage of the specified string array
		/// @Param data: The external storage array
		/// @Param Size: The Size of the array
		/// @Exception: Thrown if called from this context
		virtual void SetStorage(std::string* data, std::uint32_t size);
		
		/// Sets the external storage of the specified RTTI pointer array
		/// @Param data: The external storage array
		/// @Param Size: The Size of the array
		/// @Exception: Thrown if called from this context
		virtual void SetStorage(Library::RTTI** data, std::uint32_t size);
		
		/// Generates a string representation of the data At the specified index of the array
		/// @Param index: The index of the array being translated. Defaulted to 0
		/// @Exception: Thrown if called from this context
		virtual std::string ToString(std::uint32_t index = 0);

	protected:
		
		/// TypeState constructor. Used to generate valid states from children
		/// @Param context: The Datum object that the state will operate on
		TypeState(Datum* const context);
		Datum* mContext; /// The Datum object that the state will operate on
	};
}
