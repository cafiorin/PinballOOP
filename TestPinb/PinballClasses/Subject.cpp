#include "defines.h"
#include "Subject.h"
#include "Observer.h"

//-------------------------------------------------------//
Subject::Subject(EventType event, byte value)
//-------------------------------------------------------//
{
    headObserver = NULL;
    m_eventType = event;
    m_value = value;
}

//-------------------------------------------------------//
Subject::~Subject()
//-------------------------------------------------------//
{
    headObserver = NULL;
}

//-------------------------------------------------------//
void Subject::registerObserver(Observer* observer)
//-------------------------------------------------------//
{
    if (headObserver == NULL)
    {
        headObserver = observer;
    }
    else
    {
        observer->nextObserver = headObserver;
        headObserver = observer;
    }
}

//-------------------------------------------------------//
void Subject::notifyObserver(byte value /*=0 default*/)
//-------------------------------------------------------//
{
    for (Observer* observer = headObserver; observer; observer = observer->nextObserver)
    {
        if(m_value != 0)
            observer->onNotifySubject(m_eventType,m_value);
        else
            observer->onNotifySubject(m_eventType, value);
    }
}

