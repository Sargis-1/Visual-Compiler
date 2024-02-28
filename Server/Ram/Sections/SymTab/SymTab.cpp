#include "SymTab.h"
#include "../../../../Enums/segmentsenum.h"

SymTab::SymTab() : AbsRam(Segment::SymTab, 0, 0)//SymTab segment has no addresses, because it contains only function/Condition names
{

}

SymTab::~SymTab() noexcept
{

}

std::string SymTab::generateAddress(int size)
{

}
