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
			Assert::AreEqual(iDatum.size(), 10u, L"setSize should not reduce current size");
		}

		TEST_METHOD(TestReserve)
		{
			// TODO: Implement test method
			Assert::Fail();
		}

		TEST_METHOD(TestClear)
		{
			// TODO: Implement test method
			Assert::Fail();
		}

		TEST_METHOD(TestSetStorage)
		{
			// TODO: Implement test method
			Assert::Fail();
		}

		TEST_METHOD(TestSet)
		{
			// TODO: Implement test method
			Assert::Fail();
		}

		TEST_METHOD(TestSetFromString)
		{
			// TODO: Implement test method
			Assert::Fail();
		}

		TEST_METHOD(TestToString)
		{
			// TODO: Implement test method
			Assert::Fail();
		}
	};
}