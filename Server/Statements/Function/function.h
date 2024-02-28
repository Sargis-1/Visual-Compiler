#ifndef FUNCTION_H
#define FUNCTION_H

#include "../Scope/scope.h"

class Function : public Scope
{
public:
    Function(const std::string& name, int startrow);
};

#endif // FUNCTION_H
