#pragma once
#include "Vector.h"
#include <chrono>


namespace Library
{
	class EventQueue
	{
	public:
		EventQueue();
		~EventQueue() = default;

		void enqueue(class EventPublisher& eventPublisher, 
			class GameTime& gameTime, std::chrono::milliseconds delay = std::chrono::milliseconds(0));
		void send(class EventPublisher& eventPublisher);
		void update(class GameTime& gameTime);
		void clear();
		bool isEmpty() const;
		std::uint32_t size() const;
		
	private:
		Vector<EventPublisher*> mQueue;
	};
}