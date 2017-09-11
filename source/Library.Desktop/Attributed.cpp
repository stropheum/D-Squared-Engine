#include "pch.h"
#include "Attributed.h"

namespace Library
{
	RTTI_DEFINITIONS(Attributed)

#pragma region Constructors, Copy/Move semantics

	Attributed::Attributed()
	{
 		(*this)["this"] = static_cast<RTTI*>(this);
		mPrescribedAttributes.PushBack(
			Signature("this", DatumType::Pointer, 1u, static_cast<RTTI**>(nullptr)));
	}

	Attributed::~Attributed()
	{
		mPrescribedAttributes.Clear();
	}

	Attributed::Attributed(const  Attributed& rhs)
	{
		operator=(rhs);
	}

	Attributed& Attributed::operator=(const Attributed& rhs)
	{
		if (this != &rhs)
		{
			(*this)["this"] = static_cast<RTTI*>(this);
			
			if (rhs.mPrescribedAttributes.Size() > 1)
			{	// We only do a copy if there is more than the "this" pointer stored
				for (std::uint32_t i = 1; i < rhs.mPrescribedAttributes.Size(); i++)
				{
					mPrescribedAttributes.PushBack(rhs.mPrescribedAttributes[i]);
				}
			}

			mAuxiliaryAttributes = rhs.mAuxiliaryAttributes;
		}
		return *this;
	}

	Attributed::Attributed(Attributed&& rhs) noexcept
	{
		operator=(rhs);
	}

	Attributed& Attributed::operator=(Attributed&& rhs) noexcept
	{
		if (this != &rhs)
		{
			(*this)["this"] = static_cast<RTTI*>(this);
			
			if (rhs.mPrescribedAttributes.Size() > 1)
			{	// We only do a copy if there is more than the "this" pointer stored
				for (std::uint32_t i = 1; i < rhs.mPrescribedAttributes.Size(); i++)
				{
					Adopt(rhs[i][0], mPrescribedAttributes[i].Name);
				}
			}

			rhs.mPrescribedAttributes.Clear();
			rhs.mAuxiliaryAttributes.Clear();
		}
		return *this;
	}

#pragma endregion

#pragma region Public Methods

	void Attributed::Populate()
	{
		for (std::uint32_t i = 0; i < mPrescribedAttributes.Size(); i++)
		{
			Signature attribute = mPrescribedAttributes[i];
			auto& appendedScope = Append(attribute.Name);
			appendedScope = attribute.Type;

			switch (attribute.Type)
			{
				case DatumType::Integer:
					if (attribute.Storage.i != nullptr)
					{
						appendedScope.SetType(DatumType::Integer);
						appendedScope.SetStorage(attribute.Storage.i, attribute.Size);
					}
					break;

				case DatumType::Float:
					if (attribute.Storage.f != nullptr)
					{
						appendedScope.SetType(DatumType::Float);
						appendedScope.SetStorage(attribute.Storage.f, attribute.Size);
					}
					break;

				case DatumType::Vector:
					if (attribute.Storage.v != nullptr)
					{
						appendedScope.SetType(DatumType::Vector);
						appendedScope.SetStorage(attribute.Storage.v, attribute.Size);
					}
					break;

				case DatumType::Matrix:
					if (attribute.Storage.m != nullptr)
					{
						appendedScope.SetType(DatumType::Matrix);
						appendedScope.SetStorage(attribute.Storage.m, attribute.Size);
					}
					break;

				case DatumType::Scope:
					// Scopes don't have storage so do nothing
					break;

				case DatumType::String:
					if (attribute.Storage.s != nullptr)
					{
						appendedScope.SetType(DatumType::String);
						appendedScope.SetStorage(attribute.Storage.s, attribute.Size);
					}
					break;

				case DatumType::Pointer:
					if (attribute.Storage.r != nullptr)
					{
						appendedScope.SetType(DatumType::Pointer);
						appendedScope.SetStorage(attribute.Storage.r, attribute.Size);
					}
					break;

				default:
					throw std::exception("Setting storage of invalid/unknown type");
			}
		}
	}

	bool Attributed::IsPrescribedAttribute(const std::string& name) const
	{
		if (IsAttribute(name))
		{
			for (auto iter = mPrescribedAttributes.begin(); iter != mPrescribedAttributes.end(); ++iter)
			{
				if ((*iter).Name == name)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool Attributed::IsAuxiliaryAttribute(const std::string& name) const
	{
		return !IsPrescribedAttribute(name);
	}

	bool Attributed::IsAttribute(const std::string& name) const
	{
		return Find(name) != nullptr;
	}

	Datum& Attributed::AppendAuxiliaryAttribute(const std::string& name)
	{
		return Append(name);
	}

#pragma endregion

#pragma region Private Methods

	// Returns The signature of this attributed object
	Attributed::Signature& Attributed::GetSignature(const std::string& name)
	{	
		Signature* result = nullptr;

		if (!IsAttribute(name))
		{
			throw std::exception("Attempting to get signature of nonexistent attribute");
		}

		if (IsPrescribedAttribute(name))
		{
			for (std::uint32_t i = 0; i < mPrescribedAttributes.Size(); i++)
			{
				if (mPrescribedAttributes[i].Name == name)
				{
					result = &mPrescribedAttributes[i];
				}
			}
		}
		else
		{	// We know it's an auxiliary attribute, so we're going to Search through those now
			for (std::uint32_t i = 0; i < mAuxiliaryAttributes.Size(); i++)
			{
				if (mAuxiliaryAttributes[i].Name == name)
				{
					result = &mAuxiliaryAttributes[i];
				}
			}
		}

		// Could potentially return a nullptr reference, but if IsAttribute works properly, 
		// we could never hit that exception and would affect code coverage
		return *result; 
	}
#pragma endregion
}