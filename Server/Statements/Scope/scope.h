#ifndef SCOPE_H
#define SCOPE_H

#include "../../Ram/RamController/RamController.h"

//For every function, Condition statement, even for Global scope, Scope object will be created and held in ControlBlock
class Scope{
public:
    Scope(const std::string& name, int startrow);//Creates Scope object named - name
    virtual ~Scope();
    virtual void execute();
private:
    int startRow;//Shows where this scope starts in source code
    std::array<int, 4> segRangesStarts;
    RamController* RC;//RamController* to release variables of the scope when it goes out of scope
public:
    std::string scopeName;
};

#endif // SCOPE_H
