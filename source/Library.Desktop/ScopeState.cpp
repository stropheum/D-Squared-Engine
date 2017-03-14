#include "pch.h"
#include "ScopeState.h"
#include "Scope.h"


namespace Library
{
	ScopeState::ScopeState(Datum* context):
		TypeState(context)
	{}

	/// Comparison operator for Datum objects
	/// @Param rhs: The Datum object being compared against
	/// @Return: True if type, size, and each element of the Datum objects are equivalent. False otherwise
	/// @Exception: THrown if called from this context
	bool ScopeState::operator==(const Datum& rhs)
	{
		bool result = false;

		if (rhs.type() == DatumType::Scope && mContext->size() == rhs.size())
		{
			result = true;
			for (std::uint32_t i = 0; i < mContext->size(); i++)
			{
				if (*mContext->get<Scope*>(i) != *rhs.get<Scope*>(i))
				{	// If every scope doesn't match, we're done
					result = false;
					break;
				}
			}
		}

		return result;
	}

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
		mContext->mData.vp = realloc(mContext->mData.vp, sizeof(Scope*) * size);
		mContext->mCapacity = mContext->mSize = size;

		if (size <mContext->mSize)
		{
			for (std::uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.sc[i] = nullptr;
			}
		}
	}

	void ScopeState::reserve(std::uint32_t capacity)
	{
		if (capacity > mContext->mCapacity)
		{
			mContext->mData.vp = realloc(mContext->mData.vp, sizeof(Scope*) * capacity);
			mContext->mCapacity = capacity;
		}
	}
}
