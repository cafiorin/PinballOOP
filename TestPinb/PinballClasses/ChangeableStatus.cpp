#include "ChangeableStatus.h"
#include "StatusPinballMachine.h"

#include "defines.h"
#include "Initializable.h"

ChangeableStatus* ChangeableStatus::headChangeableStatus = NULL;

//-------------------------------------------------------//
ChangeableStatus::ChangeableStatus()
//-------------------------------------------------------//
{
    nextChangeableStatus = headChangeableStatus;
    headChangeableStatus = this;
}

//-------------------------------------------------------//
void ChangeableStatus::ChangeStatusAll(StatusPinballMachine status)
//-------------------------------------------------------//
{
    for (ChangeableStatus* r = headChangeableStatus; r; r = r->nextChangeableStatus)
        r->changeStatus(status);
}

