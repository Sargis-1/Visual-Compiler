#include "scope.h"
//#include <QDebug>

Scope::Scope(const std::string& name, int startrow):scopeName(name), startRow(startrow),
    RC(RamController::getRamController())
{
    //Getting the indexes for every segment, so we know the starting index for variables allocated in this scope
    int stackStart = RC -> stack -> getSegmentSize();
    int readOnlyStart = RC ->readonly -> getSegmentSize();
    int dataStart = RC -> data -> getSegmentSize();
    int bssStart = RC -> bss -> getSegmentSize();

    //Hold these starting positions
    segRangesStarts[0] = stackStart;
    segRangesStarts[1] = readOnlyStart;
    segRangesStarts[2] = dataStart;
    segRangesStarts[3] = bssStart;
    //std::cout << name << " scope was created\n";/* << stackStart << " " << readOnlyStart << " " << dataStart << " " << bssStart << "\n"*/;
}


Scope::~Scope()
{
    //Here we are releasing variables of this scope from each Ram Segment, for which scope is responsible for to delete
    //std::cout << "Entered Dtor of scope " << scopeName << "\n";

    RC -> stack -> eraseStartingFrom(segRangesStarts[0]);
    //std::cout << scopeName << "'s " << "stack released\n";

    //std::cout << "readonlys start  = " <<  << scopeName << "\n";
    RC -> readonly -> eraseStartingFrom(segRangesStarts[1]);
    //std::cout << scopeName << "'s " << "readonly released\n";

    RC -> bss -> eraseStartingFrom(segRangesStarts[3]);
    //std::cout << scopeName << "'s " << "bss released\n";

    RC -> data -> eraseStartingFrom(segRangesStarts[2]);
    //std::cout << scopeName << "'s " << "data released\n";

}

void Scope::execute()
{

}
