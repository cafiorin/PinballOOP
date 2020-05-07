#include "..\\OOP\\defines.h"
#include "Initializable.h"

Initializable* Initializable::headInitializable = nullptr;

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
