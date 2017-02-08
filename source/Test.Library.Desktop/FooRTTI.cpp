#include "pch.h"
#include "FooRTTI.h"


FooRTTI::FooRTTI() :
	mData(0)
{}

FooRTTI::FooRTTI(int data) :
	mData(data)
{}

FooRTTI::~FooRTTI()
{}

std::uint64_t FooRTTI::TypeIdInstance() const
{
	return 0U;
}
