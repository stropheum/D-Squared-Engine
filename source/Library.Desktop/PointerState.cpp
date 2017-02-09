#include "pch.h"
#include "PointerState.h"


namespace Library
{
	PointerState::PointerState(Datum* const context):
		TypeState(context)
	{}

	PointerState::~PointerState()
	{}

	Datum& PointerState::operator=(Library::RTTI* const& rhs)
	{
		if (mContext->mSize == 0) mContext->setSize(1);
		mContext->mData.r[0] = rhs;
		return *mContext;
	}

	/// Reserves the number of RTTI pointers in the local buffer
	/// @Param capacity: The current maximum size of the array
	void PointerState::setSize(std::uint32_t size)
	{
		if (size > mContext->mCapacity) mContext->mCapacity = size;

		Library::RTTI** temp = mContext->mData.r;
		mContext->mData.r = static_cast<Library::RTTI**>(malloc(sizeof(Library::RTTI) * mContext->mCapacity));
		memcpy_s(mContext->mData.r, sizeof(Library::RTTI) * mContext->mSize, temp, sizeof(Library::RTTI) * mContext->mSize);

		if (size < mContext->mSize)
		{
			for (std::uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.r[i] = nullptr;
			}
		}

		mContext->mSize = size;
	}
}
