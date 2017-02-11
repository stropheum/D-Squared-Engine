#include "pch.h"
#include "StringState.h"


namespace Library
{
	StringState::StringState(Datum* const context):
		TypeState(context)
	{}


	StringState::~StringState()
	{}

	Datum& StringState::operator=(const std::string& rhs)
	{
		if (mContext->mSize > 1) throw std::exception("Invalid assignment invocation");
		if (mContext->mSize == 0) mContext->setSize(1);
		mContext->mData.s[0] = rhs;
		return *mContext;
	}

	/// Reserves the number of strings in the local buffer
	/// @Param capacity: The current maximum size of the array
	void StringState::setSize(std::uint32_t size)
	{
		if (size > mContext->mCapacity) mContext->mCapacity = size;

		std::string* temp = mContext->mData.s;
		mContext->mData.s = new std::string[mContext->mCapacity];
		for (std::uint32_t i = 0; i < mContext->mSize; i++)
		{
			mContext->mData.s[i] = temp[i];
		}

		if (size < mContext->mSize)
		{
			for (std::uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.s[i] = "";
			}
		}

		mContext->mSize = size;
	}

	void StringState::reserve(std::uint32_t capacity)
	{
		if (capacity < mContext->mSize) throw std::exception("Attempting to clobber occupied data");

		std::string* temp = mContext->mData.s;
		mContext->mData.s = new std::string[capacity];
		for (std::uint32_t i = 0; i < mContext->mSize; i++)
		{
			mContext->mData.s[i] = temp[i];
		}

		mContext->mCapacity = capacity;
	}

	void StringState::clear()
	{
		if (mContext->mSize > 0)
		{
			for (std::uint32_t i = 0; i < mContext->mSize; i++) mContext->mData.s[i] = "";
			mContext->mSize = 0;
		}
	}

	void StringState::setFromString(const std::string& value, const std::uint32_t& index)
	{
		UNREFERENCED_PARAMETER(value);
		UNREFERENCED_PARAMETER(index);
	}

	void StringState::setStorage(const Datum& rhs)
	{
		setStorage(rhs.mData.s, rhs.mSize);
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Pram size: The number of elements in the external storage
	/// @Exception: Thrown if attempting to reassign datum type, or if local memory is already used
	void StringState::setStorage(std::string* data, std::uint32_t size)
	{
		if (mContext->mType != DatumType::Unknown) throw std::exception("Attempting to reassign Datum Type");
		if (mContext->mType == DatumType::String && mContext->mData.s != nullptr)
			throw std::exception("Attempting to set storage on a non-empty Datum object");
		mContext->mDataIsExternal = true;
		mContext->mType = DatumType::String;
		mContext->mData.s = data;
		mContext->mCapacity = mContext->mSize = size;
	}
}
