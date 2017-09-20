#include "pch.h"
#include "MatrixState.h"


using namespace std;

namespace Library
{
	MatrixState::MatrixState(Datum* const context):
		TypeState(context)
	{}

	bool MatrixState::operator==(const Datum& rhs)
	{
		bool result = false;

		if (mContext->mType == rhs.mType && mContext->mSize == rhs.mSize)
		{
			result = true;
			for (uint32_t i = 0; i < mContext->mSize; i++)
			{
				if (mContext->mData.m[i] != rhs.mData.m[i])
				{
					result = false;
					break;
				}
			}
		}

		return result;
	}

	Datum& MatrixState::operator=(const glm::mat4x4& rhs)
	{
		if (mContext->mSize > 1) throw exception("Invalid assignment invocation");
		if (mContext->mSize == 0) mContext->SetSize(1);
		mContext->mData.m[0] = rhs;
		return *mContext;
	}

	void MatrixState::SetSize(const uint32_t& size)
	{
		mContext->mData.vp = realloc(mContext->mData.vp, sizeof(glm::mat4x4) * size);
		mContext->mCapacity = mContext->mSize = size;

		if (size <mContext->mSize)
		{
			for (uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.m[i] = glm::mat4x4(0);
			}
		}
	}

	void MatrixState::Reserve(const uint32_t& capacity)
	{
		if (capacity > mContext->mCapacity)
		{
			mContext->mData.vp = realloc(mContext->mData.vp, sizeof(glm::mat4x4) * capacity);
			mContext->mCapacity = capacity;
		}
	}

	void MatrixState::Clear()
	{
		if (mContext->mSize > 0)
		{
			for (uint32_t i = 0; i <mContext->mSize; i++) mContext->mData.m[i] = glm::mat4x4(0);
			mContext->mSize = 0;
		}
	}

	void MatrixState::SetFromString(const string& value, const uint32_t& index)
	{
		float x1, y1, z1, w1;
		float x2, y2, z2, w2;
		float x3, y3, z3, w3;
		float x4, y4, z4, w4;

		sscanf_s(value.c_str(),
			"mat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))",
			&x1, &y1, &z1, &w1,
			&x2, &y2, &z2, &w2, 
			&x3, &y3, &z3, &w3, 
			&x4, &y4, &z4, &w4);

		mContext->Set(glm::mat4x4(
			x1, y1, z1, w1, 
			x2, y2, z2, w2, 
			x3, y3, z3, w3, 
			x4, y4, z4, w4), index);
	}

	void MatrixState::SetStorage(const Datum& rhs)
	{
		SetStorage(rhs.mData.m, rhs.mSize);
	}

	void MatrixState::SetStorage(glm::mat4x4* data, const uint32_t& size)
	{
		if (mContext->mType != DatumType::Matrix) { throw exception("Attempting to reassign Datum Type"); }
		
		if (mContext->mCapacity > 0) Clear();

		mContext->mDataIsExternal = true;
		mContext->mData.m = data;
		mContext->mCapacity = mContext->mSize = size;
	}

	string MatrixState::ToString(const uint32_t& index)
	{
		return glm::to_string(mContext->Get<glm::mat4x4>(index));
	}
}
