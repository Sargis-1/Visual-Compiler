#ifndef CONTROLBLOCK_H
#define CONTROLBLOCK_H

#include "../Statements/Scope/scope.h"
#include "../Statements/Function/function.h"
#include "../Ram/RamController/RamController.h"

//ControlBlock is used to resolve currenct line, accepted from source code, send it to according type files(int, double, char, conditions resolver, function resolver, loops resolver)
//Here Singleton pattern is used
class ControlBlock
{
public:
    void processString(std::string& str, int row);//Method which processes the input string
    void addnewScope(const std::string& name, int startrow);//must be private later to be called only under certain
    void removeLastScope();//Removes last created scope
    //conditions after processing current input row(will be called in processString)
    static ControlBlock* getControlBlock();//Method to get ControlBlock instance
    ~ControlBlock();//Dtor
private:
    ControlBlock();//Private ctor to enforce Singleton pattern
    static ControlBlock* cbinstance;//Pointer to instance of this class
    RamController* cbRC;//RamController pointer to change somthing on Ui if needed
    std::vector<std::unique_ptr<Scope>> scopes;//Vector to contain all types which have scopes, Contains Global Scope object, then main scope obj, the all other scopes
    std::unordered_map<std::string, std::pair<int, std::string>> generalTypes;//Contais general types with their sizes
    std::unordered_set<std::string> statements;//Contains Statemens(Conditions or loops)
};

#endif // CONTROLBLOCK_H
