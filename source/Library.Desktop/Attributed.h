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
		virtual ~Attributed(){};

		Attributed(const Attributed& rhs);
		Attributed& operator= (const Attributed& rhs);

		Attributed(Attributed&& rhs);
		Attributed& operator=(Attributed&& rhs);

#pragma endregion

#pragma region Public Methods

		virtual void populate();

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
			/// Constructor For the signature type
			/// @Param name: The name of the signature
			/// @Param type: The type of data being passed in
			/// @Param initialValue: The initial value of the signature's data
			/// @Param size: The number of elements in the data
			/// @Param storage: The pointer to the external storage
			/// There are constructor overloads for each type of data, where InitialValue and storage will be set uniquely
			Signature(const std::string name, const DatumType type, const std::int32_t initialValue,
				const std::uint32_t size, std::int32_t* const storage):
				Name(name), Type(type), Size(size), Storage(nullptr)
			{
				InitialValue.i = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * Size));
				*InitialValue.i = initialValue;
				if (storage != nullptr)
				{
					Storage->i = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * Size));
					Storage->i = storage;
				}
			}

			Signature(const std::string name, const DatumType type, const float initialValue,
				const std::uint32_t size, float* const storage) :
				Name(name), Type(type), Size(size), Storage(nullptr)
			{
				InitialValue.f = static_cast<float*>(malloc(sizeof(float) * Size));
				*InitialValue.f = initialValue;
				if (storage != nullptr)
				{
					Storage->f = static_cast<float*>(malloc(sizeof(float) * Size));
					Storage->f = storage;
				}
			}

			Signature(const std::string name, const DatumType type, const glm::vec4 initialValue,
				const std::uint32_t size, glm::vec4* const storage) :
				Name(name), Type(type), Size(size), Storage(nullptr)
			{
				InitialValue.v = static_cast<glm::vec4*>(malloc(sizeof(glm::vec4) * Size));
				*InitialValue.v= initialValue;
				if (storage != nullptr)
				{
					Storage->v = static_cast<glm::vec4*>(malloc(sizeof(glm::vec4) * Size));
					Storage->v = storage;
				}
			}

			Signature(const std::string name, const DatumType type, glm::mat4 initialValue,
				const std::uint32_t size, glm::mat4* const storage) :
				Name(name), Type(type), Size(size), Storage(nullptr)
			{
				InitialValue.m = static_cast<glm::mat4*>(malloc(sizeof(glm::mat4) * Size));
				*InitialValue.m = initialValue;
				if (storage != nullptr)
				{
					Storage->m = static_cast<glm::mat4*>(malloc(sizeof(glm::mat4) * Size));
					Storage->m = storage;
				}
			}

			Signature(const std::string name, const DatumType type, const std::string initialValue,
				const std::uint32_t size, std::string* const storage) :
				Name(name), Type(type), Size(size), Storage(nullptr)
			{
				InitialValue.s = new std::string[size];

				*InitialValue.s = initialValue;
				if (storage != nullptr)
				{
					Storage->s = static_cast<std::string*>(malloc(sizeof(std::string) * Size));
					Storage->s = storage;
				}
			}

			Signature(const std::string name, const DatumType type, RTTI* const initialValue,
				const std::uint32_t size, RTTI** const storage) :
				Name(name), Type(type), Size(size), Storage(nullptr)
			{
				InitialValue.r = static_cast<RTTI**>(malloc(sizeof(RTTI*) * Size));
				*InitialValue.r = initialValue;
				if (storage != nullptr)
				{
					Storage->r = static_cast<RTTI**>(malloc(sizeof(RTTI*) * Size));
					Storage->r = storage;
				}
			}

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


