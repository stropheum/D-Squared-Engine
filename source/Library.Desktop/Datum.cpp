#include "pch.h"
#include "Datum.h"

namespace Datum
{
	/// Constructor
	Datum::Datum():
		mType(DatumType::Unknown), mCapacity(13), mSize(0)
	{}

	/// Overloaded constructor
	/// @Param type: The type of the Datum object
	Datum::Datum(DatumType type): 
		mType(type), mCapacity(13), mSize(0)
	{}

	/// Destructor
	Datum::~Datum()
	{}

	/// Copy constructor
	/// @Param rhs: Datum object being copied
	Datum::Datum(const Datum& rhs):
		mType(rhs.mType), mData(rhs.mData), mCapacity(rhs.mCapacity), mSize(rhs.mSize)
	{}

	/// Move copy constructor
	/// @Param rhs: Datum object being copied
	Datum::Datum(Datum&& rhs):
		mType(rhs.mType), mData(rhs.mData)
	{
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

	/// Assignment operator
	/// @Param rhs: Datum object being copied
	/// @Return: A Copy of the specified Datum object
	Datum& Datum::operator=(const Datum& rhs)
	{
		// TODO: Implement assignment operator
		UNREFERENCED_PARAMETER(rhs);
		return *this;
	}

	/// Move assignment operator
	/// @Param rhs: Datum object being copied
	/// @Return: A Copy of the specified Datum object
	Datum& Datum::operator=(Datum&& rhs)
	{
		// TODO: Implement move assignment operator
		UNREFERENCED_PARAMETER(rhs);
		return *this;
	}

	/// Comparison operator
	/// @Param rhs: The Datum object being compared against
	/// @Return: True if the two Datum objects are equivalent
	bool Datum::operator==(const Datum& rhs) const
	{
		// TODO: Implement comparison operator
		UNREFERENCED_PARAMETER(rhs);
		return true;
	}

	/// Negated comparison operator
	/// @Param rhs: The Datum object being compared against
	/// @Return: True if the two Datum objects are not equivalent
	bool Datum::operator!=(const Datum& rhs) const
	{
		return !(operator==(rhs));
	}

	/// The type associated with this object
	/// @Return: The DatumType of this Datum object
	DatumType Datum::type() const
	{
		// TODO: Implement type method
		return DatumType::Unknown;
	}

	/// Set the DatumType of the Datum object
	/// @Param type: The new type of the Datum object
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
		// TODO: Implement setSize method
		UNREFERENCED_PARAMETER(size);
	}

	/// Clear the array without shrinking the capacity
	void Datum::clear()
	{
		// TODO: Implement clear method
	}

	/// Reserves the number of elements in the local buffer
	void Datum::reserve(std::uint32_t capacity)
	{
	}
}
