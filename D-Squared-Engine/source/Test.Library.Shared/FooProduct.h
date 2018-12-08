#pragma once
#include "RTTI.h"

namespace Library
{
    class FooProduct :
        public Library::RTTI
    {
        RTTI_DECLARATIONS(FooProduct, RTTI)
    public:
        FooProduct();
        ~FooProduct();
        bool operator==(const FooProduct& rhs) const;
        virtual std::string ToString() const override;
        virtual bool Equals(const RTTI* rhs) const override;
    };

    class BarProduct :
        public Library::RTTI
    {
        RTTI_DECLARATIONS(BarProduct, RTTI)
    public:
        BarProduct();
        ~BarProduct();
        bool operator==(const BarProduct& rhs) const;
        virtual std::string ToString() const override;
        virtual bool Equals(const RTTI* rhs) const override;
    };
}