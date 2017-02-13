#include "pch.h"
#include "IntegerState.h"

namespace Library
{
	/// Constructor
	/// @Param context: The Datum object that the state operates one
	IntegerState::IntegerState(Datum* const context):
		TypeState(context)
	{}

	/// Comparison operator for Datum objects
	/// @Param rhs: The Datum object being compared against
	/// @Return: True if type, size, and each element of the Datum objects are equivalent. False otherwise
	bool IntegerState::operator==(const Datum& rhs)
	{
		bool result = false;

		if (mContext->mType == rhs.mType && mContext->mSize == rhs.mSize)
		{
			result = true;
			for (std::uint32_t i = 0; i < mContext->mSize; i++)
			{
				if (mContext->mData.i[i] != rhs.mData.i[i])
				{
					result = false;
					break;
				}
			}
		}

		return result;
	}

	/// Scalar assignment operator
	/// @Param rhs: The integer being set to the only element in the Datum
	/// @Return: The modified Datum object
	Datum& IntegerState::operator=(const std::int32_t& rhs)
	{
		if (mContext->mSize > 1) throw std::exception("Invalid assignment invocation");
		if (mContext->mSize == 0) mContext->setSize(1);
		mContext->mData.i[0] = rhs;
		return *mContext;
	}

	/// Sets the number of integers in the local buffer
	/// @Param capacity: The current size of the array
	void IntegerState::setSize(std::uint32_t size)
	{
		if (size > mContext->mCapacity) mContext->mCapacity = size;

		std::int32_t* temp = mContext->mData.i;
		mContext->mData.i = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * mContext->mCapacity));
		memcpy_s(mContext->mData.i, sizeof(std::int32_t) * mContext->mSize, temp, sizeof(std::int32_t) * mContext->mSize);

		if (size <mContext->mSize)
		{
			for (std::uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.i[i] = NULL;
			}
		}

		mContext->mSize = size;
	}

	/// Modifies the capacity of the array to any value greater than or equal to current size
	/// @Param capacity: The new capacity of the array
	void IntegerState::reserve(std::uint32_t capacity)
	{
		if (capacity < mContext->mSize) throw std::exception("Attempting to clobber occupied data");
		

		std::int32_t* temp= mContext->mData.i;
		mContext->mData.i = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * capacity));
		memcpy_s(mContext->mData.i, sizeof(std::int32_t) * mContext->mSize, temp, sizeof(std::int32_t) * mContext->mSize);
		
		if (mContext->mCapacity > 0) { free(temp); }
		mContext->mCapacity = capacity;
	}

	/// Clears the value of all elements in the array without changing capacity
	void IntegerState::clear()
	{
		if (mContext->mSize > 0)
		{
			for (std::uint32_t i = 0; i < mContext->mSize; i++) mContext->mData.i[i] = NULL;
			mContext->mSize = 0;
		}
	}

	/// Parses a string value and assigns the specified index of the array to its value
	/// @Param value: The string value being parsed
	/// @Param index: The index of the array being assigned to
	void IntegerState::setFromString(const std::string& value, const std::uint32_t& index)
	{
		std::int32_t result = std::stoi(value);
		mContext->set(result, index);
	}

	/// Sets external storage on copy
	/// @Param rhs: The Datum object that the storage reference is being taken from
	void IntegerState::setStorage(const Datum& rhs)
	{
		setStorage(rhs.mData.i, rhs.mSize);
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Pram size: The number of elements in the external storage
	/// @Exception: Thrown if attempting to reassign datum type, or if local memory is already used
	void IntegerState::setStorage(std::int32_t* data, std::uint32_t size)
	{
		if (mContext->mType != DatumType::Integer) throw std::exception("Attempting to reassign Datum Type");
		if (mContext->mCapacity > 0) throw std::exception("Set storage called on non-empty Datum");
		
		mContext->mDataIsExternal = true;
		mContext->mData.i = data;
		mContext->mCapacity = mContext->mSize = size;
	}

	/// A string representation of a piece of data stored in the Datum object
	/// @Param index: Optional index of the value being retrieved. Defaulted to first element
	std::string IntegerState::toString(std::uint32_t index)
	{
		char value[50];
		sprintf_s(value, "%d", mContext->get<std::int32_t>(index));
		return value;
	}
}
