#include "pch.h"
#include "IntegerState.h"

namespace Library
{
	IntegerState::IntegerState(Datum* const context):
		TypeState(context)
	{}

	Datum& IntegerState::operator=(const std::int32_t& rhs)
	{
		if (mContext->mSize > 1) throw std::exception("Invalid assignment invocation");
		if (mContext->mSize == 0) mContext->setSize(1);
		mContext->mData.i[0] = rhs;
		return *mContext;
	}

	/// Reserves the number of integers in the local buffer
	/// @Param capacity: The current maximum size of the array
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

	void IntegerState::reserve(std::uint32_t capacity)
	{
		if (capacity < mContext->mSize) throw std::exception("Attempting to clobber occupied data");
		

		std::int32_t* temp= mContext->mData.i;
		mContext->mData.i = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * capacity));
		memcpy_s(mContext->mData.i, sizeof(std::int32_t) * mContext->mSize, temp, sizeof(std::int32_t) * mContext->mSize);
		
		if (mContext->mCapacity > 0) { free(temp); }
		mContext->mCapacity = capacity;
	}

	void IntegerState::clear()
	{
		if (mContext->mSize > 0)
		{
			for (std::uint32_t i = 0; i < mContext->mSize; i++) mContext->mData.i[i] = NULL;
			mContext->mSize = 0;
		}
	}

	void IntegerState::setFromString(const std::string& value, const std::uint32_t& index)
	{
		UNREFERENCED_PARAMETER(value);
		UNREFERENCED_PARAMETER(index);
	}

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
}
