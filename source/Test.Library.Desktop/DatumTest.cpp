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
			Library::Datum oldBusted;
			oldBusted = Library::DatumType::Integer;
			Library::Datum newHotness = oldBusted;
			Assert::IsTrue(oldBusted.type() == newHotness.type(), L"Copied types not equivalent");
			Assert::IsTrue(oldBusted.size() == newHotness.size(), L"Copied sizes not equivalent");
		}

		TEST_METHOD(TestCopyConstructor_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			Library::Datum iDatCopy(Library::DatumType::Integer);
			Assert::IsTrue(iDatCopy.type() == Library::DatumType::Integer);
			Assert::IsTrue(iDatCopy.size() == 0);
			Assert::IsTrue(iDatCopy.capacity() == 0);

			auto iType = iDatCopy.type();
			auto iSize = iDatCopy.size();
			auto iCapacity = iDatCopy.capacity();
			Library::Datum iDatMove(std::move(iDatCopy));
			Assert::IsTrue(iDatMove.type() == iType);
			Assert::IsTrue(iDatMove.size() == iSize);
			Assert::IsTrue(iDatMove.capacity() == iCapacity);
		}

		TEST_METHOD(TestCopyConstructor_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			Library::Datum fDatCopy(Library::DatumType::Float);
			Assert::IsTrue(fDatCopy.type() == Library::DatumType::Float);
			Assert::IsTrue(fDatCopy.size() == 0);
			Assert::IsTrue(fDatCopy.capacity() == 0);

			auto fType = fDatCopy.type();
			auto fSize = fDatCopy.size();
			auto fCapacity = fDatCopy.capacity();
			Library::Datum fDatMove(std::move(fDatCopy));
			Assert::IsTrue(fDatMove.type() == fType);
			Assert::IsTrue(fDatMove.size() == fSize);
			Assert::IsTrue(fDatMove.capacity() == fCapacity);
		}

		TEST_METHOD(TestCopyConstructor_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			Library::Datum vDatCopy(Library::DatumType::Vector);
			Assert::IsTrue(vDatCopy.type() == Library::DatumType::Vector);
			Assert::IsTrue(vDatCopy.size() == 0);
			Assert::IsTrue(vDatCopy.capacity() == 0);

			auto vType = vDatCopy.type();
			auto vSize = vDatCopy.size();
			auto vCapacity = vDatCopy.capacity();
			Library::Datum vDatMove(std::move(vDatCopy));
			Assert::IsTrue(vDatMove.type() == vType);
			Assert::IsTrue(vDatMove.size() == vSize);
			Assert::IsTrue(vDatMove.capacity() == vCapacity);
		}

		TEST_METHOD(TestCopyConstructor_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			Library::Datum mDatCopy(Library::DatumType::Matrix);
			Assert::IsTrue(mDatCopy.type() == Library::DatumType::Matrix);
			Assert::IsTrue(mDatCopy.size() == 0);
			Assert::IsTrue(mDatCopy.capacity() == 0);

			auto mType = mDatCopy.type();
			auto mSize = mDatCopy.size();
			auto mCapacity = mDatCopy.capacity();
			Library::Datum mDatMove(std::move(mDatCopy));
			Assert::IsTrue(mDatMove.type() == mType);
			Assert::IsTrue(mDatMove.size() == mSize);
			Assert::IsTrue(mDatMove.capacity() == mCapacity);
		}

		TEST_METHOD(TestCopyConstructor_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			Library::Datum sDatCopy(Library::DatumType::String);
			Assert::IsTrue(sDatCopy.type() == Library::DatumType::String);
			Assert::IsTrue(sDatCopy.size() == 0);
			Assert::IsTrue(sDatCopy.capacity() == 0);

			auto sType = sDatCopy.type();
			auto sSize = sDatCopy.size();
			auto sCapacity = sDatCopy.capacity();
			Library::Datum sDatMove(std::move(sDatCopy));
			Assert::IsTrue(sDatMove.type() == sType);
			Assert::IsTrue(sDatMove.size() == sSize);
			Assert::IsTrue(sDatMove.capacity() == sCapacity);
		}

		TEST_METHOD(TestCopyConstructor_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			Library::Datum rDatCopy(Library::DatumType::Pointer);
			Assert::IsTrue(rDatCopy.type() == Library::DatumType::Pointer);
			Assert::IsTrue(rDatCopy.size() == 0);
			Assert::IsTrue(rDatCopy.capacity() == 0);
			//			Assert::AreEqual(static_cast<std::uint32_t>(r3->TypeIdInstance()), 0u);

			auto rType = rDatCopy.type();
			auto rSize = rDatCopy.size();
			auto rCapacity = rDatCopy.capacity();
			Library::Datum rDatMove(std::move(rDatCopy));
			Assert::IsTrue(rDatMove.type() == rType);
			Assert::IsTrue(rDatMove.size() == rSize);
			Assert::IsTrue(rDatMove.capacity() == rCapacity);
		}

		TEST_METHOD(TestSetType_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			Library::Datum iDatumTemp;
			Assert::IsTrue(iDatumTemp.type() == Library::DatumType::Unknown, L"Invalid Datum Type");

			iDatumTemp = Library::DatumType::Integer;
			Assert::IsTrue(iDatumTemp.type() == Library::DatumType::Integer, L"Invalid Datum Type");

			Assert::ExpectException<std::exception>([&] { iDatumTemp.setType(Library::DatumType::Unknown); },
				L"No exception thrown when reassigning type");
		}

		TEST_METHOD(TestSetType_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			Library::Datum fDatumTemp;
			Assert::IsTrue(fDatumTemp.type() == Library::DatumType::Unknown, L"Invalid Datum Type");

			fDatumTemp = Library::DatumType::Float;
			Assert::IsTrue(fDatumTemp.type() == Library::DatumType::Float, L"Invalid Datum Type");

			Assert::ExpectException<std::exception>([&] { fDatumTemp.setType(Library::DatumType::Unknown); },
				L"No exception thrown when reassigning type");
		}

		TEST_METHOD(TestSetType_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			Library::Datum vDatumTemp;
			Assert::IsTrue(vDatumTemp.type() == Library::DatumType::Unknown, L"Invalid Datum Type");

			vDatumTemp = Library::DatumType::Vector;
			Assert::IsTrue(vDatumTemp.type() == Library::DatumType::Vector, L"Invalid Datum Type");

			Assert::ExpectException<std::exception>([&] { vDatumTemp.setType(Library::DatumType::Unknown); },
				L"No exception thrown when reassigning type");
		}

		TEST_METHOD(TestSetType_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			Library::Datum mDatumTemp;
			Assert::IsTrue(mDatumTemp.type() == Library::DatumType::Unknown, L"Invalid Datum Type");

			mDatumTemp = Library::DatumType::Matrix;
			Assert::IsTrue(mDatumTemp.type() == Library::DatumType::Matrix, L"Invalid Datum Type");

			Assert::ExpectException<std::exception>([&] { mDatumTemp.setType(Library::DatumType::Unknown); },
				L"No exception thrown when reassigning type");
		}

		TEST_METHOD(TestSetType_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			Library::Datum sDatumTemp;
			Assert::IsTrue(sDatumTemp.type() == Library::DatumType::Unknown, L"Invalid Datum Type");

			sDatumTemp = Library::DatumType::String;
			Assert::IsTrue(sDatumTemp.type() == Library::DatumType::String, L"Invalid Datum Type");

			Assert::ExpectException<std::exception>([&] { sDatumTemp.setType(Library::DatumType::Unknown); },
				L"No exception thrown when reassigning type");
		}

		TEST_METHOD(TestSetType_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			Library::Datum rDatumTemp;
			Assert::IsTrue(rDatumTemp.type() == Library::DatumType::Unknown, L"Invalid Datum Type");

			rDatumTemp = Library::DatumType::Pointer;
			Assert::IsTrue(rDatumTemp.type() == Library::DatumType::Pointer, L"Invalid Datum Type");

			Assert::ExpectException<std::exception>([&] { rDatumTemp.setType(Library::DatumType::Unknown); },
				L"No exception thrown when reassigning type");
		}

		TEST_METHOD(TestSetType_Unknown)
		{
			Library::Datum uDatumTemp;
			Assert::IsTrue(uDatumTemp.type() == Library::DatumType::Unknown, L"Invalid Datum Type");
		}

		TEST_METHOD(TestAssignmentOperator_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			iDatum = i1;
			Assert::IsTrue(iDatum.get<std::int32_t>(0) == i1);
			Assert::ExpectException<std::exception>([&] { iDatum.get<float>(0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<glm::vec4>(0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<glm::mat4>(0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<std::string>(0); });
			Assert::ExpectException<std::exception>([&] { iDatum.get<Library::RTTI*>(0); });

			std::uint32_t isize = 10;
			std::int32_t* iData = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * isize));
			Library::Datum iDatumCopy1;
			iDatumCopy1.setStorage(iData, isize);
			Library::Datum iDatumCopy2 = iDatumCopy1;
			Assert::IsTrue(iDatumCopy1.type() == iDatumCopy2.type());
			Assert::IsTrue(iDatumCopy1.size() == iDatumCopy2.size());
			Assert::IsTrue(iDatumCopy1.capacity() == iDatumCopy2.capacity());
			free(iData);

			// Move semantic assignment
			iDatum.pushBack(i1);
			iDatum.pushBack(i2);
			iDatum.pushBack(i2);
			Library::Datum iDatumCopy;
			iDatumCopy = iDatum;
			Assert::IsTrue(iDatum == iDatumCopy);

			auto iType = iDatumCopy.type();
			auto iSize = iDatumCopy.size();
			auto iCapa = iDatumCopy.capacity();
			Library::Datum iDatumMoveCopy = std::move(iDatumCopy);
			Assert::IsTrue(iDatumMoveCopy.type() == iType);
			Assert::IsTrue(iDatumMoveCopy.size() == iSize);
			Assert::IsTrue(iDatumMoveCopy.capacity() == iCapa);

			iType = iDatumCopy1.type();
			iSize = iDatumCopy1.size();
			iCapa = iDatumCopy1.capacity();
			Library::Datum iDatumCopy3 = std::move(iDatumCopy1);
			Assert::IsTrue(iDatumCopy3.type() == iType);
			Assert::IsTrue(iDatumCopy3.size() == iSize);
			Assert::IsTrue(iDatumCopy3.capacity() == iCapa);
		}

		TEST_METHOD(TestAssignmentOperator_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			fDatum = f1;
			Assert::IsTrue(fDatum.get<float>(0) == f1);
			Assert::ExpectException<std::exception>([&] { fDatum.get<std::int32_t>(0); });
			Assert::ExpectException<std::exception>([&] { fDatum.get<glm::vec4>(0); });
			Assert::ExpectException<std::exception>([&] { fDatum.get<glm::mat4>(0); });
			Assert::ExpectException<std::exception>([&] { fDatum.get<std::string>(0); });
			Assert::ExpectException<std::exception>([&] { fDatum.get<Library::RTTI*>(0); });

			std::uint32_t fsize = 10;
			float* fData = static_cast<float*>(malloc(sizeof(float) * fsize));
			Library::Datum fDatumCopy1;
			fDatumCopy1.setStorage(fData, fsize);
			Library::Datum fDatumCopy2 = fDatumCopy1;
			Assert::IsTrue(fDatumCopy1.type() == fDatumCopy2.type());
			Assert::IsTrue(fDatumCopy1.size() == fDatumCopy2.size());
			Assert::IsTrue(fDatumCopy1.capacity() == fDatumCopy2.capacity());
			free(fData);

			// Move semantic assignment
			fDatum.pushBack(f1);
			fDatum.pushBack(f2);
			fDatum.pushBack(f2);
			Library::Datum fDatumCopy;
			fDatumCopy = fDatum;
			Assert::IsTrue(fDatum == fDatumCopy);

			auto fType = fDatumCopy.type();
			auto fSize = fDatumCopy.size();
			auto fCapa = fDatumCopy.capacity();
			Library::Datum fDatumMoveCopy = std::move(fDatumCopy);
			Assert::IsTrue(fDatumMoveCopy.type() == fType);
			Assert::IsTrue(fDatumMoveCopy.size() == fSize);
			Assert::IsTrue(fDatumMoveCopy.capacity() == fCapa);

			fType = fDatumCopy1.type();
			fSize = fDatumCopy1.size();
			fCapa = fDatumCopy1.capacity();
			Library::Datum fDatumCopy3 = std::move(fDatumCopy1);
			Assert::IsTrue(fDatumCopy3.type() == fType);
			Assert::IsTrue(fDatumCopy3.size() == fSize);
			Assert::IsTrue(fDatumCopy3.capacity() == fCapa);
		}

		TEST_METHOD(TestAssignmentOperator_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			vDatum = v1;
			Assert::IsTrue(vDatum.get<glm::vec4>(0) == v1);
			Assert::ExpectException<std::exception>([&] { vDatum.get<std::int32_t>(0); });
			Assert::ExpectException<std::exception>([&] { vDatum.get<float>(0); });
			Assert::ExpectException<std::exception>([&] { vDatum.get<glm::mat4>(0); });
			Assert::ExpectException<std::exception>([&] { vDatum.get<std::string>(0); });
			Assert::ExpectException<std::exception>([&] { vDatum.get<Library::RTTI*>(0); });

			std::uint32_t vsize = 10;
			glm::vec4* vData = static_cast<glm::vec4*>(malloc(sizeof(glm::vec4) * vsize));
			Library::Datum vDatumCopy1;
			vDatumCopy1.setStorage(vData, vsize);
			Library::Datum vDatumCopy2 = vDatumCopy1;
			Assert::IsTrue(vDatumCopy1.type() == vDatumCopy2.type());
			Assert::IsTrue(vDatumCopy1.size() == vDatumCopy2.size());
			Assert::IsTrue(vDatumCopy1.capacity() == vDatumCopy2.capacity());
			free(vData);

			// Move semantic assignment
			vDatum.pushBack(v1);
			vDatum.pushBack(v2);
			vDatum.pushBack(v2);
			Library::Datum vDatumCopy;
			vDatumCopy = vDatum;
			Assert::IsTrue(vDatum == vDatumCopy);

			auto vType = vDatumCopy.type();
			auto vSize = vDatumCopy.size();
			auto vCapa = vDatumCopy.capacity();
			Library::Datum vDatumMoveCopy = std::move(vDatumCopy);
			Assert::IsTrue(vDatumMoveCopy.type() == vType);
			Assert::IsTrue(vDatumMoveCopy.size() == vSize);
			Assert::IsTrue(vDatumMoveCopy.capacity() == vCapa);

			vType = vDatumCopy1.type();
			vSize = vDatumCopy1.size();
			vCapa = vDatumCopy1.capacity();
			Library::Datum vDatumCopy3 = std::move(vDatumCopy1);
			Assert::IsTrue(vDatumCopy3.type() == vType);
			Assert::IsTrue(vDatumCopy3.size() == vSize);
			Assert::IsTrue(vDatumCopy3.capacity() == vCapa);
		}

		TEST_METHOD(TestAssignmentOperator_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			mDatum = m1;
			Assert::IsTrue(mDatum.get<glm::mat4>(0) == m1);
			Assert::ExpectException<std::exception>([&] { mDatum.get<std::int32_t>(0); });
			Assert::ExpectException<std::exception>([&] { mDatum.get<float>(0); });
			Assert::ExpectException<std::exception>([&] { mDatum.get<glm::vec4>(0); });
			Assert::ExpectException<std::exception>([&] { mDatum.get<std::string>(0); });
			Assert::ExpectException<std::exception>([&] { mDatum.get<Library::RTTI*>(0); });

			std::uint32_t msize = 10;
			glm::mat4* mData = static_cast<glm::mat4*>(malloc(sizeof(glm::mat4) * msize));
			Library::Datum mDatumCopy1;
			mDatumCopy1.setStorage(mData, msize);
			Library::Datum mDatumCopy2 = mDatumCopy1;
			Assert::IsTrue(mDatumCopy1.type() == mDatumCopy2.type());
			Assert::IsTrue(mDatumCopy1.size() == mDatumCopy2.size());
			Assert::IsTrue(mDatumCopy1.capacity() == mDatumCopy2.capacity());
			free(mData);

			// Move semantic assignment
			mDatum.pushBack(m1);
			mDatum.pushBack(m2);
			mDatum.pushBack(m2);
			Library::Datum mDatumCopy;
			mDatumCopy = mDatum;
			Assert::IsTrue(mDatum == mDatumCopy);

			auto mType = mDatumCopy.type();
			auto mSize = mDatumCopy.size();
			auto mCapa = mDatumCopy.capacity();
			Library::Datum mDatumMoveCopy = std::move(mDatumCopy);
			Assert::IsTrue(mDatumMoveCopy.type() == mType);
			Assert::IsTrue(mDatumMoveCopy.size() == mSize);
			Assert::IsTrue(mDatumMoveCopy.capacity() == mCapa);

			mType = mDatumCopy1.type();
			mSize = mDatumCopy1.size();
			mCapa = mDatumCopy1.capacity();
			Library::Datum mDatumCopy3 = std::move(mDatumCopy1);
			Assert::IsTrue(mDatumCopy3.type() == mType);
			Assert::IsTrue(mDatumCopy3.size() == mSize);
			Assert::IsTrue(mDatumCopy3.capacity() == mCapa);
		}

		TEST_METHOD(TestAssignmentOperator_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			// String
			sDatum = s1;
			Assert::IsTrue(sDatum.get<std::string>(0) == s1);
			Assert::ExpectException<std::exception>([&] { sDatum.get<std::int32_t>(0); });
			Assert::ExpectException<std::exception>([&] { sDatum.get<float>(0); });
			Assert::ExpectException<std::exception>([&] { sDatum.get<glm::vec4>(0); });
			Assert::ExpectException<std::exception>([&] { sDatum.get<glm::mat4>(0); });
			Assert::ExpectException<std::exception>([&] { sDatum.get<Library::RTTI*>(0); });

			std::uint32_t ssize = 10;
			std::string* sData = static_cast<std::string*>(malloc(sizeof(std::string) * ssize));
			Library::Datum sDatumCopy1;
			sDatumCopy1.setStorage(sData, ssize);
			Library::Datum sDatumCopy2 = sDatumCopy1;
			Assert::IsTrue(sDatumCopy1.type() == sDatumCopy2.type());
			Assert::IsTrue(sDatumCopy1.size() == sDatumCopy2.size());
			Assert::IsTrue(sDatumCopy1.capacity() == sDatumCopy2.capacity());
			free(sData);

			// Move semantic assignment
			sDatum.pushBack(s1);
			sDatum.pushBack(s2);
			sDatum.pushBack(s2);
			Library::Datum sDatumCopy;
			sDatumCopy = sDatum;
			Assert::IsTrue(sDatum == sDatumCopy);

			auto sType = sDatumCopy.type();
			auto sSize = sDatumCopy.size();
			auto sCapa = sDatumCopy.capacity();
			Library::Datum sDatumMoveCopy = std::move(sDatumCopy);
			Assert::IsTrue(sDatumMoveCopy.type() == sType);
			Assert::IsTrue(sDatumMoveCopy.size() == sSize);
			Assert::IsTrue(sDatumMoveCopy.capacity() == sCapa);

			sType = sDatumCopy1.type();
			sSize = sDatumCopy1.size();
			sCapa = sDatumCopy1.capacity();
			Library::Datum sDatumCopy3 = std::move(sDatumCopy1);
			Assert::IsTrue(sDatumCopy3.type() == sType);
			Assert::IsTrue(sDatumCopy3.size() == sSize);
			Assert::IsTrue(sDatumCopy3.capacity() == sCapa);
		}
		TEST_METHOD(TestAssignmentOperator_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			// Pointer
			//			rDatum = r1;
			//			Assert::IsTrue(rDatum.get<Library::RTTI*>(0) == r1);
			Assert::ExpectException<std::exception>([&] { rDatum.get<std::int32_t>(0); });
			Assert::ExpectException<std::exception>([&] { rDatum.get<float>(0); });
			Assert::ExpectException<std::exception>([&] { rDatum.get<glm::vec4>(0); });
			Assert::ExpectException<std::exception>([&] { rDatum.get<glm::mat4>(0); });
			Assert::ExpectException<std::exception>([&] { rDatum.get<std::string>(0); });

			std::uint32_t rsize = 10;
			Library::RTTI** rData = static_cast<Library::RTTI**>(malloc(sizeof(Library::RTTI*) * rsize));
			Library::Datum rDatumCopy1;
			rDatumCopy1.setStorage(rData, rsize);
			Library::Datum rDatumCopy2 = rDatumCopy1;
			Assert::IsTrue(rDatumCopy1.type() == rDatumCopy2.type());
			Assert::IsTrue(rDatumCopy1.size() == rDatumCopy2.size());
			Assert::IsTrue(rDatumCopy1.capacity() == rDatumCopy2.capacity());
			free(rData);

			// Move semantic assignment
			//			rDatum.pushBack(r1);
			//			rDatum.pushBack(r2);
			//			rDatum.pushBack(r2);
			Library::Datum rDatumCopy;
			rDatumCopy = rDatum;
			Assert::IsTrue(rDatum == rDatumCopy);

			auto rType = rDatumCopy.type();
			auto rSize = rDatumCopy.size();
			auto rCapa = rDatumCopy.capacity();
			Library::Datum rDatumMoveCopy = std::move(rDatumCopy);
			Assert::IsTrue(rDatumMoveCopy.type() == rType);
			Assert::IsTrue(rDatumMoveCopy.size() == rSize);
			Assert::IsTrue(rDatumMoveCopy.capacity() == rCapa);

			rType = rDatumCopy1.type();
			rSize = rDatumCopy1.size();
			rCapa = rDatumCopy1.capacity();
			Library::Datum rDatumCopy3 = std::move(rDatumCopy1);
			Assert::IsTrue(rDatumCopy3.type() == rType);
			Assert::IsTrue(rDatumCopy3.size() == rSize);
			Assert::IsTrue(rDatumCopy3.capacity() == rCapa);
		}

		TEST_METHOD(TestEqualityOperator_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);
			
			iDatum.pushBack(i1);
			Assert::IsTrue(iDatum == i1, L"Value not equivalent to value assigned");
			Assert::IsFalse(iDatum == i2, L"value equivalent to incorrect scalar value");
			Assert::IsFalse(iDatum == i3, L"value equivalent to incorrect scalar value");

			iDatum.pushBack(i2);
			Assert::IsFalse(iDatum == i1, L"operator!= should always return true when size > 1");
			Assert::IsFalse(iDatum == i2, L"operator!= should always return true when size > 1");
			Assert::IsFalse(iDatum == i3, L"operator!= should always return true when size > 1");

			Assert::IsTrue(iDatum == Library::DatumType::Integer);
			Assert::IsFalse(iDatum == Library::DatumType::Float);
			Assert::IsFalse(iDatum == Library::DatumType::Vector);
			Assert::IsFalse(iDatum == Library::DatumType::Matrix);
			Assert::IsFalse(iDatum == Library::DatumType::String);
			Assert::IsFalse(iDatum == Library::DatumType::Pointer);

			Library::Datum iDatumOther(Library::DatumType::Integer);
			iDatumOther.pushBack(i1);
			iDatumOther.pushBack(i1);
			Assert::IsFalse(iDatum == iDatumOther);
		}

		TEST_METHOD(TestEqualityOperator_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);
			
			fDatum.pushBack(f1);
			Assert::IsTrue(fDatum == f1, L"Value not equivalent to value assigned");
			Assert::IsFalse(fDatum == f2, L"value equivalent to incorrect scalar value");
			Assert::IsFalse(fDatum == f3, L"value equivalent to incorrect scalar value");

			fDatum.pushBack(f2);
			Assert::IsFalse(fDatum == f1, L"operator!= should always return true when size > 1");
			Assert::IsFalse(fDatum == f2, L"operator!= should always return true when size > 1");
			Assert::IsFalse(fDatum == f3, L"operator!= should always return true when size > 1");

			Assert::IsTrue(fDatum == Library::DatumType::Float);
			Assert::IsFalse(fDatum == Library::DatumType::Integer);
			Assert::IsFalse(fDatum == Library::DatumType::Vector);
			Assert::IsFalse(fDatum == Library::DatumType::Matrix);
			Assert::IsFalse(fDatum == Library::DatumType::String);
			Assert::IsFalse(fDatum == Library::DatumType::Pointer);

			Library::Datum fDatumOther(Library::DatumType::Float);
			fDatumOther.pushBack(f1);
			fDatumOther.pushBack(f1);
			Assert::IsFalse(fDatum == fDatumOther);
		}

		TEST_METHOD(TestEqualityOperator_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);
			
			vDatum.pushBack(v1);
			Assert::IsTrue(vDatum == v1, L"Value not equivalent to value assigned");
			Assert::IsFalse(vDatum == v2, L"value equivalent to incorrect scalar value");
			Assert::IsFalse(vDatum == v3, L"value equivalent to incorrect scalar value");

			vDatum.pushBack(v2);
			Assert::IsFalse(vDatum == v1, L"operator!= should always return true when size > 1");
			Assert::IsFalse(vDatum == v2, L"operator!= should always return true when size > 1");
			Assert::IsFalse(vDatum == v3, L"operator!= should always return true when size > 1");

			Assert::IsTrue(vDatum == Library::DatumType::Vector);
			Assert::IsFalse(vDatum == Library::DatumType::Integer);
			Assert::IsFalse(vDatum == Library::DatumType::Float);
			Assert::IsFalse(vDatum == Library::DatumType::Matrix);
			Assert::IsFalse(vDatum == Library::DatumType::String);
			Assert::IsFalse(vDatum == Library::DatumType::Pointer);

			Library::Datum vDatumOther(Library::DatumType::Vector);
			vDatumOther.pushBack(v1);
			vDatumOther.pushBack(v1);
			Assert::IsFalse(vDatum == vDatumOther);
		}

		TEST_METHOD(TestEqualityOperator_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);
			
			mDatum.pushBack(m1);
			Assert::IsTrue(mDatum == m1, L"Value not equivalent to value assigned");
			Assert::IsFalse(mDatum == m2, L"value equivalent to incorrect scalar value");
			Assert::IsFalse(mDatum == m3, L"value equivalent to incorrect scalar value");

			mDatum.pushBack(m2);
			Assert::IsFalse(mDatum == m1, L"operator!= should always return true when size > 1");
			Assert::IsFalse(mDatum == m2, L"operator!= should always return true when size > 1");
			Assert::IsFalse(mDatum == m3, L"operator!= should always return true when size > 1");

			Assert::IsTrue(mDatum == Library::DatumType::Matrix);
			Assert::IsFalse(mDatum == Library::DatumType::Integer);
			Assert::IsFalse(mDatum == Library::DatumType::Float);
			Assert::IsFalse(mDatum == Library::DatumType::Vector);
			Assert::IsFalse(mDatum == Library::DatumType::String);
			Assert::IsFalse(mDatum == Library::DatumType::Pointer);

			Library::Datum mDatumOther(Library::DatumType::Matrix);
			mDatumOther.pushBack(m1);
			mDatumOther.pushBack(m1);
			Assert::IsFalse(mDatum == mDatumOther);
		}

		TEST_METHOD(TestEqualityOperator_String)
		{
			Library::Datum sDatum(Library::DatumType::String);
			
			sDatum.pushBack(s1);
			Assert::IsTrue(sDatum == s1, L"Value not equivalent to value assigned");
			Assert::IsFalse(sDatum == s2, L"value equivalent to incorrect scalar value");
			Assert::IsFalse(sDatum == s3, L"value equivalent to incorrect scalar value");

			sDatum.pushBack(s2);
			Assert::IsFalse(sDatum == s1, L"operator!= should always return true when size > 1");
			Assert::IsFalse(sDatum == s2, L"operator!= should always return true when size > 1");
			Assert::IsFalse(sDatum == s3, L"operator!= should always return true when size > 1");

			Assert::IsTrue(sDatum == Library::DatumType::String);
			Assert::IsFalse(sDatum == Library::DatumType::Integer);
			Assert::IsFalse(sDatum == Library::DatumType::Float);
			Assert::IsFalse(sDatum == Library::DatumType::Vector);
			Assert::IsFalse(sDatum == Library::DatumType::Matrix);
			Assert::IsFalse(sDatum == Library::DatumType::Pointer);

			Library::Datum sDatumOther(Library::DatumType::String);
			sDatumOther.pushBack(s1);
			sDatumOther.pushBack(s1);
			Assert::IsFalse(sDatum == sDatumOther);
		}

		TEST_METHOD(TestEqualityOperator_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			rDatum.pushBack(r1);
			Assert::IsTrue(rDatum == r1, L"Value not equivalent to value assigned");
			Assert::IsFalse(rDatum == r2, L"value equivalent to incorrect scalar value");
			Assert::IsFalse(rDatum == r3, L"value equivalent to incorrect scalar value");
			rDatum.pushBack(r2);
			Assert::IsFalse(rDatum == r1, L"operator!= should always return true when size > 1");
			Assert::IsFalse(rDatum == r2, L"operator!= should always return true when size > 1");
			Assert::IsFalse(rDatum == r3, L"operator!= should always return true when size > 1");

			Assert::IsTrue(rDatum == Library::DatumType::Pointer);
			Assert::IsFalse(rDatum == Library::DatumType::Integer);
			Assert::IsFalse(rDatum == Library::DatumType::Float);
			Assert::IsFalse(rDatum == Library::DatumType::Vector);
			Assert::IsFalse(rDatum == Library::DatumType::Matrix);
			Assert::IsFalse(rDatum == Library::DatumType::String);

			Library::Datum rDatumOther(Library::DatumType::Pointer);
			rDatumOther.pushBack(r1);
			rDatumOther.pushBack(r1);
			Assert::IsFalse(rDatum == rDatumOther);
		}

		TEST_METHOD(TestInequalityOperator_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			Assert::IsFalse(iDatum != iDatum);

			iDatum.pushBack(i1);
			Assert::IsFalse(iDatum != i1, L"Value not equivalent to value assigned");
			Assert::IsTrue(iDatum != i2, L"value equivalent to incorrect scalar value");
			Assert::IsTrue(iDatum != i3, L"value equivalent to incorrect scalar value");

			iDatum.pushBack(i2);
			Assert::IsTrue(iDatum != i1, L"operator!= should always return true when size > 1");
			Assert::IsTrue(iDatum != i2, L"operator!= should always return true when size > 1");
			Assert::IsTrue(iDatum != i3, L"operator!= should always return true when size > 1");

			Assert::IsFalse(iDatum != Library::DatumType::Integer);
			Assert::IsTrue(iDatum.type() != Library::DatumType::Float);
			Assert::IsTrue(iDatum.type() != Library::DatumType::Vector);
			Assert::IsTrue(iDatum.type() != Library::DatumType::Matrix);
			Assert::IsTrue(iDatum.type() != Library::DatumType::String);
			Assert::IsTrue(iDatum.type() != Library::DatumType::Pointer);
		}

		TEST_METHOD(TestInequalityOperator_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			Assert::IsFalse(fDatum != fDatum);

			fDatum.pushBack(f1);
			Assert::IsFalse(fDatum != f1, L"Value not equivalent to value assigned");
			Assert::IsTrue(fDatum != f2, L"value equivalent to incorrect scalar value");
			Assert::IsTrue(fDatum != f3, L"value equivalent to incorrect scalar value");

			fDatum.pushBack(f2);
			Assert::IsTrue(fDatum != f1, L"operator!= should always return true when size > 1");
			Assert::IsTrue(fDatum != f2, L"operator!= should always return true when size > 1");
			Assert::IsTrue(fDatum != f3, L"operator!= should always return true when size > 1");

			Assert::IsFalse(fDatum != Library::DatumType::Float);
			Assert::IsTrue(fDatum.type() != Library::DatumType::Integer);
			Assert::IsTrue(fDatum.type() != Library::DatumType::Vector);
			Assert::IsTrue(fDatum.type() != Library::DatumType::Matrix);
			Assert::IsTrue(fDatum.type() != Library::DatumType::String);
			Assert::IsTrue(fDatum.type() != Library::DatumType::Pointer);
		}

		TEST_METHOD(TestInequalityOperator_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			Assert::IsFalse(vDatum != vDatum);

			vDatum.pushBack(v1);
			Assert::IsFalse(vDatum != v1, L"Value not equivalent to value assigned");
			Assert::IsTrue(vDatum != v2, L"value equivalent to incorrect scalar value");
			Assert::IsTrue(vDatum != v3, L"value equivalent to incorrect scalar value");

			vDatum.pushBack(v2);
			Assert::IsTrue(vDatum != v1, L"operator!= should always return true when size > 1");
			Assert::IsTrue(vDatum != v2, L"operator!= should always return true when size > 1");
			Assert::IsTrue(vDatum != v3, L"operator!= should always return true when size > 1");

			Assert::IsFalse(vDatum != Library::DatumType::Vector);
			Assert::IsTrue(vDatum.type() != Library::DatumType::Integer);
			Assert::IsTrue(vDatum.type() != Library::DatumType::Float);
			Assert::IsTrue(vDatum.type() != Library::DatumType::Matrix);
			Assert::IsTrue(vDatum.type() != Library::DatumType::String);
			Assert::IsTrue(vDatum.type() != Library::DatumType::Pointer);
		}

		TEST_METHOD(TestInequalityOperator_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			Assert::IsFalse(mDatum != mDatum);

			mDatum.pushBack(m1);
			Assert::IsFalse(mDatum != m1, L"Value not equivalent to value assigned");
			Assert::IsTrue(mDatum != m2, L"value equivalent to incorrect scalar value");
			Assert::IsTrue(mDatum != m3, L"value equivalent to incorrect scalar value");

			mDatum.pushBack(m2);
			Assert::IsTrue(mDatum != m1, L"operator!= should always return true when size > 1");
			Assert::IsTrue(mDatum != m2, L"operator!= should always return true when size > 1");
			Assert::IsTrue(mDatum != m3, L"operator!= should always return true when size > 1");

			Assert::IsFalse(mDatum != Library::DatumType::Matrix);
			Assert::IsTrue(mDatum.type() != Library::DatumType::Integer);
			Assert::IsTrue(mDatum.type() != Library::DatumType::Float);
			Assert::IsTrue(mDatum.type() != Library::DatumType::Vector);
			Assert::IsTrue(mDatum.type() != Library::DatumType::String);
			Assert::IsTrue(mDatum.type() != Library::DatumType::Pointer);
		}

		TEST_METHOD(TestInequalityOperator_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			Assert::IsFalse(sDatum != sDatum);

			sDatum.pushBack(s1);
			Assert::IsFalse(sDatum != s1, L"Value not equivalent to value assigned");
			Assert::IsTrue(sDatum != s2, L"value equivalent to incorrect scalar value");
			Assert::IsTrue(sDatum != s3, L"value equivalent to incorrect scalar value");

			sDatum.pushBack(s2);
			Assert::IsTrue(sDatum != s1, L"operator!= should always return true when size > 1");
			Assert::IsTrue(sDatum != s2, L"operator!= should always return true when size > 1");
			Assert::IsTrue(sDatum != s3, L"operator!= should always return true when size > 1");

			Assert::IsFalse(sDatum != Library::DatumType::String);
			Assert::IsTrue(sDatum.type() != Library::DatumType::Integer);
			Assert::IsTrue(sDatum.type() != Library::DatumType::Float);
			Assert::IsTrue(sDatum.type() != Library::DatumType::Vector);
			Assert::IsTrue(sDatum.type() != Library::DatumType::Matrix);
			Assert::IsTrue(sDatum.type() != Library::DatumType::Pointer);
		}

		TEST_METHOD(TestInequalityOperator_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			Assert::IsFalse(rDatum != rDatum);

			rDatum.pushBack(r1);
			Assert::IsFalse(rDatum != r1, L"Value not equivalent to value assigned");
			Assert::IsTrue(rDatum != r2, L"value equivalent to incorrect scalar value");
			Assert::IsTrue(rDatum != r3, L"value equivalent to incorrect scalar value");
			rDatum.pushBack(r2);
			Assert::IsTrue(rDatum != r1, L"operator!= should always return true when size > 1");
			Assert::IsTrue(rDatum != r2, L"operator!= should always return true when size > 1");
			Assert::IsTrue(rDatum != r3, L"operator!= should always return true when size > 1");

			Assert::IsFalse(rDatum != Library::DatumType::Pointer);
			Assert::IsTrue(rDatum.type() != Library::DatumType::Integer);
			Assert::IsTrue(rDatum.type() != Library::DatumType::Float);
			Assert::IsTrue(rDatum.type() != Library::DatumType::Vector);
			Assert::IsTrue(rDatum.type() != Library::DatumType::Matrix);
			Assert::IsTrue(rDatum.type() != Library::DatumType::String);
		}

		TEST_METHOD(TestType_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			Library::Datum iDatumTemp1;
			Assert::IsTrue(iDatumTemp1.type() == Library::DatumType::Unknown);

			iDatumTemp1 = Library::DatumType::Integer;
			Assert::IsTrue(iDatumTemp1.type() == Library::DatumType::Integer);

			Library::Datum iDatumTemp2;
			iDatumTemp2 = i1;
//			Assert::IsTrue(iDatumTemp2.type() == Library::DatumType::Integer);
//
//			iDatumTemp2 = i2;
//			Assert::IsTrue(iDatumTemp2.type() == Library::DatumType::Integer);
//			Assert::ExpectException<std::exception>([&] { iDatumTemp2 = f1; },
//				L"Exception not being thrown when assigned improper type");
		}

		TEST_METHOD(TestType_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			Library::Datum fDatumTemp1;
			Assert::IsTrue(fDatumTemp1.type() == Library::DatumType::Unknown);

			fDatumTemp1 = Library::DatumType::Float;
			Assert::IsTrue(fDatumTemp1.type() == Library::DatumType::Float);

			Library::Datum fDatumTemp2;
//			fDatumTemp2 = f1;
//			Assert::IsTrue(fDatumTemp2.type() == Library::DatumType::Float);
//
//			fDatumTemp2 = f2;
//			Assert::IsTrue(fDatumTemp2.type() == Library::DatumType::Float);
//			Assert::ExpectException<std::exception>([&] { fDatumTemp2 = i1; },
//				L"Exception not being thrown when assigned improper type");
		}

		TEST_METHOD(TestType_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			Library::Datum vDatumTemp1;
			Assert::IsTrue(vDatumTemp1.type() == Library::DatumType::Unknown);

			vDatumTemp1 = Library::DatumType::Vector;
			Assert::IsTrue(vDatumTemp1.type() == Library::DatumType::Vector);

			Library::Datum vDatumTemp2;
//			vDatumTemp2 = v1;
//			Assert::IsTrue(vDatumTemp2.type() == Library::DatumType::Vector);
//
//			vDatumTemp2 = v2;
//			Assert::IsTrue(vDatumTemp2.type() == Library::DatumType::Vector);
//			Assert::ExpectException<std::exception>([&] { vDatumTemp2 = i1; },
//				L"Exception not being thrown when assigned improper type");
		}

		TEST_METHOD(TestType_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			Library::Datum mDatumTemp1;
			Assert::IsTrue(mDatumTemp1.type() == Library::DatumType::Unknown);

			mDatumTemp1 = Library::DatumType::Matrix;
			Assert::IsTrue(mDatumTemp1.type() == Library::DatumType::Matrix);

			Library::Datum mDatumTemp2;
//			mDatumTemp2 = m1;
//			Assert::IsTrue(mDatumTemp2.type() == Library::DatumType::Matrix);
//
//			mDatumTemp2 = m2;
//			Assert::IsTrue(mDatumTemp2.type() == Library::DatumType::Matrix);
//			Assert::ExpectException<std::exception>([&] { mDatumTemp2 = i1; },
//				L"Exception not being thrown when assigned improper type");
		}

		TEST_METHOD(TestType_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			Library::Datum sDatumTemp1;
			Assert::IsTrue(sDatumTemp1.type() == Library::DatumType::Unknown);

			sDatumTemp1 = Library::DatumType::String;
			Assert::IsTrue(sDatumTemp1.type() == Library::DatumType::String);

			Library::Datum sDatumTemp2;
//			sDatumTemp2 = s1;
//			Assert::IsTrue(sDatumTemp2.type() == Library::DatumType::String);
//
//			sDatumTemp2 = s2;
//			Assert::IsTrue(sDatumTemp2.type() == Library::DatumType::String);
//			Assert::ExpectException<std::exception>([&] { sDatumTemp2 = i1; },
//				L"Exception not being thrown when assigned improper type");
		}

		TEST_METHOD(TestType_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			Library::Datum rDatumTemp1;
			Assert::IsTrue(rDatumTemp1.type() == Library::DatumType::Unknown);

			rDatumTemp1 = Library::DatumType::Pointer;
			Assert::IsTrue(rDatumTemp1.type() == Library::DatumType::Pointer);

			Library::Datum rDatumTemp2;
//			rDatumTemp2 = r1;
//			Assert::IsTrue(rDatumTemp2.type() == Library::DatumType::Pointer);
//
//			rDatumTemp2 = r2;
//			Assert::IsTrue(rDatumTemp2.type() == Library::DatumType::Pointer);
//			Assert::ExpectException<std::exception>([&] { rDatumTemp2 = i1; },
//				L"Exception not being thrown when assigned improper type");
		}

		TEST_METHOD(TestSize_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			Assert::AreEqual(iDatum.size(), 0u, L"Size not zero on empty Datum");

			iDatum.pushBack(i1);
			Assert::AreEqual(iDatum.size(), 1u), L"Size does not reflect number of elements pushed";

			iDatum.pushBack(i2);
			Assert::AreEqual(iDatum.size(), 2u, L"Size does not reflect number of elements pushed");

			iDatum.setSize(10);
			Assert::AreEqual(iDatum.size(), 10u, L"Size not equal after calling setSize");

			iDatum.setSize(1);
			Assert::AreEqual(iDatum.size(), 1u, L"setSize should reduce current size");
		}

		TEST_METHOD(TestSize_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			Assert::AreEqual(fDatum.size(), 0u, L"Size not zero on empty Datum");

			fDatum.pushBack(f1);
			Assert::AreEqual(fDatum.size(), 1u), L"Size does not reflect number of elements pushed";

			fDatum.pushBack(f2);
			Assert::AreEqual(fDatum.size(), 2u, L"Size does not reflect number of elements pushed");

			fDatum.setSize(10);
			Assert::AreEqual(fDatum.size(), 10u, L"Size not equal after calling setSize");

			fDatum.setSize(1);
			Assert::AreEqual(fDatum.size(), 1u, L"setSize should reduce current size");
		}

		TEST_METHOD(TestSize_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			Assert::AreEqual(vDatum.size(), 0u, L"Size not zero on empty Datum");

			vDatum.pushBack(v1);
			Assert::AreEqual(vDatum.size(), 1u), L"Size does not reflect number of elements pushed";

			vDatum.pushBack(v2);
			Assert::AreEqual(vDatum.size(), 2u, L"Size does not reflect number of elements pushed");

			vDatum.setSize(10);
			Assert::AreEqual(vDatum.size(), 10u, L"Size not equal after calling setSize");

			vDatum.setSize(1);
			Assert::AreEqual(vDatum.size(), 1u, L"setSize should reduce current size");
		}

		TEST_METHOD(TestSize_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			Assert::AreEqual(mDatum.size(), 0u, L"Size not zero on empty Datum");

			mDatum.pushBack(m1);
			Assert::AreEqual(mDatum.size(), 1u), L"Size does not reflect number of elements pushed";

			mDatum.pushBack(m2);
			Assert::AreEqual(mDatum.size(), 2u, L"Size does not reflect number of elements pushed");

			mDatum.setSize(10);
			Assert::AreEqual(mDatum.size(), 10u, L"Size not equal after calling setSize");

			mDatum.setSize(1);
			Assert::AreEqual(mDatum.size(), 1u, L"setSize should reduce current size");
		}

		TEST_METHOD(TestSize_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			Assert::AreEqual(sDatum.size(), 0u, L"Size not zero on empty Datum");

			sDatum.pushBack(s1);
			Assert::AreEqual(sDatum.size(), 1u), L"Size does not reflect number of elements pushed";

			sDatum.pushBack(s2);
			Assert::AreEqual(sDatum.size(), 2u, L"Size does not reflect number of elements pushed");

			sDatum.setSize(10);
			Assert::AreEqual(sDatum.size(), 10u, L"Size not equal after calling setSize");

			sDatum.setSize(1);
			Assert::AreEqual(sDatum.size(), 1u, L"setSize should reduce current size");
		}

		TEST_METHOD(TestSize_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

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

		TEST_METHOD(TestReserve_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			iDatum.reserve(10);
			Assert::AreEqual(0u, iDatum.size());
			Assert::AreEqual(10u, iDatum.capacity());

			iDatum.setSize(10);
			Assert::AreEqual(10u, iDatum.size());
			Assert::AreEqual(10u, iDatum.capacity());

			iDatum.reserve(10);
			Assert::AreEqual(10u, iDatum.size());
			Assert::AreEqual(10u, iDatum.capacity());
		}

		TEST_METHOD(TestReserve_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			fDatum.reserve(10);
			Assert::AreEqual(fDatum.size(), 0u);
			Assert::AreEqual(fDatum.capacity(), 10u);

			fDatum.setSize(10);
			Assert::AreEqual(fDatum.size(), 10u);
			Assert::AreEqual(fDatum.capacity(), 10u);

			fDatum.reserve(10);
			Assert::AreEqual(fDatum.size(), 10u);
			Assert::AreEqual(fDatum.capacity(), 10u);
		}

		TEST_METHOD(TestReserve_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			vDatum.reserve(10);
			Assert::AreEqual(vDatum.size(), 0u);
			Assert::AreEqual(vDatum.capacity(), 10u);

			vDatum.setSize(10);
			Assert::AreEqual(vDatum.size(), 10u);
			Assert::AreEqual(vDatum.capacity(), 10u);

			vDatum.reserve(10);
			Assert::AreEqual(vDatum.size(), 10u);
			Assert::AreEqual(vDatum.capacity(), 10u);
		}

		TEST_METHOD(TestReserve_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			mDatum.reserve(10);
			Assert::AreEqual(mDatum.size(), 0u);
			Assert::AreEqual(mDatum.capacity(), 10u);

			mDatum.setSize(10);
			Assert::AreEqual(mDatum.size(), 10u);
			Assert::AreEqual(mDatum.capacity(), 10u);

			mDatum.reserve(10);
			Assert::AreEqual(mDatum.size(), 10u);
			Assert::AreEqual(mDatum.capacity(), 10u);
		}

		TEST_METHOD(TestReserve_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			sDatum.reserve(10);
			Assert::AreEqual(sDatum.size(), 0u);
			Assert::AreEqual(sDatum.capacity(), 10u);

			sDatum.setSize(10);
			Assert::AreEqual(sDatum.size(), 10u);
			Assert::AreEqual(sDatum.capacity(), 10u);

			sDatum.reserve(10);
			Assert::AreEqual(sDatum.size(), 10u);
			Assert::AreEqual(sDatum.capacity(), 10u);
		}

		TEST_METHOD(TestReserve_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			rDatum.reserve(10);
			Assert::AreEqual(rDatum.size(), 0u);
			Assert::AreEqual(rDatum.capacity(), 10u);

			rDatum.setSize(10);
			Assert::AreEqual(rDatum.size(), 10u);
			Assert::AreEqual(rDatum.capacity(), 10u);

			rDatum.reserve(10);
			Assert::AreEqual(rDatum.size(), 10u);
			Assert::AreEqual(rDatum.capacity(), 10u);
		}

		TEST_METHOD(TestClear_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			iDatum.setSize(10);
			iDatum.clear();
			Assert::AreEqual(10u, iDatum.capacity());
			Assert::AreEqual(0u, iDatum.size());

			iDatum = i1;
			iDatum.clear();
			Assert::AreEqual(1u, iDatum.capacity());
			Assert::AreEqual(0u, iDatum.size());

			iDatum.clear();
			Assert::AreEqual(1u, iDatum.capacity());
			Assert::AreEqual(0u, iDatum.size());
		}

		TEST_METHOD(TestClear_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			fDatum.setSize(10);
			fDatum.clear();
			Assert::AreEqual(10u, fDatum.capacity());
			Assert::AreEqual(0u, fDatum.size());

			fDatum = f1;
			fDatum.clear();
			Assert::AreEqual(1u, fDatum.capacity());
			Assert::AreEqual(0u, fDatum.size());

			fDatum.clear();
			Assert::AreEqual(1u, fDatum.capacity());
			Assert::AreEqual(0u, fDatum.size());
		}

		TEST_METHOD(TestClear_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			vDatum.setSize(10);
			vDatum.clear();
			Assert::AreEqual(10u, vDatum.capacity());
			Assert::AreEqual(0u, vDatum.size());

			vDatum = v1;
			vDatum.clear();
			Assert::AreEqual(1u, vDatum.capacity());
			Assert::AreEqual(0u, vDatum.size());

			vDatum.clear();
			Assert::AreEqual(1u, vDatum.capacity());
			Assert::AreEqual(0u, vDatum.size());
		}

		TEST_METHOD(TestClear_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			mDatum.setSize(10);
			mDatum.clear();
			Assert::AreEqual(10u, mDatum.capacity());
			Assert::AreEqual(0u, mDatum.size());

			mDatum = m1;
			mDatum.clear();
			Assert::AreEqual(1u, mDatum.capacity());
			Assert::AreEqual(0u, mDatum.size());

			mDatum.clear();
			Assert::AreEqual(1u, mDatum.capacity());
			Assert::AreEqual(0u, mDatum.size());
		}

		TEST_METHOD(TestClear_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			sDatum.setSize(10);
			sDatum.clear();
			Assert::AreEqual(10u, sDatum.capacity());
			Assert::AreEqual(0u, sDatum.size());

			sDatum = s1;
			sDatum.clear();
			Assert::AreEqual(1u, sDatum.capacity());
			Assert::AreEqual(0u, sDatum.size());

			sDatum.clear();
			Assert::AreEqual(1u, sDatum.capacity());
			Assert::AreEqual(0u, sDatum.size());
		}

		TEST_METHOD(TestClear_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			rDatum.setSize(10);
			rDatum.clear();
			Assert::AreEqual(10u, rDatum.capacity());
			Assert::AreEqual(0u, rDatum.size());

			rDatum = r1;
			rDatum.clear();
			Assert::AreEqual(1u, rDatum.capacity());
			Assert::AreEqual(0u, rDatum.size());

			rDatum.clear();
			Assert::AreEqual(1u, rDatum.capacity());
			Assert::AreEqual(0u, rDatum.size());
		}

		TEST_METHOD(TestSetStorage_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			Library::Datum iTemp;
			std::int32_t* iStorage = static_cast<std::int32_t*>(malloc(sizeof(std::int32_t) * 10));
			iTemp.setStorage(iStorage, 10);
			Library::Datum iTemp2;
			iTemp2.setStorage(iStorage, 10);
			Assert::IsTrue(iTemp == iTemp2);

			free(iStorage);
		}
		TEST_METHOD(TestSetStorage_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			Library::Datum fTemp;
			float* fStorage = static_cast<float*>(malloc(sizeof(float) * 10));
			fTemp.setStorage(fStorage, 10);
			Library::Datum fTemp2;
			fTemp2.setStorage(fStorage, 10);
			Assert::IsTrue(fTemp == fTemp2);

			free(fStorage);
		}
		TEST_METHOD(TestSetStorage_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

			Library::Datum vTemp;
			glm::vec4* vStorage = static_cast<glm::vec4*>(malloc(sizeof(glm::vec4) * 10));
			vTemp.setStorage(vStorage, 10);
			Library::Datum vTemp2;
			vTemp2.setStorage(vStorage, 10);
			Assert::IsTrue(vTemp == vTemp2);

			free(vStorage);
		}
		TEST_METHOD(TestSetStorage_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

			Library::Datum mTemp;
			glm::mat4* mStorage = static_cast<glm::mat4*>(malloc(sizeof(glm::mat4) * 10));
			mTemp.setStorage(mStorage, 10);
			Library::Datum mTemp2;
			mTemp2.setStorage(mStorage, 10);
			Assert::IsTrue(mTemp == mTemp2);

			free(mStorage);
		}
		TEST_METHOD(TestSetStorage_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

			Library::Datum sTemp;
			std::string sStorage[10];
			sTemp.setStorage(sStorage, 10);
			Library::Datum sTemp2;
			sTemp2.setStorage(sStorage, 10);
			Assert::IsTrue(sTemp == sTemp2);
		}
		TEST_METHOD(TestSetStorage_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			Library::Datum rTemp;
			Library::RTTI** rStorage = static_cast<Library::RTTI**>(malloc(sizeof(Library::RTTI*) * 10));
			rTemp.setStorage(rStorage, 10);
			Library::Datum rTemp2;
			rTemp2.setStorage(rStorage, 10);
			Assert::IsTrue(rTemp == rTemp2);

			free(rStorage);
		}

		TEST_METHOD(TestSet_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

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
		}

		TEST_METHOD(TestSet_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

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
		}

		TEST_METHOD(TestSet_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

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
		}

		TEST_METHOD(TestSet_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

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
		}

		TEST_METHOD(TestSet_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

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
		}

		TEST_METHOD(TestSet_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

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

		TEST_METHOD(TestSetFromString_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

			iDatum.setFromString("1");
			Assert::IsTrue(iDatum == 1);
			Assert::IsFalse(iDatum == 2);

			iDatum.setFromString("2", 1);
			Assert::IsTrue(iDatum.get<std::int32_t>(0) == 1);
			Assert::IsTrue(iDatum.get<std::int32_t>(1) == 2);

			iDatum.setFromString("3", 1);
			Assert::IsTrue(iDatum.get<std::int32_t>(0) == 1);
			Assert::IsTrue(iDatum.get<std::int32_t>(1) == 3);
		}

		TEST_METHOD(TestSetFromString_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

			fDatum.setFromString("1.0f");
			Assert::IsTrue(fDatum == f1);
			Assert::IsFalse(fDatum == f2);

			fDatum.setFromString("2.0f", 1);
			Assert::IsTrue(fDatum.get<float>(0) == f1);
			Assert::IsTrue(fDatum.get<float>(1) == f2);

			fDatum.setFromString("3.0f", 1);
			Assert::IsTrue(fDatum.get<float>(0) == f1);
			Assert::IsTrue(fDatum.get<float>(1) == f3);
		}

		TEST_METHOD(TestSetFromString_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

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
		}

		TEST_METHOD(TestSetFromString_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

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
		}

		TEST_METHOD(TestSetFromString_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

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

		TEST_METHOD(TestSetFromString_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			Assert::ExpectException<std::exception>([&] 
			{ 
				rDatum.setFromString("Break Me"); 
			}, L"Set from string on pointer type should throw exception");
		}

		TEST_METHOD(TestToString_Integer)
		{
			Library::Datum iDatum(Library::DatumType::Integer);

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
		}

		TEST_METHOD(TestToString_Float)
		{
			Library::Datum fDatum(Library::DatumType::Float);

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
		}

		TEST_METHOD(TestToString_Vector)
		{
			Library::Datum vDatum(Library::DatumType::Vector);

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
		}

		TEST_METHOD(TestToString_Matrix)
		{
			Library::Datum mDatum(Library::DatumType::Matrix);

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
		}

		TEST_METHOD(TestToString_String)
		{
			Library::Datum sDatum(Library::DatumType::String);

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

		TEST_METHOD(TestToString_Pointer)
		{
			Library::Datum rDatum(Library::DatumType::Pointer);

			Assert::IsTrue("" == rDatum.toString(), L"pointer toString should return an empty string representation");
			Assert::IsTrue("" == rDatum.toString(0), L"pointer toString should return an empty string representation");
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

			Assert::ExpectException<std::exception>([&] { iDatum.setStorage(fData, size); });
			Assert::ExpectException<std::exception>([&] { iDatum.setStorage(vData, size); });
			Assert::ExpectException<std::exception>([&] { iDatum.setStorage(mData, size); });
			Assert::ExpectException<std::exception>([&] { iDatum.setStorage(sData, size); });
			Assert::ExpectException<std::exception>([&] { iDatum.setStorage(rData, size); });

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

			Assert::ExpectException<std::exception>([&] { fDatum.setStorage(iData, size); });
			Assert::ExpectException<std::exception>([&] { fDatum.setStorage(vData, size); });
			Assert::ExpectException<std::exception>([&] { fDatum.setStorage(mData, size); });
			Assert::ExpectException<std::exception>([&] { fDatum.setStorage(sData, size); });
			Assert::ExpectException<std::exception>([&] { fDatum.setStorage(rData, size); });

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

			Assert::ExpectException<std::exception>([&] { vDatum.setStorage(iData, size); });
			Assert::ExpectException<std::exception>([&] { vDatum.setStorage(fData, size); });
			Assert::ExpectException<std::exception>([&] { vDatum.setStorage(mData, size); });
			Assert::ExpectException<std::exception>([&] { vDatum.setStorage(sData, size); });
			Assert::ExpectException<std::exception>([&] { vDatum.setStorage(rData, size); });

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

			Assert::ExpectException<std::exception>([&] { mDatum.setStorage(iData, size); });
			Assert::ExpectException<std::exception>([&] { mDatum.setStorage(fData, size); });
			Assert::ExpectException<std::exception>([&] { mDatum.setStorage(vData, size); });
			Assert::ExpectException<std::exception>([&] { mDatum.setStorage(sData, size); });
			Assert::ExpectException<std::exception>([&] { mDatum.setStorage(rData, size); });

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

			Assert::ExpectException<std::exception>([&] { sDatum.setStorage(iData, size); });
			Assert::ExpectException<std::exception>([&] { sDatum.setStorage(fData, size); });
			Assert::ExpectException<std::exception>([&] { sDatum.setStorage(vData, size); });
			Assert::ExpectException<std::exception>([&] { sDatum.setStorage(mData, size); });
			Assert::ExpectException<std::exception>([&] { sDatum.setStorage(rData, size); });

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

			Assert::ExpectException<std::exception>([&] { rDatum.setStorage(iData, size); });
			Assert::ExpectException<std::exception>([&] { rDatum.setStorage(fData, size); });
			Assert::ExpectException<std::exception>([&] { rDatum.setStorage(vData, size); });
			Assert::ExpectException<std::exception>([&] { rDatum.setStorage(mData, size); });
			Assert::ExpectException<std::exception>([&] { rDatum.setStorage(sData, size); });

			free(iData);
			free(fData);
			free(vData);
			free(mData);
			free(sData);
		}

		TEST_METHOD(LeakTest)
		{
			Library::Datum iDatum(Library::DatumType::Integer);
			Library::Datum fDatum(Library::DatumType::Float);
			Library::Datum vDatum(Library::DatumType::Vector);
			Library::Datum mDatum(Library::DatumType::Matrix);
			Library::Datum sDatum(Library::DatumType::String);
			Library::Datum rDatum(Library::DatumType::Pointer);

			Library::Datum leaky(Library::DatumType::Integer);
			leaky = 5;

			leaky.setSize(10);
			leaky.setSize(1);
			leaky.setSize(100);
			leaky.set(4, 99);
			leaky.setSize(1);

		}

		static _CrtMemState sStartMemState;
	};

	_CrtMemState DatumTest::sStartMemState;
}