#include "pch.h"
#include "Attributed.h"

namespace Library
{
	RTTI_DEFINITIONS(Attributed)

#pragma region Constructors, Copy/Move semantics

	Attributed::Attributed()
	{
 		(*this)["this"] = static_cast<RTTI*>(this);
		mPrescribedAttributes.pushBack(
			Signature("this", DatumType::Pointer, 1u, static_cast<RTTI**>(nullptr)));
	}

	Attributed::~Attributed()
	{
		mPrescribedAttributes.clear();
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
			
			if (rhs.mPrescribedAttributes.size() > 1)
			{	// We only do a copy if there is more than the "this" pointer stored
				for (std::uint32_t i = 1; i < rhs.mPrescribedAttributes.size(); i++)
				{
					mPrescribedAttributes.pushBack(rhs.mPrescribedAttributes[i]);
				}
			}

			mAuxiliaryAttributes = rhs.mAuxiliaryAttributes;
		}
		return *this;
	}

	Attributed::Attributed(Attributed&& rhs)
	{
		operator=(rhs);
	}

	Attributed& Attributed::operator=(Attributed&& rhs)
	{
		if (this != &rhs)
		{
			(*this)["this"] = static_cast<RTTI*>(this);
			
			if (rhs.mPrescribedAttributes.size() > 1)
			{	// We only do a copy if there is more than the "this" pointer stored
				for (std::uint32_t i = 1; i < rhs.mPrescribedAttributes.size(); i++)
				{
					adopt(rhs[i][0], mPrescribedAttributes[i].Name);
				}
			}

			rhs.mPrescribedAttributes.clear();
			rhs.mAuxiliaryAttributes.clear();
		}
		return *this;
	}

#pragma endregion

#pragma region Public Methods

	void Attributed::populate()
	{
		for (std::uint32_t i = 0; i < mPrescribedAttributes.size(); i++)
		{
			Signature attribute = mPrescribedAttributes[i];
			auto& appendedScope = append(attribute.Name);
			appendedScope = attribute.Type;

			switch (attribute.Type)
			{
				case DatumType::Integer:
					if (attribute.Storage.i != nullptr)
					{
						appendedScope.setType(DatumType::Integer);
						appendedScope.setStorage(attribute.Storage.i, attribute.Size);
					}
					break;

				case DatumType::Float:
					if (attribute.Storage.f != nullptr)
					{
						appendedScope.setType(DatumType::Float);
						appendedScope.setStorage(attribute.Storage.f, attribute.Size);
					}
					break;

				case DatumType::Vector:
					if (attribute.Storage.v != nullptr)
					{
						appendedScope.setType(DatumType::Vector);
						appendedScope.setStorage(attribute.Storage.v, attribute.Size);
					}
					break;

				case DatumType::Matrix:
					if (attribute.Storage.m != nullptr)
					{
						appendedScope.setType(DatumType::Matrix);
						appendedScope.setStorage(attribute.Storage.m, attribute.Size);
					}
					break;

				case DatumType::Scope:
					// Scopes don't have storage so do nothing
					break;

				case DatumType::String:
					if (attribute.Storage.s != nullptr)
					{
						appendedScope.setType(DatumType::String);
						appendedScope.setStorage(attribute.Storage.s, attribute.Size);
					}
					break;

				case DatumType::Pointer:
					if (attribute.Storage.r != nullptr)
					{
						appendedScope.setType(DatumType::Pointer);
						appendedScope.setStorage(attribute.Storage.r, attribute.Size);
					}
					break;

				default:
					throw std::exception("Setting storage of invalid/unknown type");
			}
		}
	}

	bool Attributed::isPrescribedAttribute(std::string name) const
	{
		if (isAttribute(name))
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

	bool Attributed::isAuxiliaryAttribute(std::string name) const
	{
		return !isPrescribedAttribute(name);
	}

	bool Attributed::isAttribute(std::string name) const
	{
		return find(name) != nullptr;
	}

	Datum& Attributed::appendAuxiliaryAttribute(std::string name)
	{
		return append(name);
	}

#pragma endregion

#pragma region Private Methods

	/// Returns The signature of this attributed object
	Attributed::Signature& Attributed::getSignature(const std::string& name)
	{	
		Signature* result = nullptr;

		if (!isAttribute(name))
		{
			throw std::exception("Attempting to get signature of nonexistent attribute");
		}

		if (isPrescribedAttribute(name))
		{
			for (std::uint32_t i = 0; i < mPrescribedAttributes.size(); i++)
			{
				if (mPrescribedAttributes[i].Name == name)
				{
					result = &mPrescribedAttributes[i];
				}
			}
		}
		else
		{	// We know it's an auxiliary attribute, so we're going to search through those now
			for (std::uint32_t i = 0; i < mAuxiliaryAttributes.size(); i++)
			{
				if (mAuxiliaryAttributes[i].Name == name)
				{
					result = &mAuxiliaryAttributes[i];
				}
			}
		}

		// Could potentially return a nullptr reference, but if isAttribute works properly, 
		// we could never hit that exception and would affect code coverage
		return *result; 
	}
#pragma endregion
}