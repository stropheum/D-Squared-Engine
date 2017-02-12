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
	/// Types of possible Datum
	enum class DatumType
	{
		Unknown, // Type not specified
		Integer, // Unsigned 
		Float,   // Single-precision floating-point value
		Vector,  // 4-vector
		Matrix,  // 4x4 matrix
		Table,   // Pointer to a scope
		String,  // STL string
		Pointer  // Pointer to any RTTI instance
	};

	class Datum
	{
		friend class TypeState;
		friend class IntegerState;
		friend class FloatState;
		friend class VectorState;
		friend class MatrixState;
		friend class StringState;
		friend class PointerState;
		
	public:
		union DatumValues
		{
			void* vp; // Void pointer member for when type doesn't matter
			std::int32_t* i;
			float* f;
			glm::vec4* v;
			glm::mat4* m;
			std::string* s;
			Library::RTTI** r;
		};

		Datum();
		Datum(DatumType type);
		~Datum();
		Datum(const Datum& rhs);
		Datum(Datum&& rhs);
		
		Datum& operator=(const Datum& rhs);
		Datum& operator=(Datum&& rhs);
		Datum& operator=(const DatumType& rhs);
		Datum& operator=(const std::int32_t& rhs);
		Datum& operator=(const float& rhs);
		Datum& operator=(const glm::vec4& rhs);
		Datum& operator=(const glm::mat4& rhs);
		Datum& operator=(const std::string& rhs);
		Datum& operator=(Library::RTTI* const& rhs);

		bool operator==(const Datum& rhs) const;
		bool operator==(const DatumType& rhs) const;
		bool operator==(const std::int32_t& rhs) const;
		bool operator==(const float& rhs) const;
		bool operator==(const glm::vec4& rhs) const;
		bool operator==(const glm::mat4& rhs) const;
		bool operator==(const std::string& rhs) const;
		bool operator==(Library::RTTI* const& rhs) const;

		bool operator!=(const Datum& rhs) const;
		bool operator!=(const DatumType& rhs) const;
		bool operator!=(const std::int32_t& rhs) const;
		bool operator!=(const float& rhs) const;
		bool operator!=(const glm::vec4& rhs) const;
		bool operator!=(const glm::mat4& rhs) const;
		bool operator!=(const std::string& rhs) const;
		bool operator!=(Library::RTTI* const& rhs) const;

		DatumType type() const;
		void setType(const DatumType& type);
		std::uint32_t size() const;
		std::uint32_t capacity() const;
		void setSize(std::uint32_t size);
		void reserve(std::uint32_t capacity);
		void clear();

		void setStorage(std::int32_t* data, std::uint32_t size);
		void setStorage(float* data, std::uint32_t size);
		void setStorage(glm::vec4* data, std::uint32_t size);
		void setStorage(glm::mat4* data, std::uint32_t size);
		void setStorage(std::string* data, std::uint32_t size);
		void setStorage(Library::RTTI** data, std::uint32_t size);
		
		void set(const std::int32_t& value, const std::uint32_t index = 0);
		void set(const float& value, const std::uint32_t index = 0);
		void set(const glm::vec4& value, const std::uint32_t index = 0);
		void set(const glm::mat4& value, const std::uint32_t index = 0);
		void set(const std::string& value, const std::uint32_t index = 0);
		void set(Library::RTTI* const& value, const std::uint32_t index = 0);

		void pushBack(const std::int32_t& value);
		void pushBack(const float& value);
		void pushBack(const glm::vec4& value);
		void pushBack(const glm::mat4& value);
		void pushBack(const std::string& value);
		void pushBack(RTTI* const& value);

		/// Gets the item at the specified index in the array
		/// @Param index: The index of the item being retrieved
		/// @Return: The object at the specified index
		/// @Exception: Thrown if calling get on invalid type
		/// @Exception: Thrown if data is null
		/// @Exception: Thrown if index is greater than or equal to current size
		template <typename T> T& get(const std::uint32_t index = 0);
		
		void setFromString(const std::string& value, const std::uint32_t& index = 0);
		std::string toString(std::uint32_t index = 0);

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
