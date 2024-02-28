#include "data.h"
#include "../../../../Enums/segmentsenum.h"

Data::Data() : AbsRam(Segment::Data, 0xCCCCCCC4, 0xCCCCCCC4)//Initializing Starting and current addresses of this Segment
{

}

Data::~Data() noexcept
{

}

