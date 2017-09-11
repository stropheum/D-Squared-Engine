#pragma once

namespace Library
{
	class GameTime;

	class WorldState
	{
	public:

		/**
		 * Constructor
		 */
		WorldState();

		/**
		 * Destructor
		 */
		~WorldState();

		/**
		 * Accessor method for the gametime
		 * @Return: A reference to the gametime object
		 */
		GameTime& GetGameTime() const;

		/**
		 * Mutator method for the gametime
		 * @Param gameTime: A reference to the gametime object
		 */
		void SetGameTime(GameTime& gameTime);

		class World* world;
		class Sector* sector;
		class Entity* entity;
		class Action* action;

		GameTime* gameTime;
	};
}