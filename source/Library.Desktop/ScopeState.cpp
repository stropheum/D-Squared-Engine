#include "pch.h"
#include "ScopeState.h"
#include "Scope.h"


namespace Library
{
	ScopeState::ScopeState(Datum* context):
		TypeState(context)
	{}

	ScopeState::~ScopeState()
	{}

	/// Comparison operator for Datum objects
	/// @Param rhs: The Datum object being compared against
	/// @Return: True if type, size, and each element of the Datum objects are equivalent. False otherwise
	bool ScopeState::operator==(const Datum& rhs)
	{
		bool result = false;

		if (mContext->mType == rhs.mType && mContext->mSize == rhs.mSize)
		{
			result = true;
			for (std::uint32_t i = 0; i < mContext->mSize; i++)
			{
				if (mContext->mData.sc[i] != rhs.mData.sc[i])
				{
					result = false;
					break;
				}
			}
		}

		return result;
	}

	Datum& ScopeState::operator=(Scope* const rhs)
	{
		if (mContext->mSize > 1) throw std::exception("Invalid assignment invocation");
		if (mContext->mSize == 0) mContext->setSize(1);
		mContext->mData.sc[0] = rhs;
		return *mContext;
	}

	/// Sets the number of elements in the array
	/// @param size: The new number of elements in the array
	void ScopeState::setSize(std::uint32_t size)
	{
		if (size > mContext->mCapacity) mContext->mCapacity = size;

		Scope** temp = mContext->mData.sc;
		mContext->mData.sc = static_cast<Scope**>(malloc(sizeof(Scope*) * mContext->mCapacity));
		memcpy_s(mContext->mData.sc, sizeof(Scope*) * mContext->mSize, temp, sizeof(Scope*) * mContext->mSize);

		if (size < mContext->mSize)
		{
			for (std::uint32_t i = size; i < mContext->mSize; i++)
			{
				mContext->mData.sc[i] = nullptr;
			}
		}

		mContext->mSize = size;
	}

	void ScopeState::reserve(std::uint32_t capacity)
	{
		if (capacity < mContext->mSize) throw std::exception("Attempting to clobber occupied data");

		Scope** temp = mContext->mData.sc;
		mContext->mData.sc = static_cast<Scope**>(malloc(sizeof(Scope*) * capacity));
		memcpy_s(mContext->mData.sc, sizeof(Scope**) * mContext->mSize, temp, sizeof(Scope*) * mContext->mSize);

		if (mContext->mCapacity > 0) { free(temp); }
		mContext->mCapacity = capacity;
	}

	void ScopeState::clear()
	{
		if (mContext->mSize > 0)
		{
			for (std::uint32_t i = 0; i < mContext->mSize; i++) mContext->mData.sc[i] = nullptr;
			mContext->mSize = 0;
		}
	}

	void ScopeState::setFromString(const std::string& value, const std::uint32_t& index)
	{
		UNREFERENCED_PARAMETER(value);
		UNREFERENCED_PARAMETER(index);
		// TODO: Implement set from string for scope
	}

	/// Sets external storage on copy
	/// @Param rhs: The Datum object that the storage reference is being taken from
	void ScopeState::setStorage(const Datum& rhs)
	{
		setStorage(rhs.mData.sc, rhs.mSize);
	}

	void ScopeState::setStorage(Scope** data, std::uint32_t size)
	{
		if (mContext->mType != DatumType::Scope) throw std::exception("Attempting to reassign Datum Type");
		if (mContext->mCapacity > 0) throw std::exception("Set storage called on non-empty Datum");

		mContext->mDataIsExternal = true;
		mContext->mData.sc = data;
		mContext->mCapacity = mContext->mSize = size;
	}

	std::string ScopeState::toString(std::uint32_t index)
	{
		// TODO: Implement Scope toString method
		UNREFERENCED_PARAMETER(index);
		return "I'm a scope";
	}
}
