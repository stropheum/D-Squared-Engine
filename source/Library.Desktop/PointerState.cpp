#include "pch.h"
#include "PointerState.h"


namespace Library
{
	PointerState::PointerState(Datum* const context):
		TypeState(context)
	{}

	PointerState::~PointerState()
	{}

	Datum& PointerState::operator=(Library::RTTI* const& rhs)
	{
		if (mContext->mSize == 0) mContext->setSize(1);
		mContext->mData.r[0] = rhs;
		return *mContext;
	}

	/// Reserves the number of RTTI pointers in the local buffer
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

	void PointerState::reserve(std::uint32_t capacity)
	{
		if (capacity < mContext->mSize) throw std::exception("Attempting to clobber occupied data");

		Library::RTTI** temp = mContext->mData.r;
		mContext->mData.r = static_cast<Library::RTTI**>(malloc(sizeof(Library::RTTI*) * capacity));
		memcpy_s(mContext->mData.r, sizeof(Library::RTTI) * mContext->mSize, temp, sizeof(Library::RTTI) * mContext->mSize);

		if (mContext->mCapacity > 0) { free(temp); }
		mContext->mCapacity = capacity;
	}

	void PointerState::clear()
	{
		if (mContext->mSize > 0)
		{
			for (std::uint32_t i = 0; i < mContext->mSize; i++) mContext->mData.r[i] = nullptr;
			mContext->mSize = 0;
		}
	}

	void PointerState::setFromString(const std::string& value, const std::uint32_t& index)
	{
		UNREFERENCED_PARAMETER(value);
		UNREFERENCED_PARAMETER(index);
	}

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
}
