#include "pch.h"
#include "ScopeState.h"
#include "Scope.h"


namespace Library
{
	ScopeState::ScopeState(Datum* context):
		TypeState(context)
	{}

	Datum& ScopeState::operator=(Scope* const rhs)
	{
		if (mContext->mSize > 1) throw std::exception("Invalid assignment invocation");
		if (mContext->mSize == 0) mContext->setSize(1);
		mContext->mData.sc[0] = rhs;
		return *mContext;
	}

	/// Sets the number of elements in the array
	/// @param size: The new number of elements in the array
	void ScopeState::setSize(std::uint32_t size)
	{
		if (size > mContext->mCapacity) mContext->mCapacity = size;

		Scope** temp = mContext->mData.sc;
		mContext->mData.sc = static_cast<Scope**>(malloc(sizeof(Scope*) * mContext->mCapacity));
		memcpy_s(mContext->mData.sc, sizeof(Scope*) * mContext->mSize, temp, sizeof(Scope*) * mContext->mSize);

		if (size < mContext->mSize)
		{
			for (std::uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.sc[i] = nullptr;
			}
		}

		mContext->mSize = size;
	}

	void ScopeState::reserve(std::uint32_t capacity)
	{
		if (capacity < mContext->mSize) throw std::exception("Attempting to clobber occupied data");

		Scope** temp = mContext->mData.sc;
		mContext->mData.sc = static_cast<Scope**>(malloc(sizeof(Scope*) * capacity));
		memcpy_s(mContext->mData.sc, sizeof(Scope**) * mContext->mSize, temp, sizeof(Scope*) * mContext->mSize);

		if (mContext->mCapacity > 0) { free(temp); }
		mContext->mCapacity = capacity;
	}
}
