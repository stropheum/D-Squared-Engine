#pragma once


namespace Library
{
	class GameTime;

	class WorldState
	{

	public:

#pragma region Construction/Copy/Assignment

		WorldState();

		~WorldState();

		WorldState(const WorldState& rhs) = delete;

		WorldState& operator=(const WorldState& rhs) = delete;

		WorldState(WorldState&& rhs) = delete;

		WorldState& operator=(WorldState&& rhs) = delete;

#pragma endregion

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