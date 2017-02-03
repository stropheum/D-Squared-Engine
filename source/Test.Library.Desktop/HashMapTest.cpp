#include "pch.h"
#include "CppUnitTest.h"
#include "HashMap.h"
#include "Foo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{
	TEST_CLASS(HashMapTest)
	{
		HashMap::HashMap<int, int> intMap;
		HashMap::HashMap<int*, int> ptrMap;
		HashMap::HashMap<char*, int> chrMap;
		HashMap::HashMap<std::string, int> strMap;
		HashMap::HashMap<Foo, int> fooMap;
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
			HashMap::HashMap<int, int> intcopy1(intMap);
			Assert::IsTrue(intMap.size() == intcopy1.size(), L"HashMap sizes not equal");

			intMap.insert(std::pair<int, int>(1, 1));
			HashMap::HashMap<int, int> intcopy2(intMap);
			Assert::AreEqual(intMap.size(), intcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(intMap.begin() == intMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(intcopy2.begin() == intcopy2.end(), L"Begin of non-empty HashMap equals end");

			// ptr tests
			HashMap::HashMap<int*, int> ptrcopy1(ptrMap);
			Assert::IsTrue(ptrMap.size() == ptrcopy1.size(), L"HashMap sizes not equal");

			ptrMap.insert(std::pair<int*, int>(&x, 1));
			HashMap::HashMap<int*, int> ptrcopy2(ptrMap);
			Assert::AreEqual(ptrMap.size(), ptrcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(ptrMap.begin() == ptrMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(ptrcopy2.begin() == ptrcopy2.end(), L"Begin of non-empty HashMap equals end");


			// char* tests
			HashMap::HashMap<char*, int> chrcopy1(chrMap);
			Assert::IsTrue(chrMap.size() == chrcopy1.size(), L"HashMap sizes not equal");

			chrMap.insert(std::pair<char*, int>(a, 1));
			HashMap::HashMap<char*, int> chrcopy2(chrMap);
			Assert::AreEqual(chrMap.size(), chrcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(chrMap.begin() == chrMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(chrcopy2.begin() == chrcopy2.end(), L"Begin of non-empty HashMap equals end");


			// str test
			HashMap::HashMap<std::string, int> strcopy1(strMap);
			Assert::IsTrue(strMap.size() == strcopy1.size(), L"HashMap sizes not equal");

			strMap.insert(std::pair<std::string, int>(s, 1));
			HashMap::HashMap<std::string, int> strcopy2(strMap);
			Assert::AreEqual(strMap.size(), strcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(strMap.begin() == strMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(strcopy2.begin() == strcopy2.end(), L"Begin of non-empty HashMap equals end");
			
			
			// foo tests
			HashMap::HashMap<Foo, int> foocopy1(fooMap);
			Assert::IsTrue(fooMap.size() == foocopy1.size(), L"HashMap sizes not equal");

			fooMap.insert(std::pair<Foo, int>(foo, 1));
			HashMap::HashMap<Foo, int> foocopy2(fooMap);
			Assert::AreEqual(fooMap.size(), foocopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(fooMap.begin() == fooMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(foocopy2.begin() == foocopy2.end(), L"Begin of non-empty HashMap equals end");
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			// int tests
			HashMap::HashMap<int, int> intcopy1;
			intcopy1 = intMap;
			Assert::IsTrue(intMap.size() == intcopy1.size(), L"HashMap sizes not equal");

			intMap.insert(std::pair<int, int>(1, 1));
			HashMap::HashMap<int, int> intcopy2;
			intcopy2 = intMap;
			Assert::AreEqual(intMap.size(), intcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(intMap.begin() == intMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(intcopy2.begin() == intcopy2.end(), L"Begin of non-empty HashMap equals end");

			// pointer tests
			HashMap::HashMap<int*, int> ptrcopy1;
			ptrcopy1 = ptrMap;
			Assert::IsTrue(ptrMap.size() == ptrcopy1.size(), L"HashMap sizes not equal");

			ptrMap.insert(std::pair<int*, int>(&x, 1));
			HashMap::HashMap<int*, int> ptrcopy2;
			ptrcopy2 = ptrMap;
			Assert::AreEqual(ptrMap.size(), ptrcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(ptrMap.begin() == ptrMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(ptrcopy2.begin() == ptrcopy2.end(), L"Begin of non-empty HashMap equals end");


			// char* tests
			HashMap::HashMap<char*, int> chrcopy1;
			chrcopy1 = chrMap;
			Assert::IsTrue(chrMap.size() == chrcopy1.size(), L"HashMap sizes not equal");

			chrMap.insert(std::pair<char*, int>(a, 1));
			HashMap::HashMap<char*, int> chrcopy2;
			chrcopy2 = chrMap;
			Assert::AreEqual(chrMap.size(), chrcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(chrMap.begin() == chrMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(chrcopy2.begin() == chrcopy2.end(), L"Begin of non-empty HashMap equals end");


			// string tests
			HashMap::HashMap<std::string, int> strcopy1;
			strcopy1 = strMap;
			Assert::IsTrue(strMap.size() == strcopy1.size(), L"HashMap sizes not equal");

			strMap.insert(std::pair<std::string, int>(s, 1));
			HashMap::HashMap<std::string, int> strcopy2;
			strcopy2 = strMap;
			Assert::AreEqual(strMap.size(), strcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(strMap.begin() == strMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(strcopy2.begin() == strcopy2.end(), L"Begin of non-empty HashMap equals end");


			// foo tests
			HashMap::HashMap<Foo, int> foocopy1;
			foocopy1 = fooMap;
			Assert::IsTrue(fooMap.size() == foocopy1.size(), L"HashMap sizes not equal");

			fooMap.insert(std::pair<Foo, int>(foo, 1));
			HashMap::HashMap<Foo, int> foocopy2;
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
			intMap.insert(std::pair<int, int>(1, 1));
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
			Assert::AreEqual(intMap[1], 1, L"HashMapValue not changed when assigned from index operator");


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

			std::pair<int, int> intPair(1, 1);
			intMap.insert(intPair);
			Assert::IsTrue(intPair == *(intMap.begin()));

			intMap.remove(1);
			Assert::IsTrue(intMap.begin() == intMap.end(), L"Begin does not equal end on empty HashMap");


			// pointer tests
			Assert::IsTrue(ptrMap.begin() == ptrMap.end(), L"Begin does not equal end on empty HashMap");

			std::pair<int*, int> ptrPair(&x, 1);
			ptrMap.insert(ptrPair);
			Assert::IsTrue(ptrPair == *(ptrMap.begin()));

			ptrMap.remove(&x);
			Assert::IsTrue(ptrMap.begin() == ptrMap.end(), L"Begin does not equal end on empty HashMap");


			// char* tests
			Assert::IsTrue(chrMap.begin() == chrMap.end(), L"Begin does not equal end on empty HashMap");

			std::pair<char*, int> chrPair(a, 1);
			chrMap.insert(chrPair);
			Assert::IsTrue(chrPair == *(chrMap.begin()));

			chrMap.remove(a);
			Assert::IsTrue(chrMap.begin() == chrMap.end(), L"Begin does not equal end on empty HashMap");


			// string tests
			Assert::IsTrue(strMap.begin() == strMap.end(), L"Begin does not equal end on empty HashMap");

			std::pair<std::string, int> strPair(s, 1);
			strMap.insert(strPair);
			Assert::IsTrue(strPair == *(strMap.begin()));

			strMap.remove(s);
			Assert::IsTrue(strMap.begin() == strMap.end(), L"Begin does not equal end on empty HashMap");


			// foo tests
			Assert::IsTrue(fooMap.begin() == fooMap.end(), L"Begin does not equal end on empty HashMap");

			std::pair<Foo, int> fooPair(foo, 1);
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


			// pointer tests
			Assert::IsTrue(ptrMap.begin() == ptrMap.end(), L"Begin should be equivalent to end on empty HashMap");
			ptrMap.insert(std::pair<int*, int>(&x, 1));
			Assert::IsFalse(ptrMap.begin() == ptrMap.end(), L"Begin should not be equivalent to end on non-empty HashMap");
			ptrMap.remove(&x);
			Assert::IsTrue(ptrMap.begin() == ptrMap.end(), L"Begin should be equivalent to end on empty HashMap");


			// char* tests
			Assert::IsTrue(chrMap.begin() == chrMap.end(), L"Begin should be equivalent to end on empty HashMap");
			chrMap.insert(std::pair<char*, int>(a, 1));
			Assert::IsFalse(chrMap.begin() == chrMap.end(), L"Begin should not be equivalent to end on non-empty HashMap");
			chrMap.remove(a);
			Assert::IsTrue(chrMap.begin() == chrMap.end(), L"Begin should be equivalent to end on empty HashMap");


			// string tests
			Assert::IsTrue(strMap.begin() == strMap.end(), L"Begin should be equivalent to end on empty HashMap");
			strMap.insert(std::pair<std::string, int>(s, 1));
			Assert::IsFalse(strMap.begin() == strMap.end(), L"Begin should not be equivalent to end on non-empty HashMap");
			strMap.remove(s);
			Assert::IsTrue(strMap.begin() == strMap.end(), L"Begin should be equivalent to end on empty HashMap");


			// foo tests
			Assert::IsTrue(fooMap.begin() == fooMap.end(), L"Begin should be equivalent to end on empty HashMap");
			fooMap.insert(std::pair<Foo, int>(foo, 1));
			Assert::IsFalse(fooMap.begin() == fooMap.end(), L"Begin should not be equivalent to end on non-empty HashMap");
			fooMap.remove(foo);
			Assert::IsTrue(fooMap.begin() == fooMap.end(), L"Begin should be equivalent to end on empty HashMap");
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
//			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestContainsKey)
		{
//			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorCopyConstructor)
		{
//			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorAssignmentOperator)
		{
//			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorIncrementOperator)
		{
//			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorDereferenceOperator)
		{
//			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorArrowOperator)
		{
//			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorEqualityOperator)
		{
//			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorNotEqualOperator)
		{
//			Assert::Fail(L"Method not implemented");
		}
	};
}
