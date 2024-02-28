#ifndef ABSRAM_H
#define ABSRAM_H
#include "../../../../UserInterface/UIHeaders/uiinterface.h"

//Base class for all Ram Segment classes in Server
//Used to implement dynamic polymorphysm
//AbsRam* pointers can be bind to all types of derived objects, Stack, Heap, Bss, Data, ReadOnly, SymTab derive from this class publicly
class AbsRam
{
public:
  AbsRam(Segment segment, int currentAddress, int startAddress, bool enableAdressgGen = 0);
  virtual ~AbsRam() = default;
  virtual void pushSlot(const std::string& value, const std::string& name, const std::string& size);//Adds varibale with given values to according Ram Segment
  virtual void setSlotValue(int position, const std::string& value);//Set variable's value
  virtual const std::string getValue(const std::string&  name) const;//Get variable value by name
  virtual const std::string getAddress(const std::string& name) const;//Get variable address by name
  virtual std::size_t getSegmentSize() const;//Get Segment size
  virtual std::size_t findSlotIndexbyName(const std::string& name);//Return index of name variable
  virtual std::size_t findSlotIndexbyAddress(const std::string& address);//Return index of variable by address
  virtual void erase(const std::string& name);//Erase some variabel named name
  virtual void eraseStartingFrom(int start);//Erase staring from index start
  virtual std::string generateAddress(int size);//Generate address for varibale being added
protected:
  Segment segmentId_;//Enum to differ between Segments
  unsigned int currentAddress_;//last generated addres for this segment
  const unsigned int startAddress_;//starting address for this segment
  bool addressGenenabled;//used to solve the issue of using very first address, for ex. 0x0000 0000
  UIInterface* ui;//Pointer to ui interface to have access to its methods
};

#endif // ABSRAM_H
