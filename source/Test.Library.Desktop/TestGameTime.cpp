#include "pch.h"
#include "CppUnitTest.h"
#include "LeakDetector.h"
#include "Event.h"
#include "EventQueue.h"
#include "GameTime.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;
using namespace std;
using namespace chrono;

namespace TestLibraryDesktop
{
	TEST_CLASS(GameTimeTest)
	{
	public:

		TEST_METHOD_INITIALIZE(InitializeMethod)
		{
			LeakDetector::Initialize();
		}

		TEST_METHOD_CLEANUP(CleanupMethod)
		{
			LeakDetector::Finalize();
		}

		TEST_METHOD(TestConstruction)
		{
			GameTime gameTime;
			UNREFERENCED_PARAMETER(gameTime);
		}

		TEST_METHOD(TestCurrentTime)
		{
			GameTime gameTime;
			Assert::IsTrue(gameTime.CurrentTime() == high_resolution_clock::time_point());

			high_resolution_clock::time_point point = high_resolution_clock::now();
			gameTime.SetCurrentTime(point);
			Assert::IsTrue(gameTime.CurrentTime() == point);

			point = high_resolution_clock::now();
			gameTime.SetCurrentTime(point);
			Assert::IsTrue(gameTime.CurrentTime() == point);
		}

		TEST_METHOD(TestTotalGameTime)
		{
			GameTime gameTime;
			Assert::IsTrue(gameTime.TotalGameTime() == milliseconds(0));

			milliseconds totalGameTime(500);
			gameTime.SetTotalGameTime(totalGameTime);
			Assert::IsTrue(gameTime.TotalGameTime() == totalGameTime);
		}

		TEST_METHOD(TestElapsedGameTime)
		{
			GameTime gameTime;
			Assert::IsTrue(gameTime.ElapsedGameTime() == milliseconds(0));

			milliseconds elapsed(500);
			gameTime.SetElapsedGameTime(elapsed);
			Assert::IsTrue(gameTime.ElapsedGameTime() == elapsed);
		}

	};

}