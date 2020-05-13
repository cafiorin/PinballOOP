#include "Observer.h"
#include "Subject.h"

//-------------------------------------------------------//
Observer::Observer()
//-------------------------------------------------------//
{
    nextObserver = NULL;
}

//-------------------------------------------------------//
void Observer::attachSubject(Subject* subject)
//-------------------------------------------------------//
{
    subject->registerObserver(this);
}