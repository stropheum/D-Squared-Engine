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
