#pragma once
#include "Vector.h"
#include <chrono>
#include <mutex>


namespace Library
{
	class EventQueue
	{
	public:
		
		/**
		 * Default constructor
		 */
		EventQueue() = default;

		/**
		 * Destructor
		 */
		~EventQueue();

		/**
		 *Adds an event to the queue At a specified time
		 *@Param eventPublisher: The event being added to the queue
		 *@Param gameTime: The game time that the event was queued At
		 *@Param Delay: The Delay after which the event will be delivered
		 */
		void Enqueue(class EventPublisher& eventPublisher, 
			class GameTime& gameTime, std::chrono::milliseconds delay = std::chrono::milliseconds(0));

		/**
		 * Immediately sends the event without posting to the queue
		 * @Param eventPublisher: The event being delivered
		 */
		void Send(class EventPublisher& eventPublisher);

		/**
		 * Iterates over the queue and delivers any expired events
		 * @Param gameTime: The current game time
		 */
		void Update(class GameTime& gameTime);

		/**
		 * Clears the queue of all events without delivering them
		 */
		void Clear();

		/**
		 * Determines if there are any events currently queued
		 * @Return:True if there are no events in the queue. False otherwise
		 */
		bool IsEmpty() const;

		/**
		 * Accessor method for the number of events in the queue
		 * @Return: The number of events in the queue
		 */
		std::uint32_t Size() const;
		
	private:
		Vector<EventPublisher*> mQueue; // The queue of events
		std::mutex mQueueMutex;
	};
}
