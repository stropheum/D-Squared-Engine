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
			std::uint32_t* i;
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
		// TODO: Overload assignment operator to take a rhs of each data type
		Datum& operator=(const Datum& rhs);
		Datum& operator=(Datum&& rhs);
		Datum& operator=(const DatumType& rhs);
		Datum& operator=(const std::uint32_t& rhs);
		Datum& operator=(const float& rhs);
		Datum& operator=(const std::string& rhs);
		Datum& operator=(const Library::RTTI*& rhs);

		bool operator==(const Datum& rhs) const;
		bool operator==(const DatumType& rhs);
		bool operator==(const std::uint32_t& rhs);
		bool operator==(const float& rhs);
		bool operator==(const std::string& rhs);
		bool operator==(const Library::RTTI*& rhs);

		bool operator!=(const Datum& rhs) const;
		bool operator!=(const DatumType& rhs);
		bool operator!=(const std::uint32_t& rhs);
		bool operator!=(const float& rhs);
		bool operator!=(const std::string& rhs);
		bool operator!=(const Library::RTTI*& rhs);

		DatumType type() const;
		void setType(const DatumType& type);
		std::uint32_t size() const;
		void setSize(std::uint32_t size);
		void clear();
		// TODO: Declare setStorage()
		// TODO: Declare set();
		// TODO: Declare get();
		template <typename T> T& get(const std::uint32_t index = 0);
		// TODO: Declare setFromString()
		// TODO: Declare toString();
	private:
		void reserve(std::uint32_t capacity);
		
		DatumType mType;
		Values mData;
		std::uint32_t mCapacity;
		std::uint32_t mSize;
		bool mDataIsExternal;
	};
}
