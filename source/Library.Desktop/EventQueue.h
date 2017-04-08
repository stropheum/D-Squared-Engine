#pragma once
#include "Vector.h"


namespace Library
{
	class EventQueue
	{
	public:
		EventQueue();
		~EventQueue() = default;

		void enqueue(class EventPublisher& eventPublisher, 
			class GameTime& gameTime, std::uint32_t delay = 0);
		void send(class EventPublisher& eventPublisher);
		void update(class GameTime& gameTime);
		void clear();
		bool isEmpty() const;
		std::uint32_t size() const;
		
	private:
		void partitionEventQueue();

		Vector<EventPublisher*> mQueue;
	};
}


