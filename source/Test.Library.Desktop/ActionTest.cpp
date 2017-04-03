#include "pch.h"
#include "CppUnitTest.h"
#include "TestSharedData.h"
#include "Datum.h"
#include "XmlParseHelperEntity.h"
#include "GameTime.h"
#include "Factory.h"
#include "World.h"
#include "Sector.h"
#include "Entity.h"
#include "Action.h"
#include "ActionList.h"
#include "WorldState.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;


namespace TestLibraryDesktop
{
	TEST_CLASS(ActionTest)
	{
	public:

		ActionListFactory mActionListFactory;
		EntityFactory mEntityFactory;

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

		TEST_METHOD(UpdateLeakTest)
		{
			World* world = new World();
			Sector* sector = world->createSector("Dales Sector");
			Entity* entity = sector->createEntity("Entity", "Dale");
			Action* action = entity->createAction("ActionList", "DoThing");

			WorldState worldState;
			GameTime gameTime;

			world->update(worldState, gameTime);
			Assert::IsTrue(world != nullptr && sector != nullptr && entity != nullptr && action != nullptr);

			delete world;
		}

		TEST_METHOD(TestCreateAction)
		{
			Entity* entity = new Entity();
			Action* action = entity->createAction("ActionList", "newAction");
			Assert::IsTrue(action != nullptr);
			delete entity;
		}

		TEST_METHOD(TestName)
		{
			ActionList actionList;
			Assert::IsTrue(actionList.name() == "");
			actionList.setName("Dale");
			Assert::IsTrue(actionList.name() == "Dale");
		}

		static _CrtMemState sStartMemState;
	};
	_CrtMemState ActionTest::sStartMemState;
}