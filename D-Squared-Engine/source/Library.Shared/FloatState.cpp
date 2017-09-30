#include "pch.h"
#include "FloatState.h"


using namespace std;

namespace Library
{
	FloatState::FloatState(Datum& context):
		TypeState(context)
	{}

	bool FloatState::operator==(const Datum& rhs)
	{
		bool result = false;

		if (mContext.mType == rhs.mType && mContext.mSize == rhs.mSize)
		{
			result = true;
			for (uint32_t i = 0; i < mContext.mSize; i++)
			{
				if (mContext.mData.f[i] != rhs.mData.f[i])
				{
					result = false;
					break;
				}
			}
		}

		return result;
	}

	Datum& FloatState::operator=(const float& rhs)
	{
		if (mContext.mSize > 1) { throw exception("Invalid assignment invocation"); }
		if (mContext.mSize == 0) { mContext.SetSize(1); }
		mContext.mData.f[0] = rhs;
		return mContext;
	}

	void FloatState::SetSize(const uint32_t& size)
	{
		mContext.mData.vp = realloc(mContext.mData.vp, sizeof(float) * size);
		mContext.mCapacity = mContext.mSize = size;
	}

	void FloatState::Reserve(const uint32_t& capacity)
	{
		if (capacity > mContext.mCapacity)
		{
			mContext.mData.vp = realloc(mContext.mData.vp, sizeof(float) * capacity);
			mContext.mCapacity = capacity;
		}
	}

	void FloatState::Clear()
	{
		if (mContext.mSize > 0)
		{
			for (uint32_t i = 0; i < mContext.mSize; i++) mContext.mData.f[i] = NULL;
			mContext.mSize = 0;
		}
	}

	void FloatState::SetFromString(const string& value, const uint32_t& index)
	{
		float result;
		sscanf_s(value.c_str(), "%f", &result);
		mContext.Set(result, index);
	}

	void FloatState::SetStorage(const Datum& rhs)
	{
		SetStorage(rhs.mData.f, rhs.mSize);
	}

	void FloatState::SetStorage(float* data, const uint32_t& size)
	{
		assert(mContext.mType == DatumType::Float);
		
		if (mContext.mCapacity > 0)
		{
			Clear();
		}

		mContext.mDataIsExternal = true;
		mContext.mData.f = data;
		mContext.mCapacity = mContext.mSize = size;
	}

	string FloatState::ToString(const uint32_t& index)
	{
		char value[50];
		sprintf_s(value, "%f", mContext.Get<float>(index));
		return value;
	}
}
