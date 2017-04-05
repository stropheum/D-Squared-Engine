#include "pch.h"
#include "CppUnitTest.h"
#include "TestSharedData.h"
#include "Datum.h"
#include "GameTime.h"
#include "Factory.h"
#include "World.h"
#include "Sector.h"
#include "Entity.h"
#include "Action.h"
#include "ActionList.h"
#include "WorldState.h"
#include "ActionCreateAction.h"
#include "Scope.h"
#include "ActionDestroyAction.h"
#include "ActionListIf.h"
#include "SharedDataScope.h"
#include "XmlParseHelperEntity.h"
#include "ActionIncrement.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;


namespace TestLibraryDesktop
{
	TEST_CLASS(ActionTest)
	{
	public:

		EntityFactory mEntityFactory;
		ActionListFactory mActionListFactory;
		ActionCreateActionFactory mActionCreateActionFactory;
		ActionDestroyActionFactory mActionDestroyActionFactory;
		ActionListIfFactory mActionListIfFactory;
		ActionIncrementFactory mActionIncrementFactory;

		std::string xmlGrammar = 
			"<world Name='Dales World>"
				"<Sector Name='Dales Sector'>"
					"<Entity ClassName='Entity' InstanceName='Dale'>"
						"<Integer Name='Health' value='100' />"
						"<Float Name='Power' Value='12.34 />"
						"<Vector Name='Position' X='1.0' Y='2.0' Z='3.0' W='4.0' />"
					"</Entity>"
				"</Sector>"
			"</World>"
		;

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

		TEST_METHOD(TestActionCreateAction)
		{
			WorldState worldState;

			ActionList aList;
			aList.createAction("ActionCreateAction", "ActionCreateActionGenerically");

			ActionCreateAction* aca1 = aList["Actions"].get<Scope*>(0)->As<ActionCreateAction>();
			Assert::IsTrue(aca1 != nullptr);
			aca1->setPrototype("ActionList");
			aca1->setName("MyActionList");
			aList.update(worldState);

			Assert::IsTrue(aList["Actions"].get<Scope*>(1)->Is(ActionList::TypeIdClass()));
		}

		TEST_METHOD(TestActionDestroyAction)
		{
			WorldState worldState;

			ActionList actionList;
			actionList.createAction("ActionList", "MyActionList");

			ActionList* childActionList = actionList["Actions"].get<Scope*>(0)->As<ActionList>();
			Assert::IsTrue(childActionList != nullptr);

			ActionDestroyAction* destroyAction = 
				childActionList->createAction("ActionDestroyAction", "MyDestroyAction")->As<ActionDestroyAction>();
			destroyAction->setActionInstanceName("MyActionList");

			actionList.update(worldState);
		}

		TEST_METHOD(TestActionListIf)
		{
			WorldState worldState;

			ActionList actionList;
			ActionListIf* ifList = actionList.createAction("ActionListIf", "MyIf")->As<ActionListIf>();

			ifList->setCondition(true);
			actionList.update(worldState);
			ifList->setCondition(false);
			actionList.update(worldState);
		}

		TEST_METHOD(TestParse)
		{
			WorldState state;
			GameTime time;
			Library::SharedDataScope sharedData;
			Library::XmlParseMaster parseMaster(&sharedData);
			Library::XmlParseHelperEntity helper;
			sharedData.setXmlParseMaster(&parseMaster);
			parseMaster.addHelper(helper);

			parseMaster.parseFromFile("ActionGrammar.xml");

			World* world = sharedData.mScope->As<World>();
			Assert::IsTrue(world != nullptr);
			Assert::IsTrue(world->name() == "Dales World");

			Sector* sector = world->sectors().get<Scope*>(0)->As<Sector>();
			Assert::IsTrue(sector != nullptr);
			Assert::IsTrue(sector->name() == "Dales Sector");

			Entity* entity = sector->entities().get<Scope*>(0)->As<Entity>();
			Assert::IsTrue(entity != nullptr);
			Assert::IsTrue(entity->name() == "Dale");

			Action* action = entity->actions().get<Scope*>(0)->As<Action>();
			Assert::IsTrue(action != nullptr);
			Assert::IsTrue(action->name() == "MyList");
			Assert::IsTrue(action->Is(ActionListIf::TypeIdClass()));

			Action* then = (*action->As<ActionList>())["Then"].get<Scope*>(0)->As<Action>();
			Assert::IsTrue(then != nullptr);

			Assert::IsTrue(then->Is(ActionIncrement::TypeIdClass()));
			
			Assert::AreEqual(then->As<ActionIncrement>()->getIncrementCount(), 0);
			world->update(state, time);

			Assert::AreEqual(then->As<ActionIncrement>()->getIncrementCount(), 1);
		}

		static _CrtMemState sStartMemState;
	};
	_CrtMemState ActionTest::sStartMemState;
}