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
		mContext->mCapacity = capacity;

		std::int32_t* temp = mContext->mData.i;
		mContext->mData.i = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * mContext->mCapacity));
		memcpy_s(mContext->mData.i, sizeof(std::int32_t) * mContext->mSize, temp, sizeof(std::int32_t) * mContext->mSize);

		if (temp != nullptr) free(temp);
	}
}
