#pragma once

#include "RTTI.h"

#define CLM_FORCE_CXX98
#pragma warning(push)
#pragma warning(disable:4201)
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
#pragma warning(pop)

namespace Library
{
	class Scope;
	// Types of possible Datum
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
		friend class ScopeState;	// Handles scope-pointer specific functionality
		friend class StringState;	// Handles string-specific functionality
		friend class PointerState;	// Handles RTTI-pointer specific functionality
		
	public:
		union DatumValues
		{
			DatumValues() : vp(nullptr) {}

			void* vp;			// Void pointer member for when Type doesn't matter
			std::int32_t* i;	// Integer array pointer
			float* f;			// Float array pointer
			glm::vec4* v;		// Vector array pointer
			glm::mat4* m;		// Matrix array pointer
			Scope** sc;			// Array pointer for Scope pointers
			std::string* s;		// String array pointer
			Library::RTTI** r;	// Array pointer for RTTI pointers
		};

#pragma region Construction/Copy/Assignment

		Datum();

		explicit Datum(const DatumType& type);

		~Datum();

		Datum(const Datum& rhs);

		Datum& operator=(const Datum& rhs);

		Datum(Datum&& rhs) noexcept;

		Datum& operator=(Datum&& rhs) noexcept;

#pragma endregion

		/**
		 * Index operator for accessing nested scopes
		 * @Param index: The scope At the given index
		 * @Return: The scope At the specified index
		 */
		Scope& operator[](const std::uint32_t& index);
		
		/**
		 * Type assignment operator
		 * @Param rhs: DatumType being assigned to
		 * @Return: The newly assigned Datum object
		 * @Exception: Thrown if attempting to reassign a new Type to a Datum object
		 */
		Datum& operator=(const DatumType& rhs);

		/**
		 * Assignment operator for std::int32_t
		 * @Param rhs: Integer being assigned to
		 * @Return: The newly assigned Datum object
		 * @Exception: Thrown if attempting to assign to invalid Datum Type or if Size is greater than 1
		 */
		Datum& operator=(const std::int32_t& rhs);

		/**
		 * Assignment operator for float
		 * @Param rhs: Float being assigned to
		 * @Return: The newly assigned Datum object
		 * @Exception: Thrown if attempting to assign to invalid Datum Type or if Size is greater than 1
		 */
		Datum& operator=(const float& rhs);

		/**
		 * Assignment operator for vec4
		 * @Param rhs: Vector being assigned to
		 * @Return: The newly assigned Datum object
		 * @Exception: Thrown if attempting to assign to invalid Datum Type or if Size is greater than 1
		 */
		Datum& operator=(const glm::vec4& rhs);

		/**
		 * Assignment operator for mat4
		 * @Param rhs: Matrix being assigned to
		 * @Return: The newly assigned Datum object
		 * @Exception: Thrown if attempting to assign to invalid Datum Type or if Size is greater than 1
		 */
		Datum& operator=(const glm::mat4& rhs);

		/**
		 * Assignment operator for Scope
		 * @Param rhs: Scope being assigned to
		 * @Return: The newly assigned Datum object
		 * @Exception: Thrown if attempting to assign to invalid Datum Type or if Size is greater than 1  
		 */
		Datum& operator=(Scope* const rhs);

		/**
		 * Assignment operator for std::string
		 * @Param rhs: String being assigned to
		 * @Return: The newly assigned Datum object
		 * @Exception: Thrown if attempting to assign to invalid Datum Type or if Size is greater than 1
		 */
		Datum& operator=(const std::string& rhs);

		/**
		 * Assignment operator for float
		 * @Param rhs: Float being assigned to
		 * @Return: The newly assigned Datum object
		 * @Exception: Thrown if attempting to assign to invalid Datum Type or if Size is greater than 1
		 */
		Datum& operator=(Library::RTTI* const& rhs);

		/**
		 * Comparison operator for Datum objects
		 * @Param rhs: The Datum object being compared against
		 * @Return: True if the Datum objects are equivalent
		 */
		bool operator==(const Datum& rhs) const;

		/**
		 * Comparison operator for DatumType value
		 * @Param rhs: The DatumType being compared against
		 * @Return: True if the types are the same
		 */
		bool operator==(const DatumType& rhs) const;

		/**
		 * Comparison operator for std::int32_t
		 * @Param rhs: The signed integer being compared against
		 * @Return: True if the integer values are the same. False if Size is not 1 or if Type is invalid
		 */
		bool operator==(const std::int32_t& rhs) const;

		/**
		 * Comparison operator for float
		 * @Param rhs: The float being compared against
		 * @Return: True if the float values are the same. False if Size is not 1 or if Type is invalid
		 */
		bool operator==(const float& rhs) const;

		/**
		 * Comparison operator for v3c4
		 * @Param rhs: The vector being compared against
		 * @Return: True if the vectors are equivalent. False if Size is not 1 or if Type is invalid
		 */
		bool operator==(const glm::vec4& rhs) const;

		/**
		 * Comparison operator for mat4
		 * @Param rhs: The matrix being  compared against
		 * @Return: True if the matrices are equivalent. False if Size is not 1 or if Type is invalid
		 */
		bool operator==(const glm::mat4& rhs) const;

		/**
		 * Comparison operator for Scope
		 * @Param rhs: The scope being  compared against
		 * @Return: True if the scopes are equivalent. False if Size is not 1 or if Type is invalid
		 */
		bool operator==(const Scope* rhs) const;

		/**
		 * Comparison operator for std::string
		 * @Param rhs: The string being compared against
		 * @Return: True if the string values are the same. False if Size is not 1 or if Type is invalid
		 */
		bool operator==(const std::string& rhs) const;

		/**
		 * Comparison operator for RTTI pointers
		 * @Param rhs: The RTTI pointer being compared against
		 * @Return: True if the pointers are the same. False if Size is not 1 or if Type is invalid
		 */
		bool operator==(Library::RTTI* const& rhs) const;

		/**
		 * Inequality operator for Datum
		 * @Param rhs: The Datum object being compared against
		 * @Return: True if the Datum objects are not equivalent
		 */
		bool operator!=(const Datum& rhs) const;

		/**
		 * Inequality operator for DatumType
		 * @Param rhs: The DatumType being compared against
		 * @Return: True if the types are not equivalent
		 */
		bool operator!=(const DatumType& rhs) const;

		/**
		 * Inequality operator for std::int32_t
		 * @Param rhs: The integer being compared against
		 * @Return: True if the integers are not equivalent
		 */
		bool operator!=(const std::int32_t& rhs) const;

		/**
		 * Inequality operator for float
		 * @Param rhs: The float being compared against
		 * @Return: True if the floats are not equivalent
		 */
		bool operator!=(const float& rhs) const;

		/**
		 * Inequality operator for vec4
		 * @Param rhs: The vector being compared against
		 * @Return: True if the vectors are not equivalent
		 */
		bool operator!=(const glm::vec4& rhs) const;

		/**
		 * Inequality operator for mat4
		 * @Param rhs: The matrix being compared against
		 * @Return: True if the matrices are not equivalent
		 */
		bool operator!=(const glm::mat4& rhs) const;
		
		/**
		 * Inequality operator for std::string
		 * @Param rhs: The string being compared against
		 * @Return: True if the strings are not equivalent
		 */
		bool operator!=(const std::string& rhs) const;

		/**
		 * Inequality operator for RTTI pointer
		 * @Param rhs: The RTTI pointer being compared against
		 * @Return: True if the pointers are not equivalent
		 */
		bool operator!=(Library::RTTI* const& rhs) const;

		/**
		 * The Type associated with this object
		 * @Return: The DatumType of this Datum object
		 */
		DatumType Type() const;

		/**
		 * Set the DatumType of the Datum object
		 * @Param Type: The new Type of the Datum object
		 * @Exception: Thrown if attempting to reassign a new Type to a Datum object
		 */
		void SetType(const DatumType& type);

		/**
		 * The number of values in the Datum object
		 * @Return: The number of items associated with this Datum object
		 */
		std::uint32_t Size() const;

		/**
		 * The number of potential values in the Datum object
		 * @Return: The number of objects that can currently be stored in the Datum object
		 */
		std::uint32_t Capacity() const;

		/**
		 * Set number of values and Reserve memory if needed
		 * @Param Size: the new number of values
		 * @Exception: Thrown if attempting to resize external data
		 */
		void SetSize(const std::uint32_t& size) const;

		/**
		 * Reserve additional Capacity for uninitialized values
		 * @Param Capacity: The number of possible elements that the array will be able to hold
		 * @Exception: Thrown if attempting to resize external storage
		 */
		void Reserve(const std::uint32_t& capacity) const;

		/**
		 * Clear the array without shrinking the Capacity
		 * @Exception: Thrown if trying to Clear with an invalid Type Set
		 */
		void Clear() const;

		/**
		 * Sets the external storage to the specified int32_t*
		 * Note: Size on external storage is considered static
		 * @Param data: The specified external storage
		 * @Param Size: The number of elements available in the external storage
		 */
		void SetStorage(std::int32_t* data, const std::uint32_t& size);

		/**
		 * Sets the external storage to the specified float*
		 * Note: Size on external storage is considered static
		 * @Param data: The specified external storage
		 * @Param Size: The number of elements available in the external storage
		 */
		void SetStorage(float* data, const std::uint32_t& size);

		/**
		 * Sets the external storage to the specified glm::vec4*
		 * Note: Size on external storage is considered static
		 * @Param data: The specified external storage
		 * @Param Size: The number of elements available in the external storage
		 */
		void SetStorage(glm::vec4* data, const std::uint32_t& size);

		/**
		 * Sets the external storage to the specified glm::mat4*
		 * Note: Size on external storage is considered static
		 * @Param data: The specified external storage
		 * @Param Size: The number of elements available in the external storage
		 */
		void SetStorage(glm::mat4* data, const std::uint32_t& size);

		/**
		 * Sets the external storage to the specified std::string*
		 * Note: Size on external storage is considered static
		 * @Param data: The specified external storage
		 * @Param Size: The number of elements available in the external storage
		 */
		void SetStorage(std::string* data, const std::uint32_t& size);

		/**
		 * Sets the external storage to the specified RTTI**
		 * Note: Size on external storage is considered static
		 * @Param data: The specified external storage
		 * @Param Size: The number of elements available in the external storage
		 */
		void SetStorage(Library::RTTI** data, const std::uint32_t& size);
		
		/**
		 * Sets a specified index of the array to the specified value
		 * @Param value: The int32_t being assigned
		 * @Param index: The index of the value being assigned to
		 * @Exception invalidType: Thrown if calling Set on invalid Type
		 * @Exception indexOutObBounds: Thrown if attempting to Set beyond existing Size
		 */
		void Set(const std::int32_t& value, const std::uint32_t& index = 0);

		/**
		 * Sets a specified index of the array to the specified value
		 * @Param value: The float being assigned
		 * @Param index: The index of the value being assigned to
		 * @Exception: Thrown if calling Set on invalid Type
		 * @Exception: Thrown if attempting to Set beyond existing Size
		 */
		void Set(const float& value, const std::uint32_t& index = 0);

		/**
		 * Sets a specified index of the array to the specified value
		 * @Param value: The vec4 being assigned
		 * @Param index: The index of the value being assigned to
		 * @Exception: Thrown if calling Set on invalid Type
		 * @Exception: Thrown if attempting to Set beyond existing Size
		 */
		void Set(const glm::vec4& value, const std::uint32_t& index = 0);

		/**
		 * Sets a specified index of the array to the specified value
		 * @Param value: The mat4 being assigned
		 * @Param index: The index of the value being assigned to
		 * @Exception: Thrown if calling Set on invalid Type
		 * @Exception: Thrown if attempting to Set beyond existing Size
		 */
		void Set(const glm::mat4& value, const std::uint32_t& index = 0);

		/**
		 * Sets a specified index of the array to the specified value
		 * @Param value: The scope pointer being assigned
		 * @Param index: The index of the value being assigned to
		 * @Exception: Thrown if calling Set on invalid Type
		 * @Exception: Thrown if attempting to Set beyond existing Size
		 */
		void Set(Scope* const& value, const std::uint32_t& index = 0);

		/**
		 * Sets a specified index of the array to the specified value
		 * @Param value: The string being assigned
		 * @Param index: The index of the value being assigned to
		 * @Exception: Thrown if calling Set on invalid Type
		 * @Exception: Thrown if attempting to Set beyond existing Size
		 */
		void Set(const std::string& value, const std::uint32_t& index = 0);

		/**
		 * Sets a specified index of the array to the specified value
		 * @Param value: The RTTI* being assigned
		 * @Param index: The index of the value being assigned to
		 * @Exception: Thrown if calling Set on invalid Type
		 * @Exception: Thrown if attempting to Set beyond existing Size
		 */
		void Set(Library::RTTI* const& value, const std::uint32_t& index = 0);

		/**
		 * Pushes an std::int32_t to the Back of the array
		 * @Param value: The value being pushed onto the array
		 */
		void PushBack(const std::int32_t& value);

		/**
		 * Pushes an std::int32_t to the Back of the array
		 * @Param value: The value being pushed onto the array
		 */
		void PushBack(const float& value);

		/**
		 * Pushes an std::int32_t to the Back of the array
		 * @Param value: The value being pushed onto the array
		 */
		void PushBack(const glm::vec4& value);

		/**
		 * Pushes an std::int32_t to the Back of the array
		 * @Param value: The value being pushed onto the array
		 */
		void PushBack(const glm::mat4& value);

		/**
		 * Pushes an std::int32_t to the Back of the array
		 * @Param value: The value being pushed onto the array
		 */
		void PushBack(Scope* const& value);

		/**
		 * Pushes an std::int32_t to the Back of the array
		 * @Param value: The value being pushed onto the array
		 */
		void PushBack(const std::string& value);

		/**
		 * Pushes an std::int32_t to the Back of the array
		 * @Param value: The value being pushed onto the array
		 * @Exception: Thrown if attempting to push Back a null value
		 */
		void PushBack(RTTI* const& value);

		/**
		 * Removes a scope from the current datum
		 * @Param scope: The scope being removed
		 */
		void Remove(Scope* const scope);

		
		/**
		 * Parses a string value and sets the value to the specified index
		 * @Param value: The string value being parsed
		 * @Param index: The location being Set to. Default is 0
		 * @Exception: Thrown if syntax is invalid
		 */
		void SetFromString(const std::string& value, const std::uint32_t& index = 0) const;

		/**
		 * A string representation of a piece of data stored in the Datum object
		 * @Param index: Optional index of the value being retrieved. Defaulted to first element
		 * @Exception invalidFormat: Thrown if unable to properly Parse string
		 */
		std::string ToString(const std::uint32_t& index = 0) const;

		/**
		 * Gets the item At the specified index in the array
		 * @Param index: The index of the item being retrieved
		 * @Return: The object At the specified index
		 * @Exception: Thrown if calling Get on invalid Type
		 * @Exception: Thrown if data is null
		 * @Exception: Thrown if index is greater than or equal to current Size
		 */
		template <typename T> T& Get(const std::uint32_t& index = 0);

		/**
		* Gets the item At the specified index in the array
		* @Param index: The index of the item being retrieved
		* @Return: The object At the specified index
		* @Exception: Thrown if calling Get on invalid Type
		* @Exception: Thrown if data is null
		* @Exception: Thrown if index is greater than or equal to current Size
		*/
		template<typename T> const T& Get(const std::uint32_t& index = 0) const;

	private:

		TypeState* mTypeState; // State pattern object. Type-specific tasks will be delegated to this
		DatumType mType; // The Type of the Datum object
		DatumValues mData; // The data union of the Datum object. Can be allocated internally or assigned externally
		std::uint32_t mCapacity; // The number of elements of the Set Type that the Datum can hold
		std::uint32_t mSize; // The current number of elements in the Datum object
		bool mDataIsExternal; // True if data is stored externally of the Datum object
	};
}

#include "Datum.inl"
