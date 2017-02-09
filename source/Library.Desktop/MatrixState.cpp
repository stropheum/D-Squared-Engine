#include "pch.h"
#include "MatrixState.h"


namespace Library
{
	MatrixState::MatrixState(Datum* const context):
		TypeState(context)
	{}

	MatrixState::~MatrixState()
	{}

	Datum& MatrixState::operator=(const glm::mat4& rhs)
	{
		if (mContext->mSize > 1) throw std::exception("Invalid assignment invocation");
		if (mContext->mSize == 0) mContext->setSize(1);
		mContext->mData.m[0] = rhs;
		return *mContext;
	}

	/// Reserves the number of matrices in the local buffer
	/// @Param capacity: The current maximum size of the array
	void MatrixState::setSize(std::uint32_t size)
	{
		if (size > mContext->mCapacity) mContext->mCapacity = size;

		glm::mat4* temp = mContext->mData.m;
		mContext->mData.m = static_cast<glm::mat4*>(malloc(sizeof(glm::mat4) * mContext->mCapacity));
		memcpy_s(mContext->mData.m, sizeof(glm::mat4) * mContext->mSize, temp, sizeof(glm::mat4) * mContext->mSize);

		if (size < mContext->mSize)
		{
			for (std::uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.m[i] = glm::mat4(NULL);
			}
		}

		mContext->mSize = size;
	}
}
