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

		Signature& getSignature(const std::string& name);

#pragma endregion

	protected:
#pragma region Protected Variables

		/// This vector is used for populating prescribed attributes in children of attributed
		Vector<Signature> mPrescribedAttributes;

		/// This vector is used for populating auxiliary attributes in children of Attributed
		Vector<Signature> mAuxiliaryAttributes;

#pragma endregion

	};
}


