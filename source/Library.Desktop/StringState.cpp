#include "pch.h"
#include "StringState.h"


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
			for (std::uint32_t i = 0; i < mContext->mSize; i++)
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

	Datum& StringState::operator=(const std::string& rhs)
	{
		if (mContext->mSize > 1) throw std::exception("Invalid assignment invocation");
		if (mContext->mSize == 0) mContext->SetSize(1);
		mContext->mData.s[0] = rhs;
		return *mContext;
	}

	void StringState::SetSize(const std::uint32_t& size)
	{
		if (size < mContext->mSize)
		{
			for (std::uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.s[i].std::string::~string();
			}
		}

		mContext->mData.vp = realloc(mContext->mData.vp, sizeof(std::string) * size);

		if (size > mContext->mSize)
		{	// If our new Size is larger than before, we need to default construct new strings
			for (std::uint32_t i = mContext->mSize; i < size; i++)
			{	// Use placement new to construct new strings
				new(mContext->mData.s + i) std::string("");
			}
		}

		mContext->mCapacity = mContext->mSize = size;
	}

	void StringState::Reserve(const std::uint32_t& capacity)
	{
		if (capacity > mContext->mCapacity)
		{
			mContext->mData.vp = realloc(mContext->mData.vp, sizeof(std::string) * capacity);
			mContext->mCapacity = capacity;
		}
	}

	void StringState::Clear()
	{
		if (mContext->mSize > 0)
		{
			for (std::uint32_t i = 0; i < mContext->mSize; i++)
			{	// Placement new an empty string onto the array
				mContext->mData.s[i].std::string::~string();
			}
			mContext->mSize = 0;
		}
	}

	void StringState::SetFromString(const std::string& value, const std::uint32_t& index)
	{   // Strings don't have to be parsed, so they can be passed directly to Set
		mContext->Set(value, index); 
	}

	void StringState::SetStorage(const Datum& rhs)
	{
		SetStorage(rhs.mData.s, rhs.mSize);
	}

	void StringState::SetStorage(std::string* data, const std::uint32_t& size)
	{
		if (mContext->mType != DatumType::String)
		{
			throw std::exception("Attempting to reassign Datum Type");
		}
		
		if (mContext->mCapacity > 0) { Clear(); }

		mContext->mDataIsExternal = true;
		mContext->mData.s = data;
		mContext->mCapacity = mContext->mSize = size;
	}

	std::string StringState::ToString(const std::uint32_t& index)
	{
		return mContext->Get<std::string>(index);
	}
}
