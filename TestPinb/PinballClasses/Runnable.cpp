#include "defines.h"
#include "Runnable.h"

Runnable* Runnable::headRunnable = NULL;

//-------------------------------------------------------//
Runnable::Runnable()
//-------------------------------------------------------//
    {
        nextRunnable = headRunnable;
        headRunnable = this;
    }

//-------------------------------------------------------//
void Runnable::loopAll()
//-------------------------------------------------------//
{
    for (Runnable* r = headRunnable; r; r = r->nextRunnable)
        r->loop();
}
