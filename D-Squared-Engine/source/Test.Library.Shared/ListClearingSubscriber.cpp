#include "pch.h"
#include "ListClearingSubscriber.h"
#include <cassert>
#include "Event.h"
#include "Foo.h"


ListClearingSubscriber::ListClearingSubscriber()
{
    Library::Event<Foo>::Subscribe(*this);
}

ListClearingSubscriber::~ListClearingSubscriber()
{
    Library::Event<Foo>::Unsubscribe(*this);
}

void ListClearingSubscriber::Notify(const Library::EventPublisher& event)
{
    std::lock_guard<std::mutex> guard(mNotifyMutex);
    if (event.Is(Library::Event<Foo>::TypeIdClass()))
    {
        Library::Event<Foo>::Unsubscribe(*this);
    }
}