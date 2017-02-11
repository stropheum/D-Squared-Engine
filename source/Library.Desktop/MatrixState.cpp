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

	void MatrixState::reserve(std::uint32_t capacity)
	{
		if (capacity < mContext->mSize) throw std::exception("Attempting to clobber occupied data");

		glm::mat4* temp = mContext->mData.m;
		mContext->mData.m = static_cast<glm::mat4*>(malloc(sizeof(glm::mat4) * capacity));
		memcpy_s(mContext->mData.m, sizeof(glm::mat4) * mContext->mSize, temp, sizeof(glm::mat4) * mContext->mSize);

		if (mContext->mCapacity > 0) { free(temp); }
		mContext->mCapacity = capacity;
	}

	void MatrixState::clear()
	{
		if (mContext->mSize > 0)
		{
			for (std::uint32_t i = 0; i <mContext->mSize; i++) mContext->mData.m[i] = glm::mat4(NULL);
			mContext->mSize = 0;
		}
	}

	void MatrixState::setFromString(const std::string& value, const std::uint32_t& index)
	{
		UNREFERENCED_PARAMETER(value);
		UNREFERENCED_PARAMETER(index);
	}

	void MatrixState::setStorage(const Datum& rhs)
	{
		setStorage(rhs.mData.m, rhs.mSize);
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Pram size: The number of elements in the external storage
	/// @Exception: Thrown if attempting to reassign datum type, or if local memory is already used
	void MatrixState::setStorage(glm::mat4* data, std::uint32_t size)
	{
		if (mContext->mType != DatumType::Unknown) throw std::exception("Attempting to reassign Datum Type");
		if (mContext->mType == DatumType::Matrix && mContext->mData.m != nullptr)
			throw std::exception("Attempting to set storage on a non-empty Datum object");
		mContext->mDataIsExternal = true;
		mContext->mType = DatumType::Matrix;
		mContext->mData.m = data;
		mContext->mCapacity = mContext->mSize = size;
	}
}
