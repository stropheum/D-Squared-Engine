#include "pch.h"
#include "Datum.h"

namespace Library
{
	/// Constructor
	Datum::Datum():
		mTypeState(nullptr), mType(DatumType::Unknown), mCapacity(0), mSize(0), mDataIsExternal(false)
	{}

	/// Overloaded constructor
	/// @Param type: The type of the Datum object
	Datum::Datum(DatumType type) :
		mTypeState(nullptr), mType(type), mCapacity(1), mSize(0), mDataIsExternal(false)
	{
		// Reserve size of 1
	}

	/// Destructor
	Datum::~Datum()
	{
		switch (mType)
		{
			case DatumType::Integer:
				// TODO: Clear int values
				break;
			case DatumType::Float:
				// TODO: Clear float values
				break;
			case DatumType::Vector:
				// TODO: Clear vector values
				break;
			case DatumType::Matrix:
				// TODO: Clear matrix values
				break;
			case DatumType::String:
				// TODO: Clear string values
				break;
			case DatumType::Pointer:
				// TODO: Clear pointer values
				break;
			default: ;
		}
	}

	/// Copy constructor
	/// @Param rhs: Datum object being copied
	/// @Exception: Thrown if attempting to construct a non-existing datum type
	Datum::Datum(const Datum& rhs):
		mType(DatumType::Unknown), mCapacity(rhs.mCapacity), mSize(rhs.mSize), mDataIsExternal(rhs.mDataIsExternal)
	{
		if (rhs.mDataIsExternal) mData = rhs.mData; // If storage is external, only shallow copy the pointer
		else
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
	}

	/// Move copy constructor
	/// @Param rhs: Datum object being copied
	Datum::Datum(Datum&& rhs) :
		mTypeState(nullptr), mType(rhs.mType), mCapacity(rhs.mCapacity), mSize(rhs.mSize), mDataIsExternal(rhs.mDataIsExternal)
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
		setType(DatumType::Integer);
		return mTypeState->operator=(rhs);
	}

	/// Assignment operator for float
	/// @Param rhs: Float being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
	Datum& Datum::operator=(const float& rhs)
	{
		setType(DatumType::Float);
		return mTypeState->operator=(rhs);
	}

	/// Assignment operator for vec4
	/// @Param rhs: Vector being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
	Datum& Datum::operator=(const glm::vec4& rhs)
	{
		setType(DatumType::Vector);
		return mTypeState->operator=(rhs);
	}

	/// Assignment operator for mat4
	/// @Param rhs: Matrix being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
	Datum& Datum::operator=(const glm::mat4& rhs)
	{
		setType(DatumType::Matrix);
		return mTypeState->operator=(rhs);
	}

	/// Assignment operator for std::string
	/// @Param rhs: String being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
	Datum& Datum::operator=(const std::string& rhs)
	{
		setType(DatumType::String);
		return mTypeState->operator=(rhs);
	}

	/// Assignment operator for float
	/// @Param rhs: Float being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
	Datum& Datum::operator=(Library::RTTI* const& rhs)
	{
		setType(DatumType::Pointer);
		return mTypeState->operator=(rhs);
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
		return mType == DatumType::Matrix &&
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
	bool Datum::operator==(Library::RTTI* const& rhs) const
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
	bool Datum::operator!=(Library::RTTI* const& rhs) const
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
		if (mType == type) return; // Avoid double instantiation of state without throwing an exception
		
		if (mType == DatumType::Unknown) mType = type;
		else throw std::exception("Attempting to change type on Datum object");
		
		switch (mType)
		{
			case DatumType::Integer:
				mTypeState = new IntegerState(this);
				break;
			case DatumType::Float:
				mTypeState = new FloatState(this);
				break;
			case DatumType::Vector:
				mTypeState = new VectorState(this);
				break;
			case DatumType::Matrix:
				mTypeState = new MatrixState(this);
				break;
			case DatumType::String:
				mTypeState = new StringState(this);
				break;
			case DatumType::Pointer:
				mTypeState = new PointerState(this);
				break;
			default: throw std::exception("Invalid type assignment");
		}
	}

	/// The number of values in the Datum object
	/// @Return: The number of items associated with this Datum object
	std::uint32_t Datum::size() const
	{
		return mSize;
	}

	/// The number of potential values in the Datum object
	/// @Return: The number of objects that can currently be stored in the Datum object
	std::uint32_t Datum::capacity() const
	{
		return mCapacity;
	}

	/// Set number of values and reserve memory if needed
	/// @Param size: the new number of values
	/// @Exception: Thrown if attempting to resize external data
	void Datum::setSize(std::uint32_t size)
	{
		if (mDataIsExternal) throw std::exception("Attempting to resize external storage");
		mTypeState->setSize(size);
	}

	/// Reserve additional capacity for uninitialized values
	/// @Param capacity: The number of possible elements that the array will be able to hold
	/// @Exception: Thrown if attempting to resize external storage
	void Datum::reserve(std::uint32_t capacity)
	{
		if (mDataIsExternal) throw std::exception("Attempting to resize external storage");
		mTypeState->reserve(capacity);
	}

	/// Clear the array without shrinking the capacity
	/// @Exception: Thrown if trying to clear with an invalid type set
	void Datum::clear()
	{
		mTypeState->clear();
//		switch(mType)
//		{
//			case DatumType::Integer:
//				clearInt();
//				break;
//			case DatumType::Float:
//				clearFloat();
//				break;
//			case DatumType::Vector:
//				clearVector();
//				break;
//			case DatumType::Matrix:
//				clearMatrix();
//				break;
//			case DatumType::String:
//				clearString();
//				break;
//			case DatumType::Pointer:
//				clearPointer();
//				break;
//			default: throw std::exception("Attempting to clear invalid type");
//		}
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Pram size: The number of elements in the external storage
	/// @Exception: Thrown if attempting to reassign datum type, or if local memory is already used
	void Datum::setStorage(std::int32_t* data, std::uint32_t size)
	{
		if (mType != DatumType::Unknown) throw std::exception("Attempting to reassign Datum Type");
		if (mType == DatumType::Integer && mData.i != nullptr)
			throw std::exception("Attempting to set storage on a non-empty Datum object");
		mDataIsExternal = true;
		mType = DatumType::Integer;
		mData.i = data;
		mCapacity = mSize = size;
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Param size: The number of elements in the external storage
	/// @Exception: Thrown if attempting to reassign datum type, or if local memory is already used
	void Datum::setStorage(float* data, std::uint32_t size)
	{
		if (mType != DatumType::Unknown) throw std::exception("Attempting to reassign Datum Type");
		if (mType == DatumType::Float && mData.f != nullptr)
			throw std::exception("Attempting to set storage on a non-empty Datum object");
		mDataIsExternal = true;
		mType = DatumType::Float;
		mData.f = data;
		mCapacity = mSize = size;
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Param size: The number of elements in the external storage
	/// @Exception: Thrown if attempting to reassign datum type, or if local memory is already used
	void Datum::setStorage(glm::vec4* data, std::uint32_t size)
	{
		if (mType != DatumType::Unknown) throw std::exception("Attempting to reassign Datum Type");
		if (mType == DatumType::Vector && mData.v != nullptr)
			throw std::exception("Attempting to set storage on a non-empty Datum object");
		mDataIsExternal = true;
		mType = DatumType::Vector;
		mData.v = data;
		mCapacity = mSize = size;
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Param size: The number of elements in the external storage
	/// @Exception: Thrown if attempting to reassign datum type, or if local memory is already used
	void Datum::setStorage(glm::mat4* data, std::uint32_t size)
	{
		if (mType != DatumType::Unknown) throw std::exception("Attempting to reassign Datum Type");
		if (mType == DatumType::Matrix && mData.m != nullptr)
			throw std::exception("Attempting to set storage on a non-empty Datum object");
		mDataIsExternal = true;
		mType = DatumType::Matrix;
		mData.m = data;
		mCapacity = mSize = size;
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Pram size: The number of elements in the external storage
	/// @Exception: Thrown if attempting to reassign datum type, or if local memory is already used
	void Datum::setStorage(std::string* data, std::uint32_t size)
	{
		if (mType != DatumType::Unknown) throw std::exception("Attempting to reassign Datum Type");
		if (mType == DatumType::String && mData.s != nullptr)
			throw std::exception("Attempting to set storage on a non-empty Datum object");
		mDataIsExternal = true;
		mType = DatumType::String;
		mData.s = data;
		mCapacity = mSize = size;
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Pram size: The number of elements in the external storage
	/// @Exception: Thrown if attempting to reassign datum type, or if local memory is already used
	void Datum::setStorage(Library::RTTI** data, std::uint32_t size)
	{
		if (mType != DatumType::Unknown) throw std::exception("Attempting to reassign Datum Type");
		if (mType == DatumType::Pointer && mData.r != nullptr)
			throw std::exception("Attempting to set storage on a non-empty Datum object");
		mDataIsExternal = true;
		mType = DatumType::Pointer;
		mData.r = data;
		mCapacity = mSize = size;
	}

	/// Sets a specified index of the array to the specified value
	/// @Param value: The int32_t being assigned
	/// @Param index: The index of the value being assigned to
	/// @Exception invalidType: Thrown if calling set on invalid type
	/// @Exception indexOutObBounds: Thrown if attempting to set beyond existing size
	void Datum::set(const std::int32_t& value, const std::uint32_t index)
	{
		if (mType != DatumType::Integer) throw std::exception("Calling set on invalid type");
		if (index > mSize) throw std::exception("Attempting to set beyond current size");
		if (index == mSize) pushBack(value); // If setting end, divert functionality to a push back
		new(mData.i + index) std::int32_t(value);
	}

	/// Sets a specified index of the array to the specified value
	/// @Param value: The float being assigned
	/// @Param index: The index of the value being assigned to
	/// @Exception: Thrown if calling set on invalid type
	/// @Exception: Thrown if attempting to set beyond existing size
	void Datum::set(const float& value, const std::uint32_t index)
	{
		if (mType != DatumType::Float) throw std::exception("Calling set on invalid type");
		if (index > mSize) throw std::exception("Attempting to set beyond current size");
		if (index == mSize) pushBack(value); // If setting end, divert functionality to a push back
		new(mData.f + index) float(value);
	}

	/// Sets a specified index of the array to the specified value
	/// @Param value: The vec4 being assigned
	/// @Param index: The index of the value being assigned to
	/// @Exception: Thrown if calling set on invalid type
	/// @Exception: Thrown if attempting to set beyond existing size
	void Datum::set(const glm::vec4& value, const std::uint32_t index)
	{
		if (mType != DatumType::Vector) throw std::exception("Calling set on invalid type");
		if (index > mSize) throw std::exception("Attempting to set beyond current size");
		if (index == mSize) pushBack(value); // If setting end, divert functionality to a push back
		new(mData.v + index) glm::vec4(value);
	}

	/// Sets a specified index of the array to the specified value
	/// @Param value: The mat4 being assigned
	/// @Param index: The index of the value being assigned to
	/// @Exception: Thrown if calling set on invalid type
	/// @Exception: Thrown if attempting to set beyond existing size
	void Datum::set(const glm::mat4& value, const std::uint32_t index)
	{
		if (mType != DatumType::Matrix) throw std::exception("Calling set on invalid type");
		if (index > mSize) throw std::exception("Attempting to set beyond current size");
		if (index == mSize) pushBack(value); // If setting end, divert functionality to a push back
		new(mData.m + index) glm::mat4(value);
	}

	/// Sets a specified index of the array to the specified value
	/// @Param value: The string being assigned
	/// @Param index: The index of the value being assigned to
	/// @Exception: Thrown if calling set on invalid type
	/// @Exception: Thrown if attempting to set beyond existing size
	void Datum::set(const std::string& value, const std::uint32_t index)
	{
		if (mType != DatumType::String) throw std::exception("Calling set on invalid type");
		if (index > mSize) throw std::exception("Attempting to set beyond current size");
		if (index == mSize) pushBack(value); // If setting end, divert functionality to a push back
		new(mData.s + index) std::string(value);
	}

	/// Sets a specified index of the array to the specified value
	/// @Param value: The RTTI* being assigned
	/// @Param index: The index of the value being assigned to
	/// @Exception: Thrown if calling set on invalid type
	/// @Exception: Thrown if attempting to set beyond existing size
	void Datum::set(Library::RTTI* const& value, const std::uint32_t index)
	{
		if (mType != DatumType::Pointer) throw std::exception("Calling set on invalid type");
		if (index > mSize) throw std::exception("Attempting to set beyond current size");
		if (index == mSize) pushBack(value); // If setting end, divert functionality to a push back
		new(mData.r + index) RTTI*(value);
	}

	/// Pushes an std::int32_t to the back of the array
	/// @Param value: The value being pushed onto the array
	void Datum::pushBack(const std::int32_t& value)
	{
		setSize(mSize + 1);
		set(value, mSize - 1);
	}

	/// Pushes an std::int32_t to the back of the array
	/// @Param value: The value being pushed onto the array
	void Datum::pushBack(const float& value)
	{
		setSize(mSize + 1);
		set(value, mSize - 1);
	}

	/// Pushes an std::int32_t to the back of the array
	/// @Param value: The value being pushed onto the array
	void Datum::pushBack(const glm::vec4& value)
	{
		setSize(mSize + 1);
		set(value, mSize - 1);
	}

	/// Pushes an std::int32_t to the back of the array
	/// @Param value: The value being pushed onto the array
	void Datum::pushBack(const glm::mat4& value)
	{
		setSize(mSize + 1);
		set(value, mSize - 1);
	}

	/// Pushes an std::int32_t to the back of the array
	/// @Param value: The value being pushed onto the array
	void Datum::pushBack(const std::string& value)
	{
		setSize(mSize + 1);
		set(value, mSize - 1);
	}

	/// Pushes an std::int32_t to the back of the array
	/// @Param value: The value being pushed onto the array
	/// @Exception: Thrown if attempting to push back a null value
	void Datum::pushBack(RTTI* const& value)
	{
		if (value == nullptr) throw std::exception("Attempting to push back nullptr");
		setSize(mSize + 1);
		set(value, mSize - 1);
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

	/// Parses a string value and sets the value to the specified index
	/// @Param value: The string value being parsed
	/// @Param index: The location being set to. Default is 0
	/// @Exception: Thrown if syntax is invalid
	void Datum::setFromString(const std::string& value, const std::uint32_t& index)
	{
		// TODO: Divert this functionality to mTypeState
		switch (mType)
		{
			case DatumType::Unknown:
				setFromStringInt(value, index);
				break;
			case DatumType::Integer:
				setFromStringFloat(value, index);
				break;
			case DatumType::Float:
				setFromStringFloat(value, index);
				break;
			case DatumType::Vector:
				setFromStringVector(value, index);
				break;
			case DatumType::Matrix:
				setFromStringMatrix(value, index);
				break;
			case DatumType::String:
				setFromStringString(value, index);
				break;
			case DatumType::Pointer:
				setFromStringPointer(value, index);
				break;
			default: throw std::exception("Invalid syntax");
		}
	}

	std::string Datum::toString()
	{
		std::string result = "";
		// TODO: Implement toString		
		return result;
	}

	void Datum::setFromStringInt(const std::string& value, const std::uint32_t& index)
	{
		UNREFERENCED_PARAMETER(value);
		UNREFERENCED_PARAMETER(index);
	}

	void Datum::setFromStringFloat(const std::string& value, const std::uint32_t& index)
	{
		UNREFERENCED_PARAMETER(value);
		UNREFERENCED_PARAMETER(index);
	}

	void Datum::setFromStringVector(const std::string& value, const std::uint32_t& index)
	{
		UNREFERENCED_PARAMETER(value);
		UNREFERENCED_PARAMETER(index);
	}

	void Datum::setFromStringMatrix(const std::string& value, const std::uint32_t& index)
	{
		UNREFERENCED_PARAMETER(value);
		UNREFERENCED_PARAMETER(index);
	}

	void Datum::setFromStringString(const std::string& value, const std::uint32_t& index)
	{
		UNREFERENCED_PARAMETER(value);
		UNREFERENCED_PARAMETER(index);
	}

	void Datum::setFromStringPointer(const std::string& value, const std::uint32_t& index)
	{
		UNREFERENCED_PARAMETER(value);
		UNREFERENCED_PARAMETER(index);
	}
}
