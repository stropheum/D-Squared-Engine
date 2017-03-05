#include "pch.h"
#include "Attributed.h"

namespace Library
{
	RTTI_DEFINITIONS(Attributed)

#pragma region Constructors, Copy/Move semantics

	Attributed::Attributed()
	{
		// TODO: Implement constructor
	}

	Attributed::~Attributed()
	{
		// TODO: Implement destructor
	}

	Attributed::Attributed(const  Attributed& rhs)
	{
		// TODO: Implement copy constructor
		UNREFERENCED_PARAMETER(rhs);
	}

	Attributed& Attributed::operator=(const Attributed& rhs)
	{
		// TODO: Implement assignment operator
		UNREFERENCED_PARAMETER(rhs);
		return *this;
	}

	Attributed::Attributed(Attributed&& rhs)
	{
		// TODO: Implement move copy constructor
		UNREFERENCED_PARAMETER(rhs);
	}

	Attributed& Attributed::operator=(Attributed&& rhs)
	{
		// TODO: Implement move assignment operator
		UNREFERENCED_PARAMETER(rhs);
		return *this;
	}

#pragma endregion

#pragma region Public Methods

	void Attributed::populate()
	{
		append("this") = DatumType::Pointer;
		// TODO: Append all prescribed attributes to the scope somehow
	}

	bool Attributed::isPrescribedAttribute(std::string name) const
	{
		return mPrescribedAttributes.find(name) != mPrescribedAttributes.end();
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