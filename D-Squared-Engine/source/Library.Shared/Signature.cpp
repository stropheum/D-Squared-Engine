#include "pch.h"
#include "Signature.h"


namespace Library
{
    Attributed::Signature::Signature(const std::string name, const DatumType type,
        const std::uint32_t size, std::int32_t* storage) :
        Name(name), Type(type), Size(size)
    {
        if (storage != nullptr)
        {
            Storage.i = storage;
        }
    }

    Attributed::Signature::Signature(const std::string name, const DatumType type,
        const std::uint32_t size, float* const storage) :
        Name(name), Type(type), Size(size)
    {
        if (storage != nullptr)
        {
            Storage.f = storage;
        }
    }

    Attributed::Signature::Signature(const std::string name, const DatumType type,
        const std::uint32_t size, glm::vec4* const storage) :
        Name(name), Type(type), Size(size)
    {
        if (storage != nullptr)
        {
            Storage.v = storage;
        }
    }

    Attributed::Signature::Signature(const std::string name, const DatumType type,
        const std::uint32_t size, glm::mat4* const storage) :
        Name(name), Type(type), Size(size)
    {
        if (storage != nullptr)
        {
            Storage.m = storage;
        }
    }

    Attributed::Signature::Signature(const std::string name, const DatumType type,
        const std::uint32_t size, std::string* const storage) :
        Name(name), Type(type), Size(size)
    {
        if (storage != nullptr)
        {
            Storage.s = storage;
        }
    }

    Attributed::Signature::Signature(const std::string name, const DatumType type,
        const std::uint32_t size, Scope** const storage) :
        Name(name), Type(type), Size(size)
    {
        if (storage != nullptr)
        {
            Storage.sc = storage;
        }
    }

    Attributed::Signature::Signature(const std::string name, const DatumType type,
        const std::uint32_t size, RTTI** const storage) :
        Name(name), Type(type), Size(size)
    {
        if (storage != nullptr)
        {
            Storage.r = storage;
        }
    }
}