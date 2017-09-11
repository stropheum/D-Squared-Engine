#include "pch.h"
#include "IntegerState.h"


using namespace std;

namespace Library
{
	IntegerState::IntegerState(Datum* const context):
		TypeState(context)
	{}

	bool IntegerState::operator==(const Datum& rhs)
	{
		bool result = false;

		if (mContext->mType == rhs.mType && mContext->mSize == rhs.mSize)
		{
			result = true;
			for (uint32_t i = 0; i < mContext->mSize; i++)
			{
				if (mContext->mData.i[i] != rhs.mData.i[i])
				{
					result = false;
					break;
				}
			}
		}

		return result;
	}

	Datum& IntegerState::operator=(const int32_t& rhs)
	{
		if (mContext->mSize > 1) throw exception("Invalid assignment invocation");
		if (mContext->mSize == 0) mContext->SetSize(1);
		mContext->mData.i[0] = rhs;
		return *mContext;
	}


	void IntegerState::SetSize(const uint32_t& size)
	{
		mContext->mData.vp = realloc(mContext->mData.vp, sizeof(int32_t) * size);
		mContext->mCapacity = mContext->mSize = size;

		if (size < mContext->mSize)
		{
			for (uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.i[i] = 0;
			}
		}
	}

	void IntegerState::Reserve(const uint32_t& capacity)
	{
		if (capacity > mContext->mCapacity)
		{
			mContext->mData.vp = realloc(mContext->mData.vp, sizeof(int32_t) * capacity);
			mContext->mCapacity = capacity;
		}
	}

	void IntegerState::Clear()
	{
		if (mContext->mSize > 0)
		{
			for (uint32_t i = 0; i < mContext->mSize; i++) mContext->mData.i[i] = 0;
			mContext->mSize = 0;
		}
	}

	void IntegerState::SetFromString(const string& value, const uint32_t& index)
	{
		int32_t result = stoi(value);
		mContext->Set(result, index);
	}

	void IntegerState::SetStorage(const Datum& rhs)
	{
		SetStorage(rhs.mData.i, rhs.mSize);
	}

	void IntegerState::SetStorage(int32_t* data, const uint32_t& size)
	{
		if (mContext->mType != DatumType::Integer)
		{
			throw exception("Attempting to reassign Datum Type");
		}
		
		if (mContext->mCapacity > 0) Clear();

		mContext->mDataIsExternal = true;
		mContext->mData.i = data;
		mContext->mCapacity = mContext->mSize = size;
	}

	string IntegerState::ToString(const uint32_t& index)
	{
		char value[50];
		sprintf_s(value, "%d", mContext->Get<int32_t>(index));
		return value;
	}
}
