#include "pch.h"
#include "StringState.h"


namespace Library
{
	/// Constructor
	/// @Param context: The Datum object that the state operates one
	StringState::StringState(Datum* const context):
		TypeState(context)
	{}

	/// Comparison operator for Datum objects
	/// @Param rhs: The Datum object being compared against
	/// @Return: True if type, size, and each element of the Datum objects are equivalent. False otherwise
	bool StringState::operator==(const Datum& rhs)
	{
		bool result = false;

		if (mContext->mType == rhs.mType && mContext->mSize == rhs.mSize && mContext->mCapacity == rhs.mCapacity)
		{
			result = true;
			for (std::uint32_t i = 0; i < mContext->mSize; i++)
			{
				if (mContext->mData.s[i] != rhs.mData.s[i])
				{
					result = false;
					break;
				}
			}
		}

		return result;
	}

	/// Scalar assignment operator
	/// @Param rhs: The string being set to the only element in the Datum
	/// @Return: The modified Datum object
	Datum& StringState::operator=(const std::string& rhs)
	{
		if (mContext->mSize > 1) throw std::exception("Invalid assignment invocation");
		if (mContext->mSize == 0) mContext->setSize(1);
		mContext->mData.s[0] = rhs;
		return *mContext;
	}

	/// Sets the number of strings in the local buffer
	/// @Param capacity: The current maximum size of the array
	void StringState::setSize(std::uint32_t size)
	{
		if (size > mContext->mCapacity) mContext->mCapacity = size;

		std::string* temp = mContext->mData.s;
		mContext->mData.s = new std::string[mContext->mCapacity];
		for (std::uint32_t i = 0; i < mContext->mSize; i++)
		{
			mContext->mData.s[i] = temp[i];
		}

		if (size < mContext->mSize)
		{
			for (std::uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.s[i] = "";
			}
		}

		if (mContext->mSize > 0) { delete[] temp; }

		mContext->mSize = size;
	}

	/// Modifies the capacity of the array to any value greater than or equal to current size
	/// @Param capacity: The new capacity of the array
	void StringState::reserve(std::uint32_t capacity)
	{
		if (capacity < mContext->mSize) throw std::exception("Attempting to clobber occupied data");

		std::string* temp = mContext->mData.s;
		mContext->mData.s = new std::string[capacity];
		for (std::uint32_t i = 0; i < mContext->mSize; i++)
		{
			mContext->mData.s[i] = temp[i];
		}

		if (mContext->mCapacity > 0) { delete[] temp; }

		mContext->mCapacity = capacity;
	}

	/// Clears the value of all elements in the array without changing capacity
	void StringState::clear()
	{
		if (mContext->mSize > 0)
		{
			for (std::uint32_t i = 0; i < mContext->mSize; i++) mContext->mData.s[i] = "";
			mContext->mSize = 0;
		}
	}

	/// Parses a string value and assigns the specified index of the array to its value
	/// @Param value: The string value being parsed
	/// @Param index: The index of the array being assigned to
	void StringState::setFromString(const std::string& value, const std::uint32_t& index)
	{   // Strings don't have to be parsed, so they can be passed directly top set
		mContext->set(value, index); 
	}

	/// Sets external storage on copy
	/// @Param rhs: The Datum object that the storage reference is being taken from
	void StringState::setStorage(const Datum& rhs)
	{
		setStorage(rhs.mData.s, rhs.mSize);
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Pram size: The number of elements in the external storage
	/// @Exception: Thrown if attempting to reassign datum type, or if local memory is already used
	void StringState::setStorage(std::string* data, std::uint32_t size)
	{
		if (mContext->mType != DatumType::String) throw std::exception("Attempting to reassign Datum Type");
//		if (mContext->mCapacity > 0) throw std::exception("Set storage called on non-empty Datum");
		
		if (mContext->mCapacity > 0) clear();

		mContext->mDataIsExternal = true;
		mContext->mData.s = data;
		mContext->mCapacity = mContext->mSize = size;
	}

	/// A string representation of a piece of data stored in the Datum object
	/// @Param index: Optional index of the value being retrieved. Defaulted to first element
	std::string StringState::toString(std::uint32_t index)
	{
		return mContext->get<std::string>(index);
	}
}
