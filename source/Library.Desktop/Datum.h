#pragma once
#include "RTTI.h"

namespace Datum
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
		union Values
		{
			std::int32_t* i;
			float* f;
			// Vector;
			// Matrix
			// Table
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
		Datum& operator=(const std::string& rhs);
		Datum& operator=(Library::RTTI* const& rhs);

		bool operator==(const DatumType& rhs) const;
		bool operator==(const std::int32_t& rhs) const;
		bool operator==(const float& rhs) const;
		bool operator==(const std::string& rhs) const;
		bool operator==(const Library::RTTI*& rhs) const;

		bool operator!=(const DatumType& rhs) const;
		bool operator!=(const std::int32_t& rhs) const;
		bool operator!=(const float& rhs) const;
		bool operator!=(const std::string& rhs) const;
		bool operator!=(const Library::RTTI*& rhs) const;

		DatumType type() const;
		void setType(const DatumType& type);
		std::uint32_t size() const;
		void setSize(std::uint32_t size);
		void clear();

		void setStorage(std::int32_t* data, std::uint32_t size);
		void setStorage(float* data, std::uint32_t size);
		void setStorage(std::string* data, std::uint32_t size);
		void setStorage(Library::RTTI** data, std::uint32_t size);
		
		void set(const std::int32_t& value, const std::uint32_t index = 0) const;
		void set(const float& value, const std::uint32_t index = 0) const;
		void set(const std::string& value, const std::uint32_t index = 0) const;
		void set(Library::RTTI* const value, const std::uint32_t index = 0) const;

		template <typename T> T& get(const std::uint32_t index = 0);
		
		void setFromString(std::string value);
		std::string toString();
	private:
		void reserve(std::uint32_t capacity);
		
		DatumType mType;
		Values mData;
		std::uint32_t mCapacity;
		std::uint32_t mSize;
		bool mDataIsExternal;
	};
}
