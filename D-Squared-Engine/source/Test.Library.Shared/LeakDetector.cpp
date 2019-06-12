#include "pch.h"
#include "LeakDetector.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{

    _CrtMemState LeakDetector::s_startMemstate;

    void LeakDetector::Initialize()
    {
#if _DEBUG
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
        _CrtMemCheckpoint(&s_startMemstate);
#endif //_DEBUG
    }

    void LeakDetector::Finalize()
    {
#if _DEBUG
        _CrtMemState endMemState, diffMemState;
        _CrtMemCheckpoint(&endMemState);
        if (_CrtMemDifference(&diffMemState, &s_startMemstate, &endMemState))
        {
            _CrtMemDumpStatistics(&diffMemState);
            Assert::Fail(L"Memory Leaks!");
        }
#endif //_DEBUG
    }

}