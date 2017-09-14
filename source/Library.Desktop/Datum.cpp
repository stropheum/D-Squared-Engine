#include "pch.h"
#include "Datum.h"


using namespace std;

namespace Library
{
	Datum::Datum() :
		mTypeState(nullptr), mType(DatumType::Unknown), mCapacity(0), mSize(0), mDataIsExternal(false)
	{}

	Datum::Datum(const DatumType& type) :
		mTypeState(nullptr), mType(DatumType::Unknown), mCapacity(0), mSize(0), mDataIsExternal(false)
	{
		SetType(type);
		if (type != DatumType::Unknown) { Reserve(mCapacity); }
	}

	Datum::~Datum()
	{
		if (mCapacity > 0 && !mDataIsExternal)
		{	// Don't bother clearing memory if there isn't any reserved space
			SetSize(0); // Remove all elements, allowing us to shrink buffer to zero
		}

		delete mTypeState;
	}

	Datum::Datum(const Datum& rhs) :
		mTypeState(nullptr), mType(DatumType::Unknown), mCapacity(0), mSize(0), mDataIsExternal(false)
	{
		operator=(rhs); // Perform a deep copy of all the data
	}

	Datum& Datum::operator=(const Datum& rhs)
	{
		if (this != &rhs)
		{

			SetType(rhs.mType); // Must Set Type in order to instantiate mTypeState
			if (rhs.mDataIsExternal)
			{
				mTypeState->SetStorage(rhs);
			}
			else
			{
				Reserve(rhs.mCapacity);
				switch (rhs.mType)
				{
				case DatumType::Integer:
					for (uint32_t i = 0; i < rhs.mSize; i++)
					{
						PushBack(rhs.Get<int32_t>(i));
					}
					break;
				case DatumType::Float:
					for (uint32_t i = 0; i < rhs.mSize; i++)
					{
						PushBack(rhs.Get<float>(i));
					}
					break;
				case DatumType::Vector:
					for (uint32_t i = 0; i < rhs.mSize; i++)
					{
						PushBack(rhs.Get<glm::vec4>(i));
					}
					break;
				case DatumType::Matrix:
					for (uint32_t i = 0; i < rhs.mSize; i++)
					{
						PushBack(rhs.Get<glm::mat4>(i));
					}
					break;
				case DatumType::String:
					for (uint32_t i = 0; i < rhs.mSize; i++)
					{
						PushBack(rhs.Get<string>(i));
					}
					break;
				case DatumType::Pointer:
					for (uint32_t i = 0; i < rhs.mSize; i++)
					{
						PushBack(rhs.Get<Library::RTTI*>(i));
					}
					break;
				default: break;
				}
			}
		}

		return *this;
	}

	Datum::Datum(Datum&& rhs) noexcept :
		mTypeState(nullptr), mType(DatumType::Unknown), mCapacity(0), mSize(0), mDataIsExternal(false)
	{
		operator=(move(rhs)); // Perform a deep copy of all the data
	}

	Datum& Datum::operator=(Datum&& rhs) noexcept
	{
		if (this != &rhs)
		{
			SetType(rhs.mType); // Must Set Type in order to instantiate mTypeState
			if (rhs.mDataIsExternal)
			{
				mTypeState->SetStorage(rhs);
			}
			else
			{
				mData = move(rhs.mData);
				mType = move(rhs.mType);
				mCapacity = move(rhs.mCapacity);
				mSize = move(rhs.mSize);
			}

			rhs.mType = DatumType::Unknown;
			rhs.mCapacity = NULL;
			rhs.mSize = NULL;
		}

		return *this;
	}

	Scope& Datum::operator[](const uint32_t& index)
	{
		return *Get<Scope*>(index);
	}

	Datum& Datum::operator=(const DatumType& rhs)
	{
		SetType(rhs);
		return *this;
	}

	Datum& Datum::operator=(const int32_t& rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		SetType(DatumType::Integer);
		return mTypeState->operator=(rhs);
	}

	Datum& Datum::operator=(const float& rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		SetType(DatumType::Float);
		return mTypeState->operator=(rhs);
	}

	Datum& Datum::operator=(const glm::vec4& rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		SetType(DatumType::Vector);
		return mTypeState->operator=(rhs);
	}

	Datum& Datum::operator=(const glm::mat4& rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		SetType(DatumType::Matrix);
		return mTypeState->operator=(rhs);
	}

	Datum& Datum::operator=(Scope* const rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		SetType(DatumType::Scope);
		return mTypeState->operator=(rhs);
	}

	Datum& Datum::operator=(const string& rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		SetType(DatumType::String);
		return mTypeState->operator=(rhs);
	}

	Datum& Datum::operator=(Library::RTTI* const& rhs)
	{
		if (mTypeState != nullptr) return mTypeState->operator=(rhs);
		SetType(DatumType::Pointer);
		return mTypeState->operator=(rhs);
	}

	bool Datum::operator==(const Datum& rhs) const
	{
		if (mType == DatumType::Unknown && rhs.mType == DatumType::Unknown) { return true; }
		return mTypeState->operator==(rhs);
	}

	bool Datum::operator==(const DatumType& rhs) const
	{
		return mType == rhs;
	}

	bool Datum::operator==(const int32_t& rhs) const
	{
		return mType == DatumType::Integer &&
			mSize == 1 && mData.i[0] == rhs;
	}

	bool Datum::operator==(const float& rhs) const
	{
		return mType == DatumType::Float &&
			mSize == 1 && mData.f[0] == rhs;
	}

	bool Datum::operator==(const glm::vec4& rhs) const
	{
		return mType == DatumType::Vector &&
			mSize == 1 && mData.v[0] == rhs;
	}

	bool Datum::operator==(const glm::mat4& rhs) const
	{
		return mType == DatumType::Matrix &&
			mSize == 1 && mData.m[0] == rhs;
	}

	bool Datum::operator==(const Scope* rhs) const
	{
		return mType == DatumType::Scope &&
			mSize == 1 && mData.sc[0] == rhs;
	}

	bool Datum::operator==(const string& rhs) const
	{
		return mType == DatumType::String &&
			mSize == 1 && mData.s[0] == rhs;
	}

	bool Datum::operator==(Library::RTTI* const& rhs) const
	{
		return mType == DatumType::Pointer &&
			mSize == 1 && mData.r[0] == rhs;
	}

	bool Datum::operator!=(const Datum& rhs) const
	{
		return !(mTypeState->operator==(rhs));
	}

	bool Datum::operator!=(const DatumType& rhs) const
	{
		return !(operator==(rhs));
	}

	bool Datum::operator!=(const int32_t& rhs) const
	{
		return !(operator==(rhs));
	}

	bool Datum::operator!=(const float& rhs) const
	{
		return !(operator==(rhs));
	}

	bool Datum::operator!=(const glm::vec4& rhs) const
	{
		return !(operator==(rhs));
	}

	bool Datum::operator!=(const glm::mat4& rhs) const
	{
		return !(operator==(rhs));
	}

	bool Datum::operator!=(const string& rhs) const
	{
		return !(operator==(rhs));
	}

	bool Datum::operator!=(Library::RTTI* const& rhs) const
	{
		return !(operator==(rhs));
	}

	DatumType Datum::Type() const
	{
		return mType;
	}

	void Datum::SetType(const DatumType& type)
	{
		if (mType == type) { return; } // Avoid double instantiation of state without throwing an exception

		if (mType == DatumType::Unknown) { mType = type; }
		else { throw exception("Attempting to change Type on Datum object"); }

		if (mTypeState != nullptr)
		{	// If we've already Set state, make sure we delete the old Type state
			delete mTypeState;
		}

		switch (mType)
		{
			case DatumType::Integer:
				mTypeState = new IntegerState(this);
				break;
			case DatumType::Float:
				mTypeState = new FloatState(this);
				break;
			case DatumType::Vector:
				mTypeState = new VectorState(this);
				break;
			case DatumType::Matrix:
				mTypeState = new MatrixState(this);
				break;
			case DatumType::Scope:
				mTypeState = new ScopeState(this);
				break;
			case DatumType::String:
				mTypeState = new StringState(this);
				break;
			case DatumType::Pointer:
				mTypeState = new PointerState(this);
				break;
		}
	}

	uint32_t Datum::Size() const
	{
		return mSize;
	}

	uint32_t Datum::Capacity() const
	{
		return mCapacity;
	}

	void Datum::SetSize(const uint32_t& size) const
	{
		if (mType == DatumType::Unknown) { return; } // We don't have a type so we won't set size
		if (mDataIsExternal) { throw exception("Attempting to resize external storage"); }
		mTypeState->SetSize(size);
	}

	void Datum::Reserve(const uint32_t& capacity) const
	{
		if (mType == DatumType::Unknown) { return; }
		if (mDataIsExternal) { throw exception("Attempting to resize external storage"); }
		mTypeState->Reserve(capacity);
	}

	void Datum::Clear() const
	{
		if (mType == DatumType::Unknown) { return; } // We don't have a type so we do nothing
		mTypeState->Clear();
	}

	void Datum::SetStorage(int32_t* data, const uint32_t& size)
	{
		if (mTypeState == nullptr)
		{
			SetType(DatumType::Integer);
		}

		mTypeState->SetStorage(data, size);
	}

	void Datum::SetStorage(float* data, const uint32_t& size)
	{
		if (mTypeState == nullptr)
		{
			SetType(DatumType::Float);
		}

		mTypeState->SetStorage(data, size);
	}

	void Datum::SetStorage(glm::vec4* data, const uint32_t& size)
	{
		if (mTypeState == nullptr)
		{
			SetType(DatumType::Vector);
		}
		
		mTypeState->SetStorage(data, size);
	}

	void Datum::SetStorage(glm::mat4* data, const uint32_t& size)
	{
		if (mTypeState == nullptr)
		{
			SetType(DatumType::Matrix);
		}
		
		mTypeState->SetStorage(data, size);
	}

	void Datum::SetStorage(string* data, const uint32_t& size)
	{
		if (mTypeState == nullptr)
		{
			SetType(DatumType::String);
		}
		
		mTypeState->SetStorage(data, size);
	}

	void Datum::SetStorage(Library::RTTI** data, const uint32_t& size)
	{
		if (mTypeState == nullptr)
		{
			SetType(DatumType::Pointer);
		}
		
		mTypeState->SetStorage(data, size);
	}

	void Datum::Set(const int32_t& value, const uint32_t& index)
	{
		if (mType != DatumType::Integer) { throw exception("Calling Set on invalid Type"); }
		if (index > mSize) { throw exception("Attempting to Set beyond current Size"); }
		if (index == mSize)
		{
			PushBack(value); // If setting end, divert functionality to a push Back
		}
		new(mData.i + index) int32_t(value);
	}

	void Datum::Set(const float& value, const uint32_t& index)
	{
		if (mType != DatumType::Float) { throw exception("Calling Set on invalid Type"); }
		if (index > mSize) { throw exception("Attempting to Set beyond current Size"); }
		if (index == mSize)
		{
			PushBack(value); // If setting end, divert functionality to a push Back
		}
		new(mData.f + index) float(value);
	}

	void Datum::Set(const glm::vec4& value, const uint32_t& index)
	{
		if (mType != DatumType::Vector) { throw exception("Calling Set on invalid Type"); }
		if (index > mSize) { throw exception("Attempting to Set beyond current Size"); }
		if (index == mSize)
		{
			PushBack(value); // If setting end, divert functionality to a push Back
		}
		new(mData.v + index) glm::vec4(value);
	}

	void Datum::Set(const glm::mat4& value, const uint32_t& index)
	{
		if (mType != DatumType::Matrix) { throw exception("Calling Set on invalid Type"); }
		if (index > mSize) { throw exception("Attempting to Set beyond current Size"); }
		if (index == mSize)
		{
			PushBack(value); // If setting end, divert functionality to a push Back
		}
		new(mData.m + index) glm::mat4(value);
	}

	void Datum::Set(Scope* const& value, const uint32_t& index)
	{
		if (mType != DatumType::Scope) { throw exception("Calling Set on invalid Type"); }
		if (index > mSize) { throw exception("Attempting to Set beyond current Size"); }
		if (index == mSize)
		{
			PushBack(value); // If setting end, divert functionality to a push Back
		}
		new(mData.sc + index) Scope*(value);
	}

	void Datum::Set(const string& value, const uint32_t& index)
	{
		if (mType != DatumType::String) { throw exception("Calling Set on invalid Type"); }
		if (index > mSize) { throw exception("Attempting to Set beyond current Size"); }
		if (index == mSize)
		{
			PushBack(value); // If setting end, divert functionality to a push Back
		}
		
		mData.s[index] = value;
	}

	void Datum::Set(Library::RTTI* const& value, const uint32_t& index)
	{
		if (mType != DatumType::Pointer) { throw exception("Calling Set on invalid Type"); }
		if (index > mSize) { throw exception("Attempting to Set beyond current Size"); }
		if (index == mSize)
		{
			PushBack(value); // If setting end, divert functionality to a push Back
		}
		new(mData.r + index) RTTI*(value);
	}

	void Datum::PushBack(const int32_t& value)
	{
		SetSize(mSize + 1);
		Set(value, mSize - 1);
	}

	void Datum::PushBack(const float& value)
	{
		SetSize(mSize + 1);
		Set(value, mSize - 1);
	}

	void Datum::PushBack(const glm::vec4& value)
	{
		SetSize(mSize + 1);
		Set(value, mSize - 1);
	}

	void Datum::PushBack(const glm::mat4& value)
	{
		SetSize(mSize + 1);
		Set(value, mSize - 1);
	}

	void Datum::PushBack(Scope* const& value)
	{
		SetSize(mSize + 1);
		Set(value, mSize - 1);
	}

	void Datum::PushBack(const string& value)
	{
		SetSize(mSize + 1);
		Set(value, mSize - 1);
	}

	void Datum::PushBack(RTTI* const& value)
	{
		if (value == nullptr) { throw exception("Attempting to push Back nullptr"); }
		SetSize(mSize + 1);
		Set(value, mSize - 1);
	}

	void Datum::Remove(Scope* const scope)
	{
		if (mType == DatumType::Scope)
		{
			for (uint32_t i = 0; i < mSize; i++)
			{
				if(mData.sc[i] == scope)
				{
					mData.sc[i]->~Scope();
					memmove(mData.sc[i], mData.sc[i + 1], mSize - i - 1);
					mSize--;
				}
			}
		}
	}

	void Datum::SetFromString(const string& value, const uint32_t& index) const
	{
		mTypeState->SetFromString(value, index);
	}

	string Datum::ToString(const uint32_t& index) const
	{	
		if (mType == DatumType::Unknown) { return "Unknown Type"; }
		return mTypeState->ToString(index);
	}
}
