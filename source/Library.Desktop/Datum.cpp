#include "pch.h"
#include "Datum.h"
#include "ScopeState.h"
#include "Scope.h"

namespace Library
{
	/// Constructor
	Datum::Datum() :
		mTypeState(nullptr), mType(DatumType::Unknown), mCapacity(0), mSize(0), mDataIsExternal(false)
	{
	}

	/// Overloaded constructor
	/// @Param Type: The Type of the Datum object
	Datum::Datum(DatumType type) :
		mTypeState(nullptr), mType(DatumType::Unknown), mCapacity(0), mSize(0), mDataIsExternal(false)
	{
		SetType(type);
		if (type != DatumType::Unknown) Reserve(mCapacity);
	}

	/// Destructor
	Datum::~Datum()
	{
		if (mCapacity > 0 && !mDataIsExternal)
		{	// Don't bother clearing memory if there isn't any reserved space
			SetSize(0); // Remove all elements, allowing us to shrink buffer to zero
		}

		delete mTypeState;
	}

	/// Copy constructor
	/// @Param rhs: Datum object being copied
	/// @Exception: Thrown if attempting to construct a non-existing datum Type
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

	/// Index operator for accessing nested scopes
	/// @Param index: The scope At the given index
	/// @Return: The scope At the specified index
	Scope& Datum::operator[](std::uint32_t index)
	{
		return *Get<Scope*>(index);
	}

	/// Datum assignment operator
	/// @Param rhs: Datum object being assigned to
	/// @Return; The newly copied Datum object
	Datum& Datum::operator=(const Datum& rhs)
	{	
		if (this != &rhs)
		{
			
			SetType(rhs.mType); // Must Set Type in order to instantiate mTypeState
			if (rhs.mDataIsExternal)
			{
				mTypeState->SetStorage(rhs);
			}
			else
			{
				Reserve(rhs.mCapacity);
				switch (rhs.mType)
				{
				case DatumType::Integer:
					for (std::uint32_t i = 0; i < rhs.mSize; i++)
					{
						PushBack(rhs.Get<std::int32_t>(i));
					}
					break;
				case DatumType::Float:
					for (std::uint32_t i = 0; i < rhs.mSize; i++)
					{
						PushBack(rhs.Get<float>(i));
					}
					break;
				case DatumType::Vector:
					for (std::uint32_t i = 0; i < rhs.mSize; i++)
					{
						PushBack(rhs.Get<glm::vec4>(i));
					}
					break;
				case DatumType::Matrix:
					for (std::uint32_t i = 0; i < rhs.mSize; i++)
					{
						PushBack(rhs.Get<glm::mat4>(i));
					}
					break;
				case DatumType::String:
					for (std::uint32_t i = 0; i < rhs.mSize; i++)
					{
						PushBack(rhs.Get<std::string>(i));
					}
					break;
				case DatumType::Pointer:
					for (std::uint32_t i = 0; i < rhs.mSize; i++)
					{
						PushBack(rhs.Get<Library::RTTI*>(i));
					}
					break;
				default: break;
				}
			}
		}

		return *this;
	}

	/// Datum move assignment operator
	/// @Param rhs: Datum object being assigned to
	/// @Return: The newly copied Datum object
	Datum& Datum::operator=(Datum&& rhs)
	{	
		SetType(rhs.mType); // Must Set Type in order to instantiate mTypeState
		if (rhs.mDataIsExternal)
		{
			mTypeState->SetStorage(rhs);
		}
		else
		{
			mData = rhs.mData;
			mType = rhs.mType;
			mCapacity = rhs.mCapacity;
			mSize = rhs.mSize;
		}

		rhs.mType = DatumType::Unknown;
		rhs.mCapacity = NULL;
		rhs.mSize = NULL;

		return *this;
	}

	/// Type assignment operator
	/// @Param rhs: DatumType being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to reassign a new Type to a Datum object
	Datum& Datum::operator=(const DatumType& rhs)
	{
		SetType(rhs);
		return *this;
	}

	/// Assignment operator for std::int32_t
	/// @Param rhs: Integer being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum Type or if Size is greater than 1
	Datum& Datum::operator=(const std::int32_t& rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		SetType(DatumType::Integer);
		return mTypeState->operator=(rhs);
	}

	/// Assignment operator for float
	/// @Param rhs: Float being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum Type or if Size is greater than 1
	Datum& Datum::operator=(const float& rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		SetType(DatumType::Float);
		return mTypeState->operator=(rhs);
	}

	/// Assignment operator for vec4
	/// @Param rhs: Vector being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum Type or if Size is greater than 1
	Datum& Datum::operator=(const glm::vec4& rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		SetType(DatumType::Vector);
		return mTypeState->operator=(rhs);
	}

	/// Assignment operator for mat4
	/// @Param rhs: Matrix being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum Type or if Size is greater than 1
	Datum& Datum::operator=(const glm::mat4& rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		SetType(DatumType::Matrix);
		return mTypeState->operator=(rhs);
	}

	/// Assignment operator for Scope
	/// @Param rhs: Scope being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum Type or if Size is greater than 1
	Datum& Datum::operator=(Scope* const rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		SetType(DatumType::Scope);
		return mTypeState->operator=(rhs);
	}

	/// Assignment operator for std::string
	/// @Param rhs: String being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum Type or if Size is greater than 1
	Datum& Datum::operator=(const std::string& rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		SetType(DatumType::String);
		return mTypeState->operator=(rhs);
	}

	/// Assignment operator for float
	/// @Param rhs: Float being assigned to
	/// @Return: The newly assigned Datum object
	/// @Exception: Thrown if attempting to assign to invalid Datum Type or if Size is greater than 1
	Datum& Datum::operator=(Library::RTTI* const& rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		SetType(DatumType::Pointer);
		return mTypeState->operator=(rhs);
	}

	/// Comparison operator for Datum objects
	/// @Param rhs: The Datum object being compared against
	/// @Return: True if the Datum objects are equivalent
	bool Datum::operator==(const Datum& rhs) const
	{
		if (mType == DatumType::Unknown && rhs.mType == DatumType::Unknown) return true;
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
	/// @Return: True if the integer values are the same. False if Size is not 1 or if Type is invalid
	bool Datum::operator==(const std::int32_t& rhs) const
	{
		return mType == DatumType::Integer &&
			mSize == 1 && mData.i[0] == rhs;
	}

	/// Comparison operator for float
	/// @Param rhs: The float being compared against
	/// @Return: True if the float values are the same. False if Size is not 1 or if Type is invalid
	bool Datum::operator==(const float& rhs) const
	{
		return mType == DatumType::Float &&
			mSize == 1 && mData.f[0] == rhs;
	}

	/// Comparison operator for v3c4
	/// @Param rhs: The vector being compared against
	/// @Return: True if the vectors are equivalent. False if Size is not 1 or if Type is invalid
	bool Datum::operator==(const glm::vec4& rhs) const
	{
		return mType == DatumType::Vector &&
			mSize == 1 && mData.v[0] == rhs;
	}

	/// Comparison operator for mat4
	/// @Param rhs: The matrix being  compared against
	/// @Return: True if the matrices are equivalent. False if Size is not 1 or if Type is invalid
	bool Datum::operator==(const glm::mat4& rhs) const
	{
		return mType == DatumType::Matrix &&
			mSize == 1 && mData.m[0] == rhs;
	}

	/// Comparison operator for Scope
	/// @Param rhs: The scope being  compared against
	/// @Return: True if the scopes are equivalent. False if Size is not 1 or if Type is invalid
	bool Datum::operator==(const Scope* rhs) const
	{
		return mType == DatumType::Scope &&
			mSize == 1 && mData.sc[0] == rhs;
	}

	/// Comparison operator for std::string
	/// @Param rhs: The string being compared against
	/// @Return: True if the string values are the same. False if Size is not 1 or if Type is invalid
	bool Datum::operator==(const std::string& rhs) const
	{
		return mType == DatumType::String &&
			mSize == 1 && mData.s[0] == rhs;
	}

	/// Comparison operator for RTTI pointers
	/// @Param rhs: The RTTI pointer being compared against
	/// @Return: True if the pointers are the same. False if Size is not 1 or if Type is invalid
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

	/// The Type associated with this object
	/// @Return: The DatumType of this Datum object
	DatumType Datum::Type() const
	{
		return mType;
	}

	/// Set the DatumType of the Datum object
	/// @Param Type: The new Type of the Datum object
	/// @Exception: Thrown if attempting to reassign a new Type to a Datum object
	void Datum::SetType(const DatumType& type)
	{
		if (mType == type) return; // Avoid double instantiation of state without throwing an exception

		if (mType == DatumType::Unknown) mType = type;
		else throw std::exception("Attempting to change Type on Datum object");

		if (mTypeState != nullptr)
		{	// If we've already Set state, make sure we delete the old Type state
			delete mTypeState;
		}

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
			case DatumType::Scope:
				mTypeState = new ScopeState(this);
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
	std::uint32_t Datum::Size() const
	{
		return mSize;
	}

	/// The number of potential values in the Datum object
	/// @Return: The number of objects that can currently be stored in the Datum object
	std::uint32_t Datum::Capacity() const
	{
		return mCapacity;
	}

	/// Set number of values and Reserve memory if needed
	/// @Param Size: the new number of values
	/// @Exception: Thrown if attempting to resize external data
	void Datum::SetSize(std::uint32_t size)
	{
		if (mDataIsExternal) throw std::exception("Attempting to resize external storage");
		mTypeState->SetSize(size);
	}

	/// Reserve additional Capacity for uninitialized values
	/// @Param Capacity: The number of possible elements that the array will be able to hold
	/// @Exception: Thrown if attempting to resize external storage
	void Datum::Reserve(std::uint32_t capacity)
	{
		if (mType == DatumType::Unknown) return;
		if (mDataIsExternal) throw std::exception("Attempting to resize external storage");
		mTypeState->Reserve(capacity);
	}

	/// Clear the array without shrinking the Capacity
	/// @Exception: Thrown if trying to Clear with an invalid Type Set
	void Datum::Clear()
	{
		mTypeState->Clear();
	}

	/// Sets the external storage to the specified int32_t*
	/// Note: Size on external storage is considered static
	/// @Param data: The specified external storage
	/// @Param Size: The number of elements available in the external storage
	void Datum::SetStorage(std::int32_t* data, std::uint32_t size)
	{
//		if (mTypeState != nullptr) return mTypeState->SetStorage(data, Size);
//		SetType(DatumType::Integer);
//		mTypeState->SetStorage(data, Size);

		if (mTypeState == nullptr)
		{
			SetType(DatumType::Integer);
		}

		mTypeState->SetStorage(data, size);
	}

	/// Sets the external storage to the specified float*
	/// Note: Size on external storage is considered static
	/// @Param data: The specified external storage
	/// @Param Size: The number of elements available in the external storage
	void Datum::SetStorage(float* data, std::uint32_t size)
	{
		if (mTypeState == nullptr)
		{
			SetType(DatumType::Float);
		}

		mTypeState->SetStorage(data, size);
	}

	/// Sets the external storage to the specified glm::vec4*
	/// Note: Size on external storage is considered static
	/// @Param data: The specified external storage
	/// @Param Size: The number of elements available in the external storage
	void Datum::SetStorage(glm::vec4* data, std::uint32_t size)
	{
		if (mTypeState == nullptr)
		{
			SetType(DatumType::Vector);
		}
		
		mTypeState->SetStorage(data, size);
	}

	/// Sets the external storage to the specified glm::mat4*
	/// Note: Size on external storage is considered static
	/// @Param data: The specified external storage
	/// @Param Size: The number of elements available in the external storage
	void Datum::SetStorage(glm::mat4* data, std::uint32_t size)
	{
		if (mTypeState == nullptr)
		{
			SetType(DatumType::Matrix);
		}
		
		mTypeState->SetStorage(data, size);
	}

	/// Sets the external storage to the specified std::string*
	/// Note: Size on external storage is considered static
	/// @Param data: The specified external storage
	/// @Param Size: The number of elements available in the external storage
	void Datum::SetStorage(std::string* data, std::uint32_t size)
	{
		if (mTypeState == nullptr)
		{
			SetType(DatumType::String);
		}
		
		mTypeState->SetStorage(data, size);
	}

	/// Sets the external storage to the specified RTTI**
	/// Note: Size on external storage is considered static
	/// @Param data: The specified external storage
	/// @Param Size: The number of elements available in the external storage
	void Datum::SetStorage(Library::RTTI** data, std::uint32_t size)
	{
		if (mTypeState == nullptr)
		{
			SetType(DatumType::Pointer);
		}
		
		mTypeState->SetStorage(data, size);
	}

	/// Sets a specified index of the array to the specified value
	/// @Param value: The int32_t being assigned
	/// @Param index: The index of the value being assigned to
	/// @Exception invalidType: Thrown if calling Set on invalid Type
	/// @Exception indexOutObBounds: Thrown if attempting to Set beyond existing Size
	void Datum::Set(const std::int32_t& value, const std::uint32_t index)
	{
		if (mType != DatumType::Integer) throw std::exception("Calling Set on invalid Type");
		if (index > mSize) throw std::exception("Attempting to Set beyond current Size");
		if (index == mSize) PushBack(value); // If setting end, divert functionality to a push Back
		new(mData.i + index) std::int32_t(value);
	}

	/// Sets a specified index of the array to the specified value
	/// @Param value: The float being assigned
	/// @Param index: The index of the value being assigned to
	/// @Exception: Thrown if calling Set on invalid Type
	/// @Exception: Thrown if attempting to Set beyond existing Size
	void Datum::Set(const float& value, const std::uint32_t index)
	{
		if (mType != DatumType::Float) throw std::exception("Calling Set on invalid Type");
		if (index > mSize) throw std::exception("Attempting to Set beyond current Size");
		if (index == mSize) PushBack(value); // If setting end, divert functionality to a push Back
		new(mData.f + index) float(value);
	}

	/// Sets a specified index of the array to the specified value
	/// @Param value: The vec4 being assigned
	/// @Param index: The index of the value being assigned to
	/// @Exception: Thrown if calling Set on invalid Type
	/// @Exception: Thrown if attempting to Set beyond existing Size
	void Datum::Set(const glm::vec4& value, const std::uint32_t index)
	{
		if (mType != DatumType::Vector) throw std::exception("Calling Set on invalid Type");
		if (index > mSize) throw std::exception("Attempting to Set beyond current Size");
		if (index == mSize) PushBack(value); // If setting end, divert functionality to a push Back
		new(mData.v + index) glm::vec4(value);
	}

	/// Sets a specified index of the array to the specified value
	/// @Param value: The mat4 being assigned
	/// @Param index: The index of the value being assigned to
	/// @Exception: Thrown if calling Set on invalid Type
	/// @Exception: Thrown if attempting to Set beyond existing Size
	void Datum::Set(const glm::mat4& value, const std::uint32_t index)
	{
		if (mType != DatumType::Matrix) throw std::exception("Calling Set on invalid Type");
		if (index > mSize) throw std::exception("Attempting to Set beyond current Size");
		if (index == mSize) PushBack(value); // If setting end, divert functionality to a push Back
		new(mData.m + index) glm::mat4(value);
	}

	/// Sets a specified index of the array to the specified value
	/// @Param value: The scope pointer being assigned
	/// @Param index: The index of the value being assigned to
	/// @Exception: Thrown if calling Set on invalid Type
	/// @Exception: Thrown if attempting to Set beyond existing Size
	void Datum::Set(Scope* const& value, const std::uint32_t index)
	{
		if (mType != DatumType::Scope) throw std::exception("Calling Set on invalid Type");
		if (index > mSize) throw std::exception("Attempting to Set beyond current Size");
		if (index == mSize) PushBack(value); // If setting end, divert functionality to a push Back
		new(mData.sc + index) Scope*(value);
	}

	/// Sets a specified index of the array to the specified value
	/// @Param value: The string being assigned
	/// @Param index: The index of the value being assigned to
	/// @Exception: Thrown if calling Set on invalid Type
	/// @Exception: Thrown if attempting to Set beyond existing Size
	void Datum::Set(const std::string& value, const std::uint32_t index)
	{
		if (mType != DatumType::String) throw std::exception("Calling Set on invalid Type");
		if (index > mSize) throw std::exception("Attempting to Set beyond current Size");
		if (index == mSize) PushBack(value); // If setting end, divert functionality to a push Back
//		new(mData.s + index) std::string(value);
		mData.s[index] = value;
	}

	/// Sets a specified index of the array to the specified value
	/// @Param value: The RTTI* being assigned
	/// @Param index: The index of the value being assigned to
	/// @Exception: Thrown if calling Set on invalid Type
	/// @Exception: Thrown if attempting to Set beyond existing Size
	void Datum::Set(Library::RTTI* const& value, const std::uint32_t index)
	{
		if (mType != DatumType::Pointer) throw std::exception("Calling Set on invalid Type");
		if (index > mSize) throw std::exception("Attempting to Set beyond current Size");
		if (index == mSize) PushBack(value); // If setting end, divert functionality to a push Back
		new(mData.r + index) RTTI*(value);
	}

	/// Pushes an std::int32_t to the Back of the array
	/// @Param value: The value being pushed onto the array
	void Datum::PushBack(const std::int32_t& value)
	{
		SetSize(mSize + 1);
		Set(value, mSize - 1);
	}

	/// Pushes an std::int32_t to the Back of the array
	/// @Param value: The value being pushed onto the array
	void Datum::PushBack(const float& value)
	{
		SetSize(mSize + 1);
		Set(value, mSize - 1);
	}

	/// Pushes an std::int32_t to the Back of the array
	/// @Param value: The value being pushed onto the array
	void Datum::PushBack(const glm::vec4& value)
	{
		SetSize(mSize + 1);
		Set(value, mSize - 1);
	}

	/// Pushes an std::int32_t to the Back of the array
	/// @Param value: The value being pushed onto the array
	void Datum::PushBack(const glm::mat4& value)
	{
		SetSize(mSize + 1);
		Set(value, mSize - 1);
	}

	/// Pushes an std::int32_t to the Back of the array
	/// @Param value: The value being pushed onto the array
	void Datum::PushBack(Scope* const& value)
	{
		SetSize(mSize + 1);
		Set(value, mSize - 1);
	}

	/// Pushes an std::int32_t to the Back of the array
	/// @Param value: The value being pushed onto the array
	void Datum::PushBack(const std::string& value)
	{
		SetSize(mSize + 1);
		Set(value, mSize - 1);
	}

	/// Pushes an std::int32_t to the Back of the array
	/// @Param value: The value being pushed onto the array
	/// @Exception: Thrown if attempting to push Back a null value
	void Datum::PushBack(RTTI* const& value)
	{
		if (value == nullptr) throw std::exception("Attempting to push Back nullptr");
		SetSize(mSize + 1);
		Set(value, mSize - 1);
	}

	void Datum::Remove(Scope* const scope)
	{
		if (mType == DatumType::Scope)
		{
			for (std::uint32_t i = 0; i < mSize; i++)
			{
				if(mData.sc[i] == scope)
				{
					mData.sc[i]->~Scope();
					memmove(mData.sc[i], mData.sc[i + 1], mSize - i - 1);
					mSize--;
				}
			}
		}
	}

	/// Parses a string value and sets the value to the specified index
	/// @Param value: The string value being parsed
	/// @Param index: The location being Set to. Default is 0
	/// @Exception: Thrown if syntax is invalid
	void Datum::SetFromString(const std::string& value, const std::uint32_t& index)
	{
		mTypeState->SetFromString(value, index);
	}

	/// A string representation of a piece of data stored in the Datum object
	/// @Param index: Optional index of the value being retrieved. Defaulted to first element
	/// @Exception invalidFormat: Thrown if unable to properly Parse string
	std::string Datum::ToString(std::uint32_t index)
	{	
		if (mType == DatumType::Unknown) return "Unknown Type";
		return mTypeState->ToString(index);
	}
}
