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
		new(mContext->mData.s) std::string(rhs);
		return *mContext;
	}

	/// Sets the number of strings in the local buffer
	/// @Param capacity: The current maximum size of the array
	void StringState::setSize(std::uint32_t size)
	{
		mContext->mData.vp = realloc(mContext->mData.vp, sizeof(std::string) * size);
		mContext->mCapacity = mContext->mSize = size;

		if (size > mContext->mSize)
		{	// If our new size is larger than before, we need to default construct new strings
			for (std::uint32_t i = mContext->mSize; i < size; i++)
			{	// Use placement new to construct new strings
				new(mContext->mData.s + i) std::string("");
			}
		}

		else if (size < mContext->mSize)
		{
			for (std::uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.s[i].std::string::~string();
			}
		}
	}

	/// Modifies the capacity of the array to any value greater than or equal to current size
	/// @Param capacity: The new capacity of the array
	void StringState::reserve(std::uint32_t capacity)
	{
		if (capacity > mContext->mCapacity)
		{
			mContext->mData.vp = realloc(mContext->mData.vp, sizeof(std::string) * capacity);
			mContext->mCapacity = capacity;
		}
	}

	/// Clears the value of all elements in the array without changing capacity
	void StringState::clear()
	{
		if (mContext->mSize > 0)
		{
			for (std::uint32_t i = 0; i < mContext->mSize; i++)
			{	// Placement new an empty string onto the array
				mContext->mData.s[i].std::string::~string();
				new(mContext->mData.s + i) std::string("");
//				mContext->mData.s[i] = "";
			}
			mContext->mSize = 0;
		}
	}

	/// Parses a string value and assigns the specified index of the array to its value
	/// @Param value: The string value being parsed
	/// @Param index: The index of the array being assigned to
	void StringState::setFromString(const std::string& value, const std::uint32_t& index)
	{   // Strings don't have to be parsed, so they can be passed directly to set
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
		if (mContext->mType != DatumType::String)
		{
			throw std::exception("Attempting to reassign Datum Type");
		}
		
		if (mContext->mCapacity > 0) { clear(); }

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
