#include "pch.h"
#include "MatrixState.h"


namespace Library
{
	/// Constructor
	/// @Param context: The Datum object that the state operates one
	MatrixState::MatrixState(Datum* const context):
		TypeState(context)
	{}

	/// Scalar assignment operator
	/// @Param rhs: The matrix being set to the only element in the Datum
	/// @Return: The modified Datum object
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

	/// Modifies the capacity of the array to any value greater than or equal to current size
	/// @Param capacity: The new capacity of the array
	void MatrixState::reserve(std::uint32_t capacity)
	{
		if (capacity < mContext->mSize) throw std::exception("Attempting to clobber occupied data");

		glm::mat4* temp = mContext->mData.m;
		mContext->mData.m = static_cast<glm::mat4*>(malloc(sizeof(glm::mat4) * capacity));
		memcpy_s(mContext->mData.m, sizeof(glm::mat4) * mContext->mSize, temp, sizeof(glm::mat4) * mContext->mSize);

		if (mContext->mCapacity > 0) { free(temp); }
		mContext->mCapacity = capacity;
	}

	/// Clears the value of all elements in the array without changing capacity
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

		mContext->set(glm::mat4(
			x1, y1, z1, w1, 
			x2, y2, z2, w2, 
			x3, y3, z3, w3, 
			x4, y4, z4, w4), index);
	}

	/// Sets external storage on copy
	/// @Param rhs: The Datum object that the storage reference is being taken from
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
		if (mContext->mType != DatumType::Matrix) throw std::exception("Attempting to reassign Datum Type");
		if (mContext->mCapacity > 0) throw std::exception("Set storage called on non-empty Datum");
		
		mContext->mDataIsExternal = true;
		mContext->mData.m = data;
		mContext->mCapacity = mContext->mSize = size;
	}

	/// A string representation of a piece of data stored in the Datum object
	/// @Param index: Optional index of the value being retrieved. Defaulted to first element
	std::string MatrixState::toString(std::uint32_t index)
	{
		return glm::to_string(mContext->get<glm::mat4>(index));
	}
}
