#pragma once
#include "Scope.h"

namespace Library
{
	class Attributed : public Scope
	{
		RTTI_DECLARATIONS(Attributed, Scope)

	public:

#pragma region Constructors, Copy/Move semantics

		Attributed();
		virtual ~Attributed();

		Attributed(const Attributed& rhs);
		Attributed& operator= (const Attributed& rhs);

		Attributed(Attributed&& rhs);
		Attributed& operator=(Attributed&& rhs);

#pragma endregion

#pragma region Public Methods

		void populate();

		bool isPrescribedAttribute(std::string name) const;

		bool isAuxiliaryAttribute(std::string name) const;

		bool isAttribute(std::string name) const;

		Datum& appendAuxiliaryAttribute(std::string name);

		std::uint32_t auxiliaryBegin() const;

#pragma endregion

	protected:
#pragma region Signature
	
		class Signature
		{
		public:
			std::string Name;
			DatumType Type;
			Datum::DatumValues InitialValue;
			std::uint32_t Size;
			Datum::DatumValues* Storage;
		};

#pragma endregion

	private:
#pragma region Private Methods

		// TODO: Figure out how to get a signature from a list of signatures
		Signature& getSignature();

#pragma endregion

#pragma region Private Variables

		Vector<std::string> mPrescribedAttributes;
		Signature mSignature;

#pragma endregion

	};
}


