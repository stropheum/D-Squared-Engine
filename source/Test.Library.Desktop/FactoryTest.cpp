#include "pch.h"
#include "CppUnitTest.h"
#include "Datum.h"
#include "RTTI.h"
#include "FooRTTI.h"
#include "FooProductFactory.h"
#include "MacroGeneratedProduct.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace TestLibraryDesktop
{
	TEST_CLASS(FactoryTest)
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
		}

		TEST_METHOD_CLEANUP(methodCleanup)
		{
			finalizeLeakDetection();
		}

		TEST_METHOD(TestCreate)
		{
			FooProductFactory fooFactory;
			RTTI* product = Factory<RTTI>::create("FooProduct");
			FooProduct* fooProduct = product != nullptr ? product->As<FooProduct>() : nullptr;
			Assert::IsTrue(fooProduct != nullptr);

			BarProductFactory barFactory;
			product = Library::Factory<RTTI>::create("BarProduct");
			BarProduct* barProduct = product != nullptr ? product->As<BarProduct>() : nullptr;
			Assert::IsTrue(barProduct != nullptr);

			Assert::IsFalse(fooProduct->Equals(barProduct));

			delete fooProduct;
			delete barProduct;
		}

		TEST_METHOD(TestBeginAndEnd)
		{
			Assert::IsTrue(Factory<RTTI>::begin() == Factory<RTTI>::end());

			{
				int count = 0;
				for (auto iter = Factory<RTTI>::begin(); iter != Factory<RTTI>::end(); ++iter)
				{
					count++;
				}
				Assert::IsTrue(count == 0);
			}

			FooProductFactory fooFactory;
			Assert::IsTrue(Factory<RTTI>::begin() != Factory<RTTI>::end());
			Assert::AreEqual(fooFactory.className(), Factory<RTTI>::begin()->second->className());

			{
				int count = 0;
				for (auto iter = Factory<RTTI>::begin(); iter != Factory<RTTI>::end(); ++iter)
				{
					count++;
				}
				Assert::IsTrue(count == 1);
			}
			
			BarProductFactory barFactory;
			Assert::IsTrue(Factory<RTTI>::begin() != Factory<RTTI>::end());

			{
				int count = 0;
				for (auto iter = Factory<RTTI>::begin(); iter != Factory<RTTI>::end(); ++iter)
				{
					count++;
				}
				Assert::IsTrue(count == 2);
			}
		}

		TEST_METHOD(TestMacroUsage)
		{
			Assert::IsTrue(Factory<RTTI>::begin() == Factory<RTTI>::end());
			MacroGeneratedProductFactory factory;
			Assert::IsTrue(Factory<RTTI>::begin() != Factory<RTTI>::end());

			RTTI* product = Factory<RTTI>::create("MacroGeneratedProduct");

			Assert::IsTrue(product != nullptr && product->As<MacroGeneratedProduct>() != nullptr);

			delete product;
		}

		TEST_METHOD(TestFind)
		{
			Assert::IsTrue(Factory<RTTI>::find("FooProduct") == nullptr);
			Assert::IsTrue(Factory<RTTI>::find("BarProduct") == nullptr);

			FooProductFactory fooFactory;
			BarProductFactory barFactory;

			Assert::IsTrue(Factory<RTTI>::find("FooProduct") != nullptr);
			Assert::IsTrue(Factory<RTTI>::find("BarProduct") != nullptr);

			Assert::IsTrue(Factory<RTTI>::find("FooProduct") == &fooFactory);
			Assert::IsTrue(Factory<RTTI>::find("BarProduct") == &barFactory);
		}

		static _CrtMemState sStartMemState;
	};

	_CrtMemState FactoryTest::sStartMemState;
}