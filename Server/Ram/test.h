#ifndef TEST_H
#define TEST_H

#include "RamController/RamController.h"


//will be changed, prototype for type files

void addslottest(std::string& str){
    RamController* RC = RamController::getRamController();

    RC ->stack -> pushSlot(str, str, "4");

    // RC ->heap -> pushSlot(str, str, "2");

    // RC ->bss -> pushSlot(str, str, "8");

    // RC ->readonly ->pushSlot(str, str, "4");

    // RC ->data -> pushSlot(str, str, "1");
}

#endif // TEST_H
