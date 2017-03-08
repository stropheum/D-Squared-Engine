#include "pch.h"
#include "AttributedFoo.h"
#include <Datum.h>


namespace Library
{
	Datum::DatumValues* storage;
	AttributedFoo::AttributedFoo():
		Attributed(), i(0), f(0.0f), v(0), m(0), s(""), sc()
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
		sc = rhs.sc;

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
		sc = rhs.sc;

		return (*this);
	}

	void AttributedFoo::init()
	{
		iArray = new std::int32_t[10];
		fArray = new float[10];
		vArray = new glm::vec4[10];
		mArray = new glm::mat4[10];
		sArray = new std::string[10];

		mPrescribedAttributes.pushBack(
			Signature("External Integer", DatumType::Integer, &i, 1u, &i)
		);

		mPrescribedAttributes.pushBack(
			Signature("External Float", DatumType::Float, &f, 1u, &f)
		);

		mPrescribedAttributes.pushBack(
			Signature("External Vector", DatumType::Vector, &v, 1u, &v)
		);

		mPrescribedAttributes.pushBack(
			Signature("External Matrix", DatumType::Matrix, &m, 1u, &m)
		);

		mPrescribedAttributes.pushBack(
			Signature("External String", DatumType::String, &s, 1u, &s)
		);

		mPrescribedAttributes.pushBack(
			Signature("Internal Scope", DatumType::Scope, &sc, 1u, &sc)
		);

		populate();
	}
}

