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
#include "Datum.h"
#include "EventMessageAttributed.h"


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

		TEST_METHOD(TestReactionAttributed)
		{
			WorldState worldState;
			GameTime gameTime;
			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(0)));
			worldState.setGameTime(gameTime);

			World* world = new World();
			Sector* sector = world->createSector("Dale Sector");
			Entity* entity = sector->createEntity("Entity", "Dale");
			Action* actionEvent = entity->createAction("ActionEvent", "First Action");
			actionEvent->As<ActionEvent>()->setSubtype("Physical Attack");
			
			(*actionEvent)["Power"] = 100;
			
			ReactionAttributed physicalReaction , magicalReaction;
			physicalReaction.setSubtype("Physical Attack");
			magicalReaction.setSubtype("Magical Attack");

			Assert::IsTrue(physicalReaction["Power"].type() == DatumType::Unknown);
			Assert::IsTrue(magicalReaction["Power"].type() == DatumType::Unknown);

			world->update(worldState, gameTime);
			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(100)));
			world->update(worldState, gameTime);

//			Assert::IsTrue(physicalReaction["Power"].type() == DatumType::Integer);
//			std::int32_t power = physicalReaction["Power"].get<std::int32_t>(0);
//			Assert::AreEqual(power, 100);
//			Assert::IsFalse(magicalReaction["Power"].type() == DatumType::Integer);

			delete world;
		}

		TEST_METHOD(TestMultipleReactions)
		{
			WorldState worldState;
			GameTime gameTime;
			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(0)));
			worldState.setGameTime(gameTime);

			World* world = new World();
			Sector* sector = world->createSector("Dale Sector");
			Entity* entity = sector->createEntity("Entity", "Dale");

			Action* actionEvent1 = entity->createAction("ActionEvent", "First Action");
			actionEvent1->As<ActionEvent>()->setSubtype("Physical Attack");
			(*actionEvent1)["Power"] = 100;

			ReactionAttributed reaction1, reaction2;
			reaction1.setSubtype("Physical Attack");
			reaction2.setSubtype("Physical Attack");

			Assert::IsTrue(reaction1["Power"].type() == DatumType::Unknown);
			Assert::IsTrue(reaction2["Power"].type() == DatumType::Unknown);

			world->update(worldState, gameTime);
			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(100)));
			world->update(worldState, gameTime);

//			Assert::IsTrue(reaction1["Power"].type() == DatumType::Integer);
//			Assert::AreEqual(reaction1["Power"].get<std::int32_t>(0), 100);
//			Assert::IsTrue(reaction2["Power"].type() == DatumType::Integer);
//			Assert::AreEqual(reaction2["Power"].get<std::int32_t>(0), 100);

			delete world;
		}

		TEST_METHOD(TestMultipleActions)
		{
			WorldState worldState;
			GameTime gameTime;
			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(0)));
			worldState.setGameTime(gameTime);

			World* world = new World();
			Sector* sector = world->createSector("Dale Sector");
			Entity* entity = sector->createEntity("Entity", "Dale");

			Action* actionEvent1 = entity->createAction("ActionEvent", "First Action");
			actionEvent1->As<ActionEvent>()->setSubtype("Physical Attack");
			(*actionEvent1)["Power"] = 100;

			Action* actionEvent2 = entity->createAction("ActionEvent", "First Action");
			actionEvent2->As<ActionEvent>()->setSubtype("Magical Attack");
			(*actionEvent2)["Power"] = 200;

			ReactionAttributed reaction1, reaction2;
			reaction1.setSubtype("Physical Attack");
			reaction2.setSubtype("Magical Attack");

			Assert::IsTrue(reaction1["Power"].type() == DatumType::Unknown);
			Assert::IsTrue(reaction2["Power"].type() == DatumType::Unknown);

			world->update(worldState, gameTime);
			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(100)));
			world->update(worldState, gameTime);

//			Assert::IsTrue(reaction1["Power"].type() == DatumType::Integer);
//			Assert::AreEqual(reaction1["Power"].get<std::int32_t>(0), 100);
//			Assert::IsTrue(reaction2["Power"].type() == DatumType::Integer);
//			Assert::AreEqual(reaction2["Power"].get<std::int32_t>(0), 200);

			delete world;
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

		TEST_METHOD(TestSubtype)
		{
			ReactionAttributed ra1, ra2, ra3;
			ra1.setSubtype("PersonAction");
			ra2.setSubtype("AlienAction");
			ra3.setSubtype("PersonAction");

			Assert::AreNotEqual(ra1.getSubtype(), ra2.getSubtype());
			Assert::AreNotEqual(ra3.getSubtype(), ra2.getSubtype());
			Assert::AreEqual(ra1.getSubtype(), ra3.getSubtype());

			EventMessageAttributed ema1, ema2, ema3;
			ema1.setSubtype("PersonAction");
			ema2.setSubtype("AlienAction");
			ema3.setSubtype("PersonAction");

			Assert::AreNotEqual(ema1.getSubtype(), ema2.getSubtype());
			Assert::AreNotEqual(ema3.getSubtype(), ema2.getSubtype());
			Assert::AreEqual(ema1.getSubtype(), ema3.getSubtype());
		}

		TEST_METHOD(RTTI_Test)
		{
			ReactionAttributed ra1, ra2;
			Assert::IsTrue(ra1.Is(ReactionAttributed::TypeIdClass()));
			Assert::IsTrue(ra1.As<ReactionAttributed>() != ra2.As<ReactionAttributed>());
			Assert::IsTrue(ra1.As<ReactionAttributed>() != nullptr);
			Assert::IsTrue(ra2.As<ReactionAttributed>() != nullptr);
		}

		static _CrtMemState sStartMemState;
	};
	_CrtMemState ReactionTest::sStartMemState;
}