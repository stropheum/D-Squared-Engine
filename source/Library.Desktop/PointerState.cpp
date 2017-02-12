#include "pch.h"
#include "PointerState.h"


namespace Library
{
	/// Constructor
	/// @Param context: The Datum object that the state operates one
	PointerState::PointerState(Datum* const context):
		TypeState(context)
	{}

	/// Scalar assignment operator
	/// @Param rhs: The RTTI pointer being set to the only element in the Datum
	/// @Return: The modified Datum object
	Datum& PointerState::operator=(Library::RTTI* const& rhs)
	{
		if (mContext->mSize == 0) mContext->setSize(1);
		mContext->mData.r[0] = rhs;
		return *mContext;
	}

	/// Sets the number of RTTI pointers in the local buffer
	/// @Param capacity: The current maximum size of the array
	void PointerState::setSize(std::uint32_t size)
	{
		if (size > mContext->mCapacity) mContext->mCapacity = size;

		Library::RTTI** temp = mContext->mData.r;
		mContext->mData.r = static_cast<Library::RTTI**>(malloc(sizeof(Library::RTTI) * mContext->mCapacity));
		memcpy_s(mContext->mData.r, sizeof(Library::RTTI) * mContext->mSize, temp, sizeof(Library::RTTI) * mContext->mSize);

		if (size < mContext->mSize)
		{
			for (std::uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.r[i] = nullptr;
			}
		}

		mContext->mSize = size;
	}

	/// Modifies the capacity of the array to any value greater than or equal to current size
	/// @Param capacity: The new capacity of the array
	void PointerState::reserve(std::uint32_t capacity)
	{
		if (capacity < mContext->mSize) throw std::exception("Attempting to clobber occupied data");

		Library::RTTI** temp = mContext->mData.r;
		mContext->mData.r = static_cast<Library::RTTI**>(malloc(sizeof(Library::RTTI*) * capacity));
		memcpy_s(mContext->mData.r, sizeof(Library::RTTI) * mContext->mSize, temp, sizeof(Library::RTTI) * mContext->mSize);

		if (mContext->mCapacity > 0) { free(temp); }
		mContext->mCapacity = capacity;
	}

	/// Clears the value of all elements in the array without changing capacity
	void PointerState::clear()
	{
		if (mContext->mSize > 0)
		{
			for (std::uint32_t i = 0; i < mContext->mSize; i++) mContext->mData.r[i] = nullptr;
			mContext->mSize = 0;
		}
	}

	/// Parses a string value and assigns the specified index of the array to its value
	/// @Param value: The string value being parsed
	/// @Param index: The index of the array being assigned to
	void PointerState::setFromString(const std::string& value, const std::uint32_t& index)
	{
		UNREFERENCED_PARAMETER(value);
		UNREFERENCED_PARAMETER(index);
		throw std::exception("Attempting to set pointer from string");
	}

	/// Sets external storage on copy
	/// @Param rhs: The Datum object that the storage reference is being taken from
	void PointerState::setStorage(const Datum& rhs)
	{
		setStorage(rhs.mData.r, rhs.mSize);
	}

	/// Sets the external storage to the specified pointer
	/// @Param data: The external storage being utilized
	/// @Pram size: The number of elements in the external storage
	/// @Exception: Thrown if attempting to reassign datum type, or if local memory is already used
	void PointerState::setStorage(Library::RTTI** data, std::uint32_t size)
	{
		if (mContext->mType != DatumType::Pointer) throw std::exception("Attempting to reassign Datum Type");
		if (mContext->mCapacity > 0) throw std::exception("Set storage called on non-empty Datum");

		mContext->mDataIsExternal = true;
		mContext->mData.r = data;
		mContext->mCapacity = mContext->mSize = size;
	}

	/// A string representation of a piece of data stored in the Datum object
	/// @Param index: Optional index of the value being retrieved. Defaulted to first element
	std::string PointerState::toString(std::uint32_t index)
	{
		UNREFERENCED_PARAMETER(index);
		return "";
	}
}
