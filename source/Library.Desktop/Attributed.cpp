#include "pch.h"
#include "Attributed.h"

namespace Library
{
	RTTI_DEFINITIONS(Attributed)

#pragma region Constructors, Copy/Move semantics

	Attributed::Attributed()
	{
		(*this)["this"] = this;
	}

	Attributed::~Attributed()
	{
		// TODO: Implement destructor
	}

	Attributed::Attributed(const  Attributed& rhs)
	{
		operator=(rhs);
	}

	Attributed& Attributed::operator=(const Attributed& rhs)
	{
		if (this != &rhs)
		{
			(*this)["this"] = this;
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
			(*this)["this"] = this;
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
					// Should we do nothing for RTTI pointers?
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

	std::uint32_t Attributed::auxiliaryBegin() const
	{
		// TODO: Implement auxiliaryBegin method
		return 0;
	}

#pragma endregion

#pragma region Private Methods

	/// Returns The signature of this attributed object
	Attributed::Signature& Attributed::getSignature()
	{	// Note: Do not call this in the constructor. Will NOT get polymorphic invocation!!!
		return mSignature;
	}

#pragma endregion
}