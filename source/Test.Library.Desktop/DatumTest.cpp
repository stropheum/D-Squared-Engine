#include "pch.h"
#include "CppUnitTest.h"
#include "Datum.h"
#include "RTTI.h"
#include "FooRTTI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{
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
#if _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif //_Debug
		}

		/// Detects if memory state has been corrupted
		static void finalizeLeakDetection()
		{
#if _DEBUG
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif //_Debug
		}

		TEST_METHOD_INITIALIZE(methodInitialize)
		{
			initializeLeakDetection();

			r1 = new FooRTTI();
			r2 = new FooRTTI(2);
			r3 = new FooRTTI(3);
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
			Library::Datum oldBusted(Library::DatumType::Integer);
			Library::Datum newHotness = oldBusted;
			Assert::IsTrue(oldBusted.Type() == newHotness.Type(), L"Copied types not equivalent");
			Assert::IsTrue(oldBusted.Size() == newHotness.Size(), L"Copied sizes not equivalent");
		}

		TEST_METHOD(TestCopyConstructor_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			Library::Datum iDatCopy(Library::DatumType::Integer);
			Assert::IsTrue(iDatCopy.Type() == Library::DatumType::Integer);
			Assert::IsTrue(iDatCopy.Size() == 0);
			Assert::IsTrue(iDatCopy.Capacity() == 0);

			auto iType = iDatCopy.Type();
			auto iSize = iDatCopy.Size();
			auto iCapacity = iDatCopy.Capacity();
			Library::Datum iDatMove(std::move(iDatCopy));
			Assert::IsTrue(iDatMove.Type() == iType);
			Assert::IsTrue(iDatMove.Size() == iSize);
			Assert::IsTrue(iDatMove.Capacity() == iCapacity);
		}

		TEST_METHOD(TestCopyConstructor_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			Library::Datum fDatCopy(Library::DatumType::Float);
			Assert::IsTrue(fDatCopy.Type() == Library::DatumType::Float);
			Assert::IsTrue(fDatCopy.Size() == 0);
			Assert::IsTrue(fDatCopy.Capacity() == 0);

			auto fType = fDatCopy.Type();
			auto fSize = fDatCopy.Size();
			auto fCapacity = fDatCopy.Capacity();
			Library::Datum fDatMove(std::move(fDatCopy));
			Assert::IsTrue(fDatMove.Type() == fType);
			Assert::IsTrue(fDatMove.Size() == fSize);
			Assert::IsTrue(fDatMove.Capacity() == fCapacity);
		}

		TEST_METHOD(TestCopyConstructor_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			Library::Datum vDatCopy(Library::DatumType::Vector);
			Assert::IsTrue(vDatCopy.Type() == Library::DatumType::Vector);
			Assert::IsTrue(vDatCopy.Size() == 0);
			Assert::IsTrue(vDatCopy.Capacity() == 0);

			auto vType = vDatCopy.Type();
			auto vSize = vDatCopy.Size();
			auto vCapacity = vDatCopy.Capacity();
			Library::Datum vDatMove(std::move(vDatCopy));
			Assert::IsTrue(vDatMove.Type() == vType);
			Assert::IsTrue(vDatMove.Size() == vSize);
			Assert::IsTrue(vDatMove.Capacity() == vCapacity);
		}

		TEST_METHOD(TestCopyConstructor_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			Library::Datum mDatCopy(Library::DatumType::Matrix);
			Assert::IsTrue(mDatCopy.Type() == Library::DatumType::Matrix);
			Assert::IsTrue(mDatCopy.Size() == 0);
			Assert::IsTrue(mDatCopy.Capacity() == 0);

			auto mType = mDatCopy.Type();
			auto mSize = mDatCopy.Size();
			auto mCapacity = mDatCopy.Capacity();
			Library::Datum mDatMove(std::move(mDatCopy));
			Assert::IsTrue(mDatMove.Type() == mType);
			Assert::IsTrue(mDatMove.Size() == mSize);
			Assert::IsTrue(mDatMove.Capacity() == mCapacity);
		}

		TEST_METHOD(TestCopyConstructor_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			Library::Datum sDatCopy(Library::DatumType::String);
			Assert::IsTrue(sDatCopy.Type() == Library::DatumType::String);
			Assert::IsTrue(sDatCopy.Size() == 0);
			Assert::IsTrue(sDatCopy.Capacity() == 0);

			auto sType = sDatCopy.Type();
			auto sSize = sDatCopy.Size();
			auto sCapacity = sDatCopy.Capacity();
			Library::Datum sDatMove(std::move(sDatCopy));
			Assert::IsTrue(sDatMove.Type() == sType);
			Assert::IsTrue(sDatMove.Size() == sSize);
			Assert::IsTrue(sDatMove.Capacity() == sCapacity);
		}

		TEST_METHOD(TestCopyConstructor_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			Library::Datum rDatCopy(Library::DatumType::Pointer);
			Assert::IsTrue(rDatCopy.Type() == Library::DatumType::Pointer);
			Assert::IsTrue(rDatCopy.Size() == 0);
			Assert::IsTrue(rDatCopy.Capacity() == 0);
			Assert::AreEqual(static_cast<std::uint32_t>(r3->TypeIdInstance()), 0u);

			auto rType = rDatCopy.Type();
			auto rSize = rDatCopy.Size();
			auto rCapacity = rDatCopy.Capacity();
			Library::Datum rDatMove(std::move(rDatCopy));
			Assert::IsTrue(rDatMove.Type() == rType);
			Assert::IsTrue(rDatMove.Size() == rSize);
			Assert::IsTrue(rDatMove.Capacity() == rCapacity);
		}

		TEST_METHOD(TestSetType_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			Library::Datum iDatumTemp;
			Assert::IsTrue(iDatumTemp.Type() == Library::DatumType::Unknown, L"Invalid Datum Type");

			iDatumTemp = Library::DatumType::Integer;
			Assert::IsTrue(iDatumTemp.Type() == Library::DatumType::Integer, L"Invalid Datum Type");

			Assert::ExpectException<std::exception>([&] { iDatumTemp.SetType(Library::DatumType::Unknown); },
				L"No exception thrown when reassigning Type");
		}

		TEST_METHOD(TestSetType_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			Library::Datum fDatumTemp;
			Assert::IsTrue(fDatumTemp.Type() == Library::DatumType::Unknown, L"Invalid Datum Type");

			fDatumTemp = Library::DatumType::Float;
			Assert::IsTrue(fDatumTemp.Type() == Library::DatumType::Float, L"Invalid Datum Type");

			Assert::ExpectException<std::exception>([&] { fDatumTemp.SetType(Library::DatumType::Unknown); },
				L"No exception thrown when reassigning Type");
		}

		TEST_METHOD(TestSetType_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			Library::Datum vDatumTemp;
			Assert::IsTrue(vDatumTemp.Type() == Library::DatumType::Unknown, L"Invalid Datum Type");

			vDatumTemp = Library::DatumType::Vector;
			Assert::IsTrue(vDatumTemp.Type() == Library::DatumType::Vector, L"Invalid Datum Type");

			Assert::ExpectException<std::exception>([&] { vDatumTemp.SetType(Library::DatumType::Unknown); },
				L"No exception thrown when reassigning Type");
		}

		TEST_METHOD(TestSetType_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			Library::Datum mDatumTemp;
			Assert::IsTrue(mDatumTemp.Type() == Library::DatumType::Unknown, L"Invalid Datum Type");

			mDatumTemp = Library::DatumType::Matrix;
			Assert::IsTrue(mDatumTemp.Type() == Library::DatumType::Matrix, L"Invalid Datum Type");

			Assert::ExpectException<std::exception>([&] { mDatumTemp.SetType(Library::DatumType::Unknown); },
				L"No exception thrown when reassigning Type");
		}

		TEST_METHOD(TestSetType_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			Library::Datum sDatumTemp;
			Assert::IsTrue(sDatumTemp.Type() == Library::DatumType::Unknown, L"Invalid Datum Type");

			sDatumTemp = Library::DatumType::String;
			Assert::IsTrue(sDatumTemp.Type() == Library::DatumType::String, L"Invalid Datum Type");

			Assert::ExpectException<std::exception>([&] 
			{ 
				sDatumTemp.SetType(Library::DatumType::Unknown); 
			},
				L"No exception thrown when reassigning Type");
		}

		TEST_METHOD(TestSetType_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			Library::Datum rDatumTemp;
			Assert::IsTrue(rDatumTemp.Type() == Library::DatumType::Unknown, L"Invalid Datum Type");

			rDatumTemp = Library::DatumType::Pointer;
			Assert::IsTrue(rDatumTemp.Type() == Library::DatumType::Pointer, L"Invalid Datum Type");

			Assert::ExpectException<std::exception>([&] 
			{ 
				rDatumTemp.SetType(Library::DatumType::Unknown); 
			},
				L"No exception thrown when reassigning Type");
		}

		TEST_METHOD(TestSetType_Unknown)
		{
			Library::Datum uDatumTemp;
			Assert::IsTrue(uDatumTemp.Type() == Library::DatumType::Unknown, L"Invalid Datum Type");
		}

		TEST_METHOD(TestAssignmentOperator_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			iDatum = i1;
			Assert::IsTrue(iDatum.Get<std::int32_t>(0) == i1);
			Assert::ExpectException<std::exception>([&] { iDatum.Get<float>(0); });
			Assert::ExpectException<std::exception>([&] { iDatum.Get<glm::vec4>(0); });
			Assert::ExpectException<std::exception>([&] { iDatum.Get<glm::mat4>(0); });
			Assert::ExpectException<std::exception>([&] { iDatum.Get<std::string>(0); });
			Assert::ExpectException<std::exception>([&] { iDatum.Get<Library::RTTI*>(0); });

			std::uint32_t isize = 10;
			std::int32_t* iData = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * isize));
			Library::Datum iDatumCopy1;
			iDatumCopy1.SetStorage(iData, isize);
			Library::Datum iDatumCopy2 = iDatumCopy1;
			Assert::IsTrue(iDatumCopy1.Type() == iDatumCopy2.Type());
			Assert::IsTrue(iDatumCopy1.Size() == iDatumCopy2.Size());
			Assert::IsTrue(iDatumCopy1.Capacity() == iDatumCopy2.Capacity());
			free(iData);

			// Move semantic assignment
			iDatum.PushBack(i1);
			iDatum.PushBack(i2);
			iDatum.PushBack(i2);
			Library::Datum iDatumCopy;
			iDatumCopy = iDatum;
			Assert::IsTrue(iDatum == iDatumCopy);

			auto iType = iDatumCopy.Type();
			auto iSize = iDatumCopy.Size();
			auto iCapa = iDatumCopy.Capacity();
			Library::Datum iDatumMoveCopy = std::move(iDatumCopy);
			Assert::IsTrue(iDatumMoveCopy.Type() == iType);
			Assert::IsTrue(iDatumMoveCopy.Size() == iSize);
			Assert::IsTrue(iDatumMoveCopy.Capacity() == iCapa);

			iType = iDatumCopy1.Type();
			iSize = iDatumCopy1.Size();
			iCapa = iDatumCopy1.Capacity();
			Library::Datum iDatumCopy3 = std::move(iDatumCopy1);
			Assert::IsTrue(iDatumCopy3.Type() == iType);
			Assert::IsTrue(iDatumCopy3.Size() == iSize);
			Assert::IsTrue(iDatumCopy3.Capacity() == iCapa);
		}

		TEST_METHOD(TestAssignmentOperator_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			fDatum = f1;
			Assert::IsTrue(fDatum.Get<float>(0) == f1);
			Assert::ExpectException<std::exception>([&] { fDatum.Get<std::int32_t>(0); });
			Assert::ExpectException<std::exception>([&] { fDatum.Get<glm::vec4>(0); });
			Assert::ExpectException<std::exception>([&] { fDatum.Get<glm::mat4>(0); });
			Assert::ExpectException<std::exception>([&] { fDatum.Get<std::string>(0); });
			Assert::ExpectException<std::exception>([&] { fDatum.Get<Library::RTTI*>(0); });

			std::uint32_t fsize = 10;
			float* fData = static_cast<float*>(malloc(sizeof(float) * fsize));
			Library::Datum fDatumCopy1;
			fDatumCopy1.SetStorage(fData, fsize);
			Library::Datum fDatumCopy2 = fDatumCopy1;
			Assert::IsTrue(fDatumCopy1.Type() == fDatumCopy2.Type());
			Assert::IsTrue(fDatumCopy1.Size() == fDatumCopy2.Size());
			Assert::IsTrue(fDatumCopy1.Capacity() == fDatumCopy2.Capacity());
			free(fData);

			// Move semantic assignment
			fDatum.PushBack(f1);
			fDatum.PushBack(f2);
			fDatum.PushBack(f2);
			Library::Datum fDatumCopy;
			fDatumCopy = fDatum;
			Assert::IsTrue(fDatum == fDatumCopy);

			auto fType = fDatumCopy.Type();
			auto fSize = fDatumCopy.Size();
			auto fCapa = fDatumCopy.Capacity();
			Library::Datum fDatumMoveCopy = std::move(fDatumCopy);
			Assert::IsTrue(fDatumMoveCopy.Type() == fType);
			Assert::IsTrue(fDatumMoveCopy.Size() == fSize);
			Assert::IsTrue(fDatumMoveCopy.Capacity() == fCapa);

			fType = fDatumCopy1.Type();
			fSize = fDatumCopy1.Size();
			fCapa = fDatumCopy1.Capacity();
			Library::Datum fDatumCopy3 = std::move(fDatumCopy1);
			Assert::IsTrue(fDatumCopy3.Type() == fType);
			Assert::IsTrue(fDatumCopy3.Size() == fSize);
			Assert::IsTrue(fDatumCopy3.Capacity() == fCapa);
		}

		TEST_METHOD(TestAssignmentOperator_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			vDatum = v1;
			Assert::IsTrue(vDatum.Get<glm::vec4>(0) == v1);
			Assert::ExpectException<std::exception>([&] { vDatum.Get<std::int32_t>(0); });
			Assert::ExpectException<std::exception>([&] { vDatum.Get<float>(0); });
			Assert::ExpectException<std::exception>([&] { vDatum.Get<glm::mat4>(0); });
			Assert::ExpectException<std::exception>([&] { vDatum.Get<std::string>(0); });
			Assert::ExpectException<std::exception>([&] { vDatum.Get<Library::RTTI*>(0); });

			std::uint32_t vsize = 10;
			glm::vec4* vData = static_cast<glm::vec4*>(malloc(sizeof(glm::vec4) * vsize));
			Library::Datum vDatumCopy1;
			vDatumCopy1.SetStorage(vData, vsize);
			Library::Datum vDatumCopy2 = vDatumCopy1;
			Assert::IsTrue(vDatumCopy1.Type() == vDatumCopy2.Type());
			Assert::IsTrue(vDatumCopy1.Size() == vDatumCopy2.Size());
			Assert::IsTrue(vDatumCopy1.Capacity() == vDatumCopy2.Capacity());
			free(vData);

			// Move semantic assignment
			vDatum.PushBack(v1);
			vDatum.PushBack(v2);
			vDatum.PushBack(v2);
			Library::Datum vDatumCopy;
			vDatumCopy = vDatum;
			Assert::IsTrue(vDatum == vDatumCopy);

			auto vType = vDatumCopy.Type();
			auto vSize = vDatumCopy.Size();
			auto vCapa = vDatumCopy.Capacity();
			Library::Datum vDatumMoveCopy = std::move(vDatumCopy);
			Assert::IsTrue(vDatumMoveCopy.Type() == vType);
			Assert::IsTrue(vDatumMoveCopy.Size() == vSize);
			Assert::IsTrue(vDatumMoveCopy.Capacity() == vCapa);

			vType = vDatumCopy1.Type();
			vSize = vDatumCopy1.Size();
			vCapa = vDatumCopy1.Capacity();
			Library::Datum vDatumCopy3 = std::move(vDatumCopy1);
			Assert::IsTrue(vDatumCopy3.Type() == vType);
			Assert::IsTrue(vDatumCopy3.Size() == vSize);
			Assert::IsTrue(vDatumCopy3.Capacity() == vCapa);
		}

		TEST_METHOD(TestAssignmentOperator_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			mDatum = m1;
			Assert::IsTrue(mDatum.Get<glm::mat4>(0) == m1);
			Assert::ExpectException<std::exception>([&] { mDatum.Get<std::int32_t>(0); });
			Assert::ExpectException<std::exception>([&] { mDatum.Get<float>(0); });
			Assert::ExpectException<std::exception>([&] { mDatum.Get<glm::vec4>(0); });
			Assert::ExpectException<std::exception>([&] { mDatum.Get<std::string>(0); });
			Assert::ExpectException<std::exception>([&] { mDatum.Get<Library::RTTI*>(0); });

			std::uint32_t msize = 10;
			glm::mat4* mData = static_cast<glm::mat4*>(malloc(sizeof(glm::mat4) * msize));
			Library::Datum mDatumCopy1;
			mDatumCopy1.SetStorage(mData, msize);
			Library::Datum mDatumCopy2 = mDatumCopy1;
			Assert::IsTrue(mDatumCopy1.Type() == mDatumCopy2.Type());
			Assert::IsTrue(mDatumCopy1.Size() == mDatumCopy2.Size());
			Assert::IsTrue(mDatumCopy1.Capacity() == mDatumCopy2.Capacity());
			free(mData);

			// Move semantic assignment
			mDatum.PushBack(m1);
			mDatum.PushBack(m2);
			mDatum.PushBack(m2);
			Library::Datum mDatumCopy = mDatum;
			Assert::IsTrue(mDatum == mDatumCopy);

			auto mType = mDatumCopy.Type();
			auto mSize = mDatumCopy.Size();
			auto mCapa = mDatumCopy.Capacity();
			Library::Datum mDatumMoveCopy = std::move(mDatumCopy);
			Assert::IsTrue(mDatumMoveCopy.Type() == mType);
			Assert::IsTrue(mDatumMoveCopy.Size() == mSize);
			Assert::IsTrue(mDatumMoveCopy.Capacity() == mCapa);

			mType = mDatumCopy1.Type();
			mSize = mDatumCopy1.Size();
			mCapa = mDatumCopy1.Capacity();
			Library::Datum mDatumCopy3 = std::move(mDatumCopy1);
			Assert::IsTrue(mDatumCopy3.Type() == mType);
			Assert::IsTrue(mDatumCopy3.Size() == mSize);
			Assert::IsTrue(mDatumCopy3.Capacity() == mCapa);
		}

		TEST_METHOD(TestAssignmentOperator_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			// String
			sDatum = s1;
			Assert::IsTrue(sDatum.Get<std::string>(0) == s1);
			Assert::ExpectException<std::exception>([&] { sDatum.Get<std::int32_t>(0); });
			Assert::ExpectException<std::exception>([&] { sDatum.Get<float>(0); });
			Assert::ExpectException<std::exception>([&] { sDatum.Get<glm::vec4>(0); });
			Assert::ExpectException<std::exception>([&] { sDatum.Get<glm::mat4>(0); });
			Assert::ExpectException<std::exception>([&] { sDatum.Get<Library::RTTI*>(0); });

			std::uint32_t ssize = 10;
			std::string* sData = static_cast<std::string*>(malloc(sizeof(std::string) * ssize));
			Library::Datum sDatumCopy1;
			sDatumCopy1.SetStorage(sData, ssize);
			Library::Datum sDatumCopy2 = sDatumCopy1;
			Assert::IsTrue(sDatumCopy1.Type() == sDatumCopy2.Type());
			Assert::IsTrue(sDatumCopy1.Size() == sDatumCopy2.Size());
			Assert::IsTrue(sDatumCopy1.Capacity() == sDatumCopy2.Capacity());
			free(sData);

			// Move semantic assignment
			sDatum.PushBack(s1);
			sDatum.PushBack(s2);
			sDatum.PushBack(s2);
			Library::Datum sDatumCopy = sDatum;
			Assert::IsTrue(sDatum == sDatumCopy);

			auto sType = sDatumCopy.Type();
			auto sSize = sDatumCopy.Size();
			auto sCapa = sDatumCopy.Capacity();
			Library::Datum sDatumMoveCopy = std::move(sDatumCopy);
			Assert::IsTrue(sDatumMoveCopy.Type() == sType);
			Assert::IsTrue(sDatumMoveCopy.Size() == sSize);
			Assert::IsTrue(sDatumMoveCopy.Capacity() == sCapa);

			sType = sDatumCopy1.Type();
			sSize = sDatumCopy1.Size();
			sCapa = sDatumCopy1.Capacity();
			Library::Datum sDatumCopy3 = std::move(sDatumCopy1);
			Assert::IsTrue(sDatumCopy3.Type() == sType);
			Assert::IsTrue(sDatumCopy3.Size() == sSize);
			Assert::IsTrue(sDatumCopy3.Capacity() == sCapa);
		}
		TEST_METHOD(TestAssignmentOperator_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			// Pointer
			rDatum = r1;
			Assert::IsTrue(rDatum.Get<Library::RTTI*>(0) == r1);
			Assert::ExpectException<std::exception>([&] { rDatum.Get<std::int32_t>(0); });
			Assert::ExpectException<std::exception>([&] { rDatum.Get<float>(0); });
			Assert::ExpectException<std::exception>([&] { rDatum.Get<glm::vec4>(0); });
			Assert::ExpectException<std::exception>([&] { rDatum.Get<glm::mat4>(0); });
			Assert::ExpectException<std::exception>([&] { rDatum.Get<std::string>(0); });

			std::uint32_t rsize = 10;
			Library::RTTI** rData = static_cast<Library::RTTI**>(malloc(sizeof(Library::RTTI*) * rsize));
			Library::Datum rDatumCopy1;
			rDatumCopy1.SetStorage(rData, rsize);
			Library::Datum rDatumCopy2 = rDatumCopy1;
			Assert::IsTrue(rDatumCopy1.Type() == rDatumCopy2.Type());
			Assert::IsTrue(rDatumCopy1.Size() == rDatumCopy2.Size());
			Assert::IsTrue(rDatumCopy1.Capacity() == rDatumCopy2.Capacity());
			free(rData);

			// Move semantic assignment
			rDatum.PushBack(r1);
			rDatum.PushBack(r2);
			rDatum.PushBack(r2);
			Library::Datum rDatumCopy = rDatum;
			Assert::IsTrue(rDatum == rDatumCopy);

			auto rType = rDatumCopy.Type();
			auto rSize = rDatumCopy.Size();
			auto rCapa = rDatumCopy.Capacity();
			Library::Datum rDatumMoveCopy = std::move(rDatumCopy);
			Assert::IsTrue(rDatumMoveCopy.Type() == rType);
			Assert::IsTrue(rDatumMoveCopy.Size() == rSize);
			Assert::IsTrue(rDatumMoveCopy.Capacity() == rCapa);

			rType = rDatumCopy1.Type();
			rSize = rDatumCopy1.Size();
			rCapa = rDatumCopy1.Capacity();
			Library::Datum rDatumCopy3 = std::move(rDatumCopy1);
			Assert::IsTrue(rDatumCopy3.Type() == rType);
			Assert::IsTrue(rDatumCopy3.Size() == rSize);
			Assert::IsTrue(rDatumCopy3.Capacity() == rCapa);
		}

		TEST_METHOD(TestEqualityOperator_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);
			
			iDatum.PushBack(i1);
			Assert::IsTrue(iDatum == i1, L"Value not equivalent to value assigned");
			Assert::IsFalse(iDatum == i2, L"value equivalent to incorrect scalar value");
			Assert::IsFalse(iDatum == i3, L"value equivalent to incorrect scalar value");

			iDatum.PushBack(i2);
			Assert::IsFalse(iDatum == i1, L"operator!= should always return true when Size > 1");
			Assert::IsFalse(iDatum == i2, L"operator!= should always return true when Size > 1");
			Assert::IsFalse(iDatum == i3, L"operator!= should always return true when Size > 1");

			Assert::IsTrue(iDatum == Library::DatumType::Integer);
			Assert::IsFalse(iDatum == Library::DatumType::Float);
			Assert::IsFalse(iDatum == Library::DatumType::Vector);
			Assert::IsFalse(iDatum == Library::DatumType::Matrix);
			Assert::IsFalse(iDatum == Library::DatumType::String);
			Assert::IsFalse(iDatum == Library::DatumType::Pointer);

			Library::Datum iDatumOther(Library::DatumType::Integer);
			iDatumOther.PushBack(i1);
			iDatumOther.PushBack(i1);
			Assert::IsFalse(iDatum == iDatumOther);
		}

		TEST_METHOD(TestEqualityOperator_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);
			
			fDatum.PushBack(f1);
			Assert::IsTrue(fDatum == f1, L"Value not equivalent to value assigned");
			Assert::IsFalse(fDatum == f2, L"value equivalent to incorrect scalar value");
			Assert::IsFalse(fDatum == f3, L"value equivalent to incorrect scalar value");

			fDatum.PushBack(f2);
			Assert::IsFalse(fDatum == f1, L"operator!= should always return true when Size > 1");
			Assert::IsFalse(fDatum == f2, L"operator!= should always return true when Size > 1");
			Assert::IsFalse(fDatum == f3, L"operator!= should always return true when Size > 1");

			Assert::IsTrue(fDatum == Library::DatumType::Float);
			Assert::IsFalse(fDatum == Library::DatumType::Integer);
			Assert::IsFalse(fDatum == Library::DatumType::Vector);
			Assert::IsFalse(fDatum == Library::DatumType::Matrix);
			Assert::IsFalse(fDatum == Library::DatumType::String);
			Assert::IsFalse(fDatum == Library::DatumType::Pointer);

			Library::Datum fDatumOther(Library::DatumType::Float);
			fDatumOther.PushBack(f1);
			fDatumOther.PushBack(f1);
			Assert::IsFalse(fDatum == fDatumOther);
		}

		TEST_METHOD(TestEqualityOperator_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);
			
			vDatum.PushBack(v1);
			Assert::IsTrue(vDatum == v1, L"Value not equivalent to value assigned");
			Assert::IsFalse(vDatum == v2, L"value equivalent to incorrect scalar value");
			Assert::IsFalse(vDatum == v3, L"value equivalent to incorrect scalar value");

			vDatum.PushBack(v2);
			Assert::IsFalse(vDatum == v1, L"operator!= should always return true when Size > 1");
			Assert::IsFalse(vDatum == v2, L"operator!= should always return true when Size > 1");
			Assert::IsFalse(vDatum == v3, L"operator!= should always return true when Size > 1");

			Assert::IsTrue(vDatum == Library::DatumType::Vector);
			Assert::IsFalse(vDatum == Library::DatumType::Integer);
			Assert::IsFalse(vDatum == Library::DatumType::Float);
			Assert::IsFalse(vDatum == Library::DatumType::Matrix);
			Assert::IsFalse(vDatum == Library::DatumType::String);
			Assert::IsFalse(vDatum == Library::DatumType::Pointer);

			Library::Datum vDatumOther(Library::DatumType::Vector);
			vDatumOther.PushBack(v1);
			vDatumOther.PushBack(v1);
			Assert::IsFalse(vDatum == vDatumOther);
		}

		TEST_METHOD(TestEqualityOperator_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);
			
			mDatum.PushBack(m1);
			Assert::IsTrue(mDatum == m1, L"Value not equivalent to value assigned");
			Assert::IsFalse(mDatum == m2, L"value equivalent to incorrect scalar value");
			Assert::IsFalse(mDatum == m3, L"value equivalent to incorrect scalar value");

			mDatum.PushBack(m2);
			Assert::IsFalse(mDatum == m1, L"operator!= should always return true when Size > 1");
			Assert::IsFalse(mDatum == m2, L"operator!= should always return true when Size > 1");
			Assert::IsFalse(mDatum == m3, L"operator!= should always return true when Size > 1");

			Assert::IsTrue(mDatum == Library::DatumType::Matrix);
			Assert::IsFalse(mDatum == Library::DatumType::Integer);
			Assert::IsFalse(mDatum == Library::DatumType::Float);
			Assert::IsFalse(mDatum == Library::DatumType::Vector);
			Assert::IsFalse(mDatum == Library::DatumType::String);
			Assert::IsFalse(mDatum == Library::DatumType::Pointer);

			Library::Datum mDatumOther(Library::DatumType::Matrix);
			mDatumOther.PushBack(m1);
			mDatumOther.PushBack(m1);
			Assert::IsFalse(mDatum == mDatumOther);
		}

		TEST_METHOD(TestEqualityOperator_String)
		{
			Library::Datum sDatum(Library::DatumType::String);
			
			sDatum.PushBack(s1);
			Assert::IsTrue(sDatum == s1, L"Value not equivalent to value assigned");
			Assert::IsFalse(sDatum == s2, L"value equivalent to incorrect scalar value");
			Assert::IsFalse(sDatum == s3, L"value equivalent to incorrect scalar value");

			sDatum.PushBack(s2);
			Assert::IsFalse(sDatum == s1, L"operator!= should always return true when Size > 1");
			Assert::IsFalse(sDatum == s2, L"operator!= should always return true when Size > 1");
			Assert::IsFalse(sDatum == s3, L"operator!= should always return true when Size > 1");

			Assert::IsTrue(sDatum == Library::DatumType::String);
			Assert::IsFalse(sDatum == Library::DatumType::Integer);
			Assert::IsFalse(sDatum == Library::DatumType::Float);
			Assert::IsFalse(sDatum == Library::DatumType::Vector);
			Assert::IsFalse(sDatum == Library::DatumType::Matrix);
			Assert::IsFalse(sDatum == Library::DatumType::Pointer);

			Library::Datum sDatumOther(Library::DatumType::String);
			sDatumOther.PushBack(s1);
			sDatumOther.PushBack(s1);
			Assert::IsFalse(sDatum == sDatumOther);
		}

		TEST_METHOD(TestEqualityOperator_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			rDatum.PushBack(r1);
			Assert::IsTrue(rDatum == r1, L"Value not equivalent to value assigned");
			Assert::IsFalse(rDatum == r2, L"value equivalent to incorrect scalar value");
			Assert::IsFalse(rDatum == r3, L"value equivalent to incorrect scalar value");
			rDatum.PushBack(r2);
			Assert::IsFalse(rDatum == r1, L"operator!= should always return true when Size > 1");
			Assert::IsFalse(rDatum == r2, L"operator!= should always return true when Size > 1");
			Assert::IsFalse(rDatum == r3, L"operator!= should always return true when Size > 1");

			Assert::IsTrue(rDatum == Library::DatumType::Pointer);
			Assert::IsFalse(rDatum == Library::DatumType::Integer);
			Assert::IsFalse(rDatum == Library::DatumType::Float);
			Assert::IsFalse(rDatum == Library::DatumType::Vector);
			Assert::IsFalse(rDatum == Library::DatumType::Matrix);
			Assert::IsFalse(rDatum == Library::DatumType::String);

			Library::Datum rDatumOther(Library::DatumType::Pointer);
			rDatumOther.PushBack(r1);
			rDatumOther.PushBack(r1);
			Assert::IsFalse(rDatum == rDatumOther);
		}

		TEST_METHOD(TestInequalityOperator_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			Assert::IsFalse(iDatum != iDatum);

			iDatum.PushBack(i1);
			Assert::IsFalse(iDatum != i1, L"Value not equivalent to value assigned");
			Assert::IsTrue(iDatum != i2, L"value equivalent to incorrect scalar value");
			Assert::IsTrue(iDatum != i3, L"value equivalent to incorrect scalar value");

			iDatum.PushBack(i2);
			Assert::IsTrue(iDatum != i1, L"operator!= should always return true when Size > 1");
			Assert::IsTrue(iDatum != i2, L"operator!= should always return true when Size > 1");
			Assert::IsTrue(iDatum != i3, L"operator!= should always return true when Size > 1");

			Assert::IsFalse(iDatum != Library::DatumType::Integer);
			Assert::IsTrue(iDatum.Type() != Library::DatumType::Float);
			Assert::IsTrue(iDatum.Type() != Library::DatumType::Vector);
			Assert::IsTrue(iDatum.Type() != Library::DatumType::Matrix);
			Assert::IsTrue(iDatum.Type() != Library::DatumType::String);
			Assert::IsTrue(iDatum.Type() != Library::DatumType::Pointer);
		}

		TEST_METHOD(TestInequalityOperator_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			Assert::IsFalse(fDatum != fDatum);

			fDatum.PushBack(f1);
			Assert::IsFalse(fDatum != f1, L"Value not equivalent to value assigned");
			Assert::IsTrue(fDatum != f2, L"value equivalent to incorrect scalar value");
			Assert::IsTrue(fDatum != f3, L"value equivalent to incorrect scalar value");

			fDatum.PushBack(f2);
			Assert::IsTrue(fDatum != f1, L"operator!= should always return true when Size > 1");
			Assert::IsTrue(fDatum != f2, L"operator!= should always return true when Size > 1");
			Assert::IsTrue(fDatum != f3, L"operator!= should always return true when Size > 1");

			Assert::IsFalse(fDatum != Library::DatumType::Float);
			Assert::IsTrue(fDatum.Type() != Library::DatumType::Integer);
			Assert::IsTrue(fDatum.Type() != Library::DatumType::Vector);
			Assert::IsTrue(fDatum.Type() != Library::DatumType::Matrix);
			Assert::IsTrue(fDatum.Type() != Library::DatumType::String);
			Assert::IsTrue(fDatum.Type() != Library::DatumType::Pointer);
		}

		TEST_METHOD(TestInequalityOperator_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			Assert::IsFalse(vDatum != vDatum);

			vDatum.PushBack(v1);
			Assert::IsFalse(vDatum != v1, L"Value not equivalent to value assigned");
			Assert::IsTrue(vDatum != v2, L"value equivalent to incorrect scalar value");
			Assert::IsTrue(vDatum != v3, L"value equivalent to incorrect scalar value");

			vDatum.PushBack(v2);
			Assert::IsTrue(vDatum != v1, L"operator!= should always return true when Size > 1");
			Assert::IsTrue(vDatum != v2, L"operator!= should always return true when Size > 1");
			Assert::IsTrue(vDatum != v3, L"operator!= should always return true when Size > 1");

			Assert::IsFalse(vDatum != Library::DatumType::Vector);
			Assert::IsTrue(vDatum.Type() != Library::DatumType::Integer);
			Assert::IsTrue(vDatum.Type() != Library::DatumType::Float);
			Assert::IsTrue(vDatum.Type() != Library::DatumType::Matrix);
			Assert::IsTrue(vDatum.Type() != Library::DatumType::String);
			Assert::IsTrue(vDatum.Type() != Library::DatumType::Pointer);
		}

		TEST_METHOD(TestInequalityOperator_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			Assert::IsFalse(mDatum != mDatum);

			mDatum.PushBack(m1);
			Assert::IsFalse(mDatum != m1, L"Value not equivalent to value assigned");
			Assert::IsTrue(mDatum != m2, L"value equivalent to incorrect scalar value");
			Assert::IsTrue(mDatum != m3, L"value equivalent to incorrect scalar value");

			mDatum.PushBack(m2);
			Assert::IsTrue(mDatum != m1, L"operator!= should always return true when Size > 1");
			Assert::IsTrue(mDatum != m2, L"operator!= should always return true when Size > 1");
			Assert::IsTrue(mDatum != m3, L"operator!= should always return true when Size > 1");

			Assert::IsFalse(mDatum != Library::DatumType::Matrix);
			Assert::IsTrue(mDatum.Type() != Library::DatumType::Integer);
			Assert::IsTrue(mDatum.Type() != Library::DatumType::Float);
			Assert::IsTrue(mDatum.Type() != Library::DatumType::Vector);
			Assert::IsTrue(mDatum.Type() != Library::DatumType::String);
			Assert::IsTrue(mDatum.Type() != Library::DatumType::Pointer);
		}

		TEST_METHOD(TestInequalityOperator_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			Assert::IsFalse(sDatum != sDatum);

			sDatum.PushBack(s1);
			Assert::IsFalse(sDatum != s1, L"Value not equivalent to value assigned");
			Assert::IsTrue(sDatum != s2, L"value equivalent to incorrect scalar value");
			Assert::IsTrue(sDatum != s3, L"value equivalent to incorrect scalar value");

			sDatum.PushBack(s2);
			Assert::IsTrue(sDatum != s1, L"operator!= should always return true when Size > 1");
			Assert::IsTrue(sDatum != s2, L"operator!= should always return true when Size > 1");
			Assert::IsTrue(sDatum != s3, L"operator!= should always return true when Size > 1");

			Assert::IsFalse(sDatum != Library::DatumType::String);
			Assert::IsTrue(sDatum.Type() != Library::DatumType::Integer);
			Assert::IsTrue(sDatum.Type() != Library::DatumType::Float);
			Assert::IsTrue(sDatum.Type() != Library::DatumType::Vector);
			Assert::IsTrue(sDatum.Type() != Library::DatumType::Matrix);
			Assert::IsTrue(sDatum.Type() != Library::DatumType::Pointer);
		}

		TEST_METHOD(TestInequalityOperator_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			Assert::IsFalse(rDatum != rDatum);

			rDatum.PushBack(r1);
			Assert::IsFalse(rDatum != r1, L"Value not equivalent to value assigned");
			Assert::IsTrue(rDatum != r2, L"value equivalent to incorrect scalar value");
			Assert::IsTrue(rDatum != r3, L"value equivalent to incorrect scalar value");
			rDatum.PushBack(r2);
			Assert::IsTrue(rDatum != r1, L"operator!= should always return true when Size > 1");
			Assert::IsTrue(rDatum != r2, L"operator!= should always return true when Size > 1");
			Assert::IsTrue(rDatum != r3, L"operator!= should always return true when Size > 1");

			Assert::IsFalse(rDatum != Library::DatumType::Pointer);
			Assert::IsTrue(rDatum.Type() != Library::DatumType::Integer);
			Assert::IsTrue(rDatum.Type() != Library::DatumType::Float);
			Assert::IsTrue(rDatum.Type() != Library::DatumType::Vector);
			Assert::IsTrue(rDatum.Type() != Library::DatumType::Matrix);
			Assert::IsTrue(rDatum.Type() != Library::DatumType::String);
		}

		TEST_METHOD(TestType_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			Library::Datum iDatumTemp1;
			Assert::IsTrue(iDatumTemp1.Type() == Library::DatumType::Unknown);

			iDatumTemp1 = Library::DatumType::Integer;
			Assert::IsTrue(iDatumTemp1.Type() == Library::DatumType::Integer);

			Library::Datum iDatumTemp2;
			iDatumTemp2 = i1;
			Assert::IsTrue(iDatumTemp2.Type() == Library::DatumType::Integer);

			iDatumTemp2 = i2;
			Assert::IsTrue(iDatumTemp2.Type() == Library::DatumType::Integer);
			Assert::ExpectException<std::exception>([&] { iDatumTemp2 = f1; },
				L"Exception not being thrown when assigned improper Type");
		}

		TEST_METHOD(TestType_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			Library::Datum fDatumTemp1;
			Assert::IsTrue(fDatumTemp1.Type() == Library::DatumType::Unknown);

			fDatumTemp1 = Library::DatumType::Float;
			Assert::IsTrue(fDatumTemp1.Type() == Library::DatumType::Float);

			Library::Datum fDatumTemp2;
			fDatumTemp2 = f1;
			Assert::IsTrue(fDatumTemp2.Type() == Library::DatumType::Float);

			fDatumTemp2 = f2;
			Assert::IsTrue(fDatumTemp2.Type() == Library::DatumType::Float);
			Assert::ExpectException<std::exception>([&] { fDatumTemp2 = i1; },
				L"Exception not being thrown when assigned improper Type");
		}

		TEST_METHOD(TestType_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			Library::Datum vDatumTemp1;
			Assert::IsTrue(vDatumTemp1.Type() == Library::DatumType::Unknown);

			vDatumTemp1 = Library::DatumType::Vector;
			Assert::IsTrue(vDatumTemp1.Type() == Library::DatumType::Vector);

			Library::Datum vDatumTemp2;
			vDatumTemp2 = v1;
			Assert::IsTrue(vDatumTemp2.Type() == Library::DatumType::Vector);

			vDatumTemp2 = v2;
			Assert::IsTrue(vDatumTemp2.Type() == Library::DatumType::Vector);
			Assert::ExpectException<std::exception>([&] { vDatumTemp2 = i1; },
				L"Exception not being thrown when assigned improper Type");
		}

		TEST_METHOD(TestType_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			Library::Datum mDatumTemp1;
			Assert::IsTrue(mDatumTemp1.Type() == Library::DatumType::Unknown);

			mDatumTemp1 = Library::DatumType::Matrix;
			Assert::IsTrue(mDatumTemp1.Type() == Library::DatumType::Matrix);

			Library::Datum mDatumTemp2;
			mDatumTemp2 = m1;
			Assert::IsTrue(mDatumTemp2.Type() == Library::DatumType::Matrix);

			mDatumTemp2 = m2;
			Assert::IsTrue(mDatumTemp2.Type() == Library::DatumType::Matrix);
			Assert::ExpectException<std::exception>([&] { mDatumTemp2 = i1; },
				L"Exception not being thrown when assigned improper Type");
		}

		TEST_METHOD(TestType_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			Library::Datum sDatumTemp1;
			Assert::IsTrue(sDatumTemp1.Type() == Library::DatumType::Unknown);

			sDatumTemp1 = Library::DatumType::String;
			Assert::IsTrue(sDatumTemp1.Type() == Library::DatumType::String);

			Library::Datum sDatumTemp2;
			sDatumTemp2 = s1;
			Assert::IsTrue(sDatumTemp2.Type() == Library::DatumType::String);

			sDatumTemp2 = s2;
			Assert::IsTrue(sDatumTemp2.Type() == Library::DatumType::String);
			Assert::ExpectException<std::exception>([&] { sDatumTemp2 = i1; },
				L"Exception not being thrown when assigned improper Type");
		}

		TEST_METHOD(TestType_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			Library::Datum rDatumTemp1;
			Assert::IsTrue(rDatumTemp1.Type() == Library::DatumType::Unknown);

			rDatumTemp1 = Library::DatumType::Pointer;
			Assert::IsTrue(rDatumTemp1.Type() == Library::DatumType::Pointer);

			Library::Datum rDatumTemp2;
			rDatumTemp2 = r1;
			Assert::IsTrue(rDatumTemp2.Type() == Library::DatumType::Pointer);

			rDatumTemp2 = r2;
			Assert::IsTrue(rDatumTemp2.Type() == Library::DatumType::Pointer);
			Assert::ExpectException<std::exception>([&] { rDatumTemp2 = i1; },
				L"Exception not being thrown when assigned improper Type");
		}

		TEST_METHOD(TestSize_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			Assert::AreEqual(iDatum.Size(), 0u, L"Size not zero on empty Datum");

			iDatum.PushBack(i1);
			Assert::AreEqual(iDatum.Size(), 1u), L"Size does not reflect number of elements pushed";

			iDatum.PushBack(i2);
			Assert::AreEqual(iDatum.Size(), 2u, L"Size does not reflect number of elements pushed");

			iDatum.SetSize(10);
			Assert::AreEqual(iDatum.Size(), 10u, L"Size not equal after calling SetSize");

			iDatum.SetSize(1);
			Assert::AreEqual(iDatum.Size(), 1u, L"SetSize should reduce current Size");
		}

		TEST_METHOD(TestSize_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			Assert::AreEqual(fDatum.Size(), 0u, L"Size not zero on empty Datum");

			fDatum.PushBack(f1);
			Assert::AreEqual(fDatum.Size(), 1u), L"Size does not reflect number of elements pushed";

			fDatum.PushBack(f2);
			Assert::AreEqual(fDatum.Size(), 2u, L"Size does not reflect number of elements pushed");

			fDatum.SetSize(10);
			Assert::AreEqual(fDatum.Size(), 10u, L"Size not equal after calling SetSize");

			fDatum.SetSize(1);
			Assert::AreEqual(fDatum.Size(), 1u, L"SetSize should reduce current Size");
		}

		TEST_METHOD(TestSize_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			Assert::AreEqual(vDatum.Size(), 0u, L"Size not zero on empty Datum");

			vDatum.PushBack(v1);
			Assert::AreEqual(vDatum.Size(), 1u), L"Size does not reflect number of elements pushed";

			vDatum.PushBack(v2);
			Assert::AreEqual(vDatum.Size(), 2u, L"Size does not reflect number of elements pushed");

			vDatum.SetSize(10);
			Assert::AreEqual(vDatum.Size(), 10u, L"Size not equal after calling SetSize");

			vDatum.SetSize(1);
			Assert::AreEqual(vDatum.Size(), 1u, L"SetSize should reduce current Size");
		}

		TEST_METHOD(TestSize_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			Assert::AreEqual(mDatum.Size(), 0u, L"Size not zero on empty Datum");

			mDatum.PushBack(m1);
			Assert::AreEqual(mDatum.Size(), 1u), L"Size does not reflect number of elements pushed";

			mDatum.PushBack(m2);
			Assert::AreEqual(mDatum.Size(), 2u, L"Size does not reflect number of elements pushed");

			mDatum.SetSize(10);
			Assert::AreEqual(mDatum.Size(), 10u, L"Size not equal after calling SetSize");

			mDatum.SetSize(1);
			Assert::AreEqual(mDatum.Size(), 1u, L"SetSize should reduce current Size");
		}

		TEST_METHOD(TestSize_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			Assert::AreEqual(sDatum.Size(), 0u, L"Size not zero on empty Datum");

			sDatum.PushBack(s1);
			Assert::AreEqual(sDatum.Size(), 1u), L"Size does not reflect number of elements pushed";

			sDatum.PushBack(s2);
			Assert::AreEqual(sDatum.Size(), 2u, L"Size does not reflect number of elements pushed");

			sDatum.SetSize(10);
			Assert::AreEqual(sDatum.Size(), 10u, L"Size not equal after calling SetSize");

			sDatum.SetSize(1);
			Assert::AreEqual(sDatum.Size(), 1u, L"SetSize should reduce current Size");
		}

		TEST_METHOD(TestSize_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			Assert::AreEqual(rDatum.Size(), 0u, L"Size not zero on empty Datum");

			rDatum.PushBack(r1);
			Assert::AreEqual(rDatum.Size(), 1u), L"Size does not reflect number of elements pushed";

			rDatum.PushBack(r2);
			Assert::AreEqual(rDatum.Size(), 2u, L"Size does not reflect number of elements pushed");

			rDatum.SetSize(10);
			Assert::AreEqual(rDatum.Size(), 10u, L"Size not equal after calling SetSize");

			rDatum.SetSize(1);
			Assert::AreEqual(rDatum.Size(), 1u, L"SetSize should reduce current Size");
		}

		TEST_METHOD(TestReserve_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			iDatum.Reserve(10);
			Assert::AreEqual(0u, iDatum.Size());
			Assert::AreEqual(10u, iDatum.Capacity());

			iDatum.SetSize(10);
			Assert::AreEqual(10u, iDatum.Size());
			Assert::AreEqual(10u, iDatum.Capacity());

			iDatum.Reserve(10);
			Assert::AreEqual(10u, iDatum.Size());
			Assert::AreEqual(10u, iDatum.Capacity());
		}

		TEST_METHOD(TestReserve_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			fDatum.Reserve(10);
			Assert::AreEqual(fDatum.Size(), 0u);
			Assert::AreEqual(fDatum.Capacity(), 10u);

			fDatum.SetSize(10);
			Assert::AreEqual(fDatum.Size(), 10u);
			Assert::AreEqual(fDatum.Capacity(), 10u);

			fDatum.Reserve(10);
			Assert::AreEqual(fDatum.Size(), 10u);
			Assert::AreEqual(fDatum.Capacity(), 10u);
		}

		TEST_METHOD(TestReserve_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			vDatum.Reserve(10);
			Assert::AreEqual(vDatum.Size(), 0u);
			Assert::AreEqual(vDatum.Capacity(), 10u);

			vDatum.SetSize(10);
			Assert::AreEqual(vDatum.Size(), 10u);
			Assert::AreEqual(vDatum.Capacity(), 10u);

			vDatum.Reserve(10);
			Assert::AreEqual(vDatum.Size(), 10u);
			Assert::AreEqual(vDatum.Capacity(), 10u);
		}

		TEST_METHOD(TestReserve_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			mDatum.Reserve(10);
			Assert::AreEqual(mDatum.Size(), 0u);
			Assert::AreEqual(mDatum.Capacity(), 10u);

			mDatum.SetSize(10);
			Assert::AreEqual(mDatum.Size(), 10u);
			Assert::AreEqual(mDatum.Capacity(), 10u);

			mDatum.Reserve(10);
			Assert::AreEqual(mDatum.Size(), 10u);
			Assert::AreEqual(mDatum.Capacity(), 10u);
		}

		TEST_METHOD(TestReserve_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			sDatum.Reserve(10);
			Assert::AreEqual(sDatum.Size(), 0u);
			Assert::AreEqual(sDatum.Capacity(), 10u);

			sDatum.SetSize(10);
			Assert::AreEqual(sDatum.Size(), 10u);
			Assert::AreEqual(sDatum.Capacity(), 10u);

			sDatum.Reserve(10);
			Assert::AreEqual(sDatum.Size(), 10u);
			Assert::AreEqual(sDatum.Capacity(), 10u);
		}

		TEST_METHOD(TestReserve_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			rDatum.Reserve(10);
			Assert::AreEqual(rDatum.Size(), 0u);
			Assert::AreEqual(rDatum.Capacity(), 10u);

			rDatum.SetSize(10);
			Assert::AreEqual(rDatum.Size(), 10u);
			Assert::AreEqual(rDatum.Capacity(), 10u);

			rDatum.Reserve(10);
			Assert::AreEqual(rDatum.Size(), 10u);
			Assert::AreEqual(rDatum.Capacity(), 10u);
		}

		TEST_METHOD(TestClear_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			iDatum.SetSize(10);
			iDatum.Clear();
			Assert::AreEqual(10u, iDatum.Capacity());
			Assert::AreEqual(0u, iDatum.Size());

			iDatum = i1;
			iDatum.Clear();
			Assert::AreEqual(1u, iDatum.Capacity());
			Assert::AreEqual(0u, iDatum.Size());

			iDatum.Clear();
			Assert::AreEqual(1u, iDatum.Capacity());
			Assert::AreEqual(0u, iDatum.Size());
		}

		TEST_METHOD(TestClear_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			fDatum.SetSize(10);
			fDatum.Clear();
			Assert::AreEqual(10u, fDatum.Capacity());
			Assert::AreEqual(0u, fDatum.Size());

			fDatum = f1;
			fDatum.Clear();
			Assert::AreEqual(1u, fDatum.Capacity());
			Assert::AreEqual(0u, fDatum.Size());

			fDatum.Clear();
			Assert::AreEqual(1u, fDatum.Capacity());
			Assert::AreEqual(0u, fDatum.Size());
		}

		TEST_METHOD(TestClear_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			vDatum.SetSize(10);
			vDatum.Clear();
			Assert::AreEqual(10u, vDatum.Capacity());
			Assert::AreEqual(0u, vDatum.Size());

			vDatum = v1;
			vDatum.Clear();
			Assert::AreEqual(1u, vDatum.Capacity());
			Assert::AreEqual(0u, vDatum.Size());

			vDatum.Clear();
			Assert::AreEqual(1u, vDatum.Capacity());
			Assert::AreEqual(0u, vDatum.Size());
		}

		TEST_METHOD(TestClear_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			mDatum.SetSize(10);
			mDatum.Clear();
			Assert::AreEqual(10u, mDatum.Capacity());
			Assert::AreEqual(0u, mDatum.Size());

			mDatum = m1;
			mDatum.Clear();
			Assert::AreEqual(1u, mDatum.Capacity());
			Assert::AreEqual(0u, mDatum.Size());

			mDatum.Clear();
			Assert::AreEqual(1u, mDatum.Capacity());
			Assert::AreEqual(0u, mDatum.Size());
		}

		TEST_METHOD(TestClear_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			sDatum.SetSize(10);
			sDatum.Clear();
			Assert::AreEqual(10u, sDatum.Capacity());
			Assert::AreEqual(0u, sDatum.Size());

			sDatum = s1;
			sDatum.Clear();
			Assert::AreEqual(1u, sDatum.Capacity());
			Assert::AreEqual(0u, sDatum.Size());

			sDatum.Clear();
			Assert::AreEqual(1u, sDatum.Capacity());
			Assert::AreEqual(0u, sDatum.Size());
		}

		TEST_METHOD(TestClear_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			rDatum.SetSize(10);
			rDatum.Clear();
			Assert::AreEqual(10u, rDatum.Capacity());
			Assert::AreEqual(0u, rDatum.Size());

			rDatum = r1;
			rDatum.Clear();
			Assert::AreEqual(1u, rDatum.Capacity());
			Assert::AreEqual(0u, rDatum.Size());

			rDatum.Clear();
			Assert::AreEqual(1u, rDatum.Capacity());
			Assert::AreEqual(0u, rDatum.Size());
		}

		TEST_METHOD(TestSetStorage_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			Library::Datum iTemp;
			std::int32_t* iStorage = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * 10));
			iTemp.SetStorage(iStorage, 10);
			Library::Datum iTemp2;
			iTemp2.SetStorage(iStorage, 10);
			Assert::IsTrue(iTemp == iTemp2);

			free(iStorage);
		}
		TEST_METHOD(TestSetStorage_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			Library::Datum fTemp;
			float* fStorage = static_cast<float*>(malloc(sizeof(float) * 10));
			fTemp.SetStorage(fStorage, 10);
			Library::Datum fTemp2;
			fTemp2.SetStorage(fStorage, 10);
			Assert::IsTrue(fTemp == fTemp2);

			free(fStorage);
		}
		TEST_METHOD(TestSetStorage_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			Library::Datum vTemp;
			glm::vec4* vStorage = static_cast<glm::vec4*>(malloc(sizeof(glm::vec4) * 10));
			vTemp.SetStorage(vStorage, 10);
			Library::Datum vTemp2;
			vTemp2.SetStorage(vStorage, 10);
			Assert::IsTrue(vTemp == vTemp2);

			free(vStorage);
		}
		TEST_METHOD(TestSetStorage_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			Library::Datum mTemp;
			glm::mat4* mStorage = static_cast<glm::mat4*>(malloc(sizeof(glm::mat4) * 10));
			mTemp.SetStorage(mStorage, 10);
			Library::Datum mTemp2;
			mTemp2.SetStorage(mStorage, 10);
			Assert::IsTrue(mTemp == mTemp2);

			free(mStorage);
		}
		TEST_METHOD(TestSetStorage_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			Library::Datum sTemp;
			std::string sStorage[10];
			sTemp.SetStorage(sStorage, 10);
			Library::Datum sTemp2;
			sTemp2.SetStorage(sStorage, 10);
			Assert::IsTrue(sTemp == sTemp2);
		}
		TEST_METHOD(TestSetStorage_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			Library::Datum rTemp;
			Library::RTTI** rStorage = static_cast<Library::RTTI**>(malloc(sizeof(Library::RTTI*) * 10));
			rTemp.SetStorage(rStorage, 10);
			Library::Datum rTemp2;
			rTemp2.SetStorage(rStorage, 10);
			Assert::IsTrue(rTemp == rTemp2);

			free(rStorage);
		}

		TEST_METHOD(TestSet_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			Assert::ExpectException<std::exception>([&] {iDatum.Set(i1, 10); });
			Assert::ExpectException<std::exception>([&] {iDatum.Set(f1, 0); });

			iDatum.Reserve(10);
			iDatum.Set(i1, 0);
			Assert::IsTrue(iDatum == i1);

			iDatum.PushBack(i2);
			iDatum.Set(i3, 0);
			Assert::IsTrue(iDatum.Get<std::int32_t>(0) == i3);
			Assert::IsTrue(iDatum.Get<std::int32_t>(1) == i2);

			iDatum.Set(i1, 1);
			Assert::IsTrue(iDatum.Get<std::int32_t>(1) == i1);
			Assert::ExpectException<std::exception>([&] { iDatum.Set(i1, 10); });
		}

		TEST_METHOD(TestSet_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			Assert::ExpectException<std::exception>([&] {fDatum.Set(f1, 10); });
			Assert::ExpectException<std::exception>([&] {fDatum.Set(i1, 0); });

			fDatum.Reserve(10);
			fDatum.Set(f1, 0);
			Assert::IsTrue(fDatum == f1);

			fDatum.PushBack(f2);
			fDatum.Set(f3, 0);
			Assert::IsTrue(fDatum.Get<float>(0) == f3);
			Assert::IsTrue(fDatum.Get<float>(1) == f2);

			fDatum.Set(f1, 1);
			Assert::IsTrue(fDatum.Get<float>(1) == f1);
			Assert::ExpectException<std::exception>([&] { fDatum.Set(f1, 10); });
		}

		TEST_METHOD(TestSet_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			Assert::ExpectException<std::exception>([&] {vDatum.Set(v1, 10); });
			Assert::ExpectException<std::exception>([&] {vDatum.Set(i1, 0); });

			vDatum.Reserve(10);
			vDatum.Set(v1, 0);
			Assert::IsTrue(vDatum == v1);

			vDatum.PushBack(v2);
			vDatum.Set(v3, 0);
			Assert::IsTrue(vDatum.Get<glm::vec4>(0) == v3);
			Assert::IsTrue(vDatum.Get<glm::vec4>(1) == v2);

			vDatum.Set(v1, 1);
			Assert::IsTrue(vDatum.Get<glm::vec4>(1) == v1);
			Assert::ExpectException<std::exception>([&] { vDatum.Set(v1, 10); });
		}

		TEST_METHOD(TestSet_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			Assert::ExpectException<std::exception>([&] {mDatum.Set(m1, 10); });
			Assert::ExpectException<std::exception>([&] {mDatum.Set(i1, 0); });

			mDatum.Reserve(10);
			mDatum.Set(m1, 0);
			Assert::IsTrue(mDatum == m1);

			mDatum.PushBack(m2);
			mDatum.Set(m3, 0);
			Assert::IsTrue(mDatum.Get<glm::mat4>(0) == m3);
			Assert::IsTrue(mDatum.Get<glm::mat4>(1) == m2);

			mDatum.Set(m1, 1);
			Assert::IsTrue(mDatum.Get<glm::mat4>(1) == m1);
			Assert::ExpectException<std::exception>([&] { mDatum.Set(m1, 10); });
		}

		TEST_METHOD(TestSet_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			Assert::ExpectException<std::exception>([&] {sDatum.Set(s1, 10); });
			Assert::ExpectException<std::exception>([&] {sDatum.Set(i1, 0); });

			sDatum.Reserve(10);
			sDatum.Set(s1, 0);
			Assert::IsTrue(sDatum == s1);

			sDatum.PushBack(s2);
			sDatum.Set(s3, 0);
			Assert::IsTrue(sDatum.Get<std::string>(0) == s3);
			Assert::IsTrue(sDatum.Get<std::string>(1) == s2);

			sDatum.Set(s1, 1);
			Assert::IsTrue(sDatum.Get<std::string>(1) == s1);
			Assert::ExpectException<std::exception>([&] { sDatum.Set(s1, 10); });
		}

		TEST_METHOD(TestSet_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			Assert::ExpectException<std::exception>([&] {rDatum.Set(r1, 10); });
			Assert::ExpectException<std::exception>([&] {rDatum.Set(i1, 0); });

			rDatum.Reserve(10);
			rDatum.Set(r1, 0);
			Assert::IsTrue(rDatum == r1);

			rDatum.PushBack(r2);
			rDatum.Set(r3, 0);
			Assert::IsTrue(rDatum.Get<Library::RTTI*>(0) == r3);
			Assert::IsTrue(rDatum.Get<Library::RTTI*>(1) == r2);

			rDatum.Set(r1, 1);
			Assert::IsTrue(rDatum.Get<Library::RTTI*>(1) == r1);
			Assert::ExpectException<std::exception>([&] { rDatum.Set(r1, 10); });
		}

		TEST_METHOD(TestSetFromString_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			iDatum.SetFromString("1");
			Assert::IsTrue(iDatum == 1);
			Assert::IsFalse(iDatum == 2);

			iDatum.SetFromString("2", 1);
			Assert::IsTrue(iDatum.Get<std::int32_t>(0) == 1);
			Assert::IsTrue(iDatum.Get<std::int32_t>(1) == 2);

			iDatum.SetFromString("3", 1);
			Assert::IsTrue(iDatum.Get<std::int32_t>(0) == 1);
			Assert::IsTrue(iDatum.Get<std::int32_t>(1) == 3);
		}

		TEST_METHOD(TestSetFromString_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			fDatum.SetFromString("1.0f");
			Assert::IsTrue(fDatum == f1);
			Assert::IsFalse(fDatum == f2);

			fDatum.SetFromString("2.0f", 1);
			Assert::IsTrue(fDatum.Get<float>(0) == f1);
			Assert::IsTrue(fDatum.Get<float>(1) == f2);

			fDatum.SetFromString("3.0f", 1);
			Assert::IsTrue(fDatum.Get<float>(0) == f1);
			Assert::IsTrue(fDatum.Get<float>(1) == f3);
		}

		TEST_METHOD(TestSetFromString_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			auto vs1 = "vec4(1.000000, 1.000000, 1.000000, 1.000000)";
			auto vs2 = "vec4(2.000000, 2.000000, 2.000000, 2.000000)";
			auto vs3 = "vec4(3.000000, 3.000000, 3.000000, 3.000000)";

			vDatum.SetFromString(vs1);
			Assert::IsTrue(vDatum == v1);
			Assert::IsFalse(vDatum == v2);

			vDatum.SetFromString(vs2, 1);
			Assert::IsTrue(vDatum.Get<glm::vec4>(0) == v1);
			Assert::IsTrue(vDatum.Get<glm::vec4>(1) == v2);

			vDatum.SetFromString(vs3, 1);
			Assert::IsTrue(vDatum.Get<glm::vec4>(0) == v1);
			Assert::IsTrue(vDatum.Get<glm::vec4>(1) == v3);
		}

		TEST_METHOD(TestSetFromString_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			auto ms1 = "mat4x4((1.000000, 0.000000, 0.000000, 0.000000), (0.000000, 1.000000, 0.000000, 0.000000), (0.000000, 0.000000, 1.000000, 0.000000), (0.000000, 0.000000, 0.000000, 1.000000))";
			auto ms2 = "mat4x4((2.000000, 0.000000, 0.000000, 0.000000), (0.000000, 2.000000, 0.000000, 0.000000), (0.000000, 0.000000, 2.000000, 0.000000), (0.000000, 0.000000, 0.000000, 2.000000))";
			auto ms3 = "mat4x4((3.000000, 0.000000, 0.000000, 0.000000), (0.000000, 3.000000, 0.000000, 0.000000), (0.000000, 0.000000, 3.000000, 0.000000), (0.000000, 0.000000, 0.000000, 3.000000))";

			mDatum.SetFromString(ms1);
			Assert::IsTrue(mDatum == m1);
			Assert::IsFalse(mDatum == m2);

			mDatum.SetFromString(ms2, 1);
			Assert::IsTrue(mDatum.Get<glm::mat4>(0) == m1);
			Assert::IsTrue(mDatum.Get<glm::mat4>(1) == m2);

			mDatum.SetFromString(ms3, 1);
			Assert::IsTrue(mDatum.Get<glm::mat4>(0) == m1);
			Assert::IsTrue(mDatum.Get<glm::mat4>(1) == m3);
		}

		TEST_METHOD(TestSetFromString_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			sDatum.SetFromString(s1);
			Assert::IsTrue(sDatum == s1);
			Assert::IsFalse(sDatum == s2);

			sDatum.SetFromString(s2, 1);
			Assert::IsTrue(sDatum.Get<std::string>(0) == s1);
			Assert::IsTrue(sDatum.Get<std::string>(1) == s2);

			sDatum.SetFromString(s3, 1);
			Assert::IsTrue(sDatum.Get<std::string>(0) == s1);
			Assert::IsTrue(sDatum.Get<std::string>(1) == s3);
		}

		TEST_METHOD(TestSetFromString_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			Assert::ExpectException<std::exception>([&] 
			{ 
				rDatum.SetFromString("Break Me"); 
			}, L"Set from string on pointer Type should throw exception");
		}

		TEST_METHOD(TestToString_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			iDatum = i1;
			Assert::IsTrue("1" == iDatum.ToString(), L"ToString invalid on scalar assignment");
			iDatum = i2;
			Assert::IsTrue("2" == iDatum.ToString(), L"ToString invalid on scalar assignment");
			iDatum = i3;
			Assert::IsTrue("3" == iDatum.ToString(), L"ToString invalid on scalar assignment");

			iDatum.Clear();
			iDatum.PushBack(i1);
			iDatum.PushBack(i2);
			iDatum.PushBack(i3);
			Assert::IsTrue("1" == iDatum.ToString(0), L"ToString invalid with multiple values");
			Assert::IsTrue("2" == iDatum.ToString(1), L"ToString invalid with multiple values");
			Assert::IsTrue("3" == iDatum.ToString(2), L"ToString invalid with multiple values");

			iDatum.Set(i1, 1);
			Assert::IsTrue("1" == iDatum.ToString(1), L"ToString invalid after Set");
		}

		TEST_METHOD(TestToString_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			fDatum = f1;
			Assert::IsTrue("1.000000" == fDatum.ToString(), L"ToString invalid on scalar assignment");
			fDatum = f2;
			Assert::IsTrue("2.000000" == fDatum.ToString(), L"ToString invalid on scalar assignment");
			fDatum = f3;
			Assert::IsTrue("3.000000" == fDatum.ToString(), L"ToString invalid on scalar assignment");

			fDatum.Clear();
			fDatum.PushBack(f1);
			fDatum.PushBack(f2);
			fDatum.PushBack(f3);
			Assert::IsTrue("1.000000" == fDatum.ToString(0), L"ToString invalid with multiple values");
			Assert::IsTrue("2.000000" == fDatum.ToString(1), L"ToString invalid with multiple values");
			Assert::IsTrue("3.000000" == fDatum.ToString(2), L"ToString invalid with multiple values");

			fDatum.Set(f1, 1);
			Assert::IsTrue("1.000000" == fDatum.ToString(1), L"ToString invalid after Set");
		}

		TEST_METHOD(TestToString_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			vDatum = v1;
			auto vs1 = "vec4(1.000000, 1.000000, 1.000000, 1.000000)";
			auto vs2 = "vec4(2.000000, 2.000000, 2.000000, 2.000000)";
			auto vs3 = "vec4(3.000000, 3.000000, 3.000000, 3.000000)";
			Assert::IsTrue(vs1 == vDatum.ToString(), L"ToString invalid on scalar assignment");
			vDatum = v2;
			Assert::IsTrue(vs2 == vDatum.ToString(), L"ToString invalid on scalar assignment");
			vDatum = v3;
			Assert::IsTrue(vs3 == vDatum.ToString(), L"ToString invalid on scalar assignment");

			vDatum.Clear();
			vDatum.PushBack(v1);
			vDatum.PushBack(v2);
			vDatum.PushBack(v3);
			Assert::IsTrue(vs1 == vDatum.ToString(0), L"ToString invalid with multiple values");
			Assert::IsTrue(vs2 == vDatum.ToString(1), L"ToString invalid with multiple values");
			Assert::IsTrue(vs3 == vDatum.ToString(2), L"ToString invalid with multiple values");

			vDatum.Set(v1, 1);
			Assert::IsTrue(vs1 == vDatum.ToString(1), L"ToString invalid after Set");
		}

		TEST_METHOD(TestToString_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			mDatum = m1;
			auto ms1 = "mat4x4((1.000000, 0.000000, 0.000000, 0.000000), (0.000000, 1.000000, 0.000000, 0.000000), (0.000000, 0.000000, 1.000000, 0.000000), (0.000000, 0.000000, 0.000000, 1.000000))";
			auto ms2 = "mat4x4((2.000000, 0.000000, 0.000000, 0.000000), (0.000000, 2.000000, 0.000000, 0.000000), (0.000000, 0.000000, 2.000000, 0.000000), (0.000000, 0.000000, 0.000000, 2.000000))";
			auto ms3 = "mat4x4((3.000000, 0.000000, 0.000000, 0.000000), (0.000000, 3.000000, 0.000000, 0.000000), (0.000000, 0.000000, 3.000000, 0.000000), (0.000000, 0.000000, 0.000000, 3.000000))";
			Assert::IsTrue(ms1 == mDatum.ToString(), L"ToString invalid on scalar assignment");
			mDatum = m2;
			Assert::IsTrue(ms2 == mDatum.ToString(), L"ToString invalid on scalar assignment");
			mDatum = m3;
			Assert::IsTrue(ms3 == mDatum.ToString(), L"ToString invalid on scalar assignment");

			mDatum.Clear();
			mDatum.PushBack(m1);
			mDatum.PushBack(m2);
			mDatum.PushBack(m3);
			Assert::IsTrue(ms1 == mDatum.ToString(0), L"ToString invalid with multiple values");
			Assert::IsTrue(ms2 == mDatum.ToString(1), L"ToString invalid with multiple values");
			Assert::IsTrue(ms3 == mDatum.ToString(2), L"ToString invalid with multiple values");

			mDatum.Set(m1, 1);
			Assert::IsTrue(ms1 == mDatum.ToString(1), L"ToString invalid after Set");
		}

		TEST_METHOD(TestToString_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			sDatum = s1;
			Assert::IsTrue(s1 == sDatum.ToString(), L"ToString invalid on scalar assignment");
			sDatum = s2;
			Assert::IsTrue(s2 == sDatum.ToString(), L"ToString invalid on scalar assignment");
			sDatum = s3;
			Assert::IsTrue(s3 == sDatum.ToString(), L"ToString invalid on scalar assignment");

			sDatum.Clear();
			sDatum.PushBack(s1);
			sDatum.PushBack(s2);
			sDatum.PushBack(s3);
			Assert::IsTrue(s1 == sDatum.ToString(0), L"ToString invalid with multiple values");
			Assert::IsTrue(s2 == sDatum.ToString(1), L"ToString invalid with multiple values");
			Assert::IsTrue(s3 == sDatum.ToString(2), L"ToString invalid with multiple values");

			sDatum.Set(s1, 1);
			Assert::IsTrue(s1 == sDatum.ToString(1), L"ToString invalid after Set");
		}

		TEST_METHOD(TestToString_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			Assert::IsTrue("" == rDatum.ToString(), L"pointer ToString should return an empty string representation");
			Assert::IsTrue("" == rDatum.ToString(0), L"pointer ToString should return an empty string representation");
		}

		TEST_METHOD(TestInvalidStateUsage_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			std::uint32_t size = 10;
			float* fData = static_cast<float*>(malloc(sizeof(float) * size));
			glm::vec4* vData = static_cast<glm::vec4*>(malloc(sizeof(glm::vec4) * size));
			glm::mat4* mData = static_cast<glm::mat4*>(malloc(sizeof(glm::mat4) * size));
			std::string* sData = static_cast<std::string*>(malloc(sizeof(std::string) * size));
			Library::RTTI** rData = static_cast<Library::RTTI**>(malloc(sizeof(Library::RTTI*) * size));

			Assert::ExpectException<std::exception>([&] { iDatum = f1; });
			Assert::ExpectException<std::exception>([&] { iDatum = v1; });
			Assert::ExpectException<std::exception>([&] { iDatum = m1; });
			Assert::ExpectException<std::exception>([&] { iDatum = s1; });
			Assert::ExpectException<std::exception>([&] { iDatum = r1; });

			Assert::ExpectException<std::exception>([&] { iDatum.SetStorage(fData, size); });
			Assert::ExpectException<std::exception>([&] { iDatum.SetStorage(vData, size); });
			Assert::ExpectException<std::exception>([&] { iDatum.SetStorage(mData, size); });
			Assert::ExpectException<std::exception>([&] { iDatum.SetStorage(sData, size); });
			Assert::ExpectException<std::exception>([&] { iDatum.SetStorage(rData, size); });

			free(fData);
			free(vData);
			free(mData);
			free(sData);
			free(rData);
		}
		TEST_METHOD(TestInvalidStateUsage_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);
			
			std::uint32_t size = 10;
			std::int32_t* iData = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * size));
			glm::vec4* vData = static_cast<glm::vec4*>(malloc(sizeof(glm::vec4) * size));
			glm::mat4* mData = static_cast<glm::mat4*>(malloc(sizeof(glm::mat4) * size));
			std::string* sData = static_cast<std::string*>(malloc(sizeof(std::string) * size));
			Library::RTTI** rData = static_cast<Library::RTTI**>(malloc(sizeof(Library::RTTI*) * size));

			Assert::ExpectException<std::exception>([&] { fDatum = i1; });
			Assert::ExpectException<std::exception>([&] { fDatum = v1; });
			Assert::ExpectException<std::exception>([&] { fDatum = m1; });
			Assert::ExpectException<std::exception>([&] { fDatum = s1; });
			Assert::ExpectException<std::exception>([&] { fDatum = r1; });

			Assert::ExpectException<std::exception>([&] { fDatum.SetStorage(iData, size); });
			Assert::ExpectException<std::exception>([&] { fDatum.SetStorage(vData, size); });
			Assert::ExpectException<std::exception>([&] { fDatum.SetStorage(mData, size); });
			Assert::ExpectException<std::exception>([&] { fDatum.SetStorage(sData, size); });
			Assert::ExpectException<std::exception>([&] { fDatum.SetStorage(rData, size); });

			free(iData);
			free(vData);
			free(mData);
			free(sData);
			free(rData);
		}
		TEST_METHOD(TestInvalidStateUsage_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			std::uint32_t size = 10;
			std::int32_t* iData = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * size));
			float* fData = static_cast<float*>(malloc(sizeof(float) * size));
			glm::mat4* mData = static_cast<glm::mat4*>(malloc(sizeof(glm::mat4) * size));
			std::string* sData = static_cast<std::string*>(malloc(sizeof(std::string) * size));
			Library::RTTI** rData = static_cast<Library::RTTI**>(malloc(sizeof(Library::RTTI*) * size));

			Assert::ExpectException<std::exception>([&] { vDatum = i1; });
			Assert::ExpectException<std::exception>([&] { vDatum = f1; });
			Assert::ExpectException<std::exception>([&] { vDatum = m1; });
			Assert::ExpectException<std::exception>([&] { vDatum = s1; });
			Assert::ExpectException<std::exception>([&] { vDatum = r1; });

			Assert::ExpectException<std::exception>([&] { vDatum.SetStorage(iData, size); });
			Assert::ExpectException<std::exception>([&] { vDatum.SetStorage(fData, size); });
			Assert::ExpectException<std::exception>([&] { vDatum.SetStorage(mData, size); });
			Assert::ExpectException<std::exception>([&] { vDatum.SetStorage(sData, size); });
			Assert::ExpectException<std::exception>([&] { vDatum.SetStorage(rData, size); });

			free(iData);
			free(fData);
			free(mData);
			free(sData);
			free(rData);
		}
		TEST_METHOD(TestInvalidStateUsage_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			std::uint32_t size = 10;
			std::int32_t* iData = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * size));
			float* fData = static_cast<float*>(malloc(sizeof(float) * size));
			glm::vec4* vData = static_cast<glm::vec4*>(malloc(sizeof(glm::vec4) * size));
			std::string* sData = static_cast<std::string*>(malloc(sizeof(std::string) * size));
			Library::RTTI** rData = static_cast<Library::RTTI**>(malloc(sizeof(Library::RTTI*) * size));

			Assert::ExpectException<std::exception>([&] { mDatum = i1; });
			Assert::ExpectException<std::exception>([&] { mDatum = f1; });
			Assert::ExpectException<std::exception>([&] { mDatum = v1; });
			Assert::ExpectException<std::exception>([&] { mDatum = s1; });
			Assert::ExpectException<std::exception>([&] { mDatum = r1; });

			Assert::ExpectException<std::exception>([&] { mDatum.SetStorage(iData, size); });
			Assert::ExpectException<std::exception>([&] { mDatum.SetStorage(fData, size); });
			Assert::ExpectException<std::exception>([&] { mDatum.SetStorage(vData, size); });
			Assert::ExpectException<std::exception>([&] { mDatum.SetStorage(sData, size); });
			Assert::ExpectException<std::exception>([&] { mDatum.SetStorage(rData, size); });

			free(iData);
			free(fData);
			free(vData);
			free(sData);
			free(rData);
		}
		TEST_METHOD(TestInvalidStateUsage_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			std::uint32_t size = 10;
			std::int32_t* iData = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * size));
			float* fData = static_cast<float*>(malloc(sizeof(float) * size));
			glm::vec4* vData = static_cast<glm::vec4*>(malloc(sizeof(glm::vec4) * size));
			glm::mat4* mData = static_cast<glm::mat4*>(malloc(sizeof(glm::mat4) * size));
			Library::RTTI** rData = static_cast<Library::RTTI**>(malloc(sizeof(Library::RTTI*) * size));

			Assert::ExpectException<std::exception>([&] { sDatum = i1; });
			Assert::ExpectException<std::exception>([&] { sDatum = f1; });
			Assert::ExpectException<std::exception>([&] { sDatum = v1; });
			Assert::ExpectException<std::exception>([&] { sDatum = m1; });
			Assert::ExpectException<std::exception>([&] { sDatum = r1; });

			Assert::ExpectException<std::exception>([&] { sDatum.SetStorage(iData, size); });
			Assert::ExpectException<std::exception>([&] { sDatum.SetStorage(fData, size); });
			Assert::ExpectException<std::exception>([&] { sDatum.SetStorage(vData, size); });
			Assert::ExpectException<std::exception>([&] { sDatum.SetStorage(mData, size); });
			Assert::ExpectException<std::exception>([&] { sDatum.SetStorage(rData, size); });

			free(iData);
			free(fData);
			free(vData);
			free(mData);
			free(rData);
		}
		TEST_METHOD(TestInvalidStateUsage_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			std::uint32_t size = 10;
			std::int32_t* iData = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * size));
			float* fData = static_cast<float*>(malloc(sizeof(float) * size));
			glm::vec4* vData = static_cast<glm::vec4*>(malloc(sizeof(glm::vec4) * size));
			glm::mat4* mData = static_cast<glm::mat4*>(malloc(sizeof(glm::mat4) * size));
			std::string* sData = static_cast<std::string*>(malloc(sizeof(std::string) * size));

			Assert::ExpectException<std::exception>([&] { rDatum = i1; });
			Assert::ExpectException<std::exception>([&] { rDatum = f1; });
			Assert::ExpectException<std::exception>([&] { rDatum = v1; });
			Assert::ExpectException<std::exception>([&] { rDatum = m1; });
			Assert::ExpectException<std::exception>([&] { rDatum = s1; });

			Assert::ExpectException<std::exception>([&] { rDatum.SetStorage(iData, size); });
			Assert::ExpectException<std::exception>([&] { rDatum.SetStorage(fData, size); });
			Assert::ExpectException<std::exception>([&] { rDatum.SetStorage(vData, size); });
			Assert::ExpectException<std::exception>([&] { rDatum.SetStorage(mData, size); });
			Assert::ExpectException<std::exception>([&] { rDatum.SetStorage(sData, size); });

			free(iData);
			free(fData);
			free(vData);
			free(mData);
			free(sData);
		}

		TEST_METHOD(LeakTest)
		{
			Library::Datum sDatum(Library::DatumType::String);
			sDatum = "Hello world";
			sDatum.SetSize(10);
		}

		static _CrtMemState sStartMemState;
	};

	_CrtMemState DatumTest::sStartMemState;
}