#pragma once

#include "RTTI.h"

#define CLM_FORCE_CXX98
#pragma warning(push)
#pragma warning(disable:4201)
#include "glm/glm.hpp"
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

		bool operator==(const DatumType& rhs) const;
		bool operator==(const std::int32_t& rhs) const;
		bool operator==(const float& rhs) const;
		bool operator==(const glm::vec4& rhs) const;
		bool operator==(const glm::mat4& rhs) const;
		bool operator==(const std::string& rhs) const;
		bool operator==(Library::RTTI* const& rhs) const;

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
		std::string toString();

	private:
		void clearInt();
		void clearFloat();
		void clearVector();
		void clearMatrix();
		void clearString();
		void clearPointer();

		void setSizeInt(std::uint32_t size);
		void setSizeFloat(std::uint32_t size);
		void setSizeVector(std::uint32_t size);
		void setSizeMatrix(std::uint32_t size);
		void setSizeString(std::uint32_t size);
		void setSizePointer(std::uint32_t size);

		void reserveInt(std::uint32_t capacity);
		void reserveFloat(std::uint32_t capacity);
		void reserveVector(std::uint32_t capacity);
		void reserveMatrix(std::uint32_t capacity);
		void reserveString(std::uint32_t capacity);
		void reservePointer(std::uint32_t capacity);

		void setFromStringInt(const std::string& value, const std::uint32_t& index = 0);
		void setFromStringFloat(const std::string& value, const std::uint32_t& index = 0);
		void setFromStringVector(const std::string& value, const std::uint32_t& index = 0);
		void setFromStringMatrix(const std::string& value, const std::uint32_t& index = 0);
		void setFromStringString(const std::string& value, const std::uint32_t& index = 0);
		void setFromStringPointer(const std::string& value, const std::uint32_t& index = 0);
		
		DatumType mType;
		DatumValues mData;
		std::uint32_t mCapacity;
		std::uint32_t mSize;
		bool mDataIsExternal;
	};
}
