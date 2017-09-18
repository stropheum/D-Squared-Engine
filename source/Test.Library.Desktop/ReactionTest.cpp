#include "pch.h"
#include "CppUnitTest.h"
#include "LeakDetector.h"
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

		TEST_METHOD_INITIALIZE(InitializeMethod)
		{
			LeakDetector::Initialize();
		}

		TEST_METHOD_CLEANUP(CleanupMethod)
		{
			LeakDetector::Finalize();
		}

		TEST_METHOD(TestReactionAttributed)
		{
			WorldState worldState;
			GameTime gameTime;
			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(0)));
			worldState.SetGameTime(gameTime);

			World* world = new World();
			Sector* sector = world->CreateSector("Dale Sector");
			Entity* entity = sector->CreateEntity("Entity", "Dale");
			Action* actionEvent = entity->CreateAction("ActionEvent", "First Action");
			actionEvent->As<ActionEvent>()->SetSubtype("Physical Attack");
			
			(*actionEvent)["Power"] = 100;
			
			ReactionAttributed physicalReaction , magicalReaction;
			physicalReaction.SetSubtype("Physical Attack");
			magicalReaction.SetSubtype("Magical Attack");

			Assert::IsTrue(physicalReaction["Power"].Type() == DatumType::Unknown);
			Assert::IsTrue(magicalReaction["Power"].Type() == DatumType::Unknown);

			world->Update(worldState, gameTime);
			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(100)));
			world->Update(worldState, gameTime);

			Assert::IsTrue(physicalReaction["Power"].Type() == DatumType::Integer);
			std::int32_t power = physicalReaction["Power"].Get<std::int32_t>(0);
			Assert::AreEqual(power, 100);
			Assert::IsFalse(magicalReaction["Power"].Type() == DatumType::Integer);

			delete world;
		}

		TEST_METHOD(TestMultipleReactions)
		{
			WorldState worldState;
			GameTime gameTime;
			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(0)));
			worldState.SetGameTime(gameTime);

			World* world = new World();
			Sector* sector = world->CreateSector("Dale Sector");
			Entity* entity = sector->CreateEntity("Entity", "Dale");

			Action* actionEvent1 = entity->CreateAction("ActionEvent", "First Action");
			actionEvent1->As<ActionEvent>()->SetSubtype("Physical Attack");
			(*actionEvent1)["Power"] = 100;

			ReactionAttributed reaction1, reaction2;
			reaction1.SetSubtype("Physical Attack");
			reaction2.SetSubtype("Physical Attack");

			Assert::IsTrue(reaction1["Power"].Type() == DatumType::Unknown);
			Assert::IsTrue(reaction2["Power"].Type() == DatumType::Unknown);

			world->Update(worldState, gameTime);
			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(100)));
			world->Update(worldState, gameTime);

			Assert::IsTrue(reaction1["Power"].Type() == DatumType::Integer);
			Assert::AreEqual(reaction1["Power"].Get<std::int32_t>(0), 100);
			Assert::IsTrue(reaction2["Power"].Type() == DatumType::Integer);
			Assert::AreEqual(reaction2["Power"].Get<std::int32_t>(0), 100);

			delete world;
		}

		TEST_METHOD(TestMultipleActions)
		{
			WorldState worldState;
			GameTime gameTime;
			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(0)));
			worldState.SetGameTime(gameTime);

			World* world = new World();
			Sector* sector = world->CreateSector("Dale Sector");
			Entity* entity = sector->CreateEntity("Entity", "Dale");

			Action* actionEvent1 = entity->CreateAction("ActionEvent", "First Action");
			actionEvent1->As<ActionEvent>()->SetSubtype("Physical Attack");
			(*actionEvent1)["Power"] = 100;

			Action* actionEvent2 = entity->CreateAction("ActionEvent", "First Action");
			actionEvent2->As<ActionEvent>()->SetSubtype("Magical Attack");
			(*actionEvent2)["Power"] = 200;

			ReactionAttributed reaction1, reaction2;
			reaction1.SetSubtype("Physical Attack");
			reaction2.SetSubtype("Magical Attack");

			Assert::IsTrue(reaction1["Power"].Type() == DatumType::Unknown);
			Assert::IsTrue(reaction2["Power"].Type() == DatumType::Unknown);

			world->Update(worldState, gameTime);
			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(100)));
			world->Update(worldState, gameTime);

			Assert::IsTrue(reaction1["Power"].Type() == DatumType::Integer);
			Assert::AreEqual(reaction1["Power"].Get<std::int32_t>(0), 100);
			Assert::IsTrue(reaction2["Power"].Type() == DatumType::Integer);
			Assert::AreEqual(reaction2["Power"].Get<std::int32_t>(0), 200);

			delete world;
		}

		TEST_METHOD(TestActionEvent)
		{
			World* myworld = new World();
			WorldState worldState;
			worldState.world = myworld;
			GameTime gameTime;
			gameTime.SetCurrentTime(high_resolution_clock::time_point(milliseconds(0)));
			worldState.SetGameTime(gameTime);

			ActionEvent actionEvent;
			actionEvent.Update(worldState);

			delete myworld;
		}

		TEST_METHOD(TestSubtype)
		{
			ReactionAttributed ra1, ra2, ra3;
			ra1.SetSubtype("PersonAction");
			ra2.SetSubtype("AlienAction");
			ra3.SetSubtype("PersonAction");

			Assert::AreNotEqual(ra1.GetSubtype(), ra2.GetSubtype());
			Assert::AreNotEqual(ra3.GetSubtype(), ra2.GetSubtype());
			Assert::AreEqual(ra1.GetSubtype(), ra3.GetSubtype());

			EventMessageAttributed ema1, ema2, ema3;
			ema1.SetSubtype("PersonAction");
			ema2.SetSubtype("AlienAction");
			ema3.SetSubtype("PersonAction");

			Assert::AreNotEqual(ema1.GetSubtype(), ema2.GetSubtype());
			Assert::AreNotEqual(ema3.GetSubtype(), ema2.GetSubtype());
			Assert::AreEqual(ema1.GetSubtype(), ema3.GetSubtype());
		}

		TEST_METHOD(RTTI_Test)
		{
			ReactionAttributed ra1, ra2;
			Assert::IsTrue(ra1.Is(ReactionAttributed::TypeIdClass()));
			Assert::IsTrue(ra1.As<ReactionAttributed>() != ra2.As<ReactionAttributed>());
			Assert::IsTrue(ra1.As<ReactionAttributed>() != nullptr);
			Assert::IsTrue(ra2.As<ReactionAttributed>() != nullptr);
		}

	};

}