#include "pch.h"
#include "FooRTTI.h"


FooRTTI::FooRTTI() :
    m_data(0)
{}

FooRTTI::FooRTTI(int data) :
    m_data(data)
{}

FooRTTI::~FooRTTI()
{}

std::uint64_t FooRTTI::TypeIdInstance() const
{
    return 0U;
}