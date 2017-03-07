#include "pch.h"
#include "Attributed.h"

namespace Library
{
	RTTI_DEFINITIONS(Attributed)

#pragma region Constructors, Copy/Move semantics

	Attributed::Attributed()
	{
		appendScope("this");
	}

	Attributed::~Attributed()
	{
		
	}

	Attributed::Attributed(const  Attributed& rhs)
	{
		operator=(rhs);
	}

	Attributed& Attributed::operator=(const Attributed& rhs)
	{
		if (this != &rhs)
		{
			appendScope("this");
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
			appendScope("this");
		}
		return *this;
	}

#pragma endregion

#pragma region Public Methods

	void Attributed::populate()
	{
		//(*this)["this"] = this; // Apply the "this" attribute first

		for (std::uint32_t i = 0; i < mPrescribedAttributes.size(); i++)
		{
			Signature attribute = mPrescribedAttributes[i];
			auto& appendedScope = append(attribute.Name);
			appendedScope = attribute.Type;

			switch (attribute.Type)
			{
				case DatumType::Integer:
					appendedScope.setStorage(attribute.Storage->i, attribute.Size);
					for (std::uint32_t j = 0; j < attribute.Size; j++)
					{
						appendedScope.set(attribute.InitialValue.i[i]);
					}
					break;

				case DatumType::Float:
					appendedScope.setStorage(attribute.Storage->f, attribute.Size);
					for (std::uint32_t j = 0; j < attribute.Size; j++)
					{
						appendedScope.set(attribute.InitialValue.f[i]);
					}
					break;

				case DatumType::Vector:
					appendedScope.setStorage(attribute.Storage->v, attribute.Size);
					for (std::uint32_t j = 0; j < attribute.Size; j++)
					{
						appendedScope.set(attribute.InitialValue.v[i]);
					}
					break;

				case DatumType::Matrix:
					appendedScope.setStorage(attribute.Storage->m, attribute.Size);
					for (std::uint32_t j = 0; j < attribute.Size; j++)
					{
						appendedScope.set(attribute.InitialValue.m[i]);
					}
					break;

				case DatumType::Scope:
					// Scopes don't have storage so do nothing
					break;

				case DatumType::String:
					appendedScope.setStorage(attribute.Storage->s, attribute.Size);
					for (std::uint32_t j = 0; j < attribute.Size; j++)
					{
						appendedScope.set(attribute.InitialValue.s[i]);
					}
					break;

				case DatumType::Pointer:
					appendedScope.setStorage(attribute.Storage->r, attribute.Size);
					for (std::uint32_t j = 0; j < attribute.Size; j++)
					{
						appendedScope.set(attribute.InitialValue.r[i]);
					}
					break;

				default:
					throw std::exception("Setting storage of invalid/unknown type");
			}
		}
	}

	bool Attributed::isPrescribedAttribute(std::string name) const
	{
		for (auto iter = mPrescribedAttributes.begin(); iter != mPrescribedAttributes.end(); ++iter)
		{
			if ((*iter).Name == name)
			{
				return true;
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