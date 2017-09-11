#include "pch.h"
#include "PointerState.h"


namespace Library
{
	PointerState::PointerState(Datum* const context):
		TypeState(context)
	{}

	bool PointerState::operator==(const Datum& rhs)
	{
		bool result = false;

		if (mContext->mType == rhs.mType && mContext->mSize == rhs.mSize)
		{
			result = true;
			for (std::uint32_t i = 0; i < mContext->mSize; i++)
			{
				if (mContext->mData.r[i] != rhs.mData.r[i])
				{
					result = false;
					break;
				}
			}
		}

		return result;
	}

	Datum& PointerState::operator=(Library::RTTI* const& rhs)
	{
		if (mContext->mSize == 0) mContext->SetSize(1);
		mContext->mData.r[0] = rhs;
		return *mContext;
	}

	void PointerState::SetSize(const std::uint32_t& size)
	{
		mContext->mData.vp = realloc(mContext->mData.vp, sizeof(Library::RTTI*) * size);
		mContext->mCapacity = mContext->mSize = size;

		if (size <mContext->mSize)
		{
			for (std::uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.r[i] = nullptr;
			}
		}
	}

	void PointerState::Reserve(const std::uint32_t& capacity)
	{
		if (capacity > mContext->mCapacity)
		{
			mContext->mData.vp = realloc(mContext->mData.vp, sizeof(Library::RTTI*) * capacity);
			mContext->mCapacity = capacity;
		}
	}

	void PointerState::Clear()
	{
		if (mContext->mSize > 0)
		{
			for (std::uint32_t i = 0; i < mContext->mSize; i++) mContext->mData.r[i] = nullptr;
			mContext->mSize = 0;
		}
	}

	void PointerState::SetFromString(const std::string& value, const std::uint32_t& index)
	{
		UNREFERENCED_PARAMETER(value);
		UNREFERENCED_PARAMETER(index);
		throw std::exception("Attempting to Set pointer from string");
	}

	void PointerState::SetStorage(const Datum& rhs)
	{
		SetStorage(rhs.mData.r, rhs.mSize);
	}

	void PointerState::SetStorage(Library::RTTI** data, const std::uint32_t& size)
	{
		if (mContext->mType != DatumType::Pointer) { throw std::exception("Attempting to reassign Datum Type"); }

		if (mContext->mCapacity > 0) Clear();

		mContext->mDataIsExternal = true;
		mContext->mData.r = data;
		mContext->mCapacity = mContext->mSize = size;
	}

	std::string PointerState::ToString(const std::uint32_t& index)
	{
		UNREFERENCED_PARAMETER(index);
		return "";
	}
}
