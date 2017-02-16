#pragma once

#include "RTTI.h"

#define CLM_FORCE_CXX98
#pragma warning(push)
#pragma warning(disable:4201)
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
#include "Scope.h"
#pragma warning(pop)

namespace Library
{
	/// Types of possible Datum
	enum class DatumType
	{
		Unknown, // Type not specified
		Integer, // Unsigned 
		Float,   // Single-precision floating-point value
		Vector,  // 4-vector
		Matrix,  // 4x4 matrix
		Scope,   // Pointer to a scope
		String,  // STL string
		Pointer  // Pointer to any RTTI instance
	};

	class Datum
	{
		friend class TypeState;		// Base state class
		friend class IntegerState;	// Handles integer-specific functionality
		friend class FloatState;	// Handles float-specific functionality
		friend class VectorState;	// Handles vector-specific functionality
		friend class MatrixState;	// Handles matrix-specific functionality
		friend class StringState;	// Handles string-specific functionality
		friend class PointerState;	// Handles RTTI pointer-specific functionality
		
	public:
		union DatumValues
		{
			void* vp;			// Void pointer member for when type doesn't matter
			std::int32_t* i;	// Integer array pointer
			float* f;			// Float array pointer
			glm::vec4* v;		// Vector array pointer
			glm::mat4* m;		// Matrix array pointer
			Scope* sc;			// Array pointer for Scope pointers
			std::string* s;		// String array pointer
			Library::RTTI** r;	// Array pointer for RTTI pointers
		};

		/// Constructor
		Datum();

		/// Overloaded constructor
		/// @Param type: The type of the Datum object
		Datum(DatumType type);

		/// Destructor
		~Datum();

		/// Copy constructor
		/// @Param rhs: Datum object being copied
		/// @Exception: Thrown if attempting to construct a non-existing datum type
		Datum(const Datum& rhs);

		/// Move copy constructor
		/// @Param rhs: Datum object being copied
		Datum(Datum&& rhs);
		
		/// Datum assignment operator
		/// @Param rhs: Datum object being assigned to
		/// @Return; The newly copied Datum object
		Datum& operator=(const Datum& rhs);

		/// Datum move assignment operator
		/// @Param rhs: Datum object being assigned to
		/// @Return: The newly copied Datum object
		Datum& operator=(Datum&& rhs);

		/// Type assignment operator
		/// @Param rhs: DatumType being assigned to
		/// @Return: The newly assigned Datum object
		/// @Exception: Thrown if attempting to reassign a new type to a Datum object
		Datum& operator=(const DatumType& rhs);

		/// Assignment operator for std::int32_t
		/// @Param rhs: Integer being assigned to
		/// @Return: The newly assigned Datum object
		/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
		Datum& operator=(const std::int32_t& rhs);

		/// Assignment operator for float
		/// @Param rhs: Float being assigned to
		/// @Return: The newly assigned Datum object
		/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
		Datum& operator=(const float& rhs);

		/// Assignment operator for vec4
		/// @Param rhs: Vector being assigned to
		/// @Return: The newly assigned Datum object
		/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
		Datum& operator=(const glm::vec4& rhs);

		/// Assignment operator for mat4
		/// @Param rhs: Matrix being assigned to
		/// @Return: The newly assigned Datum object
		/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
		Datum& operator=(const glm::mat4& rhs);

		/// Assignment operator for std::string
		/// @Param rhs: String being assigned to
		/// @Return: The newly assigned Datum object
		/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
		Datum& operator=(const std::string& rhs);

		/// Assignment operator for float
		/// @Param rhs: Float being assigned to
		/// @Return: The newly assigned Datum object
		/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
		Datum& operator=(Library::RTTI* const& rhs);

		/// Comparison operator for Datum objects
		/// @Param rhs: The Datum object being compared against
		/// @Return: True if the Datum objects are equivalent
		bool operator==(const Datum& rhs) const;

		/// Comparison operator for DatumType value
		/// @Param rhs: The DatumType being compared against
		/// @Return: True if the types are the same
		bool operator==(const DatumType& rhs) const;

		/// Comparison operator for std::int32_t
		/// @Param rhs: The signed integer being compared against
		/// @Return: True if the integer values are the same. False if size is not 1 or if type is invalid
		bool operator==(const std::int32_t& rhs) const;

		/// Comparison operator for float
		/// @Param rhs: The float being compared against
		/// @Return: True if the float values are the same. False if size is not 1 or if type is invalid
		bool operator==(const float& rhs) const;

		/// Comparison operator for v3c4
		/// @Param rhs: The vector being compared against
		/// @Return: True if the vectors are equivalent. False if size is not 1 or if type is invalid
		bool operator==(const glm::vec4& rhs) const;

		/// Comparison operator for mat4
		/// @Param rhs: The matrix being  compared against
		/// @Return: True if the matrices are equivalent. FAlse if size is not 1 or if type is invalid
		bool operator==(const glm::mat4& rhs) const;

		/// Comparison operator for std::string
		/// @Param rhs: The string being compared against
		/// @Return: True if the string values are the same. False if size is not 1 or if type is invalid
		bool operator==(const std::string& rhs) const;

		/// Comparison operator for RTTI pointers
		/// @Param rhs: The RTTI pointer being compared against
		/// @Return: True if the pointers are the same. False if size is not 1 or if type is invalid
		bool operator==(Library::RTTI* const& rhs) const;

		/// Inequality operator for Datum
		/// @Param rhs: The Datum object being compared against
		/// @Return: True if the Datum objects are not equivalent
		bool operator!=(const Datum& rhs) const;

		/// Inequality operator for DatumType
		/// @Param rhs: The DatumType being compared against
		/// @Return: True if the types are not equivalent
		bool operator!=(const DatumType& rhs) const;

		/// Inequality operator for std::int32_t
		/// @Param rhs: The integer being compared against
		/// @Return: True if the integers are not equivalent
		bool operator!=(const std::int32_t& rhs) const;

		/// Inequality operator for float
		/// @Param rhs: The float being compared against
		/// @Return: True if the floats are not equivalent
		bool operator!=(const float& rhs) const;

		/// Inequality operator for vec4
		/// @Param rhs: The vector being compared against
		/// @Return: True if the vectors are not equivalent
		bool operator!=(const glm::vec4& rhs) const;

		/// Inequality operator for mat4
		/// @Param rhs: The matrix being compared against
		/// @Return: True if the matrices are not equivalent
		bool operator!=(const glm::mat4& rhs) const;

		/// Inequality operator for std::string
		/// @Param rhs: The string being compared against
		/// @Return: True if the strings are not equivalent
		bool operator!=(const std::string& rhs) const;

		/// Inequality operator for RTTI pointer
		/// @Param rhs: The RTTI pointer being compared against
		/// @Return: True if the pointers are not equivalent
		bool operator!=(Library::RTTI* const& rhs) const;

		/// The type associated with this object
		/// @Return: The DatumType of this Datum object
		DatumType type() const;

		/// Set the DatumType of the Datum object
		/// @Param type: The new type of the Datum object
		/// @Exception: Thrown if attempting to reassign a new type to a Datum object
		void setType(const DatumType& type);

		/// The number of values in the Datum object
		/// @Return: The number of items associated with this Datum object
		std::uint32_t size() const;

		/// The number of potential values in the Datum object
		/// @Return: The number of objects that can currently be stored in the Datum object
		std::uint32_t capacity() const;

		/// Set number of values and reserve memory if needed
		/// @Param size: the new number of values
		/// @Exception: Thrown if attempting to resize external data
		void setSize(std::uint32_t size);

		/// Reserve additional capacity for uninitialized values
		/// @Param capacity: The number of possible elements that the array will be able to hold
		/// @Exception: Thrown if attempting to resize external storage
		void reserve(std::uint32_t capacity);

		/// Clear the array without shrinking the capacity
		/// @Exception: Thrown if trying to clear with an invalid type set
		void clear();

		/// Sets the external storage to the specified int32_t*
		/// Note: Size on external storage is considered static
		/// @Param data: The specified external storage
		/// @Param size: The number of elements available in the external storage
		void setStorage(std::int32_t* data, std::uint32_t size);

		/// Sets the external storage to the specified float*
		/// Note: Size on external storage is considered static
		/// @Param data: The specified external storage
		/// @Param size: The number of elements available in the external storage
		void setStorage(float* data, std::uint32_t size);

		/// Sets the external storage to the specified glm::vec4*
		/// Note: Size on external storage is considered static
		/// @Param data: The specified external storage
		/// @Param size: The number of elements available in the external storage
		void setStorage(glm::vec4* data, std::uint32_t size);

		/// Sets the external storage to the specified glm::mat4*
		/// Note: Size on external storage is considered static
		/// @Param data: The specified external storage
		/// @Param size: The number of elements available in the external storage
		void setStorage(glm::mat4* data, std::uint32_t size);

		/// Sets the external storage to the specified std::string*
		/// Note: Size on external storage is considered static
		/// @Param data: The specified external storage
		/// @Param size: The number of elements available in the external storage
		void setStorage(std::string* data, std::uint32_t size);

		/// Sets the external storage to the specified RTTI**
		/// Note: Size on external storage is considered static
		/// @Param data: The specified external storage
		/// @Param size: The number of elements available in the external storage
		void setStorage(Library::RTTI** data, std::uint32_t size);
		
		/// Sets a specified index of the array to the specified value
		/// @Param value: The int32_t being assigned
		/// @Param index: The index of the value being assigned to
		/// @Exception invalidType: Thrown if calling set on invalid type
		/// @Exception indexOutObBounds: Thrown if attempting to set beyond existing size
		void set(const std::int32_t& value, const std::uint32_t index = 0);

		/// Sets a specified index of the array to the specified value
		/// @Param value: The float being assigned
		/// @Param index: The index of the value being assigned to
		/// @Exception: Thrown if calling set on invalid type
		/// @Exception: Thrown if attempting to set beyond existing size
		void set(const float& value, const std::uint32_t index = 0);

		/// Sets a specified index of the array to the specified value
		/// @Param value: The vec4 being assigned
		/// @Param index: The index of the value being assigned to
		/// @Exception: Thrown if calling set on invalid type
		/// @Exception: Thrown if attempting to set beyond existing size
		void set(const glm::vec4& value, const std::uint32_t index = 0);

		/// Sets a specified index of the array to the specified value
		/// @Param value: The mat4 being assigned
		/// @Param index: The index of the value being assigned to
		/// @Exception: Thrown if calling set on invalid type
		/// @Exception: Thrown if attempting to set beyond existing size
		void set(const glm::mat4& value, const std::uint32_t index = 0);
		/// Sets a specified index of the array to the specified value
		/// @Param value: The string being assigned
		/// @Param index: The index of the value being assigned to
		/// @Exception: Thrown if calling set on invalid type
		/// @Exception: Thrown if attempting to set beyond existing size
		void set(const std::string& value, const std::uint32_t index = 0);

		/// Sets a specified index of the array to the specified value
		/// @Param value: The RTTI* being assigned
		/// @Param index: The index of the value being assigned to
		/// @Exception: Thrown if calling set on invalid type
		/// @Exception: Thrown if attempting to set beyond existing size
		void set(Library::RTTI* const& value, const std::uint32_t index = 0);

		/// Pushes an std::int32_t to the back of the array
		/// @Param value: The value being pushed onto the array
		void pushBack(const std::int32_t& value);

		/// Pushes an std::int32_t to the back of the array
		/// @Param value: The value being pushed onto the array
		void pushBack(const float& value);

		/// Pushes an std::int32_t to the back of the array
		/// @Param value: The value being pushed onto the array
		void pushBack(const glm::vec4& value);

		/// Pushes an std::int32_t to the back of the array
		/// @Param value: The value being pushed onto the array
		void pushBack(const glm::mat4& value);

		/// Pushes an std::int32_t to the back of the array
		/// @Param value: The value being pushed onto the array
		void pushBack(const std::string& value);

		/// Pushes an std::int32_t to the back of the array
		/// @Param value: The value being pushed onto the array
		/// @Exception: Thrown if attempting to push back a null value
		void pushBack(RTTI* const& value);

		
		/// Parses a string value and sets the value to the specified index
		/// @Param value: The string value being parsed
		/// @Param index: The location being set to. Default is 0
		/// @Exception: Thrown if syntax is invalid
		void setFromString(const std::string& value, const std::uint32_t& index = 0);

		/// A string representation of a piece of data stored in the Datum object
		/// @Param index: Optional index of the value being retrieved. Defaulted to first element
		/// @Exception invalidFormat: Thrown if unable to properly parse string
		std::string toString(std::uint32_t index = 0);

		/// Gets the item at the specified index in the array
		/// @Param index: The index of the item being retrieved
		/// @Return: The object at the specified index
		/// @Exception: Thrown if calling get on invalid type
		/// @Exception: Thrown if data is null
		/// @Exception: Thrown if index is greater than or equal to current size
		template <typename T> T& get(const std::uint32_t index = 0);

	private:
		TypeState* mTypeState; /// State pattern object. Type-specific tasks will be delegated to this
		DatumType mType; /// The type of the Datum object
		DatumValues mData; /// The data union of the Datum object. Can be allocated internally or assigned externally
		std::uint32_t mCapacity; /// The number of elements of the set type that the Datum can hold
		std::uint32_t mSize; /// The current number of elements in the Datum object
		bool mDataIsExternal; /// True if data is stored externally of the Datum object
	};

	/// Template specialization for getting an integer value
	/// @Param index: The index of the array being retrieved
	/// @Return: The value of the array at the specified index
	/// @Exception invalidType: Thrown when calling get on invalid type
	/// @Exception nullRef: Thrown when attempting call get on uninitialized data
	/// @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	template<>
	inline std::int32_t& Datum::get(const std::uint32_t index)
	{
		if (mType != DatumType::Integer) throw std::exception("Calling get on invalid type");
		if (mData.i == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.i[index];
	}

	/// Template specialization for getting a float value
	/// @Param index: The index of the array being retrieved
	/// @Return: The value of the array at the specified index
	/// @Exception invalidType: Thrown when calling get on invalid type
	/// @Exception nullRef: Thrown when attempting call get on uninitialized data
	/// @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	template<>
	inline float& Datum::get(const std::uint32_t index)
	{
		if (mType != DatumType::Float) throw std::exception("Calling get on invalid type");
		if (mData.f == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.f[index];
	}

	/// Template specialization for getting a vector value
	/// @Param index: The index of the array being retrieved
	/// @Return: The value of the array at the specified index
	/// @Exception invalidType: Thrown when calling get on invalid type
	/// @Exception nullRef: Thrown when attempting call get on uninitialized data
	/// @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	template<>
	inline glm::vec4& Datum::get(const std::uint32_t index)
	{
		if (mType != DatumType::Vector) throw std::exception("Calling get on invalid type");
		if (mData.f == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.v[index];
	}

	/// Template specialization for getting a matrix value
	/// @Param index: The index of the array being retrieved
	/// @Return: The value of the array at the specified index
	/// @Exception invalidType: Thrown when calling get on invalid type
	/// @Exception nullRef: Thrown when attempting call get on uninitialized data
	/// @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	template<>
	inline glm::mat4& Datum::get(const std::uint32_t index)
	{
		if (mType != DatumType::Matrix) throw std::exception("Calling get on invalid type");
		if (mData.f == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.m[index];
	}

	/// Template specialization for getting a string value
	/// @Param index: The index of the array being retrieved
	/// @Return: The value of the array at the specified index
	/// @Exception invalidType: Thrown when calling get on invalid type
	/// @Exception nullRef: Thrown when attempting call get on uninitialized data
	/// @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	template<>
	inline std::string& Datum::get(const std::uint32_t index)
	{
		if (mType != DatumType::String) throw std::exception("Calling get on invalid type");
		if (mData.s == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.s[index];
	}

	/// Template specialization for getting an RTTI pointer value
	/// @Param index: The index of the array being retrieved
	/// @Return: The value of the array at the specified index
	/// @Exception invalidType: Thrown when calling get on invalid type
	/// @Exception nullRef: Thrown when attempting call get on uninitialized data
	/// @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	template<>
	inline Library::RTTI*& Datum::get(const std::uint32_t index)
	{
		if (mType != DatumType::Pointer) throw std::exception("Calling get on invalid type");
		if (mData.r == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.r[index];
	}
}
