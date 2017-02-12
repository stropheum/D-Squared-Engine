#include "pch.h"
#include "VectorState.h"


namespace Library
{
	/// Constructor
	/// @Param context: The Datum object that the state operates one
	VectorState::VectorState(Datum* const context):
		TypeState(context)
	{}

	/// Comparison operator for Datum objects
	/// @Param rhs: The Datum object being compared against
	/// @Return: True if type, size, and each element of the Datum objects are equivalent. False otherwise
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

	/// Scalar assignment operator
	/// @Param rhs: The vector being set to the only element in the Datum
	/// @Return: The modified Datum object
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

	/// Modifies the capacity of the array to any value greater than or equal to current size
	/// @Param capacity: The new capacity of the array
	void VectorState::reserve(std::uint32_t capacity)
	{
		if (capacity < mContext->mSize) throw std::exception("Attempting to clobber occupied data");

		glm::vec4* temp = mContext->mData.v;
		mContext->mData.v = static_cast<glm::vec4*>(malloc(sizeof(glm::vec4) * capacity));
		memcpy_s(mContext->mData.v, sizeof(glm::vec4) * mContext->mSize, temp, sizeof(glm::vec4) * mContext->mSize);

		if (mContext->mCapacity > 0) { free(temp); }
		mContext->mCapacity = capacity;
	}

	/// Clears the value of all elements in the array without changing capacity
	void VectorState::clear()
	{
		if (mContext->mSize > 0)
		{
			for (std::uint32_t i = 0; i < mContext->mSize; i++) mContext->mData.v[i] = glm::vec4(NULL);
			mContext->mSize = 0;
		}
	}

	/// Parses a string value and assigns the specified index of the array to its value
	/// @Param value: The string value being parsed
	/// @Param index: The index of the array being assigned to
	void VectorState::setFromString(const std::string& value, const std::uint32_t& index)
	{
		float x, y, z, w;
		sscanf_s(value.c_str(), "vec4(%f, %f, %f, %f)", &x, &y, &z, &w);
		mContext->set(glm::vec4(x, y, z, w), index);
	}

	/// Sets external storage on copy
	/// @Param rhs: The Datum object that the storage reference is being taken from
	void VectorState::setStorage(const Datum& rhs)
	{
		setStorage(rhs.mData.v, rhs.mSize);
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Pram size: The number of elements in the external storage
	/// @Exception: Thrown if attempting to reassign datum type, or if local memory is already used
	void VectorState::setStorage(glm::vec4* data, std::uint32_t size)
	{
		if (mContext->mType != DatumType::Vector) throw std::exception("Attempting to reassign Datum Type");
		if (mContext->mCapacity > 0) throw std::exception("Attempting to set storage on a non-empty Datum object");
		mContext->mDataIsExternal = true;
		mContext->mType = DatumType::Vector;
		mContext->mData.v = data;
		mContext->mCapacity = mContext->mSize = size;
	}

	/// A string representation of a piece of data stored in the Datum object
	/// @Param index: Optional index of the value being retrieved. Defaulted to first element
	std::string VectorState::toString(std::uint32_t index)
	{
		return glm::to_string(mContext->get<glm::vec4>(index));
	}
}
