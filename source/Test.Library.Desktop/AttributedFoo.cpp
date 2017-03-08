#include "pch.h"
#include "AttributedFoo.h"
#include <Datum.h>


namespace Library
{
	Datum::DatumValues* storage;
	AttributedFoo::AttributedFoo():
		Attributed(), i(0), f(0.0f), v(0), m(0), s("")
	{}

	AttributedFoo::~AttributedFoo()
	{}

	void AttributedFoo::populate()
	{
		mPrescribedAttributes.pushBack(
			Signature("Internal Integer", DatumType::Integer, i, 1u, nullptr));

		mPrescribedAttributes.pushBack(
			Signature("Internal Float", DatumType::Float, f, 1u, nullptr));

		mPrescribedAttributes.pushBack(
			Signature("Internal Vector", DatumType::Vector, v, 1u, nullptr));

		mPrescribedAttributes.pushBack(
			Signature("Internal Matrix", DatumType::Matrix, m, 1, nullptr));

		mPrescribedAttributes.pushBack(
			Signature("Internal String", DatumType::String, s, 1, nullptr));


		Attributed::populate();
	}
}

