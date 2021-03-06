#include "pch.h"
#include "CppUnitTest.h"
#include "LeakDetector.h"
#include "HashMap.h"
#include "Foo.h"
#include <winnt.h>

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

        TEST_METHOD_INITIALIZE(InitializeMethod)
        {
            intMap.Clear();
            ptrMap.Clear();
            chrMap.Clear();
            strMap.Clear();
            fooMap.Clear();

            LeakDetector::Initialize();

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

        TEST_METHOD_CLEANUP(CleanupMethod)
        {
            intMap.Clear();
            ptrMap.Clear();
            chrMap.Clear();
            strMap.Clear();
            fooMap.Clear();

            LeakDetector::Finalize();
        }

        TEST_METHOD(TestTemplateSpecialization_Integer)
        {
            intMap.Insert(std::pair<int, int>(1, 1));
            Assert::IsTrue(intMap.ContainsKey(1),
                L"intMap does not contain inserted key");
        }

        TEST_METHOD(TestTemplateSpecialization_Pointer)
        {
            ptrMap.Insert(std::pair<int*, int>(&x, 1));
            Assert::IsTrue(ptrMap.ContainsKey(&x),
                L"ptrMap does not contain inserted key");
        }

        TEST_METHOD(TestTemplateSpecialization_CharStar)
        {
            chrMap.Insert(std::pair<char*, int>(c, 1));
            Assert::IsTrue(chrMap.ContainsKey(c),
                L"charMap does not contain inserted key");
        }

        TEST_METHOD(TestTemplateSpecialization_String)
        {
            strMap.Insert(std::pair<std::string, int>(s, 1));
            Assert::IsTrue(strMap.ContainsKey(s),
                L"stringMap does not contain inserted key");
        }

        TEST_METHOD(TestTemplateSpecialization_Foo)
        {
            fooMap.Insert(std::pair<Foo, int>(foo, 1));
            Assert::IsTrue(fooMap.ContainsKey(foo),
                L"fooMap does not contain inserted key");
        }

        TEST_METHOD(TestCopyConstructor_Integer)
        {
            Library::HashMap<int, int> intcopy1(intMap);
            Assert::IsTrue(intMap.Size() == intcopy1.Size(),
                L"HashMap sizes not equal");

            intMap.Insert(std::pair<int, int>(1, 1));
            Library::HashMap<int, int> intcopy2(intMap);
            Assert::AreEqual(intMap.Size(), intcopy2.Size(),
                L"HashMap sizes not equal");
            Assert::IsFalse(intMap.begin() == intMap.end(),
                L"begin of non-empty HashMap equals end");
            Assert::IsFalse(intcopy2.begin() == intcopy2.end(),
                L"begin of non-empty HashMap equals end");
        }

        TEST_METHOD(TestCopyConstructor_Pointer)
        {
            Library::HashMap<int*, int> ptrcopy1(ptrMap);
            Assert::IsTrue(ptrMap.Size() == ptrcopy1.Size(),
                L"HashMap sizes not equal");

            ptrMap.Insert(std::pair<int*, int>(&x, 1));
            Library::HashMap<int*, int> ptrcopy2(ptrMap);
            Assert::AreEqual(ptrMap.Size(), ptrcopy2.Size(),
                L"HashMap sizes not equal");
            Assert::IsFalse(ptrMap.begin() == ptrMap.end(),
                L"begin of non-empty HashMap equals end");
            Assert::IsFalse(ptrcopy2.begin() == ptrcopy2.end(),
                L"begin of non-empty HashMap equals end");
        }

        TEST_METHOD(TestCopyConstructor_CharStar)
        {
            Library::HashMap<char*, int> chrcopy1(chrMap);
            Assert::IsTrue(chrMap.Size() == chrcopy1.Size(),
                L"HashMap sizes not equal");

            chrMap.Insert(std::pair<char*, int>(a, 1));
            Library::HashMap<char*, int> chrcopy2(chrMap);
            Assert::AreEqual(chrMap.Size(), chrcopy2.Size(),
                L"HashMap sizes not equal");
            Assert::IsFalse(chrMap.begin() == chrMap.end(),
                L"begin of non-empty HashMap equals end");
            Assert::IsFalse(chrcopy2.begin() == chrcopy2.end(),
                L"begin of non-empty HashMap equals end");
        }

        TEST_METHOD(TestCopyConstructor_String)
        {
            Library::HashMap<std::string, int> strcopy1(strMap);
            Assert::IsTrue(strMap.Size() == strcopy1.Size(),
                L"HashMap sizes not equal");

            strMap.Insert(std::pair<std::string, int>(s, 1));
            Library::HashMap<std::string, int> strcopy2(strMap);
            Assert::AreEqual(strMap.Size(), strcopy2.Size(),
                L"HashMap sizes not equal");
            Assert::IsFalse(strMap.begin() == strMap.end(),
                L"begin of non-empty HashMap equals end");
            Assert::IsFalse(strcopy2.begin() == strcopy2.end(),
                L"begin of non-empty HashMap equals end");
        }

        TEST_METHOD(TestCopyConstructor_Foo)
        {
            Library::HashMap<Foo, int> foocopy1(fooMap);
            Assert::IsTrue(fooMap.Size() == foocopy1.Size(),
                L"HashMap sizes not equal");

            fooMap.Insert(std::pair<Foo, int>(foo, 1));
            Library::HashMap<Foo, int> foocopy2(fooMap);
            Assert::AreEqual(fooMap.Size(), foocopy2.Size(),
                L"HashMap sizes not equal");
            Assert::IsFalse(fooMap.begin() == fooMap.end(),
                L"begin of non-empty HashMap equals end");
            Assert::IsFalse(foocopy2.begin() == foocopy2.end(),
                L"begin of non-empty HashMap equals end");
        }

        TEST_METHOD(TestAssignmentOperator_Integer)
        {
            Library::HashMap<int, int> intcopy1 = intMap;
            Assert::IsTrue(intMap.Size() == intcopy1.Size(),
                L"HashMap sizes not equal");

            intMap.Insert(std::pair<int, int>(1, 1));
            Library::HashMap<int, int> intcopy2 = intMap;
            Assert::AreEqual(intMap.Size(), intcopy2.Size(),
                L"HashMap sizes not equal");
            Assert::IsFalse(intMap.begin() == intMap.end(),
                L"begin of non-empty HashMap equals end");
            Assert::IsFalse(intcopy2.begin() == intcopy2.end(),
                L"begin of non-empty HashMap equals end");
        }

        TEST_METHOD(TestAssignmentOperator_Pointer)
        {
            Library::HashMap<int*, int> ptrcopy1 = ptrMap;
            Assert::IsTrue(ptrMap.Size() == ptrcopy1.Size(),
                L"HashMap sizes not equal");

            ptrMap.Insert(std::pair<int*, int>(&x, 1));
            Library::HashMap<int*, int> ptrcopy2 = ptrMap;
            Assert::AreEqual(ptrMap.Size(), ptrcopy2.Size(),
                L"HashMap sizes not equal");
            Assert::IsFalse(ptrMap.begin() == ptrMap.end(),
                L"begin of non-empty HashMap equals end");
            Assert::IsFalse(ptrcopy2.begin() == ptrcopy2.end(),
                L"begin of non-empty HashMap equals end");
        }

        TEST_METHOD(TestAssignmentOperator_CharStar)
        {
            Library::HashMap<char*, int> chrcopy1 = chrMap;
            Assert::IsTrue(chrMap.Size() == chrcopy1.Size(),
                L"HashMap sizes not equal");

            chrMap.Insert(std::pair<char*, int>(a, 1));
            Library::HashMap<char*, int> chrcopy2 = chrMap;
            Assert::AreEqual(chrMap.Size(), chrcopy2.Size(),
                L"HashMap sizes not equal");
            Assert::IsFalse(chrMap.begin() == chrMap.end(),
                L"begin of non-empty HashMap equals end");
            Assert::IsFalse(chrcopy2.begin() == chrcopy2.end(),
                L"begin of non-empty HashMap equals end");
        }

        TEST_METHOD(TestAssignmentOperator_String)
        {
            Library::HashMap<std::string, int> strcopy1 = strMap;
            Assert::IsTrue(strMap.Size() == strcopy1.Size(),
                L"HashMap sizes not equal");

            strMap.Insert(std::pair<std::string, int>(s, 1));
            Library::HashMap<std::string, int> strcopy2 = strMap;
            Assert::AreEqual(strMap.Size(), strcopy2.Size(),
                L"HashMap sizes not equal");
            Assert::IsFalse(strMap.begin() == strMap.end(),
                L"begin of non-empty HashMap equals end");
            Assert::IsFalse(strcopy2.begin() == strcopy2.end(),
                L"begin of non-empty HashMap equals end");
        }

        TEST_METHOD(TestAssignmentOperator_Foo)
        {
            Library::HashMap<Foo, int> foocopy1 = fooMap;
            Assert::IsTrue(fooMap.Size() == foocopy1.Size(),
                L"HashMap sizes not equal");

            fooMap.Insert(std::pair<Foo, int>(foo, 1));
            Library::HashMap<Foo, int> foocopy2 = fooMap;
            Assert::AreEqual(fooMap.Size(), foocopy2.Size(),
                L"HashMap sizes not equal");
            Assert::IsFalse(fooMap.begin() == fooMap.end(),
                L"begin of non-empty HashMap equals end");
            Assert::IsFalse(foocopy2.begin() == foocopy2.end(),
                L"begin of non-empty HashMap equals end");
        }

        TEST_METHOD(TestMoveSemantics_Integer)
        {
            Library::HashMap<int, int> map;
            for (int i = 0; i < 5; i++)
            {
                map[i] = i;
            }

            Assert::AreEqual(5u, map.Size());

            Library::HashMap<int, int> newMap = std::move(map);
            Assert::AreEqual(0u, map.Size());
            Assert::AreEqual(5u, newMap.Size());

            for (int i = 0; i < 5; i++)
            {
                Assert::AreEqual(i, newMap[i]);
            }
        }

        TEST_METHOD(TestMoveSemantics_Pointer)
        {
            int values[5] = { 1, 2, 3, 4, 5 };

            Library::HashMap<int*, int> map;
            for (int i = 0; i < 5; i++)
            {
                map[&values[i]] = i;
            }

            Assert::AreEqual(5u, map.Size());

            Library::HashMap<int*, int> newMap = std::move(map);
            Assert::AreEqual(0u, map.Size());
            Assert::AreEqual(5u, newMap.Size());

            for (int i = 0; i < 5; i++)
            {
                Assert::AreEqual(i, newMap[&values[i]]);
            }
        }

        TEST_METHOD(TestMoveSemantics_CharStar)
        {
            Library::HashMap<char*, int> map;
            char* values[5] = { "1", "2", "3", "4", "5" };

            for (int i = 0; i < 5; i++)
            {
                map[values[i]] = i;
            }

            Assert::AreEqual(5u, map.Size());

            Library::HashMap<char*, int> newMap = std::move(map);
            Assert::AreEqual(0u, map.Size());
            Assert::AreEqual(5u, newMap.Size());

            for (int i = 0; i < 5; i++)
            {
                Assert::AreEqual(i, newMap[values[i]]);
            }
        }

        TEST_METHOD(TestMoveSemantics_String)
        {
            Library::HashMap<std::string, int> map;
            std::string values[5] = { "one", "two", "three", "four", "five" };

            for (int i = 0; i < 5; i++)
            {
                map[values[i]] = i;
            }

            Assert::AreEqual(5u, map.Size());

            Library::HashMap<std::string, int> newMap = std::move(map);
            Assert::AreEqual(0u, map.Size());
            Assert::AreEqual(5u, newMap.Size());

            for (int i = 0; i < 5; i++)
            {
                Assert::AreEqual(i, newMap[values[i]]);
            }
        }

        TEST_METHOD(TestMoveSemantics_Foo)
        {
            Library::HashMap<Foo, int> map;
            Foo values[5] = { Foo(1), Foo(2), Foo(3), Foo(4), Foo(5) };

            for (int i = 0; i < 5; i++)
            {
                map[values[i]] = i;
            }

            Assert::AreEqual(5u, map.Size());

            Library::HashMap<Foo, int> newMap = std::move(map);
            Assert::AreEqual(0u, map.Size());
            Assert::AreEqual(5u, newMap.Size());

            for (int i = 0; i < 5; i++)
            {
                Assert::AreEqual(i, newMap[values[i]]);
            }
        }

        TEST_METHOD(TestFind_Integer)
        {
            Assert::IsTrue(intMap.Find(1) == intMap.end(),
                L"Find on empty HashMap does not return end");
            intMap.Insert(std::pair<int, int>(1, 1));
            Assert::IsTrue(intMap.Find(1) == intMap.begin(),
                L"Only value inserted into HashMap is not begin");
            Assert::IsFalse(intMap.Find(1) == intMap.end(),
                L"Find on existing value should not return end");
            Assert::AreEqual((*intMap.Find(1)).second, 1,
                L"Find returning incorrect value");
        }

        TEST_METHOD(TestFind_Pointer)
        {
            Assert::IsTrue(ptrMap.Find(&x) == ptrMap.end(),
                L"Find on empty HashMap does not return end");
            ptrMap.Insert(std::pair<int*, int>(&x, 1));
            Assert::IsTrue(ptrMap.Find(&x) == ptrMap.begin(),
                L"Only value inserted into HashMap is not Begin");
            Assert::IsFalse(ptrMap.Find(&x) == ptrMap.end(),
                L"Find on existing value should not return end");
            Assert::AreEqual((*ptrMap.Find(&x)).second, 1,
                L"Find returning incorrect value");
        }

        TEST_METHOD(TestFind_CharStar)
        {
            Assert::IsTrue(chrMap.Find(c) == chrMap.end(),
                L"Find on empty HashMap does not return end");
            chrMap.Insert(std::pair<char*, int>(c, 1));
            Assert::IsTrue(chrMap.Find(c) == chrMap.begin(),
                L"Only value inserted into HashMap is not begin");
            Assert::IsFalse(chrMap.Find(c) == chrMap.end(),
                L"Find on existing value should not return end");
            Assert::AreEqual((*chrMap.Find(c)).second, 1,
                L"Find returning incorrect value");
        }

        TEST_METHOD(TestFind_String)
        {
            Assert::IsTrue(strMap.Find(s) == strMap.end(),
                L"Find on empty HashMap does not return end");
            strMap.Insert(std::pair<std::string, int>(s, 1));
            Assert::IsTrue(strMap.Find(s) == strMap.begin(),
                L"Only value inserted into HashMap is not begin");
            Assert::IsFalse(strMap.Find(s) == strMap.end(),
                L"Find on existing value should not return end");
            Assert::AreEqual((*strMap.Find(s)).second, 1,
                L"Find returning incorrect value");
        }

        TEST_METHOD(TestFind_Foo)
        {
            Assert::IsTrue(fooMap.Find(foo) == fooMap.end(),
                L"Find on empty HashMap does not return end");
            fooMap.Insert(std::pair<Foo, int>(foo, 1));
            Assert::IsTrue(fooMap.Find(foo) == fooMap.begin(),
                L"Only value inserted into HashMap is not Begin");
            Assert::IsFalse(fooMap.Find(foo) == fooMap.end(),
                L"Find on existing value should not return end");
            Assert::AreEqual((*fooMap.Find(foo)).second, 1,
                L"Find returning incorrect value");
        }

        TEST_METHOD(TestInsert_Integer)
        {
            auto intInsert = intMap.Insert(std::pair<int, int>(1, 1));
            Assert::IsTrue(intInsert == intMap.begin(),
                L"Inserting first element should return begin");

            intMap.Insert(std::pair<int, int>(10, 1));
            Assert::IsTrue(intMap.ContainsKey(10),
                L"Key doesn't exist after inserting");
        }

        TEST_METHOD(TestInsert_Pointer)
        {
            auto ptrInsert = ptrMap.Insert(std::pair<int*, int>(&x, 1));
            Assert::IsTrue(ptrInsert == ptrMap.begin(),
                L"Inserting first element should return begin");

            ptrMap.Insert(std::pair<int*, int>(&y, 1));
            Assert::IsTrue(ptrMap.ContainsKey(&y),
                L"Key doesn't exist after inserting");
        }

        TEST_METHOD(TestInsert_CharStar)
        {
            auto chrInsert = chrMap.Insert(std::pair<char*, int>(a, 1));
            Assert::IsTrue(chrInsert == chrMap.begin(),
                L"Inserting first element should return begin");

            chrMap.Insert(std::pair<char*, int>(b, 1));
            Assert::IsTrue(chrMap.ContainsKey(b),
                L"Key doesn't exist after inserting");
        }

        TEST_METHOD(TestInsert_String)
        {
            auto strInsert = strMap.Insert(std::pair<std::string, int>(s, 1));
            Assert::IsTrue(strInsert == strMap.begin(),
                L"Inserting first element should return begin");

            strMap.Insert(std::pair<std::string, int>(t, 1));
            Assert::IsTrue(strMap.ContainsKey(t),
                L"Key doesn't exist after inserting");
        }

        TEST_METHOD(TestInsert_Foo)
        {
            auto fooInsert = fooMap.Insert(std::pair<Foo, int>(foo, 1));
            Assert::IsTrue(fooInsert == fooMap.begin(),
                L"Inserting first element should return begin");

            fooMap.Insert(std::pair<Foo, int>(bar, 1));
            Assert::IsTrue(fooMap.ContainsKey(bar),
                L"Key doesn't exist after inserting");
        }

        TEST_METHOD(TestRemove_Integer)
        {
            Assert::IsFalse(intMap.ContainsKey(1),
                L"Empty HashMap should not contain any keys");

            std::uint32_t intMapSize = intMap.Size();
            intMap.Insert(std::pair<const int, int>(1, 1));
            Assert::IsTrue(intMap.ContainsKey(1),
                L"Key doesn't exist in HashMap after inserting");
            Assert::AreNotEqual(intMapSize, intMap.Size(),
                L"Size not changing after inserting into HashMap");

            intMapSize = intMap.Size();
            intMap.Remove(1);
            Assert::IsFalse(intMap.ContainsKey(1),
                L"Key still exists in HashMap after removing");
            Assert::AreNotEqual(intMapSize, intMap.Size(),
                L"Size not changing after removing from HashMap");

            intMapSize = intMap.Size();
            intMap.Remove(1);
            Assert::AreEqual(intMapSize, intMap.Size(),
                L"Size should not change after removing non-existent key");
        }

        TEST_METHOD(TestRemove_Pointer)
        {
            Assert::IsFalse(ptrMap.ContainsKey(&x),
                L"Empty HashMap should not contain any keys");

            std::uint32_t ptrMapSize = ptrMap.Size();
            ptrMap.Insert(std::pair<int*, int>(&x, 1));
            Assert::IsTrue(ptrMap.ContainsKey(&x),
                L"Key doesn't exist in HashMap after inserting");
            Assert::AreNotEqual(ptrMapSize, ptrMap.Size(),
                L"Size not changing after inserting into HashMap");

            ptrMapSize = ptrMap.Size();
            ptrMap.Remove(&x);
            Assert::IsFalse(ptrMap.ContainsKey(&x),
                L"Key still exists in HashMap after removing");
            Assert::AreNotEqual(ptrMapSize, ptrMap.Size(),
                L"Size not changing after removing from HashMap");

            ptrMapSize = ptrMap.Size();
            ptrMap.Remove(&x);
            Assert::AreEqual(ptrMapSize, ptrMap.Size(),
                L"Size should not change after removing non-existent key");
        }

        TEST_METHOD(TestRemove_CharStar)
        {
            Assert::IsFalse(chrMap.ContainsKey(a),
                L"Empty HashMap should not contain any keys");

            std::uint32_t chrMapSize = chrMap.Size();
            chrMap.Insert(std::pair<char*, int>(a, 1));
            Assert::IsTrue(chrMap.ContainsKey(a),
                L"Key doesn't exist in HashMap after inserting");
            Assert::AreNotEqual(chrMapSize, chrMap.Size(),
                L"Size not changing after inserting into HashMap");

            chrMapSize = chrMap.Size();
            chrMap.Remove(a);
            Assert::IsFalse(chrMap.ContainsKey(a),
                L"Key still exists in HashMap after removing");
            Assert::AreNotEqual(chrMapSize, chrMap.Size(),
                L"Size not changing after removing from HashMap");

            chrMapSize = chrMap.Size();
            chrMap.Remove(a);
            Assert::AreEqual(chrMapSize, chrMap.Size(),
                L"Size should not change after removing non-existent key");
        }

        TEST_METHOD(TestRemove_String)
        {
            Assert::IsFalse(strMap.ContainsKey(s),
                L"Empty HashMap should not contain any keys");

            std::uint32_t strMapSize = strMap.Size();
            strMap.Insert(std::pair<std::string, int>(s, 1));
            Assert::IsTrue(strMap.ContainsKey(s),
                L"Key doesn't exist in HashMap after inserting");
            Assert::AreNotEqual(strMapSize, strMap.Size(),
                L"Size not changing after inserting into HashMap");

            strMapSize = strMap.Size();
            strMap.Remove(s);
            Assert::IsFalse(strMap.ContainsKey(s),
                L"Key still exists in HashMap after removing");
            Assert::AreNotEqual(strMapSize, strMap.Size(),
                L"Size not changing after removing from HashMap");

            strMapSize = strMap.Size();
            strMap.Remove(s);
            Assert::AreEqual(strMapSize, strMap.Size(),
                L"Size should not change after removing non-existent key");
        }

        TEST_METHOD(TestRemove_Foo)
        {
            Assert::IsFalse(fooMap.ContainsKey(foo),
                L"Empty HashMap should not contain any keys");

            std::uint32_t fooMapSize = fooMap.Size();
            fooMap.Insert(std::pair<Foo, int>(foo, 1));
            Assert::IsTrue(fooMap.ContainsKey(foo),
                L"Key doesn't exist in HashMap after inserting");
            Assert::AreNotEqual(fooMapSize, fooMap.Size(),
                L"Size not changing after inserting into HashMap");

            fooMapSize = fooMap.Size();
            fooMap.Remove(foo);
            Assert::IsFalse(fooMap.ContainsKey(foo),
                L"Key still exists in HashMap after removing");
            Assert::AreNotEqual(fooMapSize, fooMap.Size(),
                L"Size not changing after removing from HashMap");

            fooMapSize = fooMap.Size();
            fooMap.Remove(foo);
            Assert::AreEqual(fooMapSize, fooMap.Size(),
                L"Size should not change after removing non-existent key");
        }

        TEST_METHOD(TestIndexOperator_Integer)
        {
            std::uint32_t intMapSize = intMap.Size();
            auto& intMapVal = intMap[1];
            Assert::AreNotEqual(intMapSize, intMap.Size(),
                L"HashMap Size not increasing after indexing a non-existent key");

            intMap.Insert(std::pair<int, int>(1, 1));
            Assert::AreNotEqual(intMap[1], 1,
                L"Incorrect value returned with index operator");

            intMapVal = 1;
            Assert::AreEqual(1, intMap[1],
                L"HashMapValue not changed when assigned from index operator");

            const Library::HashMap<int, int> constIntMap(intMap);
            Assert::ExpectException<std::exception>([&] { constIntMap[2]; },
                L"Indexing nonexistent key value");
        }

        TEST_METHOD(TestIndexOperator_Pointer)
        {
            std::uint32_t ptrMapSize = ptrMap.Size();
            auto& ptrMapVal = ptrMap[&x];
            Assert::AreNotEqual(ptrMapSize, ptrMap.Size(),
                L"HashMap Size not increasing after indexing a non-existent key");

            ptrMap.Insert(std::pair<int*, int>(&x, 1));
            Assert::AreNotEqual(ptrMap[&x], 1,
                L"Incorrect value returned with index operator");

            ptrMapVal = 1;
            Assert::AreEqual(ptrMap[&x], 1,
                L"HashMapValue not changed when assigned from index operator");
        }

        TEST_METHOD(TestIndexOperator_CharStar)
        {
            std::uint32_t chrMapSize = chrMap.Size();
            auto& chrMapVal = chrMap[a];
            Assert::AreNotEqual(chrMapSize, chrMap.Size(),
                L"HashMap Size not increasing after indexing a non-existent key");

            chrMap.Insert(std::pair<char*, int>(a, 1));
            Assert::AreNotEqual(chrMap[a], 1,
                L"Incorrect value returned with index operator");

            chrMapVal = 1;
            Assert::AreEqual(chrMap[a], 1,
                L"HashMapValue not changed when assigned from index operator");
        }

        TEST_METHOD(TestIndexOperator_String)
        {
            std::uint32_t strMapSize = strMap.Size();
            auto& strMapVal = strMap[s];
            Assert::AreNotEqual(strMapSize, strMap.Size(),
                L"HashMap Size not increasing after indexing a non-existent key");

            strMap.Insert(std::pair<std::string, int>(s, 1));
            Assert::AreNotEqual(strMap[s], 1,
                L"Incorrect value returned with index operator");

            strMapVal = 1;
            Assert::AreEqual(strMap[s], 1,
                L"HashMapValue not changed when assigned from index operator");
        }

        TEST_METHOD(TestIndexOperator_Foo)
        {
            std::uint32_t fooMapSize = fooMap.Size();
            auto& fooMapVal = fooMap[foo];
            Assert::AreNotEqual(fooMapSize, fooMap.Size(),
                L"HashMap Size not increasing after indexing a non-existent key");

            fooMap.Insert(std::pair<Foo, int>(foo, 1));
            Assert::AreNotEqual(fooMap[foo], 1,
                L"Incorrect value returned with index operator");

            fooMapVal = 1;
            Assert::AreEqual(fooMap[foo], 1,
                L"HashMapValue not changed when assigned from index operator");
        }

        TEST_METHOD(TestConstIndexOperator_Integer)
        {
            Library::HashMap<int, int> map{};
            map[1] = 10;
            Assert::AreEqual(1u, map.Size(),
                L"HashMap Size not increasing after indexing a non-existent key");
            Assert::AreEqual(10, map[1]);
            Assert::AreEqual(10, const_cast<const Library::HashMap<int, int>*>(&map)->operator[](1));
        }

        TEST_METHOD(TestConstIndexOperator_Pointer)
        {
            Library::HashMap<int*, int> map{};
            int* key = new int(0);
            map[key] = 10;
            Assert::AreEqual(1u, map.Size(),
                L"HashMap size not increasing after indexing a non-existent key");
            Assert::AreEqual(10, map[key]);
            Assert::AreEqual(10, const_cast<const Library::HashMap<int*, int>*>(&map)->operator[](key));
            delete key;
        }

        TEST_METHOD(TestConstIndexOperator_CharStar)
        {
            Library::HashMap<char*, int> map{};
            char* key = new char(0);
            map[key] = 10;
            Assert::AreEqual(1u, map.Size(),
                L"HashMap size not increasing after indexing a non-existent key");
            Assert::AreEqual(10, map[key]);
            Assert::AreEqual(10, const_cast<const Library::HashMap<char*, int>*>(&map)->operator[](key));
            delete key;
        }

        TEST_METHOD(TestConstIndexOperator_String)
        {
            Library::HashMap<std::string, int> map{};
            std::string key = "key";
            map[key] = 10;
            Assert::AreEqual(1u, map.Size(),
                L"HashMap size not increasing after indexing a non-existent key");
            Assert::AreEqual(10, map[key]);
            Assert::AreEqual(10, const_cast<const Library::HashMap<std::string, int>*>(&map)->operator[](key));

        }

        TEST_METHOD(TestConstIndexOperator_Foo)
        {
            Library::HashMap<Foo, int> map{};
            Foo key(1);
            map[key] = 10;
            Assert::AreEqual(1u, map.Size(),
                L"HashMap size not increasing after indexing a non-existent key");
            Assert::AreEqual(10, map[key]);
            Assert::AreEqual(10, const_cast<const Library::HashMap<Foo, int>*>(&map)->operator[](key));
        }

        TEST_METHOD(TestBegin_Integer)
        {
            Assert::IsTrue(intMap.begin() == intMap.end(),
                L"begin does not equal end on empty HashMap");

            std::pair<const int, int> intPair(1, 1);
            intMap.Insert(intPair);
            Assert::IsTrue(intPair == *(intMap.begin()));

            intMap.Remove(1);
            Assert::IsTrue(intMap.begin() == intMap.end(),
                L"begin does not equal end on empty HashMap");
        }

        TEST_METHOD(TestBegin_Pointer)
        {
            Assert::IsTrue(ptrMap.begin() == ptrMap.end(),
                L"begin does not equal end on empty HashMap");

            std::pair<int* const, int> ptrPair(&x, 1);
            ptrMap.Insert(ptrPair);
            Assert::IsTrue(ptrPair == *(ptrMap.begin()));

            ptrMap.Remove(&x);
            Assert::IsTrue(ptrMap.begin() == ptrMap.end(),
                L"begin does not equal end on empty HashMap");
        }

        TEST_METHOD(TestBegin_CharStar)
        {
            Assert::IsTrue(chrMap.begin() == chrMap.end(),
                L"begin does not equal end on empty HashMap");

            std::pair<char* const, int> chrPair(a, 1);
            chrMap.Insert(chrPair);
            Assert::IsTrue(chrPair == *(chrMap.begin()));

            chrMap.Remove(a);
            Assert::IsTrue(chrMap.begin() == chrMap.end(),
                L"begin does not equal end on empty HashMap");
        }

        TEST_METHOD(TestBegin_String)
        {
            Assert::IsTrue(strMap.begin() == strMap.end(),
                L"begin does not equal end on empty HashMap");

            std::pair<const std::string, int> strPair(s, 1);
            strMap.Insert(strPair);
            Assert::IsTrue(strPair == *(strMap.begin()));

            strMap.Remove(s);
            Assert::IsTrue(strMap.begin() == strMap.end(),
                L"begin does not equal end on empty HashMap");
        }

        TEST_METHOD(TestBegin_Foo)
        {
            Assert::IsTrue(fooMap.begin() == fooMap.end(),
                L"begin does not equal end on empty HashMap");

            std::pair<const Foo, int> fooPair(foo, 1);
            fooMap.Insert(fooPair);
            Assert::IsTrue(fooPair == *(fooMap.begin()));

            fooMap.Remove(foo);
            Assert::IsTrue(fooMap.begin() == fooMap.end(),
                L"begin does not equal end on empty HashMap");
        }

        TEST_METHOD(TestEnd_Integer)
        {
            Assert::IsTrue(intMap.begin() == intMap.end(),
                L"begin should be equivalent to end on empty HashMap");
            intMap.Insert(std::pair<int, int>(1, 1));
            Assert::IsFalse(intMap.begin() == intMap.end(),
                L"begin should not be equivalent to end on non-empty HashMap");
            intMap.Remove(1);
            Assert::IsTrue(intMap.begin() == intMap.end(),
                L"begin should be equivalent to end on empty HashMap");
            auto intFunc = [&] { *intMap.end(); };
            Assert::ExpectException<std::exception>(intFunc,
                L"Dereferencing end of HashMap should throw exception");
        }

        TEST_METHOD(TestEnd_Pointer)
        {
            Assert::IsTrue(ptrMap.begin() == ptrMap.end(),
                L"begin should be equivalent to end on empty HashMap");
            ptrMap.Insert(std::pair<int*, int>(&x, 1));
            Assert::IsFalse(ptrMap.begin() == ptrMap.end(),
                L"begin should not be equivalent to end on non-empty HashMap");
            ptrMap.Remove(&x);
            Assert::IsTrue(ptrMap.begin() == ptrMap.end(),
                L"begin should be equivalent to end on empty HashMap");
            auto ptrFunc = [&] { *ptrMap.end(); };
            Assert::ExpectException<std::exception>(ptrFunc,
                L"Dereferencing end of HashMap should throw exception");
        }

        TEST_METHOD(TestEnd_CharStar)
        {
            Assert::IsTrue(chrMap.begin() == chrMap.end(),
                L"begin should be equivalent to end on empty HashMap");
            chrMap.Insert(std::pair<char*, int>(a, 1));
            Assert::IsFalse(chrMap.begin() == chrMap.end(),
                L"begin should not be equivalent to end on non-empty HashMap");
            chrMap.Remove(a);
            Assert::IsTrue(chrMap.begin() == chrMap.end(),
                L"begin should be equivalent to end on empty HashMap");
            auto chrFunc = [&] { *chrMap.end(); };
            Assert::ExpectException<std::exception>(chrFunc,
                L"Dereferencing end of HashMap should throw exception");
        }

        TEST_METHOD(TestEnd_String)
        {
            Assert::IsTrue(strMap.begin() == strMap.end(),
                L"begin should be equivalent to end on empty HashMap");
            strMap.Insert(std::pair<std::string, int>(s, 1));
            Assert::IsFalse(strMap.begin() == strMap.end(),
                L"begin should not be equivalent to end on non-empty HashMap");
            strMap.Remove(s);
            Assert::IsTrue(strMap.begin() == strMap.end(),
                L"begin should be equivalent to end on empty HashMap");
            auto strFunc = [&] { *strMap.end(); };
            Assert::ExpectException<std::exception>(strFunc,
                L"Dereferencing end of HashMap should throw exception");
        }

        TEST_METHOD(TestEnd_Foo)
        {
            Assert::IsTrue(fooMap.begin() == fooMap.end(),
                L"begin should be equivalent to end on empty HashMap");
            fooMap.Insert(std::pair<Foo, int>(foo, 1));
            Assert::IsFalse(fooMap.begin() == fooMap.end(),
                L"begin should not be equivalent to end on non-empty HashMap");
            fooMap.Remove(foo);
            Assert::IsTrue(fooMap.begin() == fooMap.end(),
                L"begin should be equivalent to end on empty HashMap");
            auto fooFunc = [&] { *fooMap.end(); };
            Assert::ExpectException<std::exception>(fooFunc,
                L"Dereferencing end of HashMap should throw exception");
        }

        TEST_METHOD(TestClear_Integer)
        {
            Assert::AreEqual(intMap.Size(), 0U,
                L"HashMap Size should be zero when empty");
            intMap.Insert(std::pair<int, int>(1, 1));
            Assert::IsTrue(intMap.Size() > 0,
                L"HashMap Size should be non-zero when not empty");
            intMap.Clear();
            Assert::AreEqual(intMap.Size(), 0U,
                L"HashMap Size should be zero when cleared");
            intMap.Clear();
            Assert::AreEqual(intMap.Size(), 0U,
                L"HashMap Size should be zero when clearing an empty HashMap");
        }

        TEST_METHOD(TestClear_Pointer)
        {
            Assert::AreEqual(ptrMap.Size(), 0U,
                L"HashMap Size should be zero when empty");
            ptrMap.Insert(std::pair<int*, int>(&x, 1));
            Assert::IsTrue(ptrMap.Size() > 0,
                L"HashMap Size should be non-zero when not empty");
            ptrMap.Clear();
            Assert::AreEqual(ptrMap.Size(), 0U,
                L"HashMap Size should be zero when cleared");
            ptrMap.Clear();
            Assert::AreEqual(ptrMap.Size(), 0U,
                L"HashMap Size should be zero when clearing an empty HashMap");
        }

        TEST_METHOD(TestClear_CharStar)
        {
            Assert::AreEqual(chrMap.Size(), 0U,
                L"HashMap Size should be zero when empty");
            chrMap.Insert(std::pair<char*, int>(a, 1));
            Assert::IsTrue(chrMap.Size() > 0,
                L"HashMap Size should be non-zero when not empty");
            chrMap.Clear();
            Assert::AreEqual(chrMap.Size(), 0U,
                L"HashMap Size should be zero when cleared");
            chrMap.Clear();
            Assert::AreEqual(chrMap.Size(), 0U,
                L"HashMap Size should be zero when clearing an empty HashMap");
        }

        TEST_METHOD(TestClear_String)
        {
            Assert::AreEqual(strMap.Size(), 0U, L"HashMap Size should be zero when empty");
            strMap.Insert(std::pair<std::string, int>(s, 1));
            Assert::IsTrue(strMap.Size() > 0,
                L"HashMap Size should be non-zero when not empty");
            strMap.Clear();
            Assert::AreEqual(strMap.Size(), 0U,
                L"HashMap Size should be zero when cleared");
            strMap.Clear();
            Assert::AreEqual(strMap.Size(), 0U,
                L"HashMap Size should be zero when clearing an empty HashMap");
        }

        TEST_METHOD(TestClear_Foo)
        {
            Assert::AreEqual(fooMap.Size(), 0U, L"HashMap Size should be zero when empty");
            fooMap.Insert(std::pair<Foo, int>(foo, 1));
            Assert::IsTrue(fooMap.Size() > 0,
                L"HashMap Size should be non-zero when not empty");
            fooMap.Clear();
            Assert::AreEqual(fooMap.Size(), 0U,
                L"HashMap Size should be zero when cleared");
            fooMap.Clear();
            Assert::AreEqual(fooMap.Size(), 0U,
                L"HashMap Size should be zero when clearing an empty HashMap");
        }

        TEST_METHOD(TestSize_Integer)
        {
            Assert::AreEqual(intMap.Size(), 0U,
                L"Length of empty HashMap should be zero");

            intMap.Insert(std::pair<int, int>(1, 1));
            Assert::AreEqual(intMap.Size(), 1U,
                L"Size should be one after inserting one item");

            intMap.Insert(std::pair<int, int>(2, 2));
            Assert::AreEqual(intMap.Size(), 2U,
                L"Size should increase when adding a value");

            intMap.Remove(10);
            Assert::AreEqual(intMap.Size(), 2U,
                L"Size should not change when removing a non-existent value");

            intMap.Remove(1);
            Assert::AreEqual(intMap.Size(), 1U,
                L"Size should decrease when removing an item");

            intMap.Clear();
            Assert::AreEqual(intMap.Size(), 0U,
                L"Size should be zero after clearing");
        }

        TEST_METHOD(TestSize_Pointer)
        {
            Assert::AreEqual(ptrMap.Size(), 0U,
                L"Length of empty HashMap should be zero");

            ptrMap.Insert(std::pair<int*, int>(&x, 1));
            Assert::AreEqual(ptrMap.Size(), 1U,
                L"Size should be one after inserting one item");

            ptrMap.Insert(std::pair<int*, int>(&y, 2));
            Assert::AreEqual(ptrMap.Size(), 2U,
                L"Size should increase when adding a value");

            ptrMap.Remove(&z);
            Assert::AreEqual(ptrMap.Size(), 2U,
                L"Size should not change when removing a non-existent value");

            ptrMap.Remove(&x);
            Assert::AreEqual(ptrMap.Size(), 1U,
                L"Size should decrease when removing an item");

            ptrMap.Clear();
            Assert::AreEqual(ptrMap.Size(), 0U,
                L"Size should be zero after clearing");
        }

        TEST_METHOD(TestSize_CharStar)
        {
            Assert::AreEqual(chrMap.Size(), 0U,
                L"Length of empty HashMap should be zero");

            chrMap.Insert(std::pair<char*, int>(a, 1));
            Assert::AreEqual(chrMap.Size(), 1U,
                L"Size should be one after inserting one item");

            chrMap.Insert(std::pair<char*, int>(b, 2));
            Assert::AreEqual(chrMap.Size(), 2U,
                L"Size should increase when adding a value");

            chrMap.Remove(c);
            Assert::AreEqual(chrMap.Size(), 2U,
                L"Size should not change when removing a non-existent value");

            chrMap.Remove(a);
            Assert::AreEqual(chrMap.Size(), 1U,
                L"Size should decrease when removing an item");

            chrMap.Clear();
            Assert::AreEqual(chrMap.Size(), 0U,
                L"Size should be zero after clearing");
        }

        TEST_METHOD(TestSize_String)
        {
            Assert::AreEqual(strMap.Size(), 0U,
                L"Length of empty HashMap should be zero");

            strMap.Insert(std::pair<std::string, int>(s, 1));
            Assert::AreEqual(strMap.Size(), 1U,
                L"Size should be one after inserting one item");

            strMap.Insert(std::pair<std::string, int>(t, 2));
            Assert::AreEqual(strMap.Size(), 2U,
                L"Size should increase when adding a value");

            strMap.Remove(u);
            Assert::AreEqual(strMap.Size(), 2U,
                L"Size should not change when removing a non-existent value");

            strMap.Remove(s);
            Assert::AreEqual(strMap.Size(), 1U,
                L"Size should decrease when removing an item");

            strMap.Clear();
            Assert::AreEqual(strMap.Size(), 0U,
                L"Size should be zero after clearing");
        }

        TEST_METHOD(TestSize_Foo)
        {
            Assert::AreEqual(fooMap.Size(), 0U,
                L"Length of empty HashMap should be zero");

            fooMap.Insert(std::pair<Foo, int>(foo, 1));
            Assert::AreEqual(fooMap.Size(), 1U,
                L"Size should be one after inserting one item");

            fooMap.Insert(std::pair<Foo, int>(bar, 2));
            Assert::AreEqual(fooMap.Size(), 2U,
                L"Size should increase when adding a value");

            fooMap.Remove(gar);
            Assert::AreEqual(fooMap.Size(), 2U,
                L"Size should not change when removing a non-existent value");

            fooMap.Remove(foo);
            Assert::AreEqual(fooMap.Size(), 1U,
                L"Size should decrease when removing an item");

            fooMap.Clear();
            Assert::AreEqual(fooMap.Size(), 0U,
                L"Size should be zero after clearing");
        }

        TEST_METHOD(TestContainsKey_Integer)
        {
            Assert::IsFalse(intMap.ContainsKey(1), L"Empty map should not contain any keys");

            intMap.Insert(std::pair<int, int>(1, 1));
            Assert::IsFalse(intMap.ContainsKey(10),
                L"Map should not contain a key that hasn't been inserted");
            Assert::IsTrue(intMap.ContainsKey(1),
                L"HashMap does not contain a key that has been inserted");

            intMap.Remove(1);
            Assert::IsFalse(intMap.ContainsKey(1),
                L"Map should not contain a key that has been removed");
        }

        TEST_METHOD(TestContainsKey_Pointer)
        {
            Assert::IsFalse(ptrMap.ContainsKey(&x),
                L"Empty map should not contain any keys");

            ptrMap.Insert(std::pair<int*, int>(&x, 1));
            Assert::IsFalse(ptrMap.ContainsKey(&y),
                L"Map should not contain a key that hasn't been inserted");
            Assert::IsTrue(ptrMap.ContainsKey(&x),
                L"HashMap does not contain a key that has been inserted");

            ptrMap.Remove(&x);
            Assert::IsFalse(ptrMap.ContainsKey(&x),
                L"Map should not contain a key that has been removed");
        }

        TEST_METHOD(TestContainsKey_CharStar)
        {
            Assert::IsFalse(chrMap.ContainsKey(a),
                L"Empty map should not contain any keys");

            chrMap.Insert(std::pair<char*, int>(a, 1));
            Assert::IsFalse(chrMap.ContainsKey(b),
                L"Map should not contain a key that hasn't been inserted");
            Assert::IsTrue(chrMap.ContainsKey(a),
                L"HashMap does not contain a key that has been inserted");

            chrMap.Remove(a);
            Assert::IsFalse(chrMap.ContainsKey(a),
                L"Map should not contain a key that has been removed");
        }

        TEST_METHOD(TestContainsKey_String)
        {
            Assert::IsFalse(strMap.ContainsKey(s),
                L"Empty map should not contain any keys");

            strMap.Insert(std::pair<std::string, int>(s, 1));
            Assert::IsFalse(strMap.ContainsKey(t),
                L"Map should not contain a key that hasn't been inserted");
            Assert::IsTrue(strMap.ContainsKey(s),
                L"HashMap does not contain a key that has been inserted");

            strMap.Remove(s);
            Assert::IsFalse(strMap.ContainsKey(s),
                L"Map should not contain a key that has been removed");
        }

        TEST_METHOD(TestContainsKey_Foo)
        {
            Assert::IsFalse(fooMap.ContainsKey(foo), L"Empty map should not contain any keys");

            fooMap.Insert(std::pair<Foo, int>(foo, 1));
            Assert::IsFalse(fooMap.ContainsKey(bar),
                L"Map should not contain a key that hasn't been inserted");
            Assert::IsTrue(fooMap.ContainsKey(foo),
                L"HashMap does not contain a key that has been inserted");

            fooMap.Remove(foo);
            Assert::IsFalse(fooMap.ContainsKey(foo),
                L"Map should not contain a key that has been removed");
        }

        TEST_METHOD(TestIteratorCopyConstructor_Integer)
        {
            auto interator_1(intMap.begin());
            Assert::IsTrue(interator_1 == intMap.begin() && interator_1 == intMap.end(),
                L"Iterator copy should be equivalent to begin and end of empty HashMap");

            intMap.Insert(std::pair<int, int>(1, 1));
            auto interator_2(intMap.begin());
            Assert::IsTrue(interator_2 == intMap.begin() && interator_2 != intMap.end(),
                L"Iterator copy should be equivalent to only the value it's assigned to");

            auto interator_3(intMap.end());
            Assert::IsTrue(interator_3 != intMap.begin() && interator_3 == intMap.end(),
                L"Iterator copy should be equivalent to only the value it's assigned to");

            auto interator_4(intMap.Find(1));
            intMap.Clear();
            Assert::IsTrue(interator_4 != intMap.Find(1),
                L"Find on empty map not returning End()");
        }

        TEST_METHOD(TestIteratorCopyConstructor_Pointer)
        {
            auto pointerator_1(ptrMap.begin());
            Assert::IsTrue(pointerator_1 == ptrMap.begin() && pointerator_1 == ptrMap.end(),
                L"Iterator copy should be equivalent to begin and end of empty HashMap");

            ptrMap.Insert(std::pair<int*, int>(&x, 1));
            auto pointerator_2(ptrMap.begin());
            Assert::IsTrue(pointerator_2 == ptrMap.begin() && pointerator_2 != ptrMap.end(),
                L"Iterator copy should be equivalent to only the value it's assigned to");

            auto pointerator_3(ptrMap.end());
            Assert::IsTrue(pointerator_3 != ptrMap.begin() && pointerator_3 == ptrMap.end(),
                L"Iterator copy should be equivalent to only the value it's assigned to");

            auto pointerator_4(ptrMap.Find(&x));
            ptrMap.Clear();
            Assert::IsTrue(pointerator_4 != ptrMap.Find(&x),
                L"Find on empty map not returning End()");
        }

        TEST_METHOD(TestIteratorCopyConstructor_CharStar)
        {
            auto charterator_1(chrMap.begin());
            Assert::IsTrue(charterator_1 == chrMap.begin() && charterator_1 == chrMap.end(),
                L"Iterator copy should be equivalent to begin and end of empty HashMap");

            chrMap.Insert(std::pair<char*, int>(a, 1));
            auto charterator_2(chrMap.begin());
            Assert::IsTrue(charterator_2 == chrMap.begin() && charterator_2 != chrMap.end(),
                L"Iterator copy should be equivalent to only the value it's assigned to");

            auto charterator_3(chrMap.end());
            Assert::IsTrue(charterator_3 != chrMap.begin() && charterator_3 == chrMap.end(),
                L"Iterator copy should be equivalent to only the value it's assigned to");

            auto charterator_4(chrMap.Find(a));
            chrMap.Clear();
            Assert::IsTrue(charterator_4 != chrMap.Find(a),
                L"Find on empty map not returning End()");
        }

        TEST_METHOD(TestIteratorCopyConstructor_String)
        {
            auto stringerator_1(strMap.begin());
            Assert::IsTrue(stringerator_1 == strMap.begin() && stringerator_1 == strMap.end(),
                L"Iterator copy should be equivalent to begin and end of empty HashMap");

            strMap.Insert(std::pair<std::string, int>(s, 1));
            auto stringerator_2(strMap.begin());
            Assert::IsTrue(stringerator_2 == strMap.begin() && stringerator_2 != strMap.end(),
                L"Iterator copy should be equivalent to only the value it's assigned to");

            auto stringerator_3(strMap.end());
            Assert::IsTrue(stringerator_3 != strMap.begin() && stringerator_3 == strMap.end(),
                L"Iterator copy should be equivalent to only the value it's assigned to");

            auto stringerator_4(strMap.Find(s));
            strMap.Clear();
            Assert::IsTrue(stringerator_4 != strMap.Find(s),
                L"Find on empty map not returning End()");
        }

        TEST_METHOD(TestIteratorCopyConstructor_Foo)
        {
            auto footerator_1(fooMap.begin());
            Assert::IsTrue(footerator_1 == fooMap.begin() && footerator_1 == fooMap.end(),
                L"Iterator copy should be equivalent to begin and end of empty HashMap");

            fooMap.Insert(std::pair<Foo, int>(foo, 1));
            auto footerator_2(fooMap.begin());
            Assert::IsTrue(footerator_2 == fooMap.begin() && footerator_2 != fooMap.end(),
                L"Iterator copy should be equivalent to only the value it's assigned to");

            auto footerator_3(fooMap.end());
            Assert::IsTrue(footerator_3 != fooMap.begin() && footerator_3 == fooMap.end(),
                L"Iterator copy should be equivalent to only the value it's assigned to");

            auto footerator_4(fooMap.Find(foo));
            fooMap.Clear();
            Assert::IsTrue(footerator_4 != fooMap.Find(foo),
                L"Find on empty map not returning End()");
        }

        TEST_METHOD(TestIteratorAssignmentOperator_Integer)
        {
            auto interator_1 = intMap.begin();
            Assert::IsTrue(interator_1 == intMap.begin() && interator_1 == intMap.end(),
                L"Iterator copy should be equivalent to begin and end of empty HashMap");

            intMap.Insert(std::pair<int, int>(1, 1));
            auto interator_2 = intMap.begin();
            Assert::IsTrue(interator_2 == intMap.begin() && interator_2 != intMap.end(),
                L"Iterator copy should be equivalent to only the value it's assigned to");

            auto interator_3 = intMap.end();
            Assert::IsTrue(interator_3 != intMap.begin() && interator_3 == intMap.end(),
                L"Iterator copy should be equivalent to only the value it's assigned to");

            auto interator_4 = intMap.Find(1);
            intMap.Clear();
            Assert::IsTrue(interator_4 != intMap.Find(1),
                L"Find on empty map not returning End()");
        }

        TEST_METHOD(TestIteratorAssignmentOperator_Pointer)
        {
            auto pointerator_1 = ptrMap.begin();
            Assert::IsTrue(pointerator_1 == ptrMap.begin() && pointerator_1 == ptrMap.end(),
                L"Iterator copy should be equivalent to begin and end of empty HashMap");

            ptrMap.Insert(std::pair<int*, int>(&x, 1));
            auto pointerator_2 = ptrMap.begin();
            Assert::IsTrue(pointerator_2 == ptrMap.begin() && pointerator_2 != ptrMap.end(),
                L"Iterator copy should be equivalent to only the value it's assigned to");

            auto pointerator_3 = ptrMap.end();
            Assert::IsTrue(pointerator_3 != ptrMap.begin() && pointerator_3 == ptrMap.end(),
                L"Iterator copy should be equivalent to only the value it's assigned to");

            auto pointerator_4 = ptrMap.Find(&x);
            ptrMap.Clear();
            Assert::IsTrue(pointerator_4 != ptrMap.Find(&x),
                L"Find on empty map not returning End()");
        }

        TEST_METHOD(TestIteratorAssignmentOperator_CharStar)
        {
            auto charterator_1 = chrMap.begin();
            Assert::IsTrue(charterator_1 == chrMap.begin() && charterator_1 == chrMap.end(),
                L"Find on empty map not returning End()");

            chrMap.Insert(std::pair<char*, int>(a, 1));
            auto charterator_2 = chrMap.begin();
            Assert::IsTrue(charterator_2 == chrMap.begin() && charterator_2 != chrMap.end(),
                L"Find on empty map not returning End()");

            auto charterator_3 = chrMap.end();
            Assert::IsTrue(charterator_3 != chrMap.begin() && charterator_3 == chrMap.end(),
                L"Find on empty map not returning End()");

            auto charterator_4 = chrMap.Find(a);
            chrMap.Clear();
            Assert::IsTrue(charterator_4 != chrMap.Find(a),
                L"Find on empty map not returning End()");
        }

        TEST_METHOD(TestIteratorAssignmentOperator_String)
        {
            auto stringerator_1 = strMap.begin();
            Assert::IsTrue(stringerator_1 == strMap.begin() && stringerator_1 == strMap.end(),
                L"Find on empty map not returning End()");

            strMap.Insert(std::pair<std::string, int>(s, 1));
            auto stringerator_2 = strMap.begin();
            Assert::IsTrue(stringerator_2 == strMap.begin() && stringerator_2 != strMap.end(),
                L"Find on empty map not returning End()");

            auto stringerator_3 = strMap.end();
            Assert::IsTrue(stringerator_3 != strMap.begin() && stringerator_3 == strMap.end(),
                L"Find on empty map not returning End()");

            auto stringerator_4 = strMap.Find(s);
            strMap.Clear();
            Assert::IsTrue(stringerator_4 != strMap.Find(s),
                L"Find on empty map not returning End()");
        }

        TEST_METHOD(TestIteratorAssignmentOperator_Foo)
        {
            auto footerator_1 = fooMap.begin();
            Assert::IsTrue(footerator_1 == fooMap.begin() && footerator_1 == fooMap.end(),
                L"Find on empty map not returning End()");

            fooMap.Insert(std::pair<Foo, int>(foo, 1));
            auto footerator_2 = fooMap.begin();
            Assert::IsTrue(footerator_2 == fooMap.begin() && footerator_2 != fooMap.end(),
                L"Find on empty map not returning End()");

            auto footerator_3 = fooMap.end();
            Assert::IsTrue(footerator_3 != fooMap.begin() && footerator_3 == fooMap.end(),
                L"Find on empty map not returning End()");

            auto footerator_4 = fooMap.Find(foo);
            fooMap.Clear();
            Assert::IsTrue(footerator_4 != fooMap.Find(foo),
                L"Find on empty map not returning End()");
        }

        TEST_METHOD(TestIteratorIncrementOperator_Integer)
        {
            intMap.Insert(std::pair<int, int>(1, 1));
            intMap.Insert(std::pair<int, int>(2, 2));
            auto interator = intMap.begin();
            Assert::IsTrue(interator == intMap.begin() && ++interator != intMap.end(),
                L"Incrementing past existing values");
            Assert::IsTrue(++interator == intMap.end() && ++interator == intMap.end(),
                L"Incrementing past end should still return end");
        }

        TEST_METHOD(TestIteratorIncrementOperator_Pointer)
        {
            ptrMap.Insert(std::pair<int*, int>(&x, 1));
            ptrMap.Insert(std::pair<int*, int>(&y, 2));
            auto pointerator = ptrMap.begin();
            Assert::IsTrue(pointerator == ptrMap.begin() && ++pointerator != ptrMap.end(),
                L"Incrementing past existing values");
            Assert::IsTrue(++pointerator == ptrMap.end() && ++pointerator == ptrMap.end(),
                L"Incrementing past end should still return end");
        }

        TEST_METHOD(TestIteratorIncrementOperator_CharStar)
        {
            chrMap.Insert(std::pair<char*, int>(a, 1));
            chrMap.Insert(std::pair<char*, int>(b, 2));
            auto charterator = chrMap.begin();
            Assert::IsTrue(charterator == chrMap.begin() && ++charterator != chrMap.end(),
                L"Incrementing past existing values");
            Assert::IsTrue(++charterator == chrMap.end() && ++charterator == chrMap.end(),
                L"Incrementing past end should still return end");
        }

        TEST_METHOD(TestIteratorIncrementOperator_String)
        {
            strMap.Insert(std::pair<std::string, int>(s, 1));
            strMap.Insert(std::pair<std::string, int>(t, 2));
            auto stringerator = strMap.begin();
            Assert::IsTrue(stringerator == strMap.begin() && ++stringerator != strMap.end(),
                L"Incrementing past existing values");
            Assert::IsTrue(++stringerator == strMap.end() && ++stringerator == strMap.end(),
                L"Incrementing past end should still return end");
        }

        TEST_METHOD(TestIteratorIncrementOperator_Foo)
        {
            fooMap.Insert(std::pair<Foo, int>(foo, 1));
            fooMap.Insert(std::pair<Foo, int>(bar, 2));
            auto footerator = fooMap.begin();
            Assert::IsTrue(footerator == fooMap.begin() && ++footerator != fooMap.end(),
                L"Incrementing past existing values");
            Assert::IsTrue(++footerator == fooMap.end() && ++footerator == fooMap.end(),
                L"Incrementing past end should still return end");
        }

        TEST_METHOD(TestIteratorDereferenceOperator_Integer)
        {
            auto intFunc = [&] { *intMap.begin(); };
            Assert::ExpectException<std::exception>(intFunc);

            intMap.Insert(std::pair<int, int>(1, 1));
            Assert::AreEqual(1, (*intMap.begin()).first);
            Assert::AreEqual(1, (*intMap.begin()).second);
        }

        TEST_METHOD(TestIteratorDereferenceOperator_Pointer)
        {
            auto ptrFunc = [&] { *ptrMap.begin(); };
            Assert::ExpectException<std::exception>(ptrFunc);

            ptrMap.Insert(std::pair<int*, int>(&x, 1));
            Assert::AreEqual(&x, (*ptrMap.begin()).first);
            Assert::AreEqual(1, (*ptrMap.begin()).second);
        }

        TEST_METHOD(TestIteratorDereferenceOperator_CharStar)
        {
            auto chrFunc = [&] { *chrMap.begin(); };
            Assert::ExpectException<std::exception>(chrFunc);

            chrMap.Insert(std::pair<char*, int>(a, 1));
            Assert::AreEqual(a, (*chrMap.begin()).first);
            Assert::AreEqual(1, (*chrMap.begin()).second);
        }

        TEST_METHOD(TestIteratorDereferenceOperator_String)
        {
            auto strFunc = [&] { *strMap.begin(); };
            Assert::ExpectException<std::exception>(strFunc);

            strMap.Insert(std::pair<std::string, int>(s, 1));
            Assert::AreEqual(s, (*strMap.begin()).first);
            Assert::AreEqual(1, (*strMap.begin()).second);
        }

        TEST_METHOD(TestIteratorDereferenceOperator_Foo)
        {
            auto fooFunc = [&] { *fooMap.begin(); };
            Assert::ExpectException<std::exception>(fooFunc);

            fooMap.Insert(std::pair<Foo, int>(foo, 1));
            Assert::IsTrue(foo == (*fooMap.begin()).first);
            Assert::AreEqual(1, (*fooMap.begin()).second);
        }

        TEST_METHOD(TestIteratorArrowOperator_Integer)
        {
            auto intFunc = [&] { *intMap.begin(); };
            Assert::ExpectException<std::exception>(intFunc);

            intMap.Insert(std::pair<int, int>(1, 1));
            Assert::AreEqual(1, intMap.begin()->first);
            Assert::AreEqual(1, intMap.begin()->second);
        }

        TEST_METHOD(TestIteratorArrowOperator_Pointer)
        {
            auto ptrFunc = [&] { *ptrMap.begin(); };
            Assert::ExpectException<std::exception>(ptrFunc);

            ptrMap.Insert(std::pair<int*, int>(&x, 1));
            Assert::AreEqual(&x, ptrMap.begin()->first);
            Assert::AreEqual(1, ptrMap.begin()->second);
        }

        TEST_METHOD(TestIteratorArrowOperator_CharStar)
        {
            auto chrFunc = [&] { *chrMap.begin(); };
            Assert::ExpectException<std::exception>(chrFunc);

            chrMap.Insert(std::pair<char*, int>(a, 1));
            Assert::AreEqual(a, chrMap.begin()->first);
            Assert::AreEqual(1, chrMap.begin()->second);
        }

        TEST_METHOD(TestIteratorArrowOperator_String)
        {
            auto strFunc = [&] { *strMap.begin(); };
            Assert::ExpectException<std::exception>(strFunc);

            strMap.Insert(std::pair<std::string, int>(s, 1));
            Assert::AreEqual(s, strMap.begin()->first);
            Assert::AreEqual(1, strMap.begin()->second);
        }

        TEST_METHOD(TestIteratorArrowOperator_Foo)
        {
            auto fooFunc = [&] { *fooMap.begin(); };
            Assert::ExpectException<std::exception>(fooFunc);

            fooMap.Insert(std::pair<Foo, int>(foo, 1));
            Assert::IsTrue(foo == fooMap.begin()->first);
            Assert::AreEqual(1, fooMap.begin()->second);
        }

    };

}