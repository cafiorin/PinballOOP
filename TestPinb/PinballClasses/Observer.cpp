#include "Observer.h"
#include "Subject.h"

//-------------------------------------------------------//
Observer::Observer()
//-------------------------------------------------------//
{
    nextObserver = nullptr;
}

//-------------------------------------------------------//
void Observer::attachSubject(Subject* subject)
//-------------------------------------------------------//
{
    subject->registerObserver(this);
}