#include "pch.h"
#include "AttributedFoo.h"
#include <Datum.h>
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"


namespace Library
{
	Datum::DatumValues* storage;
	AttributedFoo::AttributedFoo():
		Attributed(), mInt(0), mFloat(0.0f), mVector(0), mMatrix(0), mString(""), mScope()
	{
		init();
	}

	AttributedFoo::~AttributedFoo()
	{
		delete[] iArray;
		delete[] fArray;
		delete[] vArray;
		delete[] mArray;
		delete[] sArray;
	}

	AttributedFoo::AttributedFoo(const AttributedFoo& rhs) :
		Attributed(rhs)
	{
		operator=(rhs);
	}

	AttributedFoo& AttributedFoo::operator=(const AttributedFoo& rhs)
	{
		init();

		(*this)["External Integer"].SetStorage(&mInt, 1u);
		(*this)["External Float"].SetStorage(&mFloat, 1u);
		(*this)["External Vector"].SetStorage(&mVector, 1u);
		(*this)["External Matrix"].SetStorage(&mMatrix, 1u);
		(*this)["External String"].SetStorage(&mString, 1u);

		(*this)["External Integer Array"].SetStorage(iArray, 10u);
		(*this)["External Float Array"].SetStorage(fArray, 10u);
		(*this)["External Vector Array"].SetStorage(vArray, 10u);
		(*this)["External Matrix Array"].SetStorage(mArray, 10u);
		(*this)["External String Array"].SetStorage(sArray, 10u);

		mInt = rhs.mInt;
		mFloat = rhs.mFloat;
		mVector = rhs.mVector;
		mMatrix = rhs.mMatrix;
		mString = rhs.mString;
		mScope = rhs.mScope;

		for (std::uint32_t i = 0; i < 10; i++)
		{
			iArray[i] = rhs.iArray[i];
			fArray[i] = rhs.fArray[i];
			vArray[i] = rhs.vArray[i];
			mArray[i] = rhs.mArray[i];
			sArray[i] = rhs.sArray[i];
		}

		return (*this);
	}

	AttributedFoo::AttributedFoo(AttributedFoo&& rhs):
		Attributed::Attributed(std::move(rhs))
	{
		operator=(std::move(rhs));
	}

	AttributedFoo& AttributedFoo::operator=(AttributedFoo&& rhs)
	{
		(*this)["External Integer"].SetStorage(&mInt, 1u);
		(*this)["External Float"].SetStorage(&mFloat, 1u);
		(*this)["External Vector"].SetStorage(&mVector, 1u);
		(*this)["External Matrix"].SetStorage(&mMatrix, 1u);
		(*this)["External String"].SetStorage(&mString, 1u);

		(*this)["External Integer Array"].SetStorage(iArray, 10u);
		(*this)["External Float Array"].SetStorage(fArray, 10u);
		(*this)["External Vector Array"].SetStorage(vArray, 10u);
		(*this)["External Matrix Array"].SetStorage(mArray, 10u);
		(*this)["External String Array"].SetStorage(sArray, 10u);

		mInt = rhs.mInt;
		mFloat = rhs.mFloat;
		mVector = rhs.mVector;
		mMatrix = rhs.mMatrix;
		mString = rhs.mString;
		mScope = rhs.mScope;

		iArray = rhs.iArray;
		fArray = rhs.fArray;
		vArray = rhs.vArray;
		mArray = rhs.mArray;
		sArray = rhs.sArray;

		rhs.mInt = 0;
		rhs.mFloat = 0.0f;
		rhs.mVector = glm::vec4(0);
		rhs.mMatrix = glm::mat4(0);
		rhs.mString = "";
		rhs.iArray = nullptr;
		rhs.fArray = nullptr;
		rhs.vArray = nullptr;
		rhs.mArray = nullptr;
		rhs.sArray = nullptr;

		return (*this);
	}

	void AttributedFoo::init()
	{
		mPrescribedAttributes.PushBack(
			Signature("External Integer", DatumType::Integer, 1u, &mInt)
		);

		mPrescribedAttributes.PushBack(
			Signature("External Float", DatumType::Float, 1u, &mFloat)
		);

		mPrescribedAttributes.PushBack(
			Signature("External Vector", DatumType::Vector, 1u, &mVector)
		);

		mPrescribedAttributes.PushBack(
			Signature("External Matrix", DatumType::Matrix, 1u, &mMatrix)
		);

		mPrescribedAttributes.PushBack(
			Signature("External String", DatumType::String, 1u, &mString)
		);

		mPrescribedAttributes.PushBack(
			Signature("Internal Scope", DatumType::Scope, 1u, &mScope)
		);

		iArray = new std::int32_t[10];
		fArray = new float[10];
		vArray = new glm::vec4[10];
		mArray = new glm::mat4[10];
		sArray = new std::string[10];

		for (std::uint32_t i = 0; i < 10; i++)
		{
			iArray[i] = 10;
			fArray[i] = 10.0f;
		}

		mPrescribedAttributes.PushBack(
			Signature("External Integer Array", DatumType::Integer, 10u, iArray)
		);

		mPrescribedAttributes.PushBack(
			Signature("External Float Array", DatumType::Float, 10u, fArray)
		);

		mPrescribedAttributes.PushBack(
			Signature("External Vector Array", DatumType::Vector, 10u, vArray)
		);

		mPrescribedAttributes.PushBack(
			Signature("External Matrix Array", DatumType::Matrix, 10u, mArray)
		);

		mPrescribedAttributes.PushBack(
			Signature("External String Array", DatumType::String, 10u, sArray)
		);

		Populate();
	}
}

