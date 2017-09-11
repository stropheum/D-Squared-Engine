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
	/// @Return: True if Type, Size, and each element of the Datum objects are equivalent. False otherwise
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
	/// @Param rhs: The float being Set to the only element in the Datum
	/// @Return: The modified Datum object
	Datum& FloatState::operator=(const float& rhs)
	{
		if (mContext->mSize > 1) throw std::exception("Invalid assignment invocation");
		if (mContext->mSize == 0) mContext->SetSize(1);
		mContext->mData.f[0] = rhs;
		return *mContext;
	}

	/// Reserves the number of floats in the local buffer
	/// @Param Capacity: The current maximum Size of the array
	void FloatState::SetSize(std::uint32_t size)
	{
		mContext->mData.vp = realloc(mContext->mData.vp, sizeof(float) * size);
		mContext->mCapacity = mContext->mSize = size;

		if (size <mContext->mSize)
		{
			for (std::uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.f[i] = 0.0f;
			}
		}
	}

	/// Modifies the Capacity of the array to any value greater than or equal to current Size
	/// @Param Capacity: The new Capacity of the array
	void FloatState::Reserve(std::uint32_t capacity)
	{
		if (capacity > mContext->mCapacity)
		{
			mContext->mData.vp = realloc(mContext->mData.vp, sizeof(float) * capacity);
			mContext->mCapacity = capacity;
		}
	}

	/// Clears the value of all elements in the array without changing Capacity
	void FloatState::Clear()
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
	void FloatState::SetFromString(const std::string& value, const std::uint32_t& index)
	{
		float result;
		sscanf_s(value.c_str(), "%f", &result);
		mContext->Set(result, index);
	}

	/// Sets external storage on copy
	/// @Param rhs: The Datum object that the storage reference is being taken from
	void FloatState::SetStorage(const Datum& rhs)
	{
		SetStorage(rhs.mData.f, rhs.mSize);
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Pram Size: The number of elements in the external storage
	/// @Exception: Thrown if attempting to reassign datum Type, or if local memory is already used
	void FloatState::SetStorage(float* data, std::uint32_t size)
	{
		if (mContext->mType != DatumType::Float) throw std::exception("Attempting to reassign Datum Type");
//		if (mContext->mCapacity > 0) throw std::exception("Set storage called on non-empty Datum");
		
		if (mContext->mCapacity > 0) Clear();

		mContext->mDataIsExternal = true;
		mContext->mData.f = data;
		mContext->mCapacity = mContext->mSize = size;
	}

	/// A string representation of a piece of data stored in the Datum object
	/// @Param index: Optional index of the value being retrieved. Defaulted to first element
	std::string FloatState::ToString(std::uint32_t index)
	{
		char value[50];
		sprintf_s(value, "%f", mContext->Get<float>(index));
		return value;
	}
}
