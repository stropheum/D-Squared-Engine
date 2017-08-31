#pragma once
#include "EventSubscriber.h"
class ListClearingSubscriber :
	public Library::EventSubscriber
{
public:
	ListClearingSubscriber();
	~ListClearingSubscriber();
	virtual void notify(const Library::EventPublisher& event) override;
};

