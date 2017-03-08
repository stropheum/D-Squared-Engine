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
			initializeLeakDetection();
			intMap.clear();
			ptrMap.clear();
			chrMap.clear();
			strMap.clear();
			fooMap.clear();
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
			finalizeLeakDetection();
		}

		TEST_METHOD(TestTemplateSpecialization)
		{
			// int tests
			intMap.insert(std::pair<int, int>(1, 1));
			Assert::IsTrue(intMap.containsKey(1), L"intMap does not contain inserted key");


			// ptr tests
			ptrMap.insert(std::pair<int*, int>(&x, 1));
			Assert::IsTrue(ptrMap.containsKey(&x), L"ptrMap does not contain inserted key");


			// chr tests
			chrMap.insert(std::pair<char*, int>(c, 1));
			Assert::IsTrue(chrMap.containsKey(c), L"charMap does not contain inserted key");


			// str tests
			strMap.insert(std::pair<std::string, int>(s, 1));
			Assert::IsTrue(strMap.containsKey(s), L"stringMap does not contain inserted key");


			// foo tests
			fooMap.insert(std::pair<Foo, int>(foo, 1));
			Assert::IsTrue(fooMap.containsKey(foo), L"fooMap does not contain inserted key");
		}

		TEST_METHOD(TestCopyConstructor)
		{
			// int tests
			Library::HashMap<int, int> intcopy1(intMap);
			Assert::IsTrue(intMap.size() == intcopy1.size(), L"HashMap sizes not equal");

			intMap.insert(std::pair<int, int>(1, 1));
			Library::HashMap<int, int> intcopy2(intMap);
			Assert::AreEqual(intMap.size(), intcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(intMap.begin() == intMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(intcopy2.begin() == intcopy2.end(), L"Begin of non-empty HashMap equals end");

			// ptr tests
			Library::HashMap<int*, int> ptrcopy1(ptrMap);
			Assert::IsTrue(ptrMap.size() == ptrcopy1.size(), L"HashMap sizes not equal");

			ptrMap.insert(std::pair<int*, int>(&x, 1));
			Library::HashMap<int*, int> ptrcopy2(ptrMap);
			Assert::AreEqual(ptrMap.size(), ptrcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(ptrMap.begin() == ptrMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(ptrcopy2.begin() == ptrcopy2.end(), L"Begin of non-empty HashMap equals end");


			// char* tests
			Library::HashMap<char*, int> chrcopy1(chrMap);
			Assert::IsTrue(chrMap.size() == chrcopy1.size(), L"HashMap sizes not equal");

			chrMap.insert(std::pair<char*, int>(a, 1));
			Library::HashMap<char*, int> chrcopy2(chrMap);
			Assert::AreEqual(chrMap.size(), chrcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(chrMap.begin() == chrMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(chrcopy2.begin() == chrcopy2.end(), L"Begin of non-empty HashMap equals end");


			// str test
			Library::HashMap<std::string, int> strcopy1(strMap);
			Assert::IsTrue(strMap.size() == strcopy1.size(), L"HashMap sizes not equal");

			strMap.insert(std::pair<std::string, int>(s, 1));
			Library::HashMap<std::string, int> strcopy2(strMap);
			Assert::AreEqual(strMap.size(), strcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(strMap.begin() == strMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(strcopy2.begin() == strcopy2.end(), L"Begin of non-empty HashMap equals end");
			
			
			// foo tests
			Library::HashMap<Foo, int> foocopy1(fooMap);
			Assert::IsTrue(fooMap.size() == foocopy1.size(), L"HashMap sizes not equal");

			fooMap.insert(std::pair<Foo, int>(foo, 1));
			Library::HashMap<Foo, int> foocopy2(fooMap);
			Assert::AreEqual(fooMap.size(), foocopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(fooMap.begin() == fooMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(foocopy2.begin() == foocopy2.end(), L"Begin of non-empty HashMap equals end");
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			// int tests
			Library::HashMap<int, int> intcopy1;
			intcopy1 = intMap;
			Assert::IsTrue(intMap.size() == intcopy1.size(), L"HashMap sizes not equal");

			intMap.insert(std::pair<int, int>(1, 1));
			Library::HashMap<int, int> intcopy2;
			intcopy2 = intMap;
			Assert::AreEqual(intMap.size(), intcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(intMap.begin() == intMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(intcopy2.begin() == intcopy2.end(), L"Begin of non-empty HashMap equals end");

			// pointer tests
			Library::HashMap<int*, int> ptrcopy1;
			ptrcopy1 = ptrMap;
			Assert::IsTrue(ptrMap.size() == ptrcopy1.size(), L"HashMap sizes not equal");

			ptrMap.insert(std::pair<int*, int>(&x, 1));
			Library::HashMap<int*, int> ptrcopy2;
			ptrcopy2 = ptrMap;
			Assert::AreEqual(ptrMap.size(), ptrcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(ptrMap.begin() == ptrMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(ptrcopy2.begin() == ptrcopy2.end(), L"Begin of non-empty HashMap equals end");


			// char* tests
			Library::HashMap<char*, int> chrcopy1;
			chrcopy1 = chrMap;
			Assert::IsTrue(chrMap.size() == chrcopy1.size(), L"HashMap sizes not equal");

			chrMap.insert(std::pair<char*, int>(a, 1));
			Library::HashMap<char*, int> chrcopy2;
			chrcopy2 = chrMap;
			Assert::AreEqual(chrMap.size(), chrcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(chrMap.begin() == chrMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(chrcopy2.begin() == chrcopy2.end(), L"Begin of non-empty HashMap equals end");


			// string tests
			Library::HashMap<std::string, int> strcopy1;
			strcopy1 = strMap;
			Assert::IsTrue(strMap.size() == strcopy1.size(), L"HashMap sizes not equal");

			strMap.insert(std::pair<std::string, int>(s, 1));
			Library::HashMap<std::string, int> strcopy2;
			strcopy2 = strMap;
			Assert::AreEqual(strMap.size(), strcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(strMap.begin() == strMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(strcopy2.begin() == strcopy2.end(), L"Begin of non-empty HashMap equals end");


			// foo tests
			Library::HashMap<Foo, int> foocopy1;
			foocopy1 = fooMap;
			Assert::IsTrue(fooMap.size() == foocopy1.size(), L"HashMap sizes not equal");

			fooMap.insert(std::pair<Foo, int>(foo, 1));
			Library::HashMap<Foo, int> foocopy2;
			foocopy2 = fooMap;
			Assert::AreEqual(fooMap.size(), foocopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(fooMap.begin() == fooMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(foocopy2.begin() == foocopy2.end(), L"Begin of non-empty HashMap equals end");
		}

		TEST_METHOD(TestFind)
		{
			// int tests
			Assert::IsTrue(intMap.find(1) == intMap.end(), L"Find on empty HashMap does not return end");
			intMap.insert(std::pair<int, int>(1, 1));
			Assert::IsTrue(intMap.find(1) == intMap.begin(), L"Only value inserted into HashMap is not begin");
			Assert::IsFalse(intMap.find(1) == intMap.end(), L"Find on existing value should not return end");
			Assert::AreEqual((*intMap.find(1)).second, 1, L"Find returning incorrect value");

			// pointer tests
			Assert::IsTrue(ptrMap.find(&x) == ptrMap.end(), L"Find on empty HashMap does not return end");
			ptrMap.insert(std::pair<int*, int>(&x, 1));
			Assert::IsTrue(ptrMap.find(&x) == ptrMap.begin(), L"Only value inserted into HashMap is not begin");
			Assert::IsFalse(ptrMap.find(&x) == ptrMap.end(), L"Find on existing value should not return end");
			Assert::AreEqual((*ptrMap.find(&x)).second, 1, L"Find returning incorrect value");

			// char* tests
			Assert::IsTrue(chrMap.find(c) == chrMap.end(), L"Find on empty HashMap does not return end");
			chrMap.insert(std::pair<char*, int>(c, 1));
			Assert::IsTrue(chrMap.find(c) == chrMap.begin(), L"Only value inserted into HashMap is not begin");
			Assert::IsFalse(chrMap.find(c) == chrMap.end(), L"Find on existing value should not return end");
			Assert::AreEqual((*chrMap.find(c)).second, 1, L"Find returning incorrect value");

			// string tests
			Assert::IsTrue(strMap.find(s) == strMap.end(), L"Find on empty HashMap does not return end");
			strMap.insert(std::pair<std::string, int>(s, 1));
			Assert::IsTrue(strMap.find(s) == strMap.begin(), L"Only value inserted into HashMap is not begin");
			Assert::IsFalse(strMap.find(s) == strMap.end(), L"Find on existing value should not return end");
			Assert::AreEqual((*strMap.find(s)).second, 1, L"Find returning incorrect value");

			// foo tests
			Assert::IsTrue(fooMap.find(foo) == fooMap.end(), L"Find on empty HashMap does not return end");
			fooMap.insert(std::pair<Foo, int>(foo, 1));
			Assert::IsTrue(fooMap.find(foo) == fooMap.begin(), L"Only value inserted into HashMap is not begin");
			Assert::IsFalse(fooMap.find(foo) == fooMap.end(), L"Find on existing value should not return end");
			Assert::AreEqual((*fooMap.find(foo)).second, 1, L"Find returning incorrect value");
		}

		TEST_METHOD(TestInsert)
		{
			// int tests
			auto intInsert = intMap.insert(std::pair<int, int>(1, 1));
			Assert::IsTrue(intInsert == intMap.begin(), L"Inserting first element should return begin");
			
			intMap.insert(std::pair<int, int>(10, 1));
			Assert::IsTrue(intMap.containsKey(10), L"Key doesn't exist after inserting");

			
			// pointer tests
			auto ptrInsert = ptrMap.insert(std::pair<int*, int>(&x, 1));
			Assert::IsTrue(ptrInsert == ptrMap.begin(), L"Inserting first element should return begin");
			
			ptrMap.insert(std::pair<int*, int>(&y, 1));
			Assert::IsTrue(ptrMap.containsKey(&y), L"Key doesn't exist after inserting");

			
			// char* tests
			auto chrInsert = chrMap.insert(std::pair<char*, int>(a, 1));
			Assert::IsTrue(chrInsert == chrMap.begin(), L"Inserting first element should return begin");

			chrMap.insert(std::pair<char*, int>(b, 1));
			Assert::IsTrue(chrMap.containsKey(b), L"Key doesn't exist after inserting");


			// string tests
			auto strInsert = strMap.insert(std::pair<std::string, int>(s, 1));
			Assert::IsTrue(strInsert == strMap.begin(), L"Inserting first element should return begin");

			strMap.insert(std::pair<std::string, int>(t, 1));
			Assert::IsTrue(strMap.containsKey(t), L"Key doesn't exist after inserting");

			// foo tests
			auto fooInsert = fooMap.insert(std::pair<Foo, int>(foo, 1));
			Assert::IsTrue(fooInsert == fooMap.begin(), L"Inserting first element should return begin");

			fooMap.insert(std::pair<Foo, int>(bar, 1));
			Assert::IsTrue(fooMap.containsKey(bar), L"Key doesn't exist after inserting");
		}

		TEST_METHOD(TestRemove)
		{
			// int tests
			Assert::IsFalse(intMap.containsKey(1), L"Empty HashMap should not contain any keys");
			
			std::uint32_t intMapSize = intMap.size();
			intMap.insert(std::pair<const int, int>(1, 1));
			Assert::IsTrue(intMap.containsKey(1), L"Key doesn't exist in HashMap after inserting");
			Assert::AreNotEqual(intMapSize, intMap.size(), L"Size not changing after inserting into HashMap");
			
			intMapSize = intMap.size();
			intMap.remove(1);
			Assert::IsFalse(intMap.containsKey(1), L"Key still exists in HashMap after removing");
			Assert::AreNotEqual(intMapSize, intMap.size(), L"Size not changing after removing from HashMap");
			
			intMapSize = intMap.size();
			intMap.remove(1);
			Assert::AreEqual(intMapSize, intMap.size(), L"Size should not change after removing non-existent key");


			// pointer tests
			Assert::IsFalse(ptrMap.containsKey(&x), L"Empty HashMap should not contain any keys");

			std::uint32_t ptrMapSize = ptrMap.size();
			ptrMap.insert(std::pair<int*, int>(&x, 1));
			Assert::IsTrue(ptrMap.containsKey(&x), L"Key doesn't exist in HashMap after inserting");
			Assert::AreNotEqual(ptrMapSize, ptrMap.size(), L"Size not changing after inserting into HashMap");

			ptrMapSize = ptrMap.size();
			ptrMap.remove(&x);
			Assert::IsFalse(ptrMap.containsKey(&x), L"Key still exists in HashMap after removing");
			Assert::AreNotEqual(ptrMapSize, ptrMap.size(), L"Size not changing after removing from HashMap");

			ptrMapSize = ptrMap.size();
			ptrMap.remove(&x);
			Assert::AreEqual(ptrMapSize, ptrMap.size(), L"Size should not change after removing non-existent key");


			// char* tests
			Assert::IsFalse(chrMap.containsKey(a), L"Empty HashMap should not contain any keys");

			std::uint32_t chrMapSize = chrMap.size();
			chrMap.insert(std::pair<char*, int>(a, 1));
			Assert::IsTrue(chrMap.containsKey(a), L"Key doesn't exist in HashMap after inserting");
			Assert::AreNotEqual(chrMapSize, chrMap.size(), L"Size not changing after inserting into HashMap");

			chrMapSize = chrMap.size();
			chrMap.remove(a);
			Assert::IsFalse(chrMap.containsKey(a), L"Key still exists in HashMap after removing");
			Assert::AreNotEqual(chrMapSize, chrMap.size(), L"Size not changing after removing from HashMap");

			chrMapSize = chrMap.size();
			chrMap.remove(a);
			Assert::AreEqual(chrMapSize, chrMap.size(), L"Size should not change after removing non-existent key");

			// string tests
			Assert::IsFalse(strMap.containsKey(s), L"Empty HashMap should not contain any keys");

			std::uint32_t strMapSize = strMap.size();
			strMap.insert(std::pair<std::string, int>(s, 1));
			Assert::IsTrue(strMap.containsKey(s), L"Key doesn't exist in HashMap after inserting");
			Assert::AreNotEqual(strMapSize, strMap.size(), L"Size not changing after inserting into HashMap");

			strMapSize = strMap.size();
			strMap.remove(s);
			Assert::IsFalse(strMap.containsKey(s), L"Key still exists in HashMap after removing");
			Assert::AreNotEqual(strMapSize, strMap.size(), L"Size not changing after removing from HashMap");

			strMapSize = strMap.size();
			strMap.remove(s);
			Assert::AreEqual(strMapSize, strMap.size(), L"Size should not change after removing non-existent key");


			// foo tests
			Assert::IsFalse(fooMap.containsKey(foo), L"Empty HashMap should not contain any keys");

			std::uint32_t fooMapSize = fooMap.size();
			fooMap.insert(std::pair<Foo, int>(foo, 1));
			Assert::IsTrue(fooMap.containsKey(foo), L"Key doesn't exist in HashMap after inserting");
			Assert::AreNotEqual(fooMapSize, fooMap.size(), L"Size not changing after inserting into HashMap");

			fooMapSize = fooMap.size();
			fooMap.remove(foo);
			Assert::IsFalse(fooMap.containsKey(foo), L"Key still exists in HashMap after removing");
			Assert::AreNotEqual(fooMapSize, fooMap.size(), L"Size not changing after removing from HashMap");

			fooMapSize = fooMap.size();
			fooMap.remove(foo);
			Assert::AreEqual(fooMapSize, fooMap.size(), L"Size should not change after removing non-existent key");
		}

		TEST_METHOD(TestIndexOperator)
		{
			// int tests
			std::uint32_t intMapSize = intMap.size();
			auto& intMapVal = intMap[1];
			Assert::AreNotEqual(intMapSize, intMap.size(), L"HashMap size not increasing after indexing a non-existent key");

			intMap.insert(std::pair<int, int>(1, 1));
			Assert::AreNotEqual(intMap[1], 1, L"Incorrect value returned with index operator");

			intMapVal = 1;
			Assert::AreEqual(1, intMap[1], L"HashMapValue not changed when assigned from index operator");

			const Library::HashMap<int, int> constIntMap(intMap);
			Assert::ExpectException<std::exception>([&] { constIntMap[2]; }, L"Indexing nonexistent key value");

			// pointer tests
			std::uint32_t ptrMapSize = ptrMap.size();
			auto& ptrMapVal = ptrMap[&x];
			Assert::AreNotEqual(ptrMapSize, ptrMap.size(), L"HashMap size not increasing after indexing a non-existent key");

			ptrMap.insert(std::pair<int*, int>(&x, 1));
			Assert::AreNotEqual(ptrMap[&x], 1, L"Incorrect value returned with index operator");

			ptrMapVal = 1;
			Assert::AreEqual(ptrMap[&x], 1, L"HashMapValue not changed when assigned from index operator");


			// char* tests
			std::uint32_t chrMapSize = chrMap.size();
			auto& chrMapVal = chrMap[a];
			Assert::AreNotEqual(chrMapSize, chrMap.size(), L"HashMap size not increasing after indexing a non-existent key");

			chrMap.insert(std::pair<char*, int>(a, 1));
			Assert::AreNotEqual(chrMap[a], 1, L"Incorrect value returned with index operator");

			chrMapVal = 1;
			Assert::AreEqual(chrMap[a], 1, L"HashMapValue not changed when assigned from index operator");


			// string tests
			std::uint32_t strMapSize = strMap.size();
			auto& strMapVal = strMap[s];
			Assert::AreNotEqual(strMapSize, strMap.size(), L"HashMap size not increasing after indexing a non-existent key");

			strMap.insert(std::pair<std::string, int>(s, 1));
			Assert::AreNotEqual(strMap[s], 1, L"Incorrect value returned with index operator");

			strMapVal = 1;
			Assert::AreEqual(strMap[s], 1, L"HashMapValue not changed when assigned from index operator");

			// foo tests
			std::uint32_t fooMapSize = fooMap.size();
			auto& fooMapVal = fooMap[foo];
			Assert::AreNotEqual(fooMapSize, fooMap.size(), L"HashMap size not increasing after indexing a non-existent key");

			fooMap.insert(std::pair<Foo, int>(foo, 1));
			Assert::AreNotEqual(fooMap[foo], 1, L"Incorrect value returned with index operator");

			fooMapVal = 1;
			Assert::AreEqual(fooMap[foo], 1, L"HashMapValue not changed when assigned from index operator");
		}

		TEST_METHOD(TestBegin)
		{
			// int tests
			Assert::IsTrue(intMap.begin() == intMap.end(), L"Begin does not equal end on empty HashMap");

			std::pair<const int, int> intPair(1, 1);
			intMap.insert(intPair);
			Assert::IsTrue(intPair == *(intMap.begin()));

			intMap.remove(1);
			Assert::IsTrue(intMap.begin() == intMap.end(), L"Begin does not equal end on empty HashMap");


			// pointer tests
			Assert::IsTrue(ptrMap.begin() == ptrMap.end(), L"Begin does not equal end on empty HashMap");

			std::pair<int* const, int> ptrPair(&x, 1);
			ptrMap.insert(ptrPair);
			Assert::IsTrue(ptrPair == *(ptrMap.begin()));

			ptrMap.remove(&x);
			Assert::IsTrue(ptrMap.begin() == ptrMap.end(), L"Begin does not equal end on empty HashMap");


			// char* tests
			Assert::IsTrue(chrMap.begin() == chrMap.end(), L"Begin does not equal end on empty HashMap");

			std::pair<char* const, int> chrPair(a, 1);
			chrMap.insert(chrPair);
			Assert::IsTrue(chrPair == *(chrMap.begin()));

			chrMap.remove(a);
			Assert::IsTrue(chrMap.begin() == chrMap.end(), L"Begin does not equal end on empty HashMap");


			// string tests
			Assert::IsTrue(strMap.begin() == strMap.end(), L"Begin does not equal end on empty HashMap");

			std::pair<const std::string, int> strPair(s, 1);
			strMap.insert(strPair);
			Assert::IsTrue(strPair == *(strMap.begin()));

			strMap.remove(s);
			Assert::IsTrue(strMap.begin() == strMap.end(), L"Begin does not equal end on empty HashMap");


			// foo tests
			Assert::IsTrue(fooMap.begin() == fooMap.end(), L"Begin does not equal end on empty HashMap");

			std::pair<const Foo, int> fooPair(foo, 1);
			fooMap.insert(fooPair);
			Assert::IsTrue(fooPair == *(fooMap.begin()));

			fooMap.remove(foo);
			Assert::IsTrue(fooMap.begin() == fooMap.end(), L"Begin does not equal end on empty HashMap");
		}

		TEST_METHOD(TestEnd)
		{
			// int tests
			Assert::IsTrue(intMap.begin() == intMap.end(), L"Begin should be equivalent to end on empty HashMap");
			intMap.insert(std::pair<int, int>(1, 1));
			Assert::IsFalse(intMap.begin() == intMap.end(), L"Begin should not be equivalent to end on non-empty HashMap");
			intMap.remove(1);
			Assert::IsTrue(intMap.begin() == intMap.end(), L"Begin should be equivalent to end on empty HashMap");
			auto intFunc = [&] { *intMap.end(); };
			Assert::ExpectException<std::exception>(intFunc, L"Dereferencing end of HashMap should throw exception");


			// pointer tests
			Assert::IsTrue(ptrMap.begin() == ptrMap.end(), L"Begin should be equivalent to end on empty HashMap");
			ptrMap.insert(std::pair<int*, int>(&x, 1));
			Assert::IsFalse(ptrMap.begin() == ptrMap.end(), L"Begin should not be equivalent to end on non-empty HashMap");
			ptrMap.remove(&x);
			Assert::IsTrue(ptrMap.begin() == ptrMap.end(), L"Begin should be equivalent to end on empty HashMap");
			auto ptrFunc = [&] { *ptrMap.end(); };
			Assert::ExpectException<std::exception>(ptrFunc, L"Dereferencing end of HashMap should throw exception");


			// char* tests
			Assert::IsTrue(chrMap.begin() == chrMap.end(), L"Begin should be equivalent to end on empty HashMap");
			chrMap.insert(std::pair<char*, int>(a, 1));
			Assert::IsFalse(chrMap.begin() == chrMap.end(), L"Begin should not be equivalent to end on non-empty HashMap");
			chrMap.remove(a);
			Assert::IsTrue(chrMap.begin() == chrMap.end(), L"Begin should be equivalent to end on empty HashMap");
			auto chrFunc = [&] { *chrMap.end(); };
			Assert::ExpectException<std::exception>(chrFunc, L"Dereferencing end of HashMap should throw exception");


			// string tests
			Assert::IsTrue(strMap.begin() == strMap.end(), L"Begin should be equivalent to end on empty HashMap");
			strMap.insert(std::pair<std::string, int>(s, 1));
			Assert::IsFalse(strMap.begin() == strMap.end(), L"Begin should not be equivalent to end on non-empty HashMap");
			strMap.remove(s);
			Assert::IsTrue(strMap.begin() == strMap.end(), L"Begin should be equivalent to end on empty HashMap");
			auto strFunc = [&] { *strMap.end(); };
			Assert::ExpectException<std::exception>(strFunc, L"Dereferencing end of HashMap should throw exception");


			// foo tests
			Assert::IsTrue(fooMap.begin() == fooMap.end(), L"Begin should be equivalent to end on empty HashMap");
			fooMap.insert(std::pair<Foo, int>(foo, 1));
			Assert::IsFalse(fooMap.begin() == fooMap.end(), L"Begin should not be equivalent to end on non-empty HashMap");
			fooMap.remove(foo);
			Assert::IsTrue(fooMap.begin() == fooMap.end(), L"Begin should be equivalent to end on empty HashMap");
			auto fooFunc = [&] { *fooMap.end(); };
			Assert::ExpectException<std::exception>(intFunc, L"Dereferencing end of HashMap should throw exception");
		}

		TEST_METHOD(TestClear)
		{
			// int tests
			Assert::AreEqual(intMap.size(), 0U, L"HashMap size should be zero when empty");
			intMap.insert(std::pair<int, int>(1, 1));
			Assert::IsTrue(intMap.size() > 0, L"HashMap size should be non-zero when not empty");
			intMap.clear();
			Assert::AreEqual(intMap.size(), 0U, L"HashMap size should be zero when cleared");
			intMap.clear();
			Assert::AreEqual(intMap.size(), 0U, L"HashMap size should be zero when clearing an empty HashMap");


			// pointer tests
			Assert::AreEqual(ptrMap.size(), 0U, L"HashMap size should be zero when empty");
			ptrMap.insert(std::pair<int*, int>(&x, 1));
			Assert::IsTrue(ptrMap.size() > 0, L"HashMap size should be non-zero when not empty");
			ptrMap.clear();
			Assert::AreEqual(ptrMap.size(), 0U, L"HashMap size should be zero when cleared");
			ptrMap.clear();
			Assert::AreEqual(ptrMap.size(), 0U, L"HashMap size should be zero when clearing an empty HashMap");


			// char* tests
			Assert::AreEqual(chrMap.size(), 0U, L"HashMap size should be zero when empty");
			chrMap.insert(std::pair<char*, int>(a, 1));
			Assert::IsTrue(chrMap.size() > 0, L"HashMap size should be non-zero when not empty");
			chrMap.clear();
			Assert::AreEqual(chrMap.size(), 0U, L"HashMap size should be zero when cleared");
			chrMap.clear();
			Assert::AreEqual(chrMap.size(), 0U, L"HashMap size should be zero when clearing an empty HashMap");


			// string tests
			Assert::AreEqual(strMap.size(), 0U, L"HashMap size should be zero when empty");
			strMap.insert(std::pair<std::string, int>(s, 1));
			Assert::IsTrue(strMap.size() > 0, L"HashMap size should be non-zero when not empty");
			strMap.clear();
			Assert::AreEqual(strMap.size(), 0U, L"HashMap size should be zero when cleared");
			strMap.clear();
			Assert::AreEqual(strMap.size(), 0U, L"HashMap size should be zero when clearing an empty HashMap");
		}

		TEST_METHOD(TestSize)
		{
			// int tests
			Assert::AreEqual(intMap.size(), 0U, L"Length of empty HashMap should be zero");
			
			intMap.insert(std::pair<int, int>(1, 1));
			Assert::AreEqual(intMap.size(), 1U, L"Size should be one after inserting one item");
			
			intMap.insert(std::pair<int, int>(2, 2));
			Assert::AreEqual(intMap.size(), 2U, L"Size should increase when adding a value");

			intMap.remove(10);
			Assert::AreEqual(intMap.size(), 2U, L"Size should not change when removing a non-existent value");

			intMap.remove(1);
			Assert::AreEqual(intMap.size(), 1U, L"Size should decrease when removing an item");

			intMap.clear();
			Assert::AreEqual(intMap.size(), 0U, L"Size should be zero after clearing");


			// pointer tests
			Assert::AreEqual(ptrMap.size(), 0U, L"Length of empty HashMap should be zero");

			ptrMap.insert(std::pair<int*, int>(&x, 1));
			Assert::AreEqual(ptrMap.size(), 1U, L"Size should be one after inserting one item");

			ptrMap.insert(std::pair<int*, int>(&y, 2));
			Assert::AreEqual(ptrMap.size(), 2U, L"Size should increase when adding a value");

			ptrMap.remove(&z);
			Assert::AreEqual(ptrMap.size(), 2U, L"Size should not change when removing a non-existent value");

			ptrMap.remove(&x);
			Assert::AreEqual(ptrMap.size(), 1U, L"Size should decrease when removing an item");

			ptrMap.clear();
			Assert::AreEqual(ptrMap.size(), 0U, L"Size should be zero after clearing");


			// char* tests
			Assert::AreEqual(chrMap.size(), 0U, L"Length of empty HashMap should be zero");

			chrMap.insert(std::pair<char*, int>(a, 1));
			Assert::AreEqual(chrMap.size(), 1U, L"Size should be one after inserting one item");

			chrMap.insert(std::pair<char*, int>(b, 2));
			Assert::AreEqual(chrMap.size(), 2U, L"Size should increase when adding a value");

			chrMap.remove(c);
			Assert::AreEqual(chrMap.size(), 2U, L"Size should not change when removing a non-existent value");

			chrMap.remove(a);
			Assert::AreEqual(chrMap.size(), 1U, L"Size should decrease when removing an item");

			chrMap.clear();
			Assert::AreEqual(chrMap.size(), 0U, L"Size should be zero after clearing");


			// string tests
			Assert::AreEqual(strMap.size(), 0U, L"Length of empty HashMap should be zero");

			strMap.insert(std::pair<std::string, int>(s, 1));
			Assert::AreEqual(strMap.size(), 1U, L"Size should be one after inserting one item");

			strMap.insert(std::pair<std::string, int>(t, 2));
			Assert::AreEqual(strMap.size(), 2U, L"Size should increase when adding a value");

			strMap.remove(u);
			Assert::AreEqual(strMap.size(), 2U, L"Size should not change when removing a non-existent value");

			strMap.remove(s);
			Assert::AreEqual(strMap.size(), 1U, L"Size should decrease when removing an item");

			strMap.clear();
			Assert::AreEqual(strMap.size(), 0U, L"Size should be zero after clearing");


			// foo tests
			Assert::AreEqual(fooMap.size(), 0U, L"Length of empty HashMap should be zero");

			fooMap.insert(std::pair<Foo, int>(foo, 1));
			Assert::AreEqual(fooMap.size(), 1U, L"Size should be one after inserting one item");

			fooMap.insert(std::pair<Foo, int>(bar, 2));
			Assert::AreEqual(fooMap.size(), 2U, L"Size should increase when adding a value");

			fooMap.remove(gar);
			Assert::AreEqual(fooMap.size(), 2U, L"Size should not change when removing a non-existent value");

			fooMap.remove(foo);
			Assert::AreEqual(fooMap.size(), 1U, L"Size should decrease when removing an item");

			fooMap.clear();
			Assert::AreEqual(fooMap.size(), 0U, L"Size should be zero after clearing");
		}

		TEST_METHOD(TestContainsKey)
		{
			// int tests
			Assert::IsFalse(intMap.containsKey(1), L"Empty map should not contain any keys");

			intMap.insert(std::pair<int, int>(1, 1));
			Assert::IsFalse(intMap.containsKey(10), L"Map should not contain a key that hasn't been inserted");
			Assert::IsTrue(intMap.containsKey(1), L"HashMap does not contain a key that has been inserted");

			intMap.remove(1);
			Assert::IsFalse(intMap.containsKey(1), L"Map should not contain a key that has been removed");


			// pointer tests
			Assert::IsFalse(ptrMap.containsKey(&x), L"Empty map should not contain any keys");

			ptrMap.insert(std::pair<int*, int>(&x, 1));
			Assert::IsFalse(ptrMap.containsKey(&y), L"Map should not contain a key that hasn't been inserted");
			Assert::IsTrue(ptrMap.containsKey(&x), L"HashMap does not contain a key that has been inserted");

			ptrMap.remove(&x);
			Assert::IsFalse(ptrMap.containsKey(&x), L"Map should not contain a key that has been removed");


			// char* tests
			Assert::IsFalse(chrMap.containsKey(a), L"Empty map should not contain any keys");

			chrMap.insert(std::pair<char*, int>(a, 1));
			Assert::IsFalse(chrMap.containsKey(b), L"Map should not contain a key that hasn't been inserted");
			Assert::IsTrue(chrMap.containsKey(a), L"HashMap does not contain a key that has been inserted");

			chrMap.remove(a);
			Assert::IsFalse(chrMap.containsKey(a), L"Map should not contain a key that has been removed");


			// string tests
			Assert::IsFalse(strMap.containsKey(s), L"Empty map should not contain any keys");

			strMap.insert(std::pair<std::string, int>(s, 1));
			Assert::IsFalse(strMap.containsKey(t), L"Map should not contain a key that hasn't been inserted");
			Assert::IsTrue(strMap.containsKey(s), L"HashMap does not contain a key that has been inserted");

			strMap.remove(s);
			Assert::IsFalse(strMap.containsKey(s), L"Map should not contain a key that has been removed");


			// foo tests
			Assert::IsFalse(fooMap.containsKey(foo), L"Empty map should not contain any keys");

			fooMap.insert(std::pair<Foo, int>(foo, 1));
			Assert::IsFalse(fooMap.containsKey(bar), L"Map should not contain a key that hasn't been inserted");
			Assert::IsTrue(fooMap.containsKey(foo), L"HashMap does not contain a key that has been inserted");

			fooMap.remove(foo);
			Assert::IsFalse(fooMap.containsKey(foo), L"Map should not contain a key that has been removed");
		}

		TEST_METHOD(TestIteratorCopyConstructor)
		{
			// int tests
			auto interator_1(intMap.begin());
			Assert::IsTrue(interator_1 == intMap.begin() && interator_1 == intMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");
			
			intMap.insert(std::pair<int, int>(1, 1));
			auto interator_2(intMap.begin());
			Assert::IsTrue(interator_2 == intMap.begin() && interator_2 != intMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto interator_3(intMap.end());
			Assert::IsTrue(interator_3 != intMap.begin() && interator_3 == intMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto interator_4(intMap.find(1));
			intMap.clear();
			Assert::IsTrue(interator_4 != intMap.find(1), L"Iterator set to HashMap value should not be equivalent to a find call of that value after clear");


			// pointer tests
			auto pointerator_1(ptrMap.begin());
			Assert::IsTrue(pointerator_1 == ptrMap.begin() && pointerator_1 == ptrMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");

			ptrMap.insert(std::pair<int*, int>(&x, 1));
			auto pointerator_2(ptrMap.begin());
			Assert::IsTrue(pointerator_2 == ptrMap.begin() && pointerator_2 != ptrMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto pointerator_3(ptrMap.end());
			Assert::IsTrue(pointerator_3 != ptrMap.begin() && pointerator_3 == ptrMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto pointerator_4(ptrMap.find(&x));
			ptrMap.clear();
			Assert::IsTrue(pointerator_4 != ptrMap.find(&x), L"Iterator set to HashMap value should not be equivalent to a find call of that value after clear");


			// char* tests
			auto charterator_1(chrMap.begin());
			Assert::IsTrue(charterator_1 == chrMap.begin() && charterator_1 == chrMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");

			chrMap.insert(std::pair<char*, int>(a, 1));
			auto charterator_2(chrMap.begin());
			Assert::IsTrue(charterator_2 == chrMap.begin() && charterator_2 != chrMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto charterator_3(chrMap.end());
			Assert::IsTrue(charterator_3 != chrMap.begin() && charterator_3 == chrMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto charterator_4(chrMap.find(a));
			chrMap.clear();
			Assert::IsTrue(charterator_4 != chrMap.find(a), L"Iterator set to HashMap value should not be equivalent to a find call of that value after clear");


			// string tests
			auto stringerator_1(strMap.begin());
			Assert::IsTrue(stringerator_1 == strMap.begin() && stringerator_1 == strMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");

			strMap.insert(std::pair<std::string, int>(s, 1));
			auto stringerator_2(strMap.begin());
			Assert::IsTrue(stringerator_2 == strMap.begin() && stringerator_2 != strMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto stringerator_3(strMap.end());
			Assert::IsTrue(stringerator_3 != strMap.begin() && stringerator_3 == strMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto stringerator_4(strMap.find(s));
			strMap.clear();
			Assert::IsTrue(stringerator_4 != strMap.find(s), L"Iterator set to HashMap value should not be equivalent to a find call of that value after clear");


			// foo tests
			auto footerator_1(fooMap.begin());
			Assert::IsTrue(footerator_1 == fooMap.begin() && footerator_1 == fooMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");

			fooMap.insert(std::pair<Foo, int>(foo, 1));
			auto footerator_2(fooMap.begin());
			Assert::IsTrue(footerator_2 == fooMap.begin() && footerator_2 != fooMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto footerator_3(fooMap.end());
			Assert::IsTrue(footerator_3 != fooMap.begin() && footerator_3 == fooMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto footerator_4(fooMap.find(foo));
			fooMap.clear();
			Assert::IsTrue(footerator_4 != fooMap.find(foo), L"Iterator set to HashMap value should not be equivalent to a find call of that value after clear");
		}

		TEST_METHOD(TestIteratorAssignmentOperator)
		{
			// int tests
			auto interator_1 = intMap.begin();
			Assert::IsTrue(interator_1 == intMap.begin() && interator_1 == intMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");

			intMap.insert(std::pair<int, int>(1, 1));
			auto interator_2 = intMap.begin();
			Assert::IsTrue(interator_2 == intMap.begin() && interator_2 != intMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto interator_3 = intMap.end();
			Assert::IsTrue(interator_3 != intMap.begin() && interator_3 == intMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto interator_4 = intMap.find(1);
			intMap.clear();
			Assert::IsTrue(interator_4 != intMap.find(1), L"Iterator set to HashMap value should not be equivalent to a find call of that value after clear");


			// pointer tests
			auto pointerator_1 = ptrMap.begin();
			Assert::IsTrue(pointerator_1 == ptrMap.begin() && pointerator_1 == ptrMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");

			ptrMap.insert(std::pair<int*, int>(&x, 1));
			auto pointerator_2 = ptrMap.begin();
			Assert::IsTrue(pointerator_2 == ptrMap.begin() && pointerator_2 != ptrMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto pointerator_3 = ptrMap.end();
			Assert::IsTrue(pointerator_3 != ptrMap.begin() && pointerator_3 == ptrMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto pointerator_4 = ptrMap.find(&x);
			ptrMap.clear();
			Assert::IsTrue(pointerator_4 != ptrMap.find(&x), L"Iterator set to HashMap value should not be equivalent to a find call of that value after clear");


			// char* tests
			auto charterator_1 = chrMap.begin();
			Assert::IsTrue(charterator_1 == chrMap.begin() && charterator_1 == chrMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");

			chrMap.insert(std::pair<char*, int>(a, 1));
			auto charterator_2 = chrMap.begin();
			Assert::IsTrue(charterator_2 == chrMap.begin() && charterator_2 != chrMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto charterator_3 = chrMap.end();
			Assert::IsTrue(charterator_3 != chrMap.begin() && charterator_3 == chrMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto charterator_4 = chrMap.find(a);
			chrMap.clear();
			Assert::IsTrue(charterator_4 != chrMap.find(a), L"Iterator set to HashMap value should not be equivalent to a find call of that value after clear");


			// string tests
			auto stringerator_1 = strMap.begin();
			Assert::IsTrue(stringerator_1 == strMap.begin() && stringerator_1 == strMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");

			strMap.insert(std::pair<std::string, int>(s, 1));
			auto stringerator_2 = strMap.begin();
			Assert::IsTrue(stringerator_2 == strMap.begin() && stringerator_2 != strMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto stringerator_3 = strMap.end();
			Assert::IsTrue(stringerator_3 != strMap.begin() && stringerator_3 == strMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto stringerator_4 = strMap.find(s);
			strMap.clear();
			Assert::IsTrue(stringerator_4 != strMap.find(s), L"Iterator set to HashMap value should not be equivalent to a find call of that value after clear");


			// foo tests
			auto footerator_1 = fooMap.begin();
			Assert::IsTrue(footerator_1 == fooMap.begin() && footerator_1 == fooMap.end(), L"Iterator copy should be equivalent to begin and end of empty HashMap");

			fooMap.insert(std::pair<Foo, int>(foo, 1));
			auto footerator_2 = fooMap.begin();
			Assert::IsTrue(footerator_2 == fooMap.begin() && footerator_2 != fooMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto footerator_3 = fooMap.end();
			Assert::IsTrue(footerator_3 != fooMap.begin() && footerator_3 == fooMap.end(), L"Iterator copy should be equivalent to only the value it's assigned to");

			auto footerator_4 = fooMap.find(foo);
			fooMap.clear();
			Assert::IsTrue(footerator_4 != fooMap.find(foo), L"Iterator set to HashMap value should not be equivalent to a find call of that value after clear");
		}

		TEST_METHOD(TestIteratorIncrementOperator)
		{
			// int tests
			intMap.insert(std::pair<int, int>(1, 1));
			intMap.insert(std::pair<int, int>(2, 2));
			auto interator = intMap.begin();
			Assert::IsTrue(interator == intMap.begin() && ++interator != intMap.end(), 
				L"Incrementing past first element should not return end when other items exist");
			Assert::IsTrue(++interator == intMap.end() && ++interator == intMap.end(), 
				L"Incrementing past end should still return end");


			// pointer tests
			ptrMap.insert(std::pair<int*, int>(&x, 1));
			ptrMap.insert(std::pair<int*, int>(&y, 2));
			auto pointerator = ptrMap.begin();
			Assert::IsTrue(pointerator == ptrMap.begin() && ++pointerator != ptrMap.end(), 
				L"Incrementing past first element should not return end when other items exist");
			Assert::IsTrue(++pointerator == ptrMap.end() && ++pointerator == ptrMap.end(), 
				L"Incrementing past end should still return end");


			// char* tests
			chrMap.insert(std::pair<char*, int>(a, 1));
			chrMap.insert(std::pair<char*, int>(b, 2));
			auto charterator = chrMap.begin();
			Assert::IsTrue(charterator == chrMap.begin() && ++charterator != chrMap.end(), 
				L"Incrementing past first element should not return end when other items exist");
			Assert::IsTrue(++charterator == chrMap.end() && ++charterator == chrMap.end(), 
				L"Incrementing past end should still return end");


			// string tests
			strMap.insert(std::pair<std::string, int>(s, 1));
			strMap.insert(std::pair<std::string, int>(t, 2));
			auto stringerator = strMap.begin();
			Assert::IsTrue(stringerator == strMap.begin() && ++stringerator != strMap.end(), 
				L"Incrementing past first element should not return end when other items exist");
			Assert::IsTrue(++stringerator == strMap.end() && ++stringerator == strMap.end(), 
				L"Incrementing past end should still return end");


			// foo tests
			fooMap.insert(std::pair<Foo, int>(foo, 1));
			fooMap.insert(std::pair<Foo, int>(bar, 2));
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

			intMap.insert(std::pair<int, int>(1, 1));
			Assert::AreEqual(1, (*intMap.begin()).first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, (*intMap.begin()).second, L"Dereferencing iterator does not yield accurate value");


			// pointer tests
			auto ptrFunc = [&] { *ptrMap.begin(); };
			Assert::ExpectException<std::exception>(ptrFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			ptrMap.insert(std::pair<int*, int>(&x, 1));
			Assert::AreEqual(&x, (*ptrMap.begin()).first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, (*ptrMap.begin()).second, L"Dereferencing iterator does not yield accurate value");


			// char* tests
			auto chrFunc = [&] { *chrMap.begin(); };
			Assert::ExpectException<std::exception>(chrFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			chrMap.insert(std::pair<char*, int>(a, 1));
			Assert::AreEqual(a, (*chrMap.begin()).first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, (*chrMap.begin()).second, L"Dereferencing iterator does not yield accurate value");


			// string tests
			auto strFunc = [&] { *strMap.begin(); };
			Assert::ExpectException<std::exception>(strFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			strMap.insert(std::pair<std::string, int>(s, 1));
			Assert::AreEqual(s, (*strMap.begin()).first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, (*strMap.begin()).second, L"Dereferencing iterator does not yield accurate value");


			// foo tests
			auto fooFunc = [&] { *fooMap.begin(); };
			Assert::ExpectException<std::exception>(fooFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			fooMap.insert(std::pair<Foo, int>(foo, 1));
			Assert::IsTrue(foo == (*fooMap.begin()).first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, (*fooMap.begin()).second, L"Dereferencing iterator does not yield accurate value");
		}

		TEST_METHOD(TestIteratorArrowOperator)
		{
			// int tests
			auto intFunc = [&] { *intMap.begin(); };
			Assert::ExpectException<std::exception>(intFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			intMap.insert(std::pair<int, int>(1, 1));
			Assert::AreEqual(1,  intMap.begin()->first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, intMap.begin()->second, L"Dereferencing iterator does not yield accurate value");


			// pointer tests
			auto ptrFunc = [&] { *ptrMap.begin(); };
			Assert::ExpectException<std::exception>(ptrFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			ptrMap.insert(std::pair<int*, int>(&x, 1));
			Assert::AreEqual(&x, ptrMap.begin()->first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, ptrMap.begin()->second, L"Dereferencing iterator does not yield accurate value");


			// char* tests
			auto chrFunc = [&] { *chrMap.begin(); };
			Assert::ExpectException<std::exception>(chrFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			chrMap.insert(std::pair<char*, int>(a, 1));
			Assert::AreEqual(a, chrMap.begin()->first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, chrMap.begin()->second, L"Dereferencing iterator does not yield accurate value");


			// string tests
			auto strFunc = [&] { *strMap.begin(); };
			Assert::ExpectException<std::exception>(strFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			strMap.insert(std::pair<std::string, int>(s, 1));
			Assert::AreEqual(s, strMap.begin()->first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, strMap.begin()->second, L"Dereferencing iterator does not yield accurate value");


			// foo tests
			auto fooFunc = [&] { *fooMap.begin(); };
			Assert::ExpectException<std::exception>(fooFunc, 
				L"Exception should be thrown when attempting to dereference end of HashMap");

			fooMap.insert(std::pair<Foo, int>(foo, 1));
			Assert::IsTrue(foo == fooMap.begin()->first, L"Dereferencing iterator does not yield accurate key");
			Assert::AreEqual(1, fooMap.begin()->second, L"Dereferencing iterator does not yield accurate value");
		}

		static _CrtMemState sStartMemState;
	};

	_CrtMemState HashMapTest::sStartMemState;
}
