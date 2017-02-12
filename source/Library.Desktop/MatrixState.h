#pragma once
#include "TypeState.h"

namespace Library
{
	class MatrixState :
		public TypeState
	{
	public:
		/// Constructor
		/// @Param context: The Datum object that the state operates one
		explicit MatrixState(Datum* const context);

		/// Comparison operator for Datum objects
		/// @Param rhs: The Datum object being compared against
		/// @Return: True if type, size, and each element of the Datum objects are equivalent. False otherwise
		bool operator==(const Datum& rhs) override;

		/// Scalar assignment operator
		/// @Param rhs: The matrix being set to the only element in the Datum
		/// @Return: The modified Datum object
		Datum& operator=(const glm::mat4& rhs) override;

		/// Sets the number of matrices in the local buffer
		/// @Param capacity: The current maximum size of the array
		void setSize(std::uint32_t size) override;
		/// Modifies the capacity of the array to any value greater than or equal to current size
		/// @Param capacity: The new capacity of the array
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
		void setStorage(glm::mat4* data, std::uint32_t size) override;
		/// A string representation of a piece of data stored in the Datum object
		/// @Param index: Optional index of the value being retrieved. Defaulted to first element
		std::string toString(std::uint32_t index = 0) override;
	};
}

