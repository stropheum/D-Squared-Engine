#include "pch.h"
#include "FloatState.h"


namespace Library
{
	/// Constructor
	/// @Param context: The Datum object that the state operates one
	FloatState::FloatState(Datum* const context):
		TypeState(context)
	{}

	/// Comparison operator for Datum objects
	/// @Param rhs: The Datum object being compared against
	/// @Return: True if type, size, and each element of the Datum objects are equivalent. False otherwise
	bool FloatState::operator==(const Datum& rhs)
	{
		bool result = false;

		if (mContext->mType == rhs.mType && mContext->mSize == rhs.mSize)
		{
			result = true;
			for (std::uint32_t i = 0; i < mContext->mSize; i++)
			{
				if (mContext->mData.f[i] != rhs.mData.f[i])
				{
					result = false;
					break;
				}
			}
		}

		return result;
	}

	/// Scalar assignment operator
	/// @Param rhs: The float being set to the only element in the Datum
	/// @Return: The modified Datum object
	Datum& FloatState::operator=(const float& rhs)
	{
		if (mContext->mSize > 1) throw std::exception("Invalid assignment invocation");
		if (mContext->mSize == 0) mContext->setSize(1);
		mContext->mData.f[0] = rhs;
		return *mContext;
	}

	/// Reserves the number of floats in the local buffer
	/// @Param capacity: The current maximum size of the array
	void FloatState::setSize(std::uint32_t size)
	{
		if (size > mContext->mCapacity) mContext->mCapacity = size;

		float* temp = mContext->mData.f;
		mContext->mData.f = static_cast<float*>(malloc(sizeof(float) * mContext->mCapacity));
		memcpy_s(mContext->mData.f, sizeof(float) * mContext->mSize, temp, sizeof(float) * mContext->mSize);

		if (size < mContext->mSize)
		{
			for (std::uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.f[i] = NULL;
			}
		}

		mContext->mSize = size;
	}

	/// Modifies the capacity of the array to any value greater than or equal to current size
	/// @Param capacity: The new capacity of the array
	void FloatState::reserve(std::uint32_t capacity)
	{
		if (capacity < mContext->mSize) throw std::exception("Attempting to clobber occupied data");

		float* temp = mContext->mData.f;
		mContext->mData.f = static_cast<float*>(malloc(sizeof(float) * capacity));
		memcpy_s(mContext->mData.f, sizeof(float) * mContext->mSize, temp, sizeof(float) * mContext->mSize);

		if (mContext->mCapacity > 0) { free(temp); }
		mContext->mCapacity = capacity;
	}

	/// Clears the value of all elements in the array without changing capacity
	void FloatState::clear()
	{
		if (mContext->mSize > 0)
		{
			for (std::uint32_t i = 0; i < mContext->mSize; i++) mContext->mData.f[i] = NULL;
			mContext->mSize = 0;
		}
	}

	/// Parses a string value and assigns the specified index of the array to its value
	/// @Param value: The string value being parsed
	/// @Param index: The index of the array being assigned to
	void FloatState::setFromString(const std::string& value, const std::uint32_t& index)
	{
		float result;
		sscanf_s(value.c_str(), "%f", &result);
		mContext->set(result, index);
	}

	/// Sets external storage on copy
	/// @Param rhs: The Datum object that the storage reference is being taken from
	void FloatState::setStorage(const Datum& rhs)
	{
		setStorage(rhs.mData.f, rhs.mSize);
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Pram size: The number of elements in the external storage
	/// @Exception: Thrown if attempting to reassign datum type, or if local memory is already used
	void FloatState::setStorage(float* data, std::uint32_t size)
	{
		if (mContext->mType != DatumType::Float) throw std::exception("Attempting to reassign Datum Type");
//		if (mContext->mCapacity > 0) throw std::exception("Set storage called on non-empty Datum");
		
		if (mContext->mCapacity > 0) clear();

		mContext->mDataIsExternal = true;
		mContext->mData.f = data;
		mContext->mCapacity = mContext->mSize = size;
	}

	/// A string representation of a piece of data stored in the Datum object
	/// @Param index: Optional index of the value being retrieved. Defaulted to first element
	std::string FloatState::toString(std::uint32_t index)
	{
		char value[50];
		sprintf_s(value, "%f", mContext->get<float>(index));
		return value;
	}
}
