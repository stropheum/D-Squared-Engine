#include "pch.h"
#include "FooProduct.h"

namespace Library
{
    RTTI_DEFINITIONS(FooProduct)

        FooProduct::FooProduct()
    {
    }

    FooProduct::~FooProduct()
    {
    }

    bool FooProduct::operator==(const FooProduct& rhs) const
    {
        return ToString() == rhs.ToString();
    }

    std::string FooProduct::ToString() const
    {
        return "Foo Product";
    }

    bool FooProduct::Equals(const RTTI* rhs) const
    {
        if (this == rhs) { return true; }
        if (rhs == nullptr) { return false; }

        FooProduct* data = rhs->As<FooProduct>();
        if (data == nullptr) { return false; }

        return operator==(*data);
    }

    RTTI_DEFINITIONS(BarProduct)

        BarProduct::BarProduct()
    {
    }

    BarProduct::~BarProduct()
    {
    }

    bool BarProduct::operator==(const BarProduct& rhs) const
    {
        return ToString() == rhs.ToString();
    }

    std::string BarProduct::ToString() const
    {
        return "Bar Product";
    }

    bool BarProduct::Equals(const RTTI* rhs) const
    {
        if (this == rhs) { return true; }
        if (rhs == nullptr) { return false; }

        BarProduct* data = rhs->As<BarProduct>();
        if (data == nullptr) { return false; }

        return operator==(*data);
    }
}