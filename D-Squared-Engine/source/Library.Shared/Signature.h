#pragma once
#include "Attributed.h"


namespace Library
{
    class Attributed::Signature
    {

    public:

        /**
        * Constructor For the integer signature Type
        * @Param Name: The Name of the signature
        * @Param Type: The Type of data being passed in
        * @Param initialValue: The initial value of the signature's data
        * @Param Size: The number of elements in the data
        * @Param storage: The pointer to the external storage
        * There are constructor overloads for each Type of data, where InitialValue and storage will be Set uniquely
        */
        Signature(const std::string name, const DatumType type,
            const std::uint32_t size, std::int32_t* storage);

        /**
        * Constructor For the float signature Type
        * @Param Name: The Name of the signature
        * @Param Type: The Type of data being passed in
        * @Param initialValue: The initial value of the signature's data
        * @Param Size: The number of elements in the data
        * @Param storage: The pointer to the external storage
        * There are constructor overloads for each Type of data, where InitialValue and storage will be Set uniquely
        */
        Signature(const std::string name, const DatumType type,
            const std::uint32_t size, float* const storage);

        /**
        * Constructor For the vector signature Type
        * @Param Name: The Name of the signature
        * @Param Type: The Type of data being passed in
        * @Param initialValue: The initial value of the signature's data
        * @Param Size: The number of elements in the data
        * @Param storage: The pointer to the external storage
        * There are constructor overloads for each Type of data, where InitialValue and storage will be Set uniquely
        */
        Signature(const std::string name, const DatumType type,
            const std::uint32_t size, glm::vec4* const storage);

        /**
        * Constructor For the matrix signature Type
        * @Param Name: The Name of the signature
        * @Param Type: The Type of data being passed in
        * @Param initialValue: The initial value of the signature's data
        * @Param Size: The number of elements in the data
        * @Param storage: The pointer to the external storage
        * There are constructor overloads for each Type of data, where InitialValue and storage will be Set uniquely
        */
        Signature(const std::string name, const DatumType type,
            const std::uint32_t size, glm::mat4* const storage);

        /**
        * Constructor For the string signature Type
        * @Param Name: The Name of the signature
        * @Param Type: The Type of data being passed in
        * @Param initialValue: The initial value of the signature's data
        * @Param Size: The number of elements in the data
        * @Param storage: The pointer to the external storage
        * There are constructor overloads for each Type of data, where InitialValue and storage will be Set uniquely
        */
        Signature(const std::string name, const DatumType type,
            const std::uint32_t size, std::string* const storage);

        /**
        * Constructor For the scope signature Type
        * @Param Name: The Name of the signature
        * @Param type: The Type of data being passed in
        * @Param Size: The number of elements in the data
        * @Param storage: The pointer to the external storage
        * There are constructor overloads for each Type of data, where InitialValue and storage will be Set uniquely
        */
        Signature(const std::string name, const DatumType type,
            const std::uint32_t size, Scope** const storage);

        /**
        * Constructor For the RTTI pointer signature Type
        * @Param Name: The Name of the signature
        * @Param Type: The Type of data being passed in
        * @Param Size: The number of elements in the data
        * @Param storage: The pointer to the external storage
        * There are constructor overloads for each Type of data, where InitialValue and storage will be Set uniquely
        */
        Signature(const std::string name, const DatumType type,
            const std::uint32_t size, RTTI** const storage);

        std::string Name;
        DatumType Type;
        std::uint32_t Size;
        Datum::DatumValues InitialValue;
        Datum::DatumValues Storage;

    };
}