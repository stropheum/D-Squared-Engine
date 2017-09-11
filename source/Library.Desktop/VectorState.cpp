#include "pch.h"
#include "VectorState.h"


namespace Library
{
	VectorState::VectorState(Datum* const context):
		TypeState(context)
	{}

	bool VectorState::operator==(const Datum& rhs)
	{
		bool result = false;

		if (mContext->mType == rhs.mType && mContext->mSize == rhs.mSize)
		{
			result = true;
			for (std::uint32_t i = 0; i < mContext->mSize; i++)
			{
				if (mContext->mData.v[i] != rhs.mData.v[i])
				{
					result = false;
					break;
				}
			}
		}

		return result;
	}

	Datum& VectorState::operator=(const glm::vec4& rhs)
	{
		if (mContext->mSize > 1) throw std::exception("Invalid assignment invocation");
		if (mContext->mSize == 0) mContext->SetSize(1);
		mContext->mData.v[0] = rhs;
		return *mContext;
	}

	void VectorState::SetSize(const std::uint32_t& size)
	{
		mContext->mData.vp = realloc(mContext->mData.vp, sizeof(glm::vec4) * size);
		mContext->mCapacity = mContext->mSize = size;

		if (size <mContext->mSize)
		{
			for (std::uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.v[i] = glm::vec4(0);
			}
		}
	}

	void VectorState::Reserve(const std::uint32_t& capacity)
	{
		if (capacity > mContext->mCapacity)
		{
			mContext->mData.vp = realloc(mContext->mData.vp, sizeof(glm::vec4) * capacity);
			mContext->mCapacity = capacity;
		}
	}

	void VectorState::Clear()
	{
		if (mContext->mSize > 0)
		{
			for (std::uint32_t i = 0; i < mContext->mSize; i++) mContext->mData.v[i] = glm::vec4(NULL);
			mContext->mSize = 0;
		}
	}

	void VectorState::SetFromString(const std::string& value, const std::uint32_t& index)
	{
		float x;
		float y;
		float z;
		float w;
		sscanf_s(value.c_str(), "vec4(%f, %f, %f, %f)", &x, &y, &z, &w);
		mContext->Set(glm::vec4(x, y, z, w), index);
	}

	void VectorState::SetStorage(const Datum& rhs)
	{
		SetStorage(rhs.mData.v, rhs.mSize);
	}

	void VectorState::SetStorage(glm::vec4* data, const std::uint32_t& size)
	{
		if (mContext->mType != DatumType::Vector) { throw std::exception("Attempting to reassign Datum Type"); }

		if (mContext->mCapacity > 0) Clear();

		mContext->mDataIsExternal = true;
		mContext->mType = DatumType::Vector;
		mContext->mData.v = data;
		mContext->mCapacity = mContext->mSize = size;
	}

	std::string VectorState::ToString(const std::uint32_t& index)
	{
		return glm::to_string(mContext->Get<glm::vec4>(index));
	}
}
