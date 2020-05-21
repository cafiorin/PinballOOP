#ifndef ChangeableState__INCLUDED_
#define ChangeableState__INCLUDED_

#include "StatusPinballMachine.h"

class ChangeableStatus
{
private:
    static ChangeableStatus* headChangeableStatus;
    ChangeableStatus* nextChangeableStatus;

public:
    ChangeableStatus();
    virtual void changeStatus(StatusPinballMachine status) = 0;
    static void ChangeStatusAll(StatusPinballMachine status);
};

#endif
