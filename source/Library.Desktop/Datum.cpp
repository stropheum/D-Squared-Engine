#include "pch.h"
#include "Datum.h"

namespace Library
{
	/// Constructor
	Datum::Datum():
		mType(DatumType::Unknown), mCapacity(13), mSize(0), mDataIsExternal(false)
	{}

	/// Overloaded constructor
	/// @Param type: The type of the Datum object
	Datum::Datum(DatumType type) :
		mType(type), mCapacity(13), mSize(0), mDataIsExternal(false)
	{}

	/// Destructor
	Datum::~Datum()
	{}

	/// Copy constructor
	/// @Param rhs: Datum object being copied
	Datum::Datum(const Datum& rhs):
		mType(DatumType::Unknown), mCapacity(rhs.mCapacity), mSize(rhs.mSize), mDataIsExternal(rhs.mDataIsExternal)
	{
		switch (rhs.mType)
		{
			case DatumType::Integer:
				setStorage(rhs.mData.i, rhs.mSize);
				break;
			case DatumType::Float:
				setStorage(rhs.mData.f, rhs.mSize);
				break;
			case DatumType::Vector:
				setStorage(rhs.mData.v, rhs.mSize);
				break;
			case DatumType::Matrix:
				setStorage(rhs.mData.m, rhs.mSize);
				break;
			case DatumType::String:
				setStorage(rhs.mData.s, rhs.mSize);
				break;
			case DatumType::Pointer:
				setStorage(rhs.mData.r, rhs.mSize);
				break;
			default:
				throw std::exception("Attempting to set Datum to invalid type");
		}
	}

	/// Move copy constructor
	/// @Param rhs: Datum object being copied
	Datum::Datum(Datum&& rhs) :
		mType(rhs.mType), mCapacity(rhs.mCapacity), mSize(rhs.mSize), mDataIsExternal(rhs.mDataIsExternal)
	{
		// TODO: Handle deep copy semantics
		switch (rhs.mType)
		{
			case DatumType::Integer:
				if (rhs.mData.i != nullptr) free(rhs.mData.i);
				break;
			case DatumType::Float:
				if (rhs.mData.f != nullptr) free(rhs.mData.f);
				break;
			case DatumType::String:
				if (rhs.mData.s != nullptr) free(rhs.mData.s);
				break;
			case DatumType::Pointer:
				if (rhs.mData.r != nullptr) free(rhs.mData.r);
				break;
			default: 
				break;
		}
		rhs.mType = DatumType::Unknown;
		rhs.mCapacity = NULL;
		rhs.mSize = NULL;
	}

	/// Datum assignment operator
	/// @Param rhs: Datum object being assigned to
	/// @Return; The newly copied Datum object
	Datum& Datum::operator=(const Datum& rhs)
	{
		// TODO: Implement datum assignment operator
		UNREFERENCED_PARAMETER(rhs);
		return *this;
	}

	/// Datum move assignment operator
	/// @Param rhs: Datum object being assigned to
	/// @Return: The newly copied Datum object
	Datum& Datum::operator=(Datum&& rhs)
	{
		// TODO: Implement Datum move assignment operator
		UNREFERENCED_PARAMETER(rhs);
		return *this;
	}

	/// Type assignment operator
	/// @Param rhs: DatumType being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to reassign a new type to a Datum object
	Datum& Datum::operator=(const DatumType& rhs)
	{
		setType(rhs);
		return *this;
	}

	/// Assignment operator for std::int32_t
	/// @Param rhs: Integer being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
	Datum& Datum::operator=(const std::int32_t& rhs)
	{
		if (mType != DatumType::Integer || mSize > 1) throw std::exception("Invalid assignment invocation");
		mData.i[0] = rhs;
		return *this;
	}

	/// Assignment operator for float
	/// @Param rhs: Float being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
	Datum& Datum::operator=(const float& rhs)
	{
		if (mType != DatumType::Float || mSize > 1) throw std::exception("Invalid assignment invocation");
		mData.f[0] = rhs;
		return *this;
	}

	/// Assignment operator for std::string
	/// @Param rhs: String being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
	Datum& Datum::operator=(const std::string& rhs)
	{
		if (mType != DatumType::String || mSize > 1) throw std::exception("Invalid assignment invocation");
		mData.s[0] = rhs;
		return *this;
	}

	/// Assignment operator for float
	/// @Param rhs: Float being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
	Datum& Datum::operator=(Library::RTTI* const& rhs)
	{
		if (mType != DatumType::Pointer || mSize > 1) throw std::exception("Invalid assignment invocation");
		mData.r[0] = rhs;
		return *this;
	}

	/// Comparison operator for DatumType value
	/// @Param rhs: The DatumType being compared against
	/// @Return: True if the types are the same
	bool Datum::operator==(const DatumType& rhs) const
	{
		return mType == rhs;
	}

	/// Comparison operator for std::int32_t
	/// @Param rhs: The signed integer being compared against
	/// @Return: True if the integer values are the same. False if size is not 1 or if type is invalid
	bool Datum::operator==(const std::int32_t& rhs) const
	{
		return mType == DatumType::Integer &&
			mSize == 1 && mData.i[0] == rhs;
	}

	/// Comparison operator for float
	/// @Param rhs: The float being compared against
	/// @Return: True if the float values are the same. False if size is not 1 or if type is invalid
	bool Datum::operator==(const float& rhs) const
	{
		return mType == DatumType::Float &&
			mSize == 1 && mData.f[0] == rhs;
	}

	/// Comparison operator for v3c4
	/// @Param rhs: The vector being compared against
	/// @Return: True if the vectors are equivalent. False if size is not 1 or if type is invalid
	bool Datum::operator==(const glm::vec4& rhs) const
	{
		return mType == DatumType::Vector &&
			mSize == 1 && mData.v[0] == rhs;
	}

	/// Comparison operator for mat4
	/// @Param rhs: The matrix being  compared against
	/// @Return: True if the matrices are equivalent. FAlse if size is not 1 or if type is invalid
	bool Datum::operator==(const glm::mat4& rhs) const
	{
		return mType == DatumType::Vector &&
			mSize == 1 && mData.m[0] == rhs;
	}

	/// Comparison operator for std::string
	/// @Param rhs: The string being compared against
	/// @Return: True if the string values are the same. False if size is not 1 or if type is invalid
	bool Datum::operator==(const std::string& rhs) const
	{
		return mType == DatumType::String &&
			mSize == 1 && mData.s[0] == rhs;
	}

	/// Comparison operator for RTTI pointers
	/// @Param rhs: The RTTI pointer being compared against
	/// @Return: True if the pointers are the same. False if size is not 1 or if type is invalid
	bool Datum::operator==(const Library::RTTI*& rhs) const
	{
		return mType == DatumType::Pointer &&
			mSize == 1 && mData.r[0] == rhs;
	}

	/// Inequality operator for DatumType
	/// @Param rhs: The DatumType being compared against
	/// @Return: True if the types are not equivalent
	bool Datum::operator!=(const DatumType& rhs) const
	{
		return !(operator==(rhs));
	}

	/// Inequality operator for std::int32_t
	/// @Param rhs: The integer being compared against
	/// @Return: True if the integers are not equivalent
	bool Datum::operator!=(const std::int32_t& rhs) const
	{
		return !(operator==(rhs));
	}

	/// Inequality operator for float
	/// @Param rhs: The float being compared against
	/// @Return: True if the floats are not equivalent
	bool Datum::operator!=(const float& rhs) const
	{
		return !(operator==(rhs));
	}

	/// Inequality operator for vec4
	/// @Param rhs: The vector being compared against
	/// @Return: True if the vectors are not equivalent
	bool Datum::operator!=(const glm::vec4& rhs) const
	{
		return !(operator==(rhs));
	}

	/// Inequality operator for mat4
	/// @Param rhs: The matrix being compared against
	/// @Return: True if the matrices are not equivalent
	bool Datum::operator!=(const glm::mat4& rhs) const
	{
		return !(operator==(rhs));
	}

	/// Inequality operator for std::string
	/// @Param rhs: The string being compared against
	/// @Return: True if the strings are not equivalent
	bool Datum::operator!=(const std::string& rhs) const
	{
		return !(operator==(rhs));
	}

	/// Inequality operator for RTTI pointer
	/// @Param rhs: The RTTI pointer being compared against
	/// @Return: True if the pointers are not equivalent
	bool Datum::operator!=(const Library::RTTI*& rhs) const
	{
		return !(operator==(rhs));
	}

	/// The type associated with this object
	/// @Return: The DatumType of this Datum object
	DatumType Datum::type() const
	{
		return mType;
	}

	/// Set the DatumType of the Datum object
	/// @Param type: The new type of the Datum object
	/// @Exception: Thrown if attempting to reassign a new type to a Datum object
	void Datum::setType(const DatumType& type)
	{
		if (mType == DatumType::Unknown || mType == type)  mType = type;
		else throw std::exception("Attempting to change type on Datum object");
	}

	/// The number of values in the Datum object
	/// @Return: The number of items associated with this Datum object
	std::uint32_t Datum::size() const
	{
		return mSize;
	}

	/// Set number of values and reserve memory if needed
	/// @Param size: the new number of values
	void Datum::setSize(std::uint32_t size)
	{
		switch (mType)
		{
		case DatumType::Integer:
			setSizeInt(size);
			break;
		case DatumType::Float:
			setSizeFloat(size);
			break;
		case DatumType::String:
			setSizeString(size);
			break;
		case DatumType::Pointer:
			setSizePointer(size);
			break;
		default:
			throw std::exception("Attempting to reserve on uninitialized Datum object");
		}
	}

	/// Clear the array without shrinking the capacity
	void Datum::clear()
	{
		// TODO: Implement clear method
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Pram size: The number of elements in the external storage
	void Datum::setStorage(std::int32_t* data, std::uint32_t size)
	{
		if (mType != DatumType::Unknown) throw std::exception("Attempting to reassign Datum Type");
		mType = DatumType::Integer;
		mData.i = data;
		mSize = size;
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Param size: The number of elements in the external storage
	void Datum::setStorage(float* data, std::uint32_t size)
	{
		if (mType != DatumType::Unknown) throw std::exception("Attempting to reassign Datum Type");
		mType = DatumType::Float;
		mData.f = data;
		mSize = size;
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Param size: The number of elements in the external storage
	void Datum::setStorage(glm::vec4* data, std::uint32_t size)
	{
		if (mType != DatumType::Unknown) throw std::exception("Attempting to reassign Datum Type");
		mType = DatumType::Vector;
		mData.v = data;
		mSize = size;
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Param size: The number of elements in the external storage
	void Datum::setStorage(glm::mat4* data, std::uint32_t size)
	{
		if (mType != DatumType::Unknown) throw std::exception("Attempting to reassign Datum Type");
		mType = DatumType::Matrix;
		mData.m = data;
		mSize = size;
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Pram size: The number of elements in the external storage
	void Datum::setStorage(std::string* data, std::uint32_t size)
	{
		if (mType != DatumType::Unknown) throw std::exception("Attempting to reassign Datum Type");
		mType = DatumType::String;
		mData.s = data;
		mSize = size;
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Pram size: The number of elements in the external storage
	void Datum::setStorage(Library::RTTI** data, std::uint32_t size)
	{
		if (mType != DatumType::Unknown) throw std::exception("Attempting to reassign Datum Type");
		mType = DatumType::Pointer;
		mData.r = data;
		mSize = size;
	}

	/// Sets the value of a given index of the data
	/// @Param value: The value being assigned
	/// @Param index: The index of the value being assigned to
	void Datum::set(const std::int32_t& value, const std::uint32_t index) const
	{
		if (mType != DatumType::Integer) throw std::exception("Calling set on invalid type");
		mData.i[index] = value;
	}

	/// Sets the value of a given index of the data
	/// @Param value: The value being assigned
	/// @Param index: The index of the value being assigned to
	void Datum::set(const float& value, const std::uint32_t index) const
	{
		if (mType != DatumType::Float) throw std::exception("Calling set on invalid type");
		mData.f[index] = value;
	}

	/// Sets the value of a given index of the data
	/// @Param value: The value being assigned
	/// @Param index: The index of the value being assigned to
	void Datum::set(const std::string& value, const std::uint32_t index) const
	{
		if (mType != DatumType::String) throw std::exception("Calling set on invalid type");
		mData.s[index] = value;
	}

	/// Sets the value of a given index of the data
	/// @Param value: The value being assigned
	/// @Param index: The index of the value being assigned to
	void Datum::set(Library::RTTI* const value, const std::uint32_t index) const
	{
		if (mType != DatumType::Pointer) throw std::exception("Calling set on invalid type");
		mData.r[index] = value;
	}

	template<>
	std::int32_t& Datum::get(const std::uint32_t index)
	{
		if (mType != DatumType::Integer) throw std::exception("Calling get on invalid type");
		if (mData.i == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.i[index];
		
	}

	template<>
	float& Datum::get(const std::uint32_t index)
	{
		if (mType != DatumType::Float) throw std::exception("Calling get on invalid type");
		if (mData.f == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.f[index];
		
	}

	template<>
	glm::vec4& Datum::get(const std::uint32_t index)
	{
		if (mType != DatumType::Vector) throw std::exception("Calling get on invalid type");
		if (mData.f == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.v[index];
	}

	template<>
	glm::mat4& Datum::get(const std::uint32_t index)
	{
		if (mType != DatumType::Matrix) throw std::exception("Calling get on invalid type");
		if (mData.f == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.m[index];
	}

	template<>
	std::string& Datum::get(const std::uint32_t index)
	{
		if (mType != DatumType::String) throw std::exception("Calling get on invalid type");
		if (mData.s == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.s[index];
	}

	template<>
	Library::RTTI*& Datum::get(const std::uint32_t index)
	{
		if (mType != DatumType::Pointer) throw std::exception("Calling get on invalid type");
		if (mData.r == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.r[index];
	}

	void Datum::setFromString(std::string value)
	{
		// TODO: Implement setFromString method
		UNREFERENCED_PARAMETER(value);
	}

	std::string Datum::toString()
	{
		return "I didn't do the thing yet";
	}

	/// Reserves the number of integers in the local buffer
	/// @Param capacity: The current maximum size of the array
	void Datum::setSizeInt(std::uint32_t capacity)
	{
		if (capacity < mSize) capacity = mSize;

		std::int32_t* temp = mData.i;
		mData.i = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * capacity));
		memcpy_s(mData.i, sizeof(std::int32_t) * mSize, temp, sizeof(std::int32_t) * mSize);

		free(temp);
		mCapacity = capacity;
	}

	/// Reserves the number of floats in the local buffer
	/// @Param capacity: The current maximum size of the array
	void Datum::setSizeFloat(std::uint32_t capacity)
	{
		if (capacity < mSize) capacity = mSize;

		std::int32_t* temp = mData.i;
		mData.i = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * capacity));
		memcpy_s(mData.i, sizeof(std::int32_t) * mSize, temp, sizeof(std::int32_t) * mSize);

		free(temp);
		mCapacity = capacity;
	}

	/// Reserves the number of strings in the local buffer
	/// @Param capacity: The current maximum size of the array
	void Datum::setSizeString(std::uint32_t capacity)
	{
		if (capacity < mSize) capacity = mSize;

		std::int32_t* temp = mData.i;
		mData.i = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * capacity));
		memcpy_s(mData.i, sizeof(std::int32_t) * mSize, temp, sizeof(std::int32_t) * mSize);

		free(temp);
		mCapacity = capacity;
	}

	/// Reserves the number of RTTI pointers in the local buffer
	/// @Param capacity: The current maximum size of the array
	void Datum::setSizePointer(std::uint32_t capacity)
	{
		if (capacity < mSize) capacity = mSize;

		std::int32_t* temp = mData.i;
		mData.i = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * capacity));
		memcpy_s(mData.i, sizeof(std::int32_t) * mSize, temp, sizeof(std::int32_t) * mSize);

		free(temp);
		mCapacity = capacity;
	}
}
