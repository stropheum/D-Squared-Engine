#include "pch.h"
#include "VectorState.h"


namespace Library
{
	VectorState::VectorState(Datum* const context):
		TypeState(context)
	{}

	VectorState::~VectorState()
	{}

	Datum& VectorState::operator=(const glm::vec4& rhs)
	{
		if (mContext->mSize > 1) throw std::exception("Invalid assignment invocation");
		if (mContext->mSize == 0) mContext->setSize(1);
		mContext->mData.v[0] = rhs;
		return *mContext;
	}

	/// Reserves the number of vectors in the local buffer
	/// @Param capacity: The current maximum size of the array
	void VectorState::setSize(std::uint32_t size)
	{
		if (size > mContext->mCapacity) mContext->mCapacity = size;

		glm::vec4* temp = mContext->mData.v;
		mContext->mData.v = static_cast<glm::vec4*>(malloc(sizeof(glm::vec4) * mContext->mCapacity));
		memcpy_s(mContext->mData.v, sizeof(glm::vec4) * mContext->mSize, temp, sizeof(glm::vec4) * mContext->mSize);

		if (size < mContext->mSize)
		{
			for (std::uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.v[i] = glm::vec4(NULL);
			}
		}

		mContext->mSize = size;
	}

	void VectorState::reserve(std::uint32_t capacity)
	{
		if (capacity < mContext->mSize) throw std::exception("Attempting to clobber occupied data");
		mContext->mCapacity = capacity;

		glm::vec4* temp = mContext->mData.v;
		mContext->mData.v = static_cast<glm::vec4*>(malloc(sizeof(glm::vec4) * mContext->mCapacity));
		memcpy_s(mContext->mData.v, sizeof(glm::vec4) * mContext->mSize, temp, sizeof(glm::vec4) * mContext->mSize);

		if (temp != nullptr) free(temp);
	}

	void VectorState::clear()
	{
		if (mContext->mSize > 0)
		{
			for (std::uint32_t i = 0; i < mContext->mSize; i++) mContext->mData.v[i] = glm::vec4(NULL);
			mContext->mSize = 0;
		}
	}

	void VectorState::setFromString(const std::string& value, const std::uint32_t& index)
	{
		UNREFERENCED_PARAMETER(value);
		UNREFERENCED_PARAMETER(index);
	}
}
