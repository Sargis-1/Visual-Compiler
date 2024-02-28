#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../ControlBlock/controlblock.h"

//Controller will be used for compiling, preprocessing source code
class Controller
{
public:
    Controller();
    void processInput();
private:
    ControlBlock* cb;
};

#endif // CONTROLLER_H
