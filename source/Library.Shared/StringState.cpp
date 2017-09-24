#include "pch.h"
#include "StringState.h"


using namespace std;

namespace Library
{
	StringState::StringState(Datum* const context):
		TypeState(context)
	{}

	bool StringState::operator==(const Datum& rhs)
	{
		bool result = false;

		if (mContext->mType == rhs.mType && mContext->mSize == rhs.mSize && mContext->mCapacity == rhs.mCapacity)
		{
			result = true;
			for (uint32_t i = 0; i < mContext->mSize; i++)
			{
				if (mContext->mData.s[i] != rhs.mData.s[i])
				{
					result = false;
					break;
				}
			}
		}

		return result;
	}

	Datum& StringState::operator=(const string& rhs)
	{
		if (mContext->mSize > 1) { throw exception("Invalid assignment invocation"); }
		if (mContext->mSize == 0) { mContext->SetSize(1); }
		mContext->mData.s[0] = rhs;
		return *mContext;
	}

	void StringState::SetSize(const uint32_t& size)
	{
		if (size < mContext->mSize)
		{
			for (uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.s[i].string::~string();
			}
		}

		mContext->mData.vp = realloc(mContext->mData.vp, sizeof(string) * size);

		if (size > mContext->mSize)
		{	// If our new Size is larger than before, we need to default construct new strings
			for (uint32_t i = mContext->mSize; i < size; i++)
			{	// Use placement new to construct new strings
				new(mContext->mData.s + i) string("");
			}
		}

		mContext->mCapacity = mContext->mSize = size;
	}

	void StringState::Reserve(const uint32_t& capacity)
	{
		if (capacity > mContext->mCapacity)
		{
			mContext->mData.vp = realloc(mContext->mData.vp, sizeof(string) * capacity);
			mContext->mCapacity = capacity;
		}
	}

	void StringState::Clear()
	{
		if (mContext->mSize > 0)
		{
			for (uint32_t i = 0; i < mContext->mSize; i++)
			{	// Placement new an empty string onto the array
				mContext->mData.s[i].string::~string();
			}
			mContext->mSize = 0;
		}
	}

	void StringState::SetFromString(const string& value, const uint32_t& index)
	{   // Strings don't have to be parsed, so they can be passed directly to Set
		mContext->Set(value, index); 
	}

	void StringState::SetStorage(const Datum& rhs)
	{
		SetStorage(rhs.mData.s, rhs.mSize);
	}

	void StringState::SetStorage(string* data, const uint32_t& size)
	{
		assert(mContext->mType == DatumType::String);
		
		if (mContext->mCapacity > 0) { Clear(); }

		mContext->mDataIsExternal = true;
		mContext->mData.s = data;
		mContext->mCapacity = mContext->mSize = size;
	}

	string StringState::ToString(const uint32_t& index)
	{
		return mContext->Get<string>(index);
	}
}
