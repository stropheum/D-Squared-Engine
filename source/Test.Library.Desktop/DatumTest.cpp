#include "pch.h"
#include "CppUnitTest.h"
#include "Datum.h"
#include "RTTI.h"
#include "FooRTTI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{		
	static Library::Datum iDatum;
	static Library::Datum fDatum;
	static Library::Datum vDatum;
	static Library::Datum mDatum;
	static Library::Datum sDatum;
	static Library::Datum rDatum;
	static std::int32_t i1 = 1;
	static std::int32_t i2 = 2;
	static std::int32_t i3 = 3;
	static float f1 = 1.0f;
	static float f2 = 2.0f;
	static float f3 = 3.0f;
	static glm::vec4 v1(1, 1, 1, 1);
	static glm::vec4 v2(2, 2, 2, 2);
	static glm::vec4 v3(3, 3, 3, 3);
	static glm::mat4 m1(1.0f);
	static glm::mat4 m2(2.0f);
	static glm::mat4 m3(3.0f);
	static std::string s1 = "one";
	static std::string s2 = "two";
	static std::string s3 = "three";
	static FooRTTI* r1;
	static FooRTTI* r2;
	static FooRTTI* r3;

	TEST_CLASS(DatumTest)
	{
	public:
		/// Sets up leak detection logic
		static void initializeLeakDetection()
		{
#if _Debug
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif //_Debug
		}

		/// Detects if memory state has been corrupted
		static void finalizeLeakDetection()
		{
#if _Debug
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif //_Debug
		}

		TEST_CLASS_INITIALIZE(classInitialize)
		{
			iDatum.setType(Library::DatumType::Integer);
			fDatum.setType(Library::DatumType::Float);
			vDatum.setType(Library::DatumType::Vector);
			mDatum.setType(Library::DatumType::Matrix);
			sDatum.setType(Library::DatumType::String);
			rDatum.setType(Library::DatumType::Pointer);
		}

		TEST_METHOD_INITIALIZE(methodInitialize)
		{
			initializeLeakDetection();
			iDatum.clear();
			fDatum.clear();
			vDatum.clear();
			mDatum.clear();
			sDatum.clear();
			rDatum.clear();
			r1 = new FooRTTI();
			r2 = new FooRTTI();
			r3 = new FooRTTI();
		}

		TEST_METHOD_CLEANUP(methodCleanup)
		{
			delete(r1);
			delete(r2);
			delete(r3);
			finalizeLeakDetection();
		}

		TEST_METHOD(TestCopyConstructor)
		{
			Library::Datum oldBusted;
			oldBusted = Library::DatumType::Integer;
			Library::Datum newHotness = oldBusted;
			Assert::IsTrue(oldBusted.type() == newHotness.type(), L"Copied types not equivalent");
			Assert::IsTrue(oldBusted.size() == newHotness.size(), L"Copied sizes not equivalent");
		}

		TEST_METHOD(TestSetType)
		{
			// Integer
			Library::Datum iDatumTemp;
			Assert::IsTrue(iDatumTemp.type() == Library::DatumType::Unknown, L"Invalid Datum Type");

			iDatumTemp = Library::DatumType::Integer;
			Assert::IsTrue(iDatumTemp.type() == Library::DatumType::Integer, L"Invalid Datum Type");

			Assert::ExpectException<std::exception>([&] { iDatumTemp.setType(Library::DatumType::Unknown); },
				L"No exception thrown when reassigning type");


			// Float
			Library::Datum fDatumTemp;
			Assert::IsTrue(fDatumTemp.type() == Library::DatumType::Unknown, L"Invalid Datum Type");

			fDatumTemp = Library::DatumType::Float;
			Assert::IsTrue(fDatumTemp.type() == Library::DatumType::Float, L"Invalid Datum Type");

			Assert::ExpectException<std::exception>([&] { fDatumTemp.setType(Library::DatumType::Unknown); },
				L"No exception thrown when reassigning type");


			// Vector
			Library::Datum vDatumTemp;
			Assert::IsTrue(vDatumTemp.type() == Library::DatumType::Unknown, L"Invalid Datum Type");

			vDatumTemp = Library::DatumType::Vector;
			Assert::IsTrue(vDatumTemp.type() == Library::DatumType::Vector, L"Invalid Datum Type");

			Assert::ExpectException<std::exception>([&] { vDatumTemp.setType(Library::DatumType::Unknown); },
				L"No exception thrown when reassigning type");


			// Matrix
			Library::Datum mDatumTemp;
			Assert::IsTrue(mDatumTemp.type() == Library::DatumType::Unknown, L"Invalid Datum Type");

			mDatumTemp = Library::DatumType::Matrix;
			Assert::IsTrue(mDatumTemp.type() == Library::DatumType::Matrix, L"Invalid Datum Type");

			Assert::ExpectException<std::exception>([&] { mDatumTemp.setType(Library::DatumType::Unknown); },
				L"No exception thrown when reassigning type");


			// String
			Library::Datum sDatumTemp;
			Assert::IsTrue(sDatumTemp.type() == Library::DatumType::Unknown, L"Invalid Datum Type");

			sDatumTemp = Library::DatumType::String;
			Assert::IsTrue(sDatumTemp.type() == Library::DatumType::String, L"Invalid Datum Type");

			Assert::ExpectException<std::exception>([&] { sDatumTemp.setType(Library::DatumType::Unknown); },
				L"No exception thrown when reassigning type");


			// Pointer
			Library::Datum rDatumTemp;
			Assert::IsTrue(rDatumTemp.type() == Library::DatumType::Unknown, L"Invalid Datum Type");

			rDatumTemp = Library::DatumType::Pointer;
			Assert::IsTrue(rDatumTemp.type() == Library::DatumType::Pointer, L"Invalid Datum Type");

			Assert::ExpectException<std::exception>([&] { rDatumTemp.setType(Library::DatumType::Unknown); },
				L"No exception thrown when reassigning type");
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			// Integer
			iDatum = i1;
			Assert::IsTrue(iDatum.get<std::int32_t>(0) == i1);
			Assert::ExpectException<std::exception>([&] { iDatum.get<float>         (0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<glm::vec4>     (0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<glm::mat4>     (0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<std::string>   (0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<Library::RTTI*>(0); });


			// Float
			fDatum = f1;
			Assert::IsTrue(fDatum.get<float>(0) == f1);
			Assert::ExpectException<std::exception>([&] { fDatum.get<std::int32_t>  (0); });
			Assert::ExpectException<std::exception>([&] { fDatum.get<glm::vec4>     (0); });
			Assert::ExpectException<std::exception>([&] { fDatum.get<glm::mat4>     (0); });
			Assert::ExpectException<std::exception>([&] { fDatum.get<std::string>   (0); });
			Assert::ExpectException<std::exception>([&] { fDatum.get<Library::RTTI*>(0); });


			// Vector
			vDatum = v1;
			Assert::IsTrue(vDatum.get<glm::vec4>(0) == v1);
			Assert::ExpectException<std::exception>([&] { vDatum.get<std::int32_t>  (0); });
			Assert::ExpectException<std::exception>([&] { vDatum.get<float>         (0); });
			Assert::ExpectException<std::exception>([&] { vDatum.get<glm::mat4>     (0); });
			Assert::ExpectException<std::exception>([&] { vDatum.get<std::string>   (0); });
			Assert::ExpectException<std::exception>([&] { vDatum.get<Library::RTTI*>(0); });


			// Matrix
			iDatum = i1;
			Assert::IsTrue(iDatum.get<std::int32_t>(0) == i1);
			Assert::ExpectException<std::exception>([&] { iDatum.get<float>         (0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<glm::vec4>     (0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<glm::mat4>     (0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<std::string>   (0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<Library::RTTI*>(0); });


			// String
			iDatum = i1;
			Assert::IsTrue(iDatum.get<std::int32_t>(0) == i1);
			Assert::ExpectException<std::exception>([&] { iDatum.get<float>         (0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<glm::vec4>     (0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<glm::mat4>     (0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<std::string>   (0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<Library::RTTI*>(0); });


			// Pointer
			iDatum = i1;
			Assert::IsTrue(iDatum.get<std::int32_t>(0) == i1);
			Assert::ExpectException<std::exception>([&] { iDatum.get<float>         (0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<glm::vec4>     (0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<glm::mat4>     (0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<std::string>   (0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<Library::RTTI*>(0); });
		}

		TEST_METHOD(TestInequalityOperator)
		{
			// Integer
			iDatum.pushBack(i1);
			Assert::IsFalse(iDatum != i1, L"Value not equivalent to value assigned");
			Assert::IsTrue(iDatum != i2, L"value equivalent to incorrect scalar value");
			Assert::IsTrue(iDatum != i3, L"value equivalent to incorrect scalar value");
			
			iDatum.pushBack(i2);
			Assert::IsTrue(iDatum != i1, L"operator!= should always return true when size > 1");
			Assert::IsTrue(iDatum != i2, L"operator!= should always return true when size > 1");
			Assert::IsTrue(iDatum != i3, L"operator!= should always return true when size > 1");


			// Float
			fDatum.pushBack(f1);
			Assert::IsFalse(fDatum != f1, L"Value not equivalent to value assigned");
			Assert::IsTrue(fDatum != f2, L"value equivalent to incorrect scalar value");
			Assert::IsTrue(fDatum != f3, L"value equivalent to incorrect scalar value");
			
			fDatum.pushBack(f2);
			Assert::IsTrue(fDatum != f1, L"operator!= should always return true when size > 1");
			Assert::IsTrue(fDatum != f2, L"operator!= should always return true when size > 1");
			Assert::IsTrue(fDatum != f3, L"operator!= should always return true when size > 1");


			// Vector
			vDatum.pushBack(v1);
			Assert::IsFalse(vDatum != v1, L"Value not equivalent to value assigned");
			Assert::IsTrue(vDatum != v2, L"value equivalent to incorrect scalar value");
			Assert::IsTrue(vDatum != v3, L"value equivalent to incorrect scalar value");
			
			vDatum.pushBack(v2);
			Assert::IsTrue(vDatum != v1, L"operator!= should always return true when size > 1");
			Assert::IsTrue(vDatum != v2, L"operator!= should always return true when size > 1");
			Assert::IsTrue(vDatum != v3, L"operator!= should always return true when size > 1");


			// Matrix
			mDatum.pushBack(m1);
			Assert::IsFalse(mDatum != m1, L"Value not equivalent to value assigned");
			Assert::IsTrue(mDatum != m2, L"value equivalent to incorrect scalar value");
			Assert::IsTrue(mDatum != m3, L"value equivalent to incorrect scalar value");
			
			mDatum.pushBack(m2);
			Assert::IsTrue(mDatum != m1, L"operator!= should always return true when size > 1");
			Assert::IsTrue(mDatum != m2, L"operator!= should always return true when size > 1");
			Assert::IsTrue(mDatum != m3, L"operator!= should always return true when size > 1");


			// String
			sDatum.pushBack(s1);
			Assert::IsFalse(sDatum != s1, L"Value not equivalent to value assigned");
			Assert::IsTrue(sDatum != s2, L"value equivalent to incorrect scalar value");
			Assert::IsTrue(sDatum != s3, L"value equivalent to incorrect scalar value");
			
			sDatum.pushBack(s2);
			Assert::IsTrue(sDatum != s1, L"operator!= should always return true when size > 1");
			Assert::IsTrue(sDatum != s2, L"operator!= should always return true when size > 1");
			Assert::IsTrue(sDatum != s3, L"operator!= should always return true when size > 1");


			// Pointer
			rDatum.pushBack(r1);
			Assert::IsFalse(rDatum != r1, L"Value not equivalent to value assigned");
			Assert::IsTrue(rDatum != r2, L"value equivalent to incorrect scalar value");
			Assert::IsTrue(rDatum != r3, L"value equivalent to incorrect scalar value");
			rDatum.pushBack(r2);
			Assert::IsTrue(rDatum != r1, L"operator!= should always return true when size > 1");
			Assert::IsTrue(rDatum != r2, L"operator!= should always return true when size > 1");
			Assert::IsTrue(rDatum != r3, L"operator!= should always return true when size > 1");
		}

		TEST_METHOD(TestType)
		{
			Assert::IsTrue(iDatum.type() == Library::DatumType::Integer);
			Assert::IsTrue(fDatum.type() == Library::DatumType::Float);
			Assert::IsTrue(vDatum.type() == Library::DatumType::Vector);
			Assert::IsTrue(mDatum.type() == Library::DatumType::Matrix);
			Assert::IsTrue(sDatum.type() == Library::DatumType::String);
			Assert::IsTrue(rDatum.type() == Library::DatumType::Pointer);

			// Integer
			Library::Datum iDatumTemp1;
			Assert::IsTrue(iDatumTemp1.type() == Library::DatumType::Unknown);
			
			iDatumTemp1 = Library::DatumType::Integer;
			Assert::IsTrue(iDatumTemp1.type() == Library::DatumType::Integer);

			Library::Datum iDatumTemp2;
			iDatumTemp2 = i1;
			Assert::IsTrue(iDatumTemp2.type() == Library::DatumType::Integer);
			
			iDatumTemp2 = i2;
			Assert::IsTrue(iDatumTemp2.type() == Library::DatumType::Integer);
			Assert::ExpectException<std::exception>([&] { iDatumTemp2 = f1; },
				L"Exception not being thrown when assigned improper type");


			// Float
			Library::Datum fDatumTemp1;
			Assert::IsTrue(fDatumTemp1.type() == Library::DatumType::Unknown);

			fDatumTemp1 = Library::DatumType::Float;
			Assert::IsTrue(fDatumTemp1.type() == Library::DatumType::Float);

			Library::Datum fDatumTemp2;
			fDatumTemp2 = f1;
			Assert::IsTrue(fDatumTemp2.type() == Library::DatumType::Float);

			fDatumTemp2 = f2;
			Assert::IsTrue(fDatumTemp2.type() == Library::DatumType::Float);
			Assert::ExpectException<std::exception>([&] { fDatumTemp2 = i1; },
				L"Exception not being thrown when assigned improper type");


			// Vector
			Library::Datum vDatumTemp1;
			Assert::IsTrue(vDatumTemp1.type() == Library::DatumType::Unknown);

			vDatumTemp1 = Library::DatumType::Vector;
			Assert::IsTrue(vDatumTemp1.type() == Library::DatumType::Vector);

			Library::Datum vDatumTemp2;
			vDatumTemp2 = v1;
			Assert::IsTrue(vDatumTemp2.type() == Library::DatumType::Vector);

			vDatumTemp2 = v2;
			Assert::IsTrue(vDatumTemp2.type() == Library::DatumType::Vector);
			Assert::ExpectException<std::exception>([&] { vDatumTemp2 = i1; },
				L"Exception not being thrown when assigned improper type");


			// Matrix
			Library::Datum mDatumTemp1;
			Assert::IsTrue(mDatumTemp1.type() == Library::DatumType::Unknown);

			mDatumTemp1 = Library::DatumType::Matrix;
			Assert::IsTrue(mDatumTemp1.type() == Library::DatumType::Matrix);

			Library::Datum mDatumTemp2;
			mDatumTemp2 = m1;
			Assert::IsTrue(mDatumTemp2.type() == Library::DatumType::Matrix);

			mDatumTemp2 = m2;
			Assert::IsTrue(mDatumTemp2.type() == Library::DatumType::Matrix);
			Assert::ExpectException<std::exception>([&] { mDatumTemp2 = i1; },
				L"Exception not being thrown when assigned improper type");


			// String
			Library::Datum sDatumTemp1;
			Assert::IsTrue(sDatumTemp1.type() == Library::DatumType::Unknown);

			sDatumTemp1 = Library::DatumType::String;
			Assert::IsTrue(sDatumTemp1.type() == Library::DatumType::String);

			Library::Datum sDatumTemp2;
			sDatumTemp2 = s1;
			Assert::IsTrue(sDatumTemp2.type() == Library::DatumType::String);

			sDatumTemp2 = s2;
			Assert::IsTrue(sDatumTemp2.type() == Library::DatumType::String);
			Assert::ExpectException<std::exception>([&] { sDatumTemp2 = i1; },
				L"Exception not being thrown when assigned improper type");


			// Pointer
			Library::Datum rDatumTemp1;
			Assert::IsTrue(rDatumTemp1.type() == Library::DatumType::Unknown);

			rDatumTemp1 = Library::DatumType::Pointer;
			Assert::IsTrue(rDatumTemp1.type() == Library::DatumType::Pointer);

			Library::Datum rDatumTemp2;
			rDatumTemp2 = r1;
			Assert::IsTrue(rDatumTemp2.type() == Library::DatumType::Pointer);

			rDatumTemp2 = r2;
			Assert::IsTrue(rDatumTemp2.type() == Library::DatumType::Pointer);
			Assert::ExpectException<std::exception>([&] { rDatumTemp2 = i1; },
				L"Exception not being thrown when assigned improper type");
		}

		TEST_METHOD(TestSize)
		{
			// Integer
			Assert::AreEqual(iDatum.size(), 0u, L"Size not zero on empty Datum");
			iDatum.pushBack(i1);
			Assert::AreEqual(iDatum.size(), 1u), L"Size does not reflect number of elements pushed";
			iDatum.pushBack(i2);
			Assert::AreEqual(iDatum.size(), 2u, L"Size does not reflect number of elements pushed");
			iDatum.setSize(10);
			Assert::AreEqual(iDatum.size(), 10u, L"Size not equal after calling setSize");
			iDatum.setSize(1);
			Assert::AreEqual(iDatum.size(), 1u, L"setSize should reduce current size");


			// Float
			Assert::AreEqual(fDatum.size(), 0u, L"Size not zero on empty Datum");
			fDatum.pushBack(f1);
			Assert::AreEqual(fDatum.size(), 1u), L"Size does not reflect number of elements pushed";
			fDatum.pushBack(f2);
			Assert::AreEqual(fDatum.size(), 2u, L"Size does not reflect number of elements pushed");
			fDatum.setSize(10);
			Assert::AreEqual(fDatum.size(), 10u, L"Size not equal after calling setSize");
			fDatum.setSize(1);
			Assert::AreEqual(fDatum.size(), 1u, L"setSize should reduce current size");


			// Vector
			Assert::AreEqual(vDatum.size(), 0u, L"Size not zero on empty Datum");
			vDatum.pushBack(v1);
			Assert::AreEqual(vDatum.size(), 1u), L"Size does not reflect number of elements pushed";
			vDatum.pushBack(v2);
			Assert::AreEqual(vDatum.size(), 2u, L"Size does not reflect number of elements pushed");
			vDatum.setSize(10);
			Assert::AreEqual(vDatum.size(), 10u, L"Size not equal after calling setSize");
			vDatum.setSize(1);
			Assert::AreEqual(vDatum.size(), 1u, L"setSize should reduce current size");


			// Matrix
			Assert::AreEqual(mDatum.size(), 0u, L"Size not zero on empty Datum");
			mDatum.pushBack(m1);
			Assert::AreEqual(mDatum.size(), 1u), L"Size does not reflect number of elements pushed";
			mDatum.pushBack(m2);
			Assert::AreEqual(mDatum.size(), 2u, L"Size does not reflect number of elements pushed");
			mDatum.setSize(10);
			Assert::AreEqual(mDatum.size(), 10u, L"Size not equal after calling setSize");
			mDatum.setSize(1);
			Assert::AreEqual(mDatum.size(), 1u, L"setSize should reduce current size");


			// String
			Assert::AreEqual(sDatum.size(), 0u, L"Size not zero on empty Datum");
			sDatum.pushBack(s1);
			Assert::AreEqual(sDatum.size(), 1u), L"Size does not reflect number of elements pushed";
			sDatum.pushBack(s2);
			Assert::AreEqual(sDatum.size(), 2u, L"Size does not reflect number of elements pushed");
			sDatum.setSize(10);
			Assert::AreEqual(sDatum.size(), 10u, L"Size not equal after calling setSize");
			sDatum.setSize(1);
			Assert::AreEqual(sDatum.size(), 1u, L"setSize should reduce current size");


			// Pointer
			Assert::AreEqual(rDatum.size(), 0u, L"Size not zero on empty Datum");
			rDatum.pushBack(r1);
			Assert::AreEqual(rDatum.size(), 1u), L"Size does not reflect number of elements pushed";
			rDatum.pushBack(r2);
			Assert::AreEqual(rDatum.size(), 2u, L"Size does not reflect number of elements pushed");
			rDatum.setSize(10);
			Assert::AreEqual(rDatum.size(), 10u, L"Size not equal after calling setSize");
			rDatum.setSize(1);
			Assert::AreEqual(rDatum.size(), 1u, L"setSize should reduce current size");
		}

		TEST_METHOD(TestReserve)
		{
			// Integer
			iDatum.reserve(10);
			Assert::AreEqual(0u, iDatum.size());
			Assert::AreEqual(10u, iDatum.capacity());

			iDatum.setSize(10);
			Assert::AreEqual(10u, iDatum.size());
			Assert::AreEqual(10u, iDatum.capacity());

			iDatum.reserve(10);
			Assert::AreEqual(10u, iDatum.size());
			Assert::AreEqual(10u, iDatum.capacity());
			
			Assert::ExpectException<std::exception>([&] {iDatum.reserve(0); });


			// Float
			fDatum.reserve(10);
			Assert::AreEqual(fDatum.size(), 0u);
			Assert::AreEqual(fDatum.capacity(), 10u);

			fDatum.setSize(10);
			Assert::AreEqual(fDatum.size(), 10u);
			Assert::AreEqual(fDatum.capacity(), 10u);

			fDatum.reserve(10);
			Assert::AreEqual(fDatum.size(), 10u);
			Assert::AreEqual(fDatum.capacity(), 10u);

			Assert::ExpectException<std::exception>([&] {fDatum.reserve(0); });


			// Vector
			vDatum.reserve(10);
			Assert::AreEqual(vDatum.size(), 0u);
			Assert::AreEqual(vDatum.capacity(), 10u);

			vDatum.setSize(10);
			Assert::AreEqual(vDatum.size(), 10u);
			Assert::AreEqual(vDatum.capacity(), 10u);

			vDatum.reserve(10);
			Assert::AreEqual(vDatum.size(), 10u);
			Assert::AreEqual(vDatum.capacity(), 10u);

			Assert::ExpectException<std::exception>([&] {vDatum.reserve(0); });
			

			// Matrix
			mDatum.reserve(10);
			Assert::AreEqual(mDatum.size(), 0u);
			Assert::AreEqual(mDatum.capacity(), 10u);

			mDatum.setSize(10);
			Assert::AreEqual(mDatum.size(), 10u);
			Assert::AreEqual(mDatum.capacity(), 10u);

			mDatum.reserve(10);
			Assert::AreEqual(mDatum.size(), 10u);
			Assert::AreEqual(mDatum.capacity(), 10u);

			Assert::ExpectException<std::exception>([&] {mDatum.reserve(0); });


			// String
			sDatum.reserve(10);
			Assert::AreEqual(sDatum.size(), 0u);
			Assert::AreEqual(sDatum.capacity(), 10u);

			sDatum.setSize(10);
			Assert::AreEqual(sDatum.size(), 10u);
			Assert::AreEqual(sDatum.capacity(), 10u);

			sDatum.reserve(10);
			Assert::AreEqual(sDatum.size(), 10u);
			Assert::AreEqual(sDatum.capacity(), 10u);

			Assert::ExpectException<std::exception>([&] {sDatum.reserve(0); });


			// Pointer
			rDatum.reserve(10);
			Assert::AreEqual(rDatum.size(), 0u);
			Assert::AreEqual(rDatum.capacity(), 10u);

			rDatum.setSize(10);
			Assert::AreEqual(rDatum.size(), 10u);
			Assert::AreEqual(rDatum.capacity(), 10u);

			rDatum.reserve(10);
			Assert::AreEqual(rDatum.size(), 10u);
			Assert::AreEqual(rDatum.capacity(), 10u);

			Assert::ExpectException<std::exception>([&] {rDatum.reserve(0); });
		}

		TEST_METHOD(TestClear)
		{
			// Integer
			iDatum.setSize(10);
			iDatum.clear();
			Assert::AreEqual(10u, iDatum.capacity());
			Assert::AreEqual(0u, iDatum.size());

			iDatum = i1;
			iDatum.clear();
			Assert::AreEqual(10u, iDatum.capacity());
			Assert::AreEqual(0u, iDatum.size());
			
			iDatum.clear();
			Assert::AreEqual(10u, iDatum.capacity());
			Assert::AreEqual(0u, iDatum.size());


			// Float
			fDatum.setSize(10);
			fDatum.clear();
			Assert::AreEqual(10u, fDatum.capacity());
			Assert::AreEqual(0u, fDatum.size());

			fDatum = f1;
			fDatum.clear();
			Assert::AreEqual(10u, fDatum.capacity());
			Assert::AreEqual(0u, fDatum.size());

			fDatum.clear();
			Assert::AreEqual(10u, fDatum.capacity());
			Assert::AreEqual(0u, fDatum.size());


			// Vector
			vDatum.setSize(10);
			vDatum.clear();
			Assert::AreEqual(10u, vDatum.capacity());
			Assert::AreEqual(0u, vDatum.size());

			vDatum = v1;
			vDatum.clear();
			Assert::AreEqual(10u, vDatum.capacity());
			Assert::AreEqual(0u, vDatum.size());

			vDatum.clear();
			Assert::AreEqual(10u, vDatum.capacity());
			Assert::AreEqual(0u, vDatum.size());


			// Matrix
			mDatum.setSize(10);
			mDatum.clear();
			Assert::AreEqual(10u, mDatum.capacity());
			Assert::AreEqual(0u, mDatum.size());

			mDatum = m1;
			mDatum.clear();
			Assert::AreEqual(10u, mDatum.capacity());
			Assert::AreEqual(0u, mDatum.size());

			mDatum.clear();
			Assert::AreEqual(10u, mDatum.capacity());
			Assert::AreEqual(0u, mDatum.size());


			// String
			sDatum.setSize(10);
			sDatum.clear();
			Assert::AreEqual(10u, sDatum.capacity());
			Assert::AreEqual(0u, sDatum.size());

			sDatum = s1;
			sDatum.clear();
			Assert::AreEqual(10u, sDatum.capacity());
			Assert::AreEqual(0u, sDatum.size());

			sDatum.clear();
			Assert::AreEqual(10u, sDatum.capacity());
			Assert::AreEqual(0u, sDatum.size());


			// Pointer
			rDatum.setSize(10);
			rDatum.clear();
			Assert::AreEqual(10u, rDatum.capacity());
			Assert::AreEqual(0u, rDatum.size());

			rDatum = r1;
			rDatum.clear();
			Assert::AreEqual(10u, rDatum.capacity());
			Assert::AreEqual(0u, rDatum.size());

			rDatum.clear();
			Assert::AreEqual(10u, rDatum.capacity());
			Assert::AreEqual(0u, rDatum.size());
		}

		TEST_METHOD(TestSetStorage)
		{
			Library::Datum iTemp;
			std::int32_t* iStorage = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * 10));
			iTemp.setStorage(iStorage, 10);
		}

		TEST_METHOD(TestSet)
		{
			// Integer
			Assert::ExpectException<std::exception>([&] {iDatum.set(i1, 10); });
			Assert::ExpectException<std::exception>([&] {iDatum.set(f1, 0); });
			
			iDatum.reserve(10);
			iDatum.set(i1, 0);
			Assert::IsTrue(iDatum == i1);
			
			iDatum.pushBack(i2);
			iDatum.set(i3, 0);
			Assert::IsTrue(iDatum.get<std::int32_t>(0) == i3);
			Assert::IsTrue(iDatum.get<std::int32_t>(1) == i2);

			iDatum.set(i1, 1);
			Assert::IsTrue(iDatum.get<std::int32_t>(1) == i1);
			Assert::ExpectException<std::exception>([&] { iDatum.set(i1, 10); });


			// Float
			Assert::ExpectException<std::exception>([&] {fDatum.set(f1, 10); });
			Assert::ExpectException<std::exception>([&] {fDatum.set(i1, 0); });

			fDatum.reserve(10);
			fDatum.set(f1, 0);
			Assert::IsTrue(fDatum == f1);

			fDatum.pushBack(f2);
			fDatum.set(f3, 0);
			Assert::IsTrue(fDatum.get<float>(0) == f3);
			Assert::IsTrue(fDatum.get<float>(1) == f2);

			fDatum.set(f1, 1);
			Assert::IsTrue(fDatum.get<float>(1) == f1);
			Assert::ExpectException<std::exception>([&] { fDatum.set(f1, 10); });


			// Vector
			Assert::ExpectException<std::exception>([&] {vDatum.set(v1, 10); });
			Assert::ExpectException<std::exception>([&] {vDatum.set(i1, 0); });

			vDatum.reserve(10);
			vDatum.set(v1, 0);
			Assert::IsTrue(vDatum == v1);

			vDatum.pushBack(v2);
			vDatum.set(v3, 0);
			Assert::IsTrue(vDatum.get<glm::vec4>(0) == v3);
			Assert::IsTrue(vDatum.get<glm::vec4>(1) == v2);

			vDatum.set(v1, 1);
			Assert::IsTrue(vDatum.get<glm::vec4>(1) == v1);
			Assert::ExpectException<std::exception>([&] { vDatum.set(v1, 10); });


			// Matrix
			Assert::ExpectException<std::exception>([&] {mDatum.set(m1, 10); });
			Assert::ExpectException<std::exception>([&] {mDatum.set(i1, 0); });

			mDatum.reserve(10);
			mDatum.set(m1, 0);
			Assert::IsTrue(mDatum == m1);

			mDatum.pushBack(m2);
			mDatum.set(m3, 0);
			Assert::IsTrue(mDatum.get<glm::mat4>(0) == m3);
			Assert::IsTrue(mDatum.get<glm::mat4>(1) == m2);

			mDatum.set(m1, 1);
			Assert::IsTrue(mDatum.get<glm::mat4>(1) == m1);
			Assert::ExpectException<std::exception>([&] { mDatum.set(m1, 10); });


			// String
			Assert::ExpectException<std::exception>([&] {sDatum.set(s1, 10); });
			Assert::ExpectException<std::exception>([&] {sDatum.set(i1, 0); });

			sDatum.reserve(10);
			sDatum.set(s1, 0);
			Assert::IsTrue(sDatum == s1);

			sDatum.pushBack(s2);
			sDatum.set(s3, 0);
			Assert::IsTrue(sDatum.get<std::string>(0) == s3);
			Assert::IsTrue(sDatum.get<std::string>(1) == s2);

			sDatum.set(s1, 1);
			Assert::IsTrue(sDatum.get<std::string>(1) == s1);
			Assert::ExpectException<std::exception>([&] { sDatum.set(s1, 10); });


			// Pointer
			Assert::ExpectException<std::exception>([&] {rDatum.set(r1, 10); });
			Assert::ExpectException<std::exception>([&] {rDatum.set(i1, 0); });

			rDatum.reserve(10);
			rDatum.set(r1, 0);
			Assert::IsTrue(rDatum == r1);

			rDatum.pushBack(r2);
			rDatum.set(r3, 0);
			Assert::IsTrue(rDatum.get<Library::RTTI*>(0) == r3);
			Assert::IsTrue(rDatum.get<Library::RTTI*>(1) == r2);

			rDatum.set(r1, 1);
			Assert::IsTrue(rDatum.get<Library::RTTI*>(1) == r1);
			Assert::ExpectException<std::exception>([&] { rDatum.set(r1, 10); });
		}

		TEST_METHOD(TestSetFromString)
		{
			// Integer
			iDatum.setFromString("1");
			Assert::IsTrue(iDatum == 1);
			Assert::IsFalse(iDatum == 2);
			
			iDatum.setFromString("2", 1);
			Assert::IsTrue(iDatum.get<std::int32_t>(0) == 1);
			Assert::IsTrue(iDatum.get<std::int32_t>(1) == 2);

			iDatum.setFromString("3", 1);
			Assert::IsTrue(iDatum.get<std::int32_t>(0) == 1);
			Assert::IsTrue(iDatum.get<std::int32_t>(1) == 3);


			// Float
			fDatum.setFromString("1.0f");
			Assert::IsTrue(fDatum == f1);
			Assert::IsFalse(fDatum == f2);

			fDatum.setFromString("2.0f", 1);
			Assert::IsTrue(fDatum.get<float>(0) == f1);
			Assert::IsTrue(fDatum.get<float>(1) == f2);

			fDatum.setFromString("3.0f", 1);
			Assert::IsTrue(fDatum.get<float>(0) == f1);
			Assert::IsTrue(fDatum.get<float>(1) == f3);


			// Vector
			auto vs1 = "vec4(1.000000, 1.000000, 1.000000, 1.000000)";
			auto vs2 = "vec4(2.000000, 2.000000, 2.000000, 2.000000)";
			auto vs3 = "vec4(3.000000, 3.000000, 3.000000, 3.000000)";

			vDatum.setFromString(vs1);
			Assert::IsTrue(vDatum == v1);
			Assert::IsFalse(vDatum == v2);

			vDatum.setFromString(vs2, 1);
			Assert::IsTrue(vDatum.get<glm::vec4>(0) == v1);
			Assert::IsTrue(vDatum.get<glm::vec4>(1) == v2);

			vDatum.setFromString(vs3, 1);
			Assert::IsTrue(vDatum.get<glm::vec4>(0) == v1);
			Assert::IsTrue(vDatum.get<glm::vec4>(1) == v3);


			// Matrix
			auto ms1 = "mat4x4((1.000000, 0.000000, 0.000000, 0.000000), (0.000000, 1.000000, 0.000000, 0.000000), (0.000000, 0.000000, 1.000000, 0.000000), (0.000000, 0.000000, 0.000000, 1.000000))";
			auto ms2 = "mat4x4((2.000000, 0.000000, 0.000000, 0.000000), (0.000000, 2.000000, 0.000000, 0.000000), (0.000000, 0.000000, 2.000000, 0.000000), (0.000000, 0.000000, 0.000000, 2.000000))";
			auto ms3 = "mat4x4((3.000000, 0.000000, 0.000000, 0.000000), (0.000000, 3.000000, 0.000000, 0.000000), (0.000000, 0.000000, 3.000000, 0.000000), (0.000000, 0.000000, 0.000000, 3.000000))";
			
			mDatum.setFromString(ms1);
			Assert::IsTrue(mDatum == m1);
			Assert::IsFalse(mDatum == m2);

			mDatum.setFromString(ms2, 1);
			Assert::IsTrue(mDatum.get<glm::mat4>(0) == m1);
			Assert::IsTrue(mDatum.get<glm::mat4>(1) == m2);

			mDatum.setFromString(ms3, 1);
			Assert::IsTrue(mDatum.get<glm::mat4>(0) == m1);
			Assert::IsTrue(mDatum.get<glm::mat4>(1) == m3);


			// String
			sDatum.setFromString(s1);
			Assert::IsTrue(sDatum == s1);
			Assert::IsFalse(sDatum == s2);
			
			sDatum.setFromString(s2, 1);
			Assert::IsTrue(sDatum.get<std::string>(0) == s1);
			Assert::IsTrue(sDatum.get<std::string>(1) == s2);

			sDatum.setFromString(s3, 1);
			Assert::IsTrue(sDatum.get<std::string>(0) == s1);
			Assert::IsTrue(sDatum.get<std::string>(1) == s3);
		}

		TEST_METHOD(TestToString)
		{
			// Integer
			iDatum = i1;
			Assert::IsTrue("1" == iDatum.toString(), L"toString invalid on scalar assignment");
			iDatum = i2;
			Assert::IsTrue("2" == iDatum.toString(), L"toString invalid on scalar assignment");
			iDatum = i3;
			Assert::IsTrue("3" == iDatum.toString(), L"toString invalid on scalar assignment");

			iDatum.clear();
			iDatum.pushBack(i1);
			iDatum.pushBack(i2);
			iDatum.pushBack(i3);
			Assert::IsTrue("1" == iDatum.toString(0), L"toString invalid with multiple values");
			Assert::IsTrue("2" == iDatum.toString(1), L"toString invalid with multiple values");
			Assert::IsTrue("3" == iDatum.toString(2), L"toString invalid with multiple values");

			iDatum.set(i1, 1);
			Assert::IsTrue("1" == iDatum.toString(1), L"toString invalid after set");

			
			// Float
			fDatum = f1;
			Assert::IsTrue("1.000000" == fDatum.toString(), L"toString invalid on scalar assignment");
			fDatum = f2;
			Assert::IsTrue("2.000000" == fDatum.toString(), L"toString invalid on scalar assignment");
			fDatum = f3;
			Assert::IsTrue("3.000000" == fDatum.toString(), L"toString invalid on scalar assignment");

			fDatum.clear();
			fDatum.pushBack(f1);
			fDatum.pushBack(f2);
			fDatum.pushBack(f3);
			Assert::IsTrue("1.000000" == fDatum.toString(0), L"toString invalid with multiple values");
			Assert::IsTrue("2.000000" == fDatum.toString(1), L"toString invalid with multiple values");
			Assert::IsTrue("3.000000" == fDatum.toString(2), L"toString invalid with multiple values");

			fDatum.set(f1, 1);
			Assert::IsTrue("1.000000" == fDatum.toString(1), L"toString invalid after set");


			// Vector
			vDatum = v1;
			auto vs1 = "vec4(1.000000, 1.000000, 1.000000, 1.000000)";
			auto vs2 = "vec4(2.000000, 2.000000, 2.000000, 2.000000)";
			auto vs3 = "vec4(3.000000, 3.000000, 3.000000, 3.000000)";
			Assert::IsTrue(vs1 == vDatum.toString(), L"toString invalid on scalar assignment");
			vDatum = v2;
			Assert::IsTrue(vs2 == vDatum.toString(), L"toString invalid on scalar assignment");
			vDatum = v3;
			Assert::IsTrue(vs3 == vDatum.toString(), L"toString invalid on scalar assignment");

			vDatum.clear();
			vDatum.pushBack(v1);
			vDatum.pushBack(v2);
			vDatum.pushBack(v3);
			Assert::IsTrue(vs1 == vDatum.toString(0), L"toString invalid with multiple values");
			Assert::IsTrue(vs2 == vDatum.toString(1), L"toString invalid with multiple values");
			Assert::IsTrue(vs3 == vDatum.toString(2), L"toString invalid with multiple values");

			vDatum.set(v1, 1);
			Assert::IsTrue(vs1 == vDatum.toString(1), L"toString invalid after set");


			// Matrix
			mDatum = m1;
			auto ms1 = "mat4x4((1.000000, 0.000000, 0.000000, 0.000000), (0.000000, 1.000000, 0.000000, 0.000000), (0.000000, 0.000000, 1.000000, 0.000000), (0.000000, 0.000000, 0.000000, 1.000000))";
			auto ms2 = "mat4x4((2.000000, 0.000000, 0.000000, 0.000000), (0.000000, 2.000000, 0.000000, 0.000000), (0.000000, 0.000000, 2.000000, 0.000000), (0.000000, 0.000000, 0.000000, 2.000000))";
			auto ms3 = "mat4x4((3.000000, 0.000000, 0.000000, 0.000000), (0.000000, 3.000000, 0.000000, 0.000000), (0.000000, 0.000000, 3.000000, 0.000000), (0.000000, 0.000000, 0.000000, 3.000000))";
			Assert::IsTrue(ms1 == mDatum.toString(), L"toString invalid on scalar assignment");
			mDatum = m2;
			Assert::IsTrue(ms2 == mDatum.toString(), L"toString invalid on scalar assignment");
			mDatum = m3;
			Assert::IsTrue(ms3 == mDatum.toString(), L"toString invalid on scalar assignment");

			mDatum.clear();
			mDatum.pushBack(m1);
			mDatum.pushBack(m2);
			mDatum.pushBack(m3);
			Assert::IsTrue(ms1 == mDatum.toString(0), L"toString invalid with multiple values");
			Assert::IsTrue(ms2 == mDatum.toString(1), L"toString invalid with multiple values");
			Assert::IsTrue(ms3 == mDatum.toString(2), L"toString invalid with multiple values");

			mDatum.set(m1, 1);
			Assert::IsTrue(ms1 == mDatum.toString(1), L"toString invalid after set");


			// String
			sDatum = s1;
			Assert::IsTrue(s1 == sDatum.toString(), L"toString invalid on scalar assignment");
			sDatum = s2;
			Assert::IsTrue(s2 == sDatum.toString(), L"toString invalid on scalar assignment");
			sDatum = s3;
			Assert::IsTrue(s3 == sDatum.toString(), L"toString invalid on scalar assignment");

			sDatum.clear();
			sDatum.pushBack(s1);
			sDatum.pushBack(s2);
			sDatum.pushBack(s3);
			Assert::IsTrue(s1 == sDatum.toString(0), L"toString invalid with multiple values");
			Assert::IsTrue(s2 == sDatum.toString(1), L"toString invalid with multiple values");
			Assert::IsTrue(s3 == sDatum.toString(2), L"toString invalid with multiple values");

			sDatum.set(s1, 1);
			Assert::IsTrue(s1 == sDatum.toString(1), L"toString invalid after set");
		}
	};
}