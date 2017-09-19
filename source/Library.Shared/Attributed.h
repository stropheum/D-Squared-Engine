#pragma once
#include "Scope.h"


namespace Library
{
	class Attributed : public Scope
	{
		RTTI_DECLARATIONS(Attributed, Scope)

	public:

#pragma region Construction/Copy/Assignment

		Attributed();

		virtual ~Attributed();

		Attributed(const Attributed& rhs);

		Attributed& operator=(const Attributed& rhs);

		Attributed(Attributed&& rhs) noexcept;

		Attributed& operator=(Attributed&& rhs) noexcept;

#pragma endregion

		/**
		 *  Populates the attributes
		 */
		void Populate();

		/**
		 * Determines if the specified string is a prescribed attribute
		 * @Param Name: The attribute being checked
		 * @Return: True if the attribute is a prescribed attribute
		 */
		bool IsPrescribedAttribute(const std::string& name) const;

		/**
		 * Determines if the specified string is an auxiliary attribute
		 * @Param Name: The attribute being checked
		 * @Return: True if the attribute is an auxiliary attribute
		 */
		bool IsAuxiliaryAttribute(const std::string& name) const;

		/**
		 * Determines if the specified string is an attribute
		 * @Param Name: The attribute being checked
		 * @Return: True if the attribute is an attribute
		 */
		bool IsAttribute(const std::string& name) const;

		/**
		 * Adds an auxiliary attribute to the current collection
		 * @Param Name: The Name of the new auxiliary attribute
		 * @Return: A reference to the Datum created from the appended attribute
		 */
		Datum& AppendAuxiliaryAttribute(const std::string& name);

	protected:
	
		class Signature;
//		{
//
//		public:
//			
//			/**
//			 * Constructor For the integer signature Type
//			 * @Param Name: The Name of the signature
//			 * @Param Type: The Type of data being passed in
//			 * @Param initialValue: The initial value of the signature's data
//			 * @Param Size: The number of elements in the data
//			 * @Param storage: The pointer to the external storage
//			 * There are constructor overloads for each Type of data, where InitialValue and storage will be Set uniquely
//			 */
//			Signature(const std::string name, const DatumType type,
//				const std::uint32_t size, std::int32_t* storage);
//
//			/**
//			 * Constructor For the float signature Type
//			 * @Param Name: The Name of the signature
//			 * @Param Type: The Type of data being passed in
//			 * @Param initialValue: The initial value of the signature's data
//			 * @Param Size: The number of elements in the data
//			 * @Param storage: The pointer to the external storage
//			 * There are constructor overloads for each Type of data, where InitialValue and storage will be Set uniquely
//			 */
//			Signature(const std::string name, const DatumType type,
//				const std::uint32_t size, float* const storage);
//
//			/**
//			 * Constructor For the vector signature Type
//			 * @Param Name: The Name of the signature
//			 * @Param Type: The Type of data being passed in
//			 * @Param initialValue: The initial value of the signature's data
//			 * @Param Size: The number of elements in the data
//			 * @Param storage: The pointer to the external storage
//			 * There are constructor overloads for each Type of data, where InitialValue and storage will be Set uniquely
//			 */
//			Signature(const std::string name, const DatumType type,
//				const std::uint32_t size, glm::vec4* const storage);
//
//			/**
//			 * Constructor For the matrix signature Type
//			 * @Param Name: The Name of the signature
//			 * @Param Type: The Type of data being passed in
//			 * @Param initialValue: The initial value of the signature's data
//			 * @Param Size: The number of elements in the data
//			 * @Param storage: The pointer to the external storage
//			 * There are constructor overloads for each Type of data, where InitialValue and storage will be Set uniquely
//			 */
//			Signature(const std::string name, const DatumType type,
//				const std::uint32_t size, glm::mat4* const storage);
//
//			/**
//			 * Constructor For the string signature Type
//			 * @Param Name: The Name of the signature
//			 * @Param Type: The Type of data being passed in
//			 * @Param initialValue: The initial value of the signature's data
//			 * @Param Size: The number of elements in the data
//			 * @Param storage: The pointer to the external storage
//			 * There are constructor overloads for each Type of data, where InitialValue and storage will be Set uniquely
//			 */
//			Signature(const std::string name, const DatumType type,
//				const std::uint32_t size, std::string* const storage);
//
//			/**
//			 * Constructor For the scope signature Type
//			 * @Param Name: The Name of the signature
//			 * @Param type: The Type of data being passed in
//			 * @Param Size: The number of elements in the data
//			 * @Param storage: The pointer to the external storage
//			 * There are constructor overloads for each Type of data, where InitialValue and storage will be Set uniquely
//			 */
//			Signature(const std::string name, const DatumType type,
//				const std::uint32_t size, Scope** const storage);
//
//			/**
//			 * Constructor For the RTTI pointer signature Type
//			 * @Param Name: The Name of the signature
//			 * @Param Type: The Type of data being passed in
//			 * @Param Size: The number of elements in the data
//			 * @Param storage: The pointer to the external storage
//			 * There are constructor overloads for each Type of data, where InitialValue and storage will be Set uniquely
//			 */
//			Signature(const std::string name, const DatumType type,
//				const std::uint32_t size, RTTI** const storage);
//
//			std::string Name;
//			DatumType Type;
//			std::uint32_t Size;
//			Datum::DatumValues InitialValue;
//			Datum::DatumValues Storage;
//
//		};

		// This vector is used for populating prescribed attributes in children of attributed
		Vector<Signature> mPrescribedAttributes;

	};
}


