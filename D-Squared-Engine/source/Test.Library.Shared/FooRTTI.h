#pragma once
#include "RTTI.h"

class FooRTTI : public Library::RTTI
{
public:
    FooRTTI();
    FooRTTI(int data);
    ~FooRTTI();
    int mData;
    std::uint64_t TypeIdInstance() const override;
};