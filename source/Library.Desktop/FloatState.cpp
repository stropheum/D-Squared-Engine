#include "pch.h"
#include "FloatState.h"


namespace Library
{
	FloatState::FloatState(Datum* const context):
		TypeState(context)
	{}

	FloatState::~FloatState()
	{}

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

	void FloatState::reserve(std::uint32_t capacity)
	{
		if (capacity < mContext->mSize) throw std::exception("Attempting to clobber occupied data");
		mContext->mCapacity = capacity;

		float* temp = mContext->mData.f;
		mContext->mData.f = static_cast<float*>(malloc(sizeof(float) * mContext->mCapacity));
		memcpy_s(mContext->mData.f, sizeof(float) * mContext->mSize, temp, sizeof(float) * mContext->mSize);

		if (temp != nullptr) free(temp);
	}

	void FloatState::clear()
	{
		if (mContext->mSize > 0)
		{
			for (std::uint32_t i = 0; i < mContext->mSize; i++) mContext->mData.f[i] = NULL;
			mContext->mSize = 0;
		}
	}
}