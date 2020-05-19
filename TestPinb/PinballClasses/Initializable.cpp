#include "defines.h"
#include "Initializable.h"

Initializable* Initializable::headInitializable = NULL;

//-------------------------------------------------------//
Initializable::Initializable()
//-------------------------------------------------------//
    {
        nextInitializable = headInitializable;
        headInitializable = this;
    }

//-------------------------------------------------------//
void Initializable::initAll()
//-------------------------------------------------------//
{
    for (Initializable* r = headInitializable; r; r = r->nextInitializable)
        r->init();
}
