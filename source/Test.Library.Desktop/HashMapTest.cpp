#include "pch.h"
#include "CppUnitTest.h"
#include "HashMap.h"
#include "Foo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<>
class Library::DefaultHash<Foo>
{
public:
	std::uint32_t operator()(const Foo& key) const
	{
		std::uint32_t value = key.getData();
		const std::int8_t* bytes = reinterpret_cast<const std::int8_t*>(&value);

		std::uint32_t hash = 0;
		auto size = strlen(reinterpret_cast<const char*>(bytes));
		for (std::uint32_t i = 0; i < size; i++)
		{
			hash += bytes[i];
		}

		return hash;
	}
};

namespace TestLibraryDesktop
{
	TEST_CLASS(HashMapTest)
	{
		Library::HashMap<int, int> intMap;
		Library::HashMap<int*, int> ptrMap;
		Library::HashMap<char*, int> chrMap;
		Library::HashMap<std::string, int> strMap;
		Library::HashMap<Foo, int> fooMap;
		int x = 1;
		int y = 2;
		int z = 3;
		char* a = "a";
		char* b = "b";
		char* c = "c";
		std::string s = "Steve";
		std::string t = "Tyler";
		std::string u = "Uncle Phil";
		Foo foo, bar, gar;
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
			intMap.Clear();
			ptrMap.Clear();
			chrMap.Clear();
			strMap.Clear();
			fooMap.Clear();

			initializeLeakDetection();
			
			x = 1;
			y = 2;
			z = 3;
			a = "a";
			b = "b";
			c = "c";
			s = "Steve";
			t = "Tyler";
			u = "Uncle Phil";
			foo = Foo(1);
			bar = Foo(2);
			gar = Foo(3);
		}

		TEST_METHOD_CLEANUP(methodCleanup)
		{
			intMap.Clear();
			ptrMap.Clear();
			chrMap.Clear();
			strMap.Clear();
			fooMap.Clear();

			finalizeLeakDetection();
		}

		TEST_METHOD(TestTemplateSpecialization)
		{
			// int tests
			intMap.Insert(std::pair<int, int>(1, 1));
			Assert::IsTrue(intMap.ContainsKey(1), L"intMap does not contain inserted key");


			// ptr tests
			ptrMap.Insert(std::pair<int*, int>(&x, 1));
			Assert::IsTrue(ptrMap.ContainsKey(&x), L"ptrMap does not contain inserted key");


			// chr tests
			chrMap.Insert(std::pair<char*, int>(c, 1));
			Assert::IsTrue(chrMap.ContainsKey(c), L"charMap does not contain inserted key");


			// str tests
			strMap.Insert(std::pair<std::string, int>(s, 1));
			Assert::IsTrue(strMap.ContainsKey(s), L"stringMap does not contain inserted key");


			// foo tests
			fooMap.Insert(std::pair<Foo, int>(foo, 1));
			Assert::IsTrue(fooMap.ContainsKey(foo), L"fooMap does not contain inserted key");
		}

		TEST_METHOD(TestCopyConstructor)
		{
			// int tests
			Library::HashMap<int, int> intcopy1(intMap);
			Assert::IsTrue(intMap.Size() == intcopy1.Size(), L"HashMap sizes not equal");

			intMap.Insert(std::pair<int, int>(1, 1));
			Library::HashMap<int, int> intcopy2(intMap);
			Assert::AreEqual(intMap.Size(), intcopy2.Size(), L"HashMap sizes not equal");
			Assert::IsFalse(intMap.begin() == intMap.end(), L"begin of non-empty HashMap equals end");
			Assert::IsFalse(intcopy2.begin() == intcopy2.end(), L"begin of non-empty HashMap equals end");

			// ptr tests
			Library::HashMap<int*, int> ptrcopy1(ptrMap);
			Assert::IsTrue(ptrMap.Size() == ptrcopy1.Size(), L"HashMap sizes not equal");

			ptrMap.Insert(std::pair<int*, int>(&x, 1));
			Library::HashMap<int*, int> ptrcopy2(ptrMap);
			Assert::AreEqual(ptrMap.Size(), ptrcopy2.Size(), L"HashMap sizes not equal");
			Assert::IsFalse(ptrMap.begin() == ptrMap.end(), L"begin of non-empty HashMap equals end");
			Assert::IsFalse(ptrcopy2.begin() == ptrcopy2.end(), L"begin of non-empty HashMap equals end");


			// char* tests
			Library::HashMap<char*, int> chrcopy1(chrMap);
			Assert::IsTrue(chrMap.Size() == chrcopy1.Size(), L"HashMap sizes not equal");

			chrMap.Insert(std::pair<char*, int>(a, 1));
			Library::HashMap<char*, int> chrcopy2(chrMap);
			Assert::AreEqual(chrMap.Size(), chrcopy2.Size(), L"HashMap sizes not equal");
			Assert::IsFalse(chrMap.begin() == chrMap.end(), L"begin of non-empty HashMap equals end");
			Assert::IsFalse(chrcopy2.begin() == chrcopy2.end(), L"begin of non-empty HashMap equals end");


			// str test
			Library::HashMap<std::string, int> strcopy1(strMap);
			Assert::IsTrue(strMap.Size() == strcopy1.Size(), L"HashMap sizes not equal");

			strMap.Insert(std::pair<std::string, int>(s, 1));
			Library::HashMap<std::string, int> strcopy2(strMap);
			Assert::AreEqual(strMap.Size(), strcopy2.Size(), L"HashMap sizes not equal");
			Assert::IsFalse(strMap.begin() == strMap.end(), L"begin of non-empty HashMap equals end");
			Assert::IsFalse(strcopy2.begin() == strcopy2.end(), L"begin of non-empty HashMap equals end");
			
			
			// foo tests
			Library::HashMap<Foo, int> foocopy1(fooMap);
			Assert::IsTrue(fooMap.Size() == foocopy1.Size(), L"HashMap sizes not equal");

			fooMap.Insert(std::pair<Foo, int>(foo, 1));
			Library::HashMap<Foo, int> foocopy2(fooMap);
			Assert::AreEqual(fooMap.Size(), foocopy2.Size(), L"HashMap sizes not equal");
			Assert::IsFalse(fooMap.begin() == fooMap.end(), L"begin of non-empty HashMap equals end");
			Assert::IsFalse(foocopy2.begin() == foocopy2.end(), L"begin of non-empty HashMap equals end");
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			// int tests
			Library::HashMap<int, int> intcopy1;
			intcopy1 = intMap;
			Assert::IsTrue(intMap.Size() == intcopy1.Size(), L"HashMap sizes not equal");

			intMap.Insert(std::pair<int, int>(1, 1));
			Library::HashMap<int, int> intcopy2;
			intcopy2 = intMap;
			Assert::AreEqual(intMap.Size(), intcopy2.Size(), L"HashMap sizes not equal");
			Assert::IsFalse(intMap.begin() == intMap.end(), L"begin of non-empty HashMap equals end");
			Assert::IsFalse(intcopy2.begin() == intcopy2.end(), L"begin of non-empty HashMap equals end");

			// pointer tests
			Library::HashMap<int*, int> ptrcopy1;
			ptrcopy1 = ptrMap;
			Assert::IsTrue(ptrMap.Size() == ptrcopy1.Size(), L"HashMap sizes not equal");

			ptrMap.Insert(std::pair<int*, int>(&x, 1));
			Library::HashMap<int*, int> ptrcopy2;
			ptrcopy2 = ptrMap;
			Assert::AreEqual(ptrMap.Size(), ptrcopy2.Size(), L"HashMap sizes not equal");
			Assert::IsFalse(ptrMap.begin() == ptrMap.end(), L"begin of non-empty HashMap equals end");
			Assert::IsFalse(ptrcopy2.begin() == ptrcopy2.end(), L"begin of non-empty HashMap equals end");


			// char* tests
			Library::HashMap<char*, int> chrcopy1;
			chrcopy1 = chrMap;
			Assert::IsTrue(chrMap.Size() == chrcopy1.Size(), L"HashMap sizes not equal");

			chrMap.Insert(std::pair<char*, int>(a, 1));
			Library::HashMap<char*, int> chrcopy2;
			chrcopy2 = chrMap;
			Assert::AreEqual(chrMap.Size(), chrcopy2.Size(), L"HashMap sizes not equal");
			Assert::IsFalse(chrMap.begin() == chrMap.end(), L"begin of non-empty HashMap equals end");
			Assert::IsFalse(chrcopy2.begin() == chrcopy2.end(), L"begin of non-empty HashMap equals end");


			// string tests
			Library::HashMap<std::string, int> strcopy1;
			strcopy1 = strMap;
			Assert::IsTrue(strMap.Size() == strcopy1.Size(), L"HashMap sizes not equal");

			strMap.Insert(std::pair<std::string, int>(s, 1));
			Library::HashMap<std::string, int> strcopy2;
			strcopy2 = strMap;
			Assert::AreEqual(strMap.Size(), strcopy2.Size(), L"HashMap sizes not equal");
			Assert::IsFalse(strMap.begin() == strMap.end(), L"begin of non-empty HashMap equals end");
			Assert::IsFalse(strcopy2.begin() == strcopy2.end(), L"begin of non-empty HashMap equals end");


			// foo tests
			Library::HashMap<Foo, int> foocopy1;
			foocopy1 = fooMap;
			Assert::IsTrue(fooMap.Size() == foocopy1.Size(), L"HashMap sizes not equal");

			fooMap.Insert(std::pair<Foo, int>(foo, 1));
			Library::HashMap<Foo, int> foocopy2;
			foocopy2 = fooMap;
			Assert::AreEqual(fooMap.Size(), foocopy2.Size(), L"HashMap sizes not equal");
			Assert::IsFalse(fooMap.begin() == fooMap.end(), L"begin of non-empty HashMap equals end");
			Assert::IsFalse(foocopy2.begin() == foocopy2.end(), L"begin of non-empty HashMap equals end");
		}

		TEST_METHOD(TestFind)
		{
			// int tests
			Assert::IsTrue(intMap.Find(1) == intMap.end(), L"Find on empty HashMap does not return end");
			intMap.Insert(std::pair<int, int>(1, 1));
			Assert::IsTrue(intMap.Find(1) == intMap.begin(), L"Only value inserted into HashMap is not begin");
			Assert::IsFalse(intMap.Find(1) == intMap.end(), L"Find on existing value should not return end");
			Assert::AreEqual((*intMap.Find(1)).second, 1, L"Find returning incorrect value");

			// pointer tests
			Assert::IsTrue(ptrMap.Find(&x) == ptrMap.end(), L"Find on empty HashMap does not return end");
			ptrMap.Insert(std::pair<int*, int>(&x, 1));
			Assert::IsTrue(ptrMap.Find(&x) == ptrMap.begin(), L"Only value inserted into HashMap is not Begin");
			Assert::IsFalse(ptrMap.Find(&x) == ptrMap.end(), L"Find on existing value should not return end");
			Assert::AreEqual((*ptrMap.Find(&x)).second, 1, L"Find returning incorrect value");

			// char* tests
			Assert::IsTrue(chrMap.Find(c) == chrMap.end(), L"Find on empty HashMap does not return end");
			chrMap.Insert(std::pair<char*, int>(c, 1));
			Assert::IsTrue(chrMap.Find(c) == chrMap.begin(), L"Only value inserted into HashMap is not begin");
			Assert::IsFalse(chrMap.Find(c) == chrMap.end(), L"Find on existing value should not return end");
			Assert::AreEqual((*chrMap.Find(c)).second, 1, L"Find returning incorrect value");

			// string tests
			Assert::IsTrue(strMap.Find(s) == strMap.end(), L"Find on empty HashMap does not return end");
			strMap.Insert(std::pair<std::string, int>(s, 1));
			Assert::IsTrue(strMap.Find(s) == strMap.begin(), L"Only value inserted into HashMap is not begin");
			Assert::IsFalse(strMap.Find(s) == strMap.end(), L"Find on existing value should not return end");
			Assert::AreEqual((*strMap.Find(s)).second, 1, L"Find returning incorrect value");

			// foo tests
			Assert::IsTrue(fooMap.Find(foo) == fooMap.end(), L"Find on empty HashMap does not return end");
			fooMap.Insert(std::pair<Foo, int>(foo, 1));
			Assert::IsTrue(fooMap.Find(foo) == fooMap.begin(), L"Only value inserted into HashMap is not Begin");
			Assert::IsFalse(fooMap.Find(foo) == fooMap.end(), L"Find on existing value should not return end");
			Assert::AreEqual((*fooMap.Find(foo)).second, 1, L"Find returning incorrect value");
		}

		TEST_METHOD(TestInsert)
		{
			// int tests
			auto intInsert = intMap.Insert(std::pair<int, int>(1, 1));
			Assert::IsTrue(intInsert == intMap.begin(), L"Inserting first element should return begin");
			
			intMap.Insert(std::pair<int, int>(10, 1));
			Assert::IsTrue(intMap.ContainsKey(10), L"Key doesn't exist after inserting");

			
			// pointer tests
			auto ptrInsert = ptrMap.Insert(std::pair<int*, int>(&x, 1));
			Assert::IsTrue(ptrInsert == ptrMap.begin(), L"Inserting first element should return begin");
			
			ptrMap.Insert(std::pair<int*, int>(&y, 1));
			Assert::IsTrue(ptrMap.ContainsKey(&y), L"Key doesn't exist after inserting");

			
			// char* tests
			auto chrInsert = chrMap.Insert(std::pair<char*, int>(a, 1));
			Assert::IsTrue(chrInsert == chrMap.begin(), L"Inserting first element should return begin");

			chrMap.Insert(std::pair<char*, int>(b, 1));
			Assert::IsTrue(chrMap.ContainsKey(b), L"Key doesn't exist after inserting");


			// string tests
			auto strInsert = strMap.Insert(std::pair<std::string, int>(s, 1));
			Assert::IsTrue(strInsert == strMap.begin(), L"Inserting first element should return begin");

			strMap.Insert(std::pair<std::string, int>(t, 1));
			Assert::IsTrue(strMap.ContainsKey(t), L"Key doesn't exist after inserting");

			// foo tests
			auto fooInsert = fooMap.Insert(std::pair<Foo, int>(foo, 1));
			Assert::IsTrue(fooInsert == fooMap.begin(), L"Inserting first element should return begin");

			fooMap.Insert(std::pair<Foo, int>(bar, 1));
			Assert::IsTrue(fooMap.ContainsKey(bar), L"Key doesn't exist after inserting");
		}

		TEST_METHOD(TestRemove)
		{
			// int tests
			Assert::IsFalse(intMap.ContainsKey(1), L"Empty HashMap should not contain any keys");
			
			std::uint32_t intMapSize = intMap.Size();
			intMap.Insert(std::pair<const int, int>(1, 1));
			Assert::IsTrue(intMap.ContainsKey(1), L"Key doesn't exist in HashMap after inserting");
			Assert::AreNotEqual(intMapSize, intMap.Size(), L"Size not changing after inserting into HashMap");
			
			intMapSize = intMap.Size();
			intMap.Remove(1);
			Assert::IsFalse(intMap.ContainsKey(1), L"Key still exists in HashMap after removing");
			Assert::AreNotEqual(intMapSize, intMap.Size(), L"Size not changing after removing from HashMap");
			
			intMapSize = intMap.Size();
			intMap.Remove(1);
			Assert::AreEqual(intMapSize, intMap.Size(), L"Size should not change after removing non-existent key");


			// pointer tests
			Assert::IsFalse(ptrMap.ContainsKey(&x), L"Empty HashMap should not contain any keys");

			std::uint32_t ptrMapSize = ptrMap.Size();
			ptrMap.Insert(std::pair<int*, int>(&x, 1));
			Assert::IsTrue(ptrMap.ContainsKey(&x), L"Key doesn't exist in HashMap after inserting");
			Assert::AreNotEqual(ptrMapSize, ptrMap.Size(), L"Size not changing after inserting into HashMap");

			ptrMapSize = ptrMap.Size();
			ptrMap.Remove(&x);
			Assert::IsFalse(ptrMap.ContainsKey(&x), L"Key still exists in HashMap after removing");
			Assert::AreNotEqual(ptrMapSize, ptrMap.Size(), L"Size not changing after removing from HashMap");

			ptrMapSize = ptrMap.Size();
			ptrMap.Remove(&x);
			Assert::AreEqual(ptrMapSize, ptrMap.Size(), L"Size should not change after removing non-existent key");


			// char* tests
			Assert::IsFalse(chrMap.ContainsKey(a), L"Empty HashMap should not contain any keys");

			std::uint32_t chrMapSize = chrMap.Size();
			chrMap.Insert(std::pair<char*, int>(a, 1));
			Assert::IsTrue(chrMap.ContainsKey(a), L"Key doesn't exist in HashMap after inserting");
			Assert::AreNotEqual(chrMapSize, chrMap.Size(), L"Size not changing after inserting into HashMap");

			chrMapSize = chrMap.Size();
			chrMap.Remove(a);
			Assert::IsFalse(chrMap.ContainsKey(a), L"Key still exists in HashMap after removing");
			Assert::AreNotEqual(chrMapSize, chrMap.Size(), L"Size not changing after removing from HashMap");

			chrMapSize = chrMap.Size();
			chrMap.Remove(a);
			Assert::AreEqual(chrMapSize, chrMap.Size(), L"Size should not change after removing non-existent key");

			// string tests
			Assert::IsFalse(strMap.ContainsKey(s), L"Empty HashMap should not contain any keys");

			std::uint32_t strMapSize = strMap.Size();
			strMap.Insert(std::pair<std::string, int>(s, 1));
			Assert::IsTrue(strMap.ContainsKey(s), L"Key doesn't exist in HashMap after inserting");
			Assert::AreNotEqual(strMapSize, strMap.Size(), L"Size not changing after inserting into HashMap");

			strMapSize = strMap.Size();
			strMap.Remove(s);
			Assert::IsFalse(strMap.ContainsKey(s), L"Key still exists in HashMap after removing");
			Assert::AreNotEqual(strMapSize, strMap.Size(), L"Size not changing after removing from HashMap");

			strMapSize = strMap.Size();
			strMap.Remove(s);
			Assert::AreEqual(strMapSize, strMap.Size(), L"Size should not change after removing non-existent key");


			// foo tests
			Assert::IsFalse(fooMap.ContainsKey(foo), L"Empty HashMap should not contain any keys");

			std::uint32_t fooMapSize = fooMap.Size();
			fooMap.Insert(std::pair<Foo, int>(foo, 1));
			Assert::IsTrue(fooMap.ContainsKey(foo), L"Key doesn't exist in HashMap after inserting");
			Assert::AreNotEqual(fooMapSize, fooMap.Size(), L"Size not changing after inserting into HashMap");

			fooMapSize = fooMap.Size();
			fooMap.Remove(foo);
			Assert::IsFalse(fooMap.ContainsKey(foo), L"Key still exists in HashMap after removing");
			Assert::AreNotEqual(fooMapSize, fooMap.Size(), L"Size not changing after removing from HashMap");

			fooMapSize = fooMap.Size();
			fooMap.Remove(foo);
			Assert::AreEqual(fooMapSize, fooMap.Size(), L"Size should not change after removing non-existent key");
		}

		TEST_METHOD(TestIndexOperator)
		{
			// int tests
			std::uint32_t intMapSize = intMap.Size();
			auto& intMapVal = intMap[1];
			Assert::AreNotEqual(intMapSize, intMap.Size(), L"HashMap Size not increasing after indexing a non-existent key");

			intMap.Insert(std::pair<int, int>(1, 1));
			Assert::AreNotEqual(intMap[1], 1, L"Incorrect value returned with index operator");

			intMapVal = 1;
			Assert::AreEqual(1, intMap[1], L"HashMapValue not changed when assigned from index operator");

			const Library::HashMap<int, int> constIntMap(intMap);
			Assert::ExpectException<std::exception>([&] { constIntMap[2]; }, L"Indexing nonexistent key value");

			// pointer tests
			std::uint32_t ptrMapSize = ptrMap.Size();
			auto& ptrMapVal = ptrMap[&x];
			Assert::AreNotEqual(ptrMapSize, ptrMap.Size(), L"HashMap Size not increasing after indexing a non-existent key");

			ptrMap.Insert(std::pair<int*, int>(&x, 1));
			Assert::AreNotEqual(ptrMap[&x], 1, L"Incorrect value returned with index operator");

			ptrMapVal = 1;
			Assert::AreEqual(ptrMap[&x], 1, L"HashMapValue not changed when assigned from index operator");


			// char* tests
			std::uint32_t chrMapSize = chrMap.Size();
			auto& chrMapVal = chrMap[a];
			Assert::AreNotEqual(chrMapSize, chrMap.Size(), L"HashMap Size not increasing after indexing a non-existent key");

			chrMap.Insert(std::pair<char*, int>(a, 1));
			Assert::AreNotEqual(chrMap[a], 1, L"Incorrect value returned with index operator");

			chrMapVal = 1;
			Assert::AreEqual(chrMap[a], 1, L"HashMapValue not changed when assigned from index operator");


			// string tests
			std::uint32_t strMapSize = strMap.Size();
			auto& strMapVal = strMap[s];
			Assert::AreNotEqual(strMapSize, strMap.Size(), L"HashMap Size not increasing after indexing a non-existent key");

			strMap.Insert(std::pair<std::string, int>(s, 1));
			Assert::AreNotEqual(strMap[s], 1, L"Incorrect value returned with index operator");

			strMapVal = 1;
			Assert::AreEqual(strMap[s], 1, L"HashMapValue not changed when assigned from index operator");

			// foo tests
			std::uint32_t fooMapSize = fooMap.Size();
			auto& fooMapVal = fooMap[foo];
			Assert::AreNotEqual(fooMapSize, fooMap.Size(), L"HashMap Size not increasing after indexing a non-existent key");

			fooMap.Insert(std::pair<Foo, int>(foo, 1));
			Assert::AreNotEqual(fooMap[foo], 1, L"Incorrect value returned with index operator");

			fooMapVal = 1;
			Assert::AreEqual(fooMap[foo], 1, L"HashMapValue not changed when assigned from index operator");
		}

		TEST_METHOD(TestBegin)
		{
			// int tests
			Assert::IsTrue(intMap.begin() == intMap.end(), L"begin does not equal end on empty HashMap");

			std::pair<const int, int> intPair(1, 1);
			intMap.Insert(intPair);
			Assert::IsTrue(intPair == *(intMap.begin()));

			intMap.Remove(1);
			Assert::IsTrue(intMap.begin() == intMap.end(), L"begin does not equal end on empty HashMap");


			// pointer tests
			Assert::IsTrue(ptrMap.begin() == ptrMap.end(), L"begin does not equal end on empty HashMap");

			std::pair<int* const, int> ptrPair(&x, 1);
			ptrMap.Insert(ptrPair);
			Assert::IsTrue(ptrPair == *(ptrMap.begin()));

			ptrMap.Remove(&x);
			Assert::IsTrue(ptrMap.begin() == ptrMap.end(), L"begin does not equal end on empty HashMap");


			// char* tests
			Assert::IsTrue(chrMap.begin() == chrMap.end(), L"begin does not equal end on empty HashMap");

			std::pair<char* const, int> chrPair(a, 1);
			chrMap.Insert(chrPair);
			Assert::IsTrue(chrPair == *(chrMap.begin()));

			chrMap.Remove(a);
			Assert::IsTrue(chrMap.begin() == chrMap.end(), L"begin does not equal end on empty HashMap");


			// string tests
			Assert::IsTrue(strMap.begin() == strMap.end(), L"begin does not equal end on empty HashMap");

			std::pair<const std::string, int> strPair(s, 1);
			strMap.Insert(strPair);
			Assert::IsTrue(strPair == *(strMap.begin()));

			strMap.Remove(s);
			Assert::IsTrue(strMap.begin() == strMap.end(), L"begin does not equal end on empty HashMap");


			// foo tests
			Assert::IsTrue(fooMap.begin() == fooMap.end(), L"begin does not equal end on empty HashMap");

			std::pair<const Foo, int> fooPair(foo, 1);
			fooMap.Insert(fooPair);
			Assert::IsTrue(fooPair == *(fooMap.begin()));

			fooMap.Remove(foo);
			Assert::IsTrue(fooMap.begin() == fooMap.end(), L"begin does not equal end on empty HashMap");
		}

		TEST_METHOD(TestEnd)
		{
			// int tests
			Assert::IsTrue(intMap.begin() == intMap.end(), L"begin should be equivalent to end on empty HashMap");
			intMap.Insert(std::pair<int, int>(1, 1));
			Assert::IsFalse(intMap.begin() == intMap.end(), L"begin should not be equivalent to end on non-empty HashMap");
			intMap.Remove(1);
			Assert::IsTrue(intMap.begin() == intMap.end(), L"begin should be equivalent to end on empty HashMap");
			auto intFunc = [&] { *intMap.end(); };
			Assert::ExpectException<std::exception>(intFunc, L"Dereferencing end of HashMap should throw exception");


			// pointer tests
			Assert::IsTrue(ptrMap.begin() == ptrMap.end(), L"begin should be equivalent to end on empty HashMap");
			ptrMap.Insert(std::pair<int*, int>(&x, 1));
			Assert::IsFalse(ptrMap.begin() == ptrMap.end(), L"begin should not be equivalent to end on non-empty HashMap");
			ptrMap.Remove(&x);
			Assert::IsTrue(ptrMap.begin() == ptrMap.end(), L"begin should be equivalent to end on empty HashMap");
			auto ptrFunc = [&] { *ptrMap.end(); };
			Assert::ExpectException<std::exception>(ptrFunc, L"Dereferencing end of HashMap should throw exception");


			// char* tests
			Assert::IsTrue(chrMap.begin() == chrMap.end(), L"begin should be equivalent to end on empty HashMap");
			chrMap.Insert(std::pair<char*, int>(a, 1));
			Assert::IsFalse(chrMap.begin() == chrMap.end(), L"begin should not be equivalent to end on non-empty HashMap");
			chrMap.Remove(a);
			Assert::IsTrue(chrMap.begin() == chrMap.end(), L"begin should be equivalent to end on empty HashMap");
			auto chrFunc = [&] { *chrMap.end(); };
			Assert::ExpectException<std::exception>(chrFunc, L"Dereferencing end of HashMap should throw exception");


			// string tests
			Assert::IsTrue(strMap.begin() == strMap.end(), L"begin should be equivalent to end on empty HashMap");
			strMap.Insert(std::pair<std::string, int>(s, 1));
			Assert::IsFalse(strMap.begin() == strMap.end(), L"begin should not be equivalent to end on non-empty HashMap");
			strMap.Remove(s);
			Assert::IsTrue(strMap.begin() == strMap.end(), L"begin should be equivalent to end on empty HashMap");
			auto strFunc = [&] { *strMap.end(); };
			Assert::ExpectException<std::exception>(strFunc, L"Dereferencing end of HashMap should throw exception");


			// foo tests
			Assert::IsTrue(fooMap.begin() == fooMap.end(), L"begin should be equivalent to end on empty HashMap");
			fooMap.Insert(std::pair<Foo, int>(foo, 1));
			Assert::IsFalse(fooMap.begin() == fooMap.end(), L"begin should not be equivalent to end on non-empty HashMap");
			fooMap.Remove(foo);
			Assert::IsTrue(fooMap.begin() == fooMap.end(), L"begin should be equivalent to end on empty HashMap");
			auto fooFunc = [&] { *fooMap.end(); };
			Assert::ExpectException<std::exception>(intFunc, L"Dereferencing end of HashMap should throw exception");
		}

		TEST_METHOD(TestClear)
		{
			// int tests
			Assert::AreEqual(intMap.Size(), 0U, L"HashMap Size should be zero when empty");
			intMap.Insert(std::pair<int, int>(1, 1));
			Assert::IsTrue(intMap.Size() > 0, L"HashMap Size should be non-zero when not empty");
			intMap.Clear();
			Assert::AreEqual(intMap.Size(), 0U, L"HashMap Size should be zero when cleared");
			intMap.Clear();
			Assert::AreEqual(intMap.Size(), 0U, L"HashMap Size should be zero when clearing an empty HashMap");


			// pointer tests
			Assert::AreEqual(ptrMap.Size(), 0U, L"HashMap Size should be zero when empty");
			ptrMap.Insert(std::pair<int*, int>(&x, 1));
			Assert::IsTrue(ptrMap.Size() > 0, L"HashMap Size should be non-zero when not empty");
			ptrMap.Clear();
			Assert::AreEqual(ptrMap.Size(), 0U, L"HashMap Size should be zero when cleared");
			ptrMap.Clear();
			Assert::AreEqual(ptrMap.Size(), 0U, L"HashMap Size should be zero when clearing an empty HashMap");


			// char* tests
			Assert::AreEqual(chrMap.Size(), 0U, L"HashMap Size should be zero when empty");
			chrMap.Insert(std::pair<char*, int>(a, 1));
			Assert::IsTrue(chrMap.Size() > 0, L"HashMap Size should be non-zero when not empty");
			chrMap.Clear();
			Assert::AreEqual(chrMap.Size(), 0U, L"HashMap Size should be zero when cleared");
			chrMap.Clear();
			Assert::AreEqual(chrMap.Size(), 0U, L"HashMap Size should be zero when clearing an empty HashMap");


			// string tests
			Assert::AreEqual(strMap.Size(), 0U, L"HashMap Size should be zero when empty");
			strMap.Insert(std::pair<std::string, int>(s, 1));
			Assert::IsTrue(strMap.Size() > 0, L"HashMap Size should be non-zero when not empty");
			strMap.Clear();
			Assert::AreEqual(strMap.Size(), 0U, L"HashMap Size should be zero when cleared");
			strMap.Clear();
			Assert::AreEqual(strMap.Size(), 0U, L"HashMap Size should be zero when clearing an empty HashMap");
		}

		TEST_METHOD(TestSize)
		{
			// int tests
			Assert::AreEqual(intMap.Size(), 0U, L"Length of empty HashMap should be zero");
			
			intMap.Insert(std::pair<int, int>(1, 1));
			Assert::AreEqual(intMap.Size(), 1U, L"Size should be one after inserting one item");
			
			intMap.Insert(std::pair<int, int>(2, 2));
			Assert::AreEqual(intMap.Size(), 2U, L"Size should increase when adding a value");

			intMap.Remove(10);
			Assert::AreEqual(intMap.Size(), 2U, L"Size should not change when removing a non-existent value");

			intMap.Remove(1);
			Assert::AreEqual(intMap.Size(), 1U, L"Size should decrease when removing an item");

			intMap.Clear();
			Assert::AreEqual(intMap.Size(), 0U, L"Size should be zero after clearing");


			// pointer tests
			Assert::AreEqual(ptrMap.Size(), 0U, L"Length of empty HashMap should be zero");

			ptrMap.Insert(std::pair<int*, int>(&x, 1));
			Assert::AreEqual(ptrMap.Size(), 1U, L"Size should be one after inserting one item");

			ptrMap.Insert(std::pair<int*, int>(&y, 2));
			Assert::AreEqual(ptrMap.Size(), 2U, L"Size should increase when adding a value");

			ptrMap.Remove(&z);
			Assert::AreEqual(ptrMap.Size(), 2U, L"Size should not change when removing a non-existent value");

			ptrMap.Remove(&x);
			Assert::AreEqual(ptrMap.Size(), 1U, L"Size should decrease when removing an item");

			ptrMap.Clear();
			Assert::AreEqual(ptrMap.Size(), 0U, L"Size should be zero after clearing");


			// char* tests
			Assert::AreEqual(chrMap.Size(), 0U, L"Length of empty HashMap should be zero");

			chrMap.Insert(std::pair<char*, int>(a, 1));
			Assert::AreEqual(chrMap.Size(), 1U, L"Size should be one after inserting one item");

			chrMap.Insert(std::pair<char*, int>(b, 2));
			Assert::AreEqual(chrMap.Size(), 2U, L"Size should increase when adding a value");

			chrMap.Remove(c);
			Assert::AreEqual(chrMap.Size(), 2U, L"Size should not change when removing a non-existent value");

			chrMap.Remove(a);
			Assert::AreEqual(chrMap.Size(), 1U, L"Size should decrease when removing an item");

			chrMap.Clear();
			Assert::AreEqual(chrMap.Size(), 0U, L"Size should be zero after clearing");


			// string tests
			Assert::AreEqual(strMap.Size(), 0U, L"Length of empty HashMap should be zero");

			strMap.Insert(std::pair<std::string, int>(s, 1));
			Assert::AreEqual(strMap.Size(), 1U, L"Size should be one after inserting one item");

			strMap.Insert(std::pair<std::string, int>(t, 2));
			Assert::AreEqual(strMap.Size(), 2U, L"Size should increase when adding a value");

			strMap.Remove(u);
			Assert::AreEqual(strMap.Size(), 2U, L"Size should not change when removing a non-existent value");

			strMap.Remove(s);
			Assert::AreEqual(strMap.Size(), 1U, L"Size should decrease when removing an item");

			strMap.Clear();
			Assert::AreEqual(strMap.Size(), 0U, L"Size should be zero after clearing");


			// foo tests
			Assert::AreEqual(fooMap.Size(), 0U, L"Length of empty HashMap should be zero");

			fooMap.Insert(std::pair<Foo, int>(foo, 1));
			Assert::AreEqual(fooMap.Size(), 1U, L"Size should be one after inserting one item");

			fooMap.Insert(std::pair<Foo, int>(bar, 2));
			Assert::AreEqual(fooMap.Size(), 2U, L"Size should increase when adding a value");

			fooMap.Remove(gar);
			Assert::AreEqual(fooMap.Size(), 2U, L"Size should not change when removing a non-existent value");

			fooMap.Remove(foo);
			Assert::AreEqual(fooMap.Size(), 1U, L"Size should decrease when removing an item");

			fooMap.Clear();
			Assert::AreEqual(fooMap.Size(), 0U, L"Size should be zero after clearing");
		}

		TEST_METHOD(TestContainsKey)
		{
			// int tests
			Assert::IsFalse(intMap.ContainsKey(1), L"Empty map should not contain any keys");

			intMap.Insert(std::pair<int, int>(1, 1));
			Assert::IsFalse(intMap.ContainsKey(10), L"Map should not contain a key that hasn't been inserted");
			Assert::IsTrue(intMap.ContainsKey(1), L"HashMap does not contain a key that has been inserted");

			intMap.Remove(1);
			Assert::IsFalse(intMap.ContainsKey(1), L"Map should not contain a key that has been removed");


			// pointer tests
			Assert::IsFalse(ptrMap.ContainsKey(&x), L"Empty map should not contain any keys");

			ptrMap.Insert(std::pair<int*, int>(&x, 1));
			Assert::IsFalse(ptrMap.ContainsKey(&y), L"Map should not contain a key that hasn't been inserted");
			Assert::IsTrue(ptrMap.ContainsKey(&x), L"HashMap does not contain a key that has been inserted");

			ptrMap.Remove(&x);
			Assert::IsFalse(ptrMap.ContainsKey(&x), L"Map should not contain a key that has been removed");


			// char* tests
			Assert::IsFalse(chrMap.ContainsKey(a), L"Empty map should not contain any keys");

			chrMap.Insert(std::pair<char*, int>(a, 1));
			Assert::IsFalse(chrMap.ContainsKey(b), L"Map should not contain a key that hasn't been inserted");
			Assert::IsTrue(chrMap.ContainsKey(a), L"HashMap does not contain a key that has been inserted");

			chrMap.Remove(a);
			Assert::IsFalse(chrMap.ContainsKey(a), L"Map should not contain a key that has been removed");


			// string tests
			Assert::IsFalse(strMap.ContainsKey(s), L"Empty map should not contain any keys");

			strMap.Insert(std::pair<std::string, int>(s, 1));
			Assert::IsFalse(strMap.ContainsKey(t), L"Map should not contain a key that hasn't been inserted");
			Assert::IsTrue(strMap.ContainsKey(s), L"HashMap does not contain a key that has been inserted");

			strMap.Remove(s);
			Assert::IsFalse(strMap.ContainsKey(s), L"Map should not contain a key that has been removed");


			// foo tests
			Assert::IsFalse(fooMap.ContainsKey(foo), L"Empty map should not contain any keys");

			fooMap.Insert(std::pair<Foo, int>(foo, 1));
			Assert::IsFalse(fooMap.ContainsKey(bar), L"Map should not contain a key that hasn't been inserted");
			Assert::IsTrue(fooMap.ContainsKey(foo), L"HashMap does not contain a key that has been inserted");

			fooMap.Remove(foo);
			Assert::IsFalse(fooMap.ContainsKey(foo), L"Map should not contain a key that has been removed");
		}

		TEST_METHOD(TestIteratorCopyConstructor)
		{
			// int tests
			auto interator_1(intMap.begin());
			Assert::IsTrue(interator_1 == intMap.begin() && interator_1 == intMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");
			
			intMap.Insert(std::pair<int, int>(1, 1));
			auto interator_2(intMap.begin());
			Assert::IsTrue(interator_2 == intMap.begin() && interator_2 != intMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto interator_3(intMap.end());
			Assert::IsTrue(interator_3 != intMap.begin() && interator_3 == intMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto interator_4(intMap.Find(1));
			intMap.Clear();
			Assert::IsTrue(interator_4 != intMap.Find(1), L"Iterator set to HashMap value should not be equivalent to a Find call of that value after Clear");


			// pointer tests
			auto pointerator_1(ptrMap.begin());
			Assert::IsTrue(pointerator_1 == ptrMap.begin() && pointerator_1 == ptrMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");

			ptrMap.Insert(std::pair<int*, int>(&x, 1));
			auto pointerator_2(ptrMap.begin());
			Assert::IsTrue(pointerator_2 == ptrMap.begin() && pointerator_2 != ptrMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto pointerator_3(ptrMap.end());
			Assert::IsTrue(pointerator_3 != ptrMap.begin() && pointerator_3 == ptrMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto pointerator_4(ptrMap.Find(&x));
			ptrMap.Clear();
			Assert::IsTrue(pointerator_4 != ptrMap.Find(&x), L"Iterator set to HashMap value should not be equivalent to a Find call of that value after Clear");


			// char* tests
			auto charterator_1(chrMap.begin());
			Assert::IsTrue(charterator_1 == chrMap.begin() && charterator_1 == chrMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");

			chrMap.Insert(std::pair<char*, int>(a, 1));
			auto charterator_2(chrMap.begin());
			Assert::IsTrue(charterator_2 == chrMap.begin() && charterator_2 != chrMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto charterator_3(chrMap.end());
			Assert::IsTrue(charterator_3 != chrMap.begin() && charterator_3 == chrMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto charterator_4(chrMap.Find(a));
			chrMap.Clear();
			Assert::IsTrue(charterator_4 != chrMap.Find(a), L"Iterator set to HashMap value should not be equivalent to a Find call of that value after Clear");


			// string tests
			auto stringerator_1(strMap.begin());
			Assert::IsTrue(stringerator_1 == strMap.begin() && stringerator_1 == strMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");

			strMap.Insert(std::pair<std::string, int>(s, 1));
			auto stringerator_2(strMap.begin());
			Assert::IsTrue(stringerator_2 == strMap.begin() && stringerator_2 != strMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto stringerator_3(strMap.end());
			Assert::IsTrue(stringerator_3 != strMap.begin() && stringerator_3 == strMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto stringerator_4(strMap.Find(s));
			strMap.Clear();
			Assert::IsTrue(stringerator_4 != strMap.Find(s), L"Iterator set to HashMap value should not be equivalent to a Find call of that value after Clear");


			// foo tests
			auto footerator_1(fooMap.begin());
			Assert::IsTrue(footerator_1 == fooMap.begin() && footerator_1 == fooMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");

			fooMap.Insert(std::pair<Foo, int>(foo, 1));
			auto footerator_2(fooMap.begin());
			Assert::IsTrue(footerator_2 == fooMap.begin() && footerator_2 != fooMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto footerator_3(fooMap.end());
			Assert::IsTrue(footerator_3 != fooMap.begin() && footerator_3 == fooMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto footerator_4(fooMap.Find(foo));
			fooMap.Clear();
			Assert::IsTrue(footerator_4 != fooMap.Find(foo), L"Iterator set to HashMap value should not be equivalent to a Find call of that value after Clear");
		}

		TEST_METHOD(TestIteratorAssignmentOperator)
		{
			// int tests
			auto interator_1 = intMap.begin();
			Assert::IsTrue(interator_1 == intMap.begin() && interator_1 == intMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");

			intMap.Insert(std::pair<int, int>(1, 1));
			auto interator_2 = intMap.begin();
			Assert::IsTrue(interator_2 == intMap.begin() && interator_2 != intMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto interator_3 = intMap.end();
			Assert::IsTrue(interator_3 != intMap.begin() && interator_3 == intMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto interator_4 = intMap.Find(1);
			intMap.Clear();
			Assert::IsTrue(interator_4 != intMap.Find(1), L"Iterator set to HashMap value should not be equivalent to a Find call of that value after Clear");


			// pointer tests
			auto pointerator_1 = ptrMap.begin();
			Assert::IsTrue(pointerator_1 == ptrMap.begin() && pointerator_1 == ptrMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");

			ptrMap.Insert(std::pair<int*, int>(&x, 1));
			auto pointerator_2 = ptrMap.begin();
			Assert::IsTrue(pointerator_2 == ptrMap.begin() && pointerator_2 != ptrMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto pointerator_3 = ptrMap.end();
			Assert::IsTrue(pointerator_3 != ptrMap.begin() && pointerator_3 == ptrMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto pointerator_4 = ptrMap.Find(&x);
			ptrMap.Clear();
			Assert::IsTrue(pointerator_4 != ptrMap.Find(&x), L"Iterator set to HashMap value should not be equivalent to a Find call of that value after Clear");


			// char* tests
			auto charterator_1 = chrMap.begin();
			Assert::IsTrue(charterator_1 == chrMap.begin() && charterator_1 == chrMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");

			chrMap.Insert(std::pair<char*, int>(a, 1));
			auto charterator_2 = chrMap.begin();
			Assert::IsTrue(charterator_2 == chrMap.begin() && charterator_2 != chrMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto charterator_3 = chrMap.end();
			Assert::IsTrue(charterator_3 != chrMap.begin() && charterator_3 == chrMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto charterator_4 = chrMap.Find(a);
			chrMap.Clear();
			Assert::IsTrue(charterator_4 != chrMap.Find(a), L"Iterator set to HashMap value should not be equivalent to a Find call of that value after Clear");


			// string tests
			auto stringerator_1 = strMap.begin();
			Assert::IsTrue(stringerator_1 == strMap.begin() && stringerator_1 == strMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");

			strMap.Insert(std::pair<std::string, int>(s, 1));
			auto stringerator_2 = strMap.begin();
			Assert::IsTrue(stringerator_2 == strMap.begin() && stringerator_2 != strMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto stringerator_3 = strMap.end();
			Assert::IsTrue(stringerator_3 != strMap.begin() && stringerator_3 == strMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto stringerator_4 = strMap.Find(s);
			strMap.Clear();
			Assert::IsTrue(stringerator_4 != strMap.Find(s), L"Iterator set to HashMap value should not be equivalent to a Find call of that value after Clear");


			// foo tests
			auto footerator_1 = fooMap.begin();
			Assert::IsTrue(footerator_1 == fooMap.begin() && footerator_1 == fooMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");

			fooMap.Insert(std::pair<Foo, int>(foo, 1));
			auto footerator_2 = fooMap.begin();
			Assert::IsTrue(footerator_2 == fooMap.begin() && footerator_2 != fooMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto footerator_3 = fooMap.end();
			Assert::IsTrue(footerator_3 != fooMap.begin() && footerator_3 == fooMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto footerator_4 = fooMap.Find(foo);
			fooMap.Clear();
			Assert::IsTrue(footerator_4 != fooMap.Find(foo), L"Iterator set to HashMap value should not be equivalent to a Find call of that value after Clear");
		}

		TEST_METHOD(TestIteratorIncrementOperator)
		{
			// int tests
			intMap.Insert(std::pair<int, int>(1, 1));
			intMap.Insert(std::pair<int, int>(2, 2));
			auto interator = intMap.begin();
			Assert::IsTrue(interator == intMap.begin() && ++interator != intMap.end(), 
				L"Incrementing past first element should not return end when other items exist");
			Assert::IsTrue(++interator == intMap.end() && ++interator == intMap.end(), 
				L"Incrementing past end should still return end");


			// pointer tests
			ptrMap.Insert(std::pair<int*, int>(&x, 1));
			ptrMap.Insert(std::pair<int*, int>(&y, 2));
			auto pointerator = ptrMap.begin();
			Assert::IsTrue(pointerator == ptrMap.begin() && ++pointerator != ptrMap.end(), 
				L"Incrementing past first element should not return end when other items exist");
			Assert::IsTrue(++pointerator == ptrMap.end() && ++pointerator == ptrMap.end(), 
				L"Incrementing past end should still return end");


			// char* tests
			chrMap.Insert(std::pair<char*, int>(a, 1));
			chrMap.Insert(std::pair<char*, int>(b, 2));
			auto charterator = chrMap.begin();
			Assert::IsTrue(charterator == chrMap.begin() && ++charterator != chrMap.end(), 
				L"Incrementing past first element should not return end when other items exist");
			Assert::IsTrue(++charterator == chrMap.end() && ++charterator == chrMap.end(), 
				L"Incrementing past end should still return end");


			// string tests
			strMap.Insert(std::pair<std::string, int>(s, 1));
			strMap.Insert(std::pair<std::string, int>(t, 2));
			auto stringerator = strMap.begin();
			Assert::IsTrue(stringerator == strMap.begin() && ++stringerator != strMap.end(), 
				L"Incrementing past first element should not return end when other items exist");
			Assert::IsTrue(++stringerator == strMap.end() && ++stringerator == strMap.end(), 
				L"Incrementing past end should still return end");


			// foo tests
			fooMap.Insert(std::pair<Foo, int>(foo, 1));
			fooMap.Insert(std::pair<Foo, int>(bar, 2));
			auto footerator = fooMap.begin();
			Assert::IsTrue(footerator == fooMap.begin() && ++footerator != fooMap.end(), 
				L"Incrementing past first element should not return end when other items exist");
			Assert::IsTrue(++footerator == fooMap.end() && ++footerator == fooMap.end(), 
				L"Incrementing past end should still return end");
		}

		TEST_METHOD(TestIteratorDereferenceOperator)
		{
			// int tests
			auto intFunc = [&]{ *intMap.begin(); };
			Assert::ExpectException<std::exception>(intFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			intMap.Insert(std::pair<int, int>(1, 1));
			Assert::AreEqual(1, (*intMap.begin()).first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, (*intMap.begin()).second, L"Dereferencing iterator does not yield accurate value");


			// pointer tests
			auto ptrFunc = [&] { *ptrMap.begin(); };
			Assert::ExpectException<std::exception>(ptrFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			ptrMap.Insert(std::pair<int*, int>(&x, 1));
			Assert::AreEqual(&x, (*ptrMap.begin()).first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, (*ptrMap.begin()).second, L"Dereferencing iterator does not yield accurate value");


			// char* tests
			auto chrFunc = [&] { *chrMap.begin(); };
			Assert::ExpectException<std::exception>(chrFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			chrMap.Insert(std::pair<char*, int>(a, 1));
			Assert::AreEqual(a, (*chrMap.begin()).first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, (*chrMap.begin()).second, L"Dereferencing iterator does not yield accurate value");


			// string tests
			auto strFunc = [&] { *strMap.begin(); };
			Assert::ExpectException<std::exception>(strFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			strMap.Insert(std::pair<std::string, int>(s, 1));
			Assert::AreEqual(s, (*strMap.begin()).first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, (*strMap.begin()).second, L"Dereferencing iterator does not yield accurate value");


			// foo tests
			auto fooFunc = [&] { *fooMap.begin(); };
			Assert::ExpectException<std::exception>(fooFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			fooMap.Insert(std::pair<Foo, int>(foo, 1));
			Assert::IsTrue(foo == (*fooMap.begin()).first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, (*fooMap.begin()).second, L"Dereferencing iterator does not yield accurate value");
		}

		TEST_METHOD(TestIteratorArrowOperator)
		{
			// int tests
			auto intFunc = [&] { *intMap.begin(); };
			Assert::ExpectException<std::exception>(intFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			intMap.Insert(std::pair<int, int>(1, 1));
			Assert::AreEqual(1,  intMap.begin()->first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, intMap.begin()->second, L"Dereferencing iterator does not yield accurate value");


			// pointer tests
			auto ptrFunc = [&] { *ptrMap.begin(); };
			Assert::ExpectException<std::exception>(ptrFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			ptrMap.Insert(std::pair<int*, int>(&x, 1));
			Assert::AreEqual(&x, ptrMap.begin()->first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, ptrMap.begin()->second, L"Dereferencing iterator does not yield accurate value");


			// char* tests
			auto chrFunc = [&] { *chrMap.begin(); };
			Assert::ExpectException<std::exception>(chrFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			chrMap.Insert(std::pair<char*, int>(a, 1));
			Assert::AreEqual(a, chrMap.begin()->first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, chrMap.begin()->second, L"Dereferencing iterator does not yield accurate value");


			// string tests
			auto strFunc = [&] { *strMap.begin(); };
			Assert::ExpectException<std::exception>(strFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			strMap.Insert(std::pair<std::string, int>(s, 1));
			Assert::AreEqual(s, strMap.begin()->first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, strMap.begin()->second, L"Dereferencing iterator does not yield accurate value");


			// foo tests
			auto fooFunc = [&] { *fooMap.begin(); };
			Assert::ExpectException<std::exception>(fooFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			fooMap.Insert(std::pair<Foo, int>(foo, 1));
			Assert::IsTrue(foo == fooMap.begin()->first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, fooMap.begin()->second, L"Dereferencing iterator does not yield accurate value");
		}

		static _CrtMemState sStartMemState;
	};

	_CrtMemState HashMapTest::sStartMemState;
}
