#include "pch.h"
#include "Datum.h"

namespace Library
{
	/// Constructor
	Datum::Datum() :
		mTypeState(nullptr), mType(DatumType::Unknown), mCapacity(0), mSize(0), mDataIsExternal(false)
	{}

	/// Overloaded constructor
	/// @Param type: The type of the Datum object
	Datum::Datum(DatumType type) :
		mTypeState(nullptr), mType(DatumType::Unknown), mCapacity(0), mSize(0), mDataIsExternal(false)
	{
		setType(type);
		reserve(mCapacity);
	}

	/// Destructor
	Datum::~Datum()
	{
		if (mCapacity > 0 && !mDataIsExternal)
		{	// Don't bother clearing memory if there isn't any reserved space
			setSize(0); // Remove all elements, allowing us to shrink buffer to zero
			reserve(0); // Reserve frees the old buffer and allocates new size (of nothing)
		}
	}

	/// Copy constructor
	/// @Param rhs: Datum object being copied
	/// @Exception: Thrown if attempting to construct a non-existing datum type
	Datum::Datum(const Datum& rhs) :
		mTypeState(nullptr), mType(DatumType::Unknown), mCapacity(0), mSize(0), mDataIsExternal(false)
	{
		operator=(rhs); // Perform a deep copy of all the data
	}

	/// Move copy constructor
	/// @Param rhs: Datum object being copied
	Datum::Datum(Datum&& rhs) :
		mTypeState(nullptr), mType(DatumType::Unknown), mCapacity(0), mSize(0), mDataIsExternal(false)
	{
		operator=(std::move(rhs)); // Perform a deep copy of all the data
	}

	/// Datum assignment operator
	/// @Param rhs: Datum object being assigned to
	/// @Return; The newly copied Datum object
	Datum& Datum::operator=(const Datum& rhs)
	{	
		setType(rhs.mType); // Must set type in order to instantiate mTypeState
		if (rhs.mDataIsExternal)
		{
			mTypeState->setStorage(rhs);
		}
		else
		{
			reserve(rhs.mCapacity);
			switch (rhs.mType)
			{
				case DatumType::Integer:
					for (std::uint32_t i = 0; i < rhs.mSize; i++)
					{
						pushBack(const_cast<Datum&>(rhs).get<std::int32_t>(i));
					}
					break;
				case DatumType::Float:
					for (std::uint32_t i = 0; i < rhs.mSize; i++)
					{
						pushBack(const_cast<Datum&>(rhs).get<float>(i));
					}
					break;
				case DatumType::Vector:
					for (std::uint32_t i = 0; i < rhs.mSize; i++)
					{
						pushBack(const_cast<Datum&>(rhs).get<glm::vec4>(i));
					}
					break;
				case DatumType::Matrix:
					for (std::uint32_t i = 0; i < rhs.mSize; i++)
					{
						pushBack(const_cast<Datum&>(rhs).get<glm::mat4>(i));
					}
					break;
				case DatumType::String:
					for (std::uint32_t i = 0; i < rhs.mSize; i++)
					{
						pushBack(const_cast<Datum&>(rhs).get<std::string>(i));
					}
					break;
				case DatumType::Pointer:
					for (std::uint32_t i = 0; i < rhs.mSize; i++)
					{
						pushBack(const_cast<Datum&>(rhs).get<Library::RTTI*>(i));
					}
					break;
				default: break;
			}
		}

		return *this;
	}

	/// Datum move assignment operator
	/// @Param rhs: Datum object being assigned to
	/// @Return: The newly copied Datum object
	Datum& Datum::operator=(Datum&& rhs)
	{	
		setType(rhs.mType); // Must set type in order to instantiate mTypeState
		if (rhs.mDataIsExternal)
		{
			mTypeState->setStorage(rhs);
		}
		else
		{
			switch (rhs.mType)
			{	// Destroy all the data in rhs
				case DatumType::Integer:
					for (std::uint32_t i = 0; i < rhs.mSize; i++)
					{
						pushBack(const_cast<Datum&>(rhs).get<std::int32_t>(i));
					}
					if (rhs.mData.i != nullptr) free(rhs.mData.i);
					break;
				case DatumType::Float:
					for (std::uint32_t i = 0; i < rhs.mSize; i++)
					{
						pushBack(const_cast<Datum&>(rhs).get<float>(i));
					}
					if (rhs.mData.f != nullptr) free(rhs.mData.f);
					break;
				case DatumType::Vector:
					for (std::uint32_t i = 0; i < rhs.mSize; i++)
					{
						pushBack(const_cast<Datum&>(rhs).get<glm::vec4>(i));
					}
					if (rhs.mData.v != nullptr) free(rhs.mData.v);
					break;
				case DatumType::Matrix:
					for (std::uint32_t i = 0; i < rhs.mSize; i++)
					{
						pushBack(const_cast<Datum&>(rhs).get<glm::mat4>(i));
					}
					if (rhs.mData.m != nullptr) free(rhs.mData.m);
					break;
				case DatumType::String:
					for (std::uint32_t i = 0; i < rhs.mSize; i++)
					{
						pushBack(const_cast<Datum&>(rhs).get<std::string>(i));
					}
					if (rhs.mCapacity > 0)
					{
						rhs.setSize(0);
						rhs.reserve(0);
					};
					break;
				case DatumType::Pointer:
					for (std::uint32_t i = 0; i < rhs.mSize; i++)
					{
						pushBack(const_cast<Datum&>(rhs).get<Library::RTTI*>(i));
					}
					if (rhs.mData.r != nullptr) free(rhs.mData.r);
					break;
				default:
					break;
			}
		}

		rhs.mType = DatumType::Unknown;
		rhs.mCapacity = NULL;
		rhs.mSize = NULL;

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
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		setType(DatumType::Integer);
		return mTypeState->operator=(rhs);
	}

	/// Assignment operator for float
	/// @Param rhs: Float being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
	Datum& Datum::operator=(const float& rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		setType(DatumType::Float);
		return mTypeState->operator=(rhs);
	}

	/// Assignment operator for vec4
	/// @Param rhs: Vector being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
	Datum& Datum::operator=(const glm::vec4& rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		setType(DatumType::Vector);
		return mTypeState->operator=(rhs);
	}

	/// Assignment operator for mat4
	/// @Param rhs: Matrix being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
	Datum& Datum::operator=(const glm::mat4& rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		setType(DatumType::Matrix);
		return mTypeState->operator=(rhs);
	}

	/// Assignment operator for Scope
	/// @Param rhs: Scope being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
	Datum& Datum::operator=(Scope* const rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		setType(DatumType::Scope);
		return mTypeState->operator=(rhs);
	}

	/// Assignment operator for std::string
	/// @Param rhs: String being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
	Datum& Datum::operator=(const std::string& rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		setType(DatumType::String);
		return mTypeState->operator=(rhs);
	}

	/// Assignment operator for float
	/// @Param rhs: Float being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum type or if size is greater than 1
	Datum& Datum::operator=(Library::RTTI* const& rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		setType(DatumType::Pointer);
		return mTypeState->operator=(rhs);
	}

	/// Comparison operator for Datum objects
	/// @Param rhs: The Datum object being compared against
	/// @Return: True if the Datum objects are equivalent
	bool Datum::operator==(const Datum& rhs) const
	{
		return mTypeState->operator==(rhs);
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

	/// Inequality operator for Datum
	/// @Param rhs: The Datum object being compared against
	/// @Return: True if the Datum objects are not equivalent
	bool Datum::operator!=(const Datum& rhs) const
	{
		return !(mTypeState->operator==(rhs));
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
	}

	/// Sets the external storage to the specified int32_t*
	/// Note: Size on external storage is considered static
	/// @Param data: The specified external storage
	/// @Param size: The number of elements available in the external storage
	void Datum::setStorage(std::int32_t* data, std::uint32_t size)
	{
		if (mTypeState != nullptr) return mTypeState->setStorage(data, size);
		setType(DatumType::Integer);
		mTypeState->setStorage(data, size);
	}

	/// Sets the external storage to the specified float*
	/// Note: Size on external storage is considered static
	/// @Param data: The specified external storage
	/// @Param size: The number of elements available in the external storage
	void Datum::setStorage(float* data, std::uint32_t size)
	{
		if (mTypeState != nullptr) return mTypeState->setStorage(data, size);
		setType(DatumType::Float);
		mTypeState->setStorage(data, size);
	}

	/// Sets the external storage to the specified glm::vec4*
	/// Note: Size on external storage is considered static
	/// @Param data: The specified external storage
	/// @Param size: The number of elements available in the external storage
	void Datum::setStorage(glm::vec4* data, std::uint32_t size)
	{
		if (mTypeState != nullptr) return mTypeState->setStorage(data, size);
		setType(DatumType::Vector);
		mTypeState->setStorage(data, size);
	}

	/// Sets the external storage to the specified glm::mat4*
	/// Note: Size on external storage is considered static
	/// @Param data: The specified external storage
	/// @Param size: The number of elements available in the external storage
	void Datum::setStorage(glm::mat4* data, std::uint32_t size)
	{
		if (mTypeState != nullptr) return mTypeState->setStorage(data, size);
		setType(DatumType::Matrix);
		mTypeState->setStorage(data, size);
	}

	/// Sets the external storage to the specified std::string*
	/// Note: Size on external storage is considered static
	/// @Param data: The specified external storage
	/// @Param size: The number of elements available in the external storage
	void Datum::setStorage(std::string* data, std::uint32_t size)
	{
		if (mTypeState != nullptr) return mTypeState->setStorage(data, size);
		setType(DatumType::String);
		mTypeState->setStorage(data, size);
	}

	/// Sets the external storage to the specified RTTI**
	/// Note: Size on external storage is considered static
	/// @Param data: The specified external storage
	/// @Param size: The number of elements available in the external storage
	void Datum::setStorage(Library::RTTI** data, std::uint32_t size)
	{
		if (mTypeState != nullptr) return mTypeState->setStorage(data, size);
		setType(DatumType::Pointer);
		mTypeState->setStorage(data, size);
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

	/// Parses a string value and sets the value to the specified index
	/// @Param value: The string value being parsed
	/// @Param index: The location being set to. Default is 0
	/// @Exception: Thrown if syntax is invalid
	void Datum::setFromString(const std::string& value, const std::uint32_t& index)
	{
		mTypeState->setFromString(value, index);
	}

	/// A string representation of a piece of data stored in the Datum object
	/// @Param index: Optional index of the value being retrieved. Defaulted to first element
	/// @Exception invalidFormat: Thrown if unable to properly parse string
	std::string Datum::toString(std::uint32_t index)
	{	
		return mTypeState->toString(index);
	}
}