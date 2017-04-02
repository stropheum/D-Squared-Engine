#include "pch.h"
#include "CppUnitTest.h"
#include "XmlParseMaster.h"
#include "TestSharedData.h"
#include "SharedDataScope.h"
#include "Scope.h"
#include "Datum.h"
#include <glm/detail/type_vec4.hpp>
#include <glm/mat4x4.hpp>
#include "XmlParseHelperEntity.h"
#include "Entity.h"
#include "World.h"
#include "Sector.h"
#include "GameTime.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace TestLibraryDesktop
{
	TEST_CLASS(XmlParseHelperEntityTest)
	{
	public:

		Library::EntityFactory mEntityFactory;

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

		TEST_METHOD(TestParse)
		{
			Library::SharedDataScope sharedData;
			Library::XmlParseMaster parseMaster(&sharedData);
			Library::XmlParseHelperEntity helper;
			sharedData.setXmlParseMaster(&parseMaster);
			parseMaster.addHelper(helper);

			parseMaster.parseFromFile("EntityGrammar.xml");

			Library::Scope* scope = sharedData.mScope;
			World* world = scope->As<World>();
			std::string name = world != nullptr ? world->name() : "";

			Assert::IsTrue(name == "Dales World");

			Assert::IsTrue(world->sectors()[0].As<Sector>() != nullptr);
			Sector* sector = world->sectors()[0].As<Sector>();
			Assert::IsTrue(sector->name() == "Dales Sector");
			Assert::IsTrue(sector->getParent() == world);

			Entity* entity = sector->entities()[0].As<Entity>();
			Assert::IsTrue(entity != nullptr);
			Assert::IsTrue(entity->name() == "Dale");
			
			Entity& entityRef = *entity;
			Assert::IsTrue(entityRef["Health"] == 100);
			Assert::IsTrue(entityRef["Power"] == 12.34f);
			Assert::IsTrue(entityRef["Position"] == glm::vec4(1, 2, 3, 4));
		}

		TEST_METHOD(TestWorldName)
		{
			World* world = new World();

			Assert::IsTrue(world->name() == "");
			
			world->setName("NewName");
			Assert::IsTrue(world->name() == "NewName");

			delete world;
		}

		TEST_METHOD(TestSectorName)
		{
			Sector* sector = new Sector();

			Assert::IsTrue(sector->name() == "");

			sector->setName("NewName");
			Assert::IsTrue(sector->name() == "NewName");

			delete sector;
		}

		TEST_METHOD(TestEntityName)
		{
			Entity* entity = new Entity();

			Assert::IsTrue(entity->name() == "");

			entity->setName("NewName");
			Assert::IsTrue(entity->name() == "NewName");

			delete entity;
		}

		TEST_METHOD(TestCreateSector)
		{
			World* world = new World();

			Assert::IsTrue(world->sectors().size() == 0);

			world->createSector("NewSector");
			Assert::IsTrue(world->sectors().size() == 1);

			delete world;
		}

		TEST_METHOD(TestCreateEntity)
		{
			Sector* sector = new Sector();

			Assert::IsTrue(sector->entities().size() == 0);

			sector->createEntity("Entity", "Dale");
			Assert::IsTrue(sector->entities().size() == 1);

			delete sector;
		}

		TEST_METHOD(TestCloneLeaks)
		{
			/// Clone for leak detection. Cloning functioality already tests in other test class
			Library::SharedDataScope sharedData;
			Library::XmlParseMaster parseMaster(&sharedData);
			Library::XmlParseHelperEntity helper;
			sharedData.setXmlParseMaster(&parseMaster);
			parseMaster.addHelper(helper);
			XmlParseMaster* clone = parseMaster.clone();
			delete clone;
			Assert::IsTrue(true);
		}

		TEST_METHOD(Testupdate)
		{
			/// Update has no current functionality, so test currently exists for coverage and leak detection
			World* world = new World();
			WorldState worldState;
			GameTime gameTime;
			world->update(worldState, gameTime);

			delete world;
		}

		TEST_METHOD(TestGetWorld)
		{
			World* world = new World();

			Sector* sector = world->createSector("NewSector");
			Assert::IsTrue(sector->getWorld() == *world);

			World* wrongWorld = new World();
			Assert::IsFalse(sector->getWorld() == *wrongWorld);

			delete world;
			delete wrongWorld;
		}

		TEST_METHOD(TestGetSector)
		{
			Sector* sector = new Sector();

			Entity* entity = sector->createEntity("Entity", "Dale");
			Assert::IsTrue(entity->getSector() == *sector);

			Sector* wrongSector = new Sector();
			Assert::IsFalse(entity->getSector() == *wrongSector);

			delete sector;
			delete wrongSector;
		}

		TEST_METHOD(TestSetWorld)
		{
			World* world1 = new World();
			Sector* sector = world1->createSector("sector");

			Assert::IsTrue(sector->getWorld() == *world1);

			World* world2 = new World();
			sector->setWorld(*world2);
			Assert::IsTrue(sector->getWorld() == *world2);
			Assert::IsFalse(sector->getWorld() == *world1);

			delete world1;
			delete world2;
		}

		TEST_METHOD(TestSetSector)
		{
			Sector* sector1 = new Sector();
			Entity* entity = sector1->createEntity("Entity", "Dale");

			Assert::IsTrue(entity->getSector() == *sector1);

			Sector* sector2 = new Sector();
			entity->setSector(*sector2);
			Assert::IsTrue(entity->getSector() == *sector2);
			Assert::IsFalse(entity->getSector() == *sector1);

			delete sector1;
			delete sector2;
		}

		static _CrtMemState sStartMemState;
	};
	_CrtMemState XmlParseHelperEntityTest::sStartMemState;
}