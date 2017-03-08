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
			Signature("External Integer", DatumType::Integer, i, 1u, &i));

		mPrescribedAttributes.pushBack(
			Signature("External Float", DatumType::Float, f, 1u, &f));

		mPrescribedAttributes.pushBack(
			Signature("External Vector", DatumType::Vector, v, 1u, &v));

		mPrescribedAttributes.pushBack(
			Signature("External Matrix", DatumType::Matrix, m, 1u, &m));

		mPrescribedAttributes.pushBack(
			Signature("External String", DatumType::String, s, 1u, &s));


		Attributed::populate();
	}
}

