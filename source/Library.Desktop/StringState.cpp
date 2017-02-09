#include "pch.h"
#include "StringState.h"


namespace Library
{
	StringState::StringState(Datum* const context):
		TypeState(context)
	{}


	StringState::~StringState()
	{}

	Datum& StringState::operator=(const std::string& rhs)
	{
		if (mContext->mSize > 1) throw std::exception("Invalid assignment invocation");
		if (mContext->mSize == 0) mContext->setSize(1);
		mContext->mData.s[0] = rhs;
		return *mContext;
	}

	/// Reserves the number of strings in the local buffer
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

		mContext->mSize = size;
	}

	void StringState::reserve(std::uint32_t capacity)
	{
		if (capacity < mContext->mSize) throw std::exception("Attempting to clobber occupied data");
		mContext->mCapacity = capacity;

		std::string* temp = mContext->mData.s;
		mContext->mData.s = new std::string[mContext->mCapacity];
		for (std::uint32_t i = 0; i < mContext->mSize; i++)
		{
			mContext->mData.s[i] = temp[i];
		}
	}

	void StringState::clear()
	{
		if (mContext->mSize > 0)
		{
			for (std::uint32_t i = 0; i < mContext->mSize; i++) mContext->mData.s[i] = "";
			mContext->mSize = 0;
		}
	}
}