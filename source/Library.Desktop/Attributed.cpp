#include "pch.h"
#include "Attributed.h"

namespace Library
{
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
		mScope["this"] = DatumType::Pointer;
	}

	bool Attributed::isPrescribedAttribute(std::string name) const
	{
		// TODO: Implement isPrescrubedAttribute method
		UNREFERENCED_PARAMETER(name);
		return false;
	}

	bool Attributed::isAuxiliaryAttribute(std::string name) const
	{
		// TODO: Implement isAuxiliaryAttribute method
		UNREFERENCED_PARAMETER(name);
		return false;
	}

	bool Attributed::isAttribute(std::string name) const
	{
		return mScope.find(name) != nullptr;
	}

	Datum& Attributed::appendAuxiliaryAttribute(std::string name)
	{
		// TODO: Implement appendAuxiliaryAttribute method
		UNREFERENCED_PARAMETER(name);
		Datum* temp = new Datum();
		return *temp;
	}

	std::uint32_t Attributed::auxiliaryBegin() const
	{
		// TODO: Implement auxiliaryBegin method
		return 0;
	}

#pragma endregion

#pragma region Private Methods

	Attributed::Signature& Attributed::getSignature()
	{
		// TODO: Implement getSignature method
		Signature* temp = new Signature();
		return *temp;
	}

#pragma endregion
}