#include "pch.h"
#include "ScopeState.h"
#include "Scope.h"


using namespace std;

namespace Library
{
	ScopeState::ScopeState(Datum* context):
		TypeState(context)
	{}

	bool ScopeState::operator==(const Datum& rhs)
	{
		bool result = false;

		if (rhs.Type() == DatumType::Scope && mContext->Size() == rhs.Size())
		{
			result = true;
			for (uint32_t i = 0; i < mContext->Size(); i++)
			{
				if (*mContext->Get<Scope*>(i) != *rhs.Get<Scope*>(i))
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
		if (mContext->mSize > 1) throw exception("Invalid assignment invocation");
		if (mContext->mSize == 0) mContext->SetSize(1);
		mContext->mData.sc[0] = rhs;
		return *mContext;
	}

	void ScopeState::SetSize(const uint32_t& size)
	{
		mContext->mData.vp = realloc(mContext->mData.vp, sizeof(Scope*) * size);
		mContext->mCapacity = mContext->mSize = size;

		if (size <mContext->mSize)
		{
			for (uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.sc[i] = nullptr;
			}
		}
	}

	void ScopeState::Reserve(const uint32_t& capacity)
	{
		if (capacity > mContext->mCapacity)
		{
			mContext->mData.vp = realloc(mContext->mData.vp, sizeof(Scope*) * capacity);
			mContext->mCapacity = capacity;
		}
	}
}
