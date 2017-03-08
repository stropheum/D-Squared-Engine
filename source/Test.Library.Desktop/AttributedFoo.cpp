#include "pch.h"
#include "AttributedFoo.h"
#include <Datum.h>


namespace Library
{
	Datum::DatumValues* storage;
	AttributedFoo::AttributedFoo():
		Attributed(), i(0), f(0.0f), v(0), m(0), s("")
	{
		init();
	}

	AttributedFoo::~AttributedFoo()
	{}

	AttributedFoo::AttributedFoo(const AttributedFoo& rhs) :
		Attributed(rhs)
	{
		operator=(rhs);
	}

	AttributedFoo& AttributedFoo::operator=(const AttributedFoo& rhs)
	{
		(*this)["External Integer"].setStorage(&i, 1u);
		(*this)["External Float"].setStorage(&f, 1u);
		(*this)["External Vector"].setStorage(&v, 1u);
		(*this)["External Matrix"].setStorage(&m, 1u);
		(*this)["External String"].setStorage(&s, 1u);

		i = rhs.i;
		f = rhs.f;
		v = rhs.v;
		m = rhs.m;
		s = rhs.s;

		return (*this);
	}

	AttributedFoo::AttributedFoo(const AttributedFoo&& rhs):
		Attributed::Attributed(std::move(rhs))
	{
		operator=(std::move(rhs));
	}

	AttributedFoo& AttributedFoo::operator=(const AttributedFoo&& rhs)
	{
		(*this)["External Integer"].setStorage(&i, 1u);
		(*this)["External Float"].setStorage(&f, 1u);
		(*this)["External Vector"].setStorage(&v, 1u);
		(*this)["External Matrix"].setStorage(&m, 1u);
		(*this)["External String"].setStorage(&s, 1u);

		i = rhs.i;
		f = rhs.f;
		v = rhs.v;
		m = rhs.m;
		s = rhs.s;

		return (*this);
	}

	void AttributedFoo::init()
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


		populate();
	}
}

