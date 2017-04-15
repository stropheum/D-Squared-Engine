#include "pch.h"
#include "CppUnitTest.h"
#include "TestSharedData.h"
#include "GameTime.h"
#include "World.h"
#include "Sector.h"
#include "Entity.h"
#include "ActionList.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h"
#include "ActionListIf.h"
#include "ActionIncrement.h"
#include "ActionEvent.h"
#include "ReactionAttributed.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::chrono;
using namespace Library;


namespace TestLibraryDesktop
{
	TEST_CLASS(ReactionTest)
	{
	public:

		EntityFactory mEntityFactory;
		ActionListFactory mActionListFactory;
		ActionEventFactory mActionEventFactory;
		ActionCreateActionFactory mActionCreateActionFactory;
		ActionDestroyActionFactory mActionDestroyActionFactory;
		ActionListIfFactory mActionListIfFactory;
		ActionIncrementFactory mActionIncrementFactory;

		/// Sets up leak detection logic
		static void initializeLeakDetection()
		{
#if _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif //_DEBUG
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
#endif //_DEBUG
		}

		TEST_METHOD_INITIALIZE(methodInitialize)
		{
			initializeLeakDetection();
		}

		TEST_METHOD_CLEANUP(methodCleanup)
		{
			finalizeLeakDetection();
		}

		TEST_METHOD(TestStub)
		{
//			WorldState worldState;
//			GameTime gameTime;
//			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(0)));
//			worldState.setGameTime(gameTime);
//
//			World* world = new World();
//			Sector* sector = world->createSector("Dale Sector");
//			Entity* entity = sector->createEntity("Entity", "Dale");
//			entity->createAction("ActionEvent", "MyActionEvenqt");
//			
//			ReactionAttributed myReactionAttributed;
//
//			world->update(worldState, gameTime);
//			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(100)));
//			world->update(worldState, gameTime);
//
//			delete world;
		}

		TEST_METHOD(TestActionEvent)
		{
			World* myworld = new World();
			WorldState worldState;
			worldState.world = myworld;
			GameTime gameTime;
			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(0)));
			worldState.setGameTime(gameTime);

			ActionEvent actionEvent;
			actionEvent.update(worldState);

			delete myworld;
		}

		static _CrtMemState sStartMemState;
	};
	_CrtMemState ReactionTest::sStartMemState;
}