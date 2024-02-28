#include "../UIHeaders/uiinterface.h"
#include "../UIHeaders/mainwindow.h"
#include "../UIHeaders/ramsegment.h"


UIInterface* UIInterface::instance = nullptr;
// Implementation of the private constructor

UIInterface::UIInterface(MainWindow* window)
    : mainwindow(window)//Initialize mainwindow pointer, which will be used in most of method in UIInterface
{
    // Additional setup if needed
}

// Implementation of the static method to get the singleton instance
UIInterface* UIInterface::getUiInterface(MainWindow* window)
{
    if (!instance) {//If there is no UIInterface instance created yet, create one
        instance = new UIInterface(window);//Initialize instance member with created UIInterface ptr
    }
    return instance;//Return created instance
}

void UIInterface::pushSlot(Segment segment, const QString &address, const QString &value, const QString &name, const QString &size)
{
    RAMSegment* neededSegment = mainwindow->getSegment(segment);//Gets segment using enum value of argument segment
    neededSegment->addSlot(address, value, name, size);//Addslot to needed segment
}

void UIInterface::setSlotValue(Segment segment, int position, const QString &value)
{
  RAMSegment* neededSegment = mainwindow->getSegment(segment);//Gets segment using enum value of argument segment
  auto slot = neededSegment->getSlotByIndex(position);//Get slot by index
  slot->setSlotValue(value);//Set slot's value to value
}

const QString UIInterface::getValue(Segment segment, const QString &name)
{
  auto neededSegment = mainwindow->getSegment(segment);//Gets segment using enum value of argument segment

  // Check if neededSegment is not nullptr
  if (neededSegment) {
    try {
      QString slotValue = neededSegment->getValue(name);//Get's value of name varibale from needed segment

      // Check if the slotValue is not empty
      if (!slotValue.isEmpty()) {
        return slotValue;
      } else {
        qDebug() << "Value not found for slot: " << name;
      }
    } catch (const std::exception &e) {
      qDebug() << "Exception while getting value: " << e.what();
    }
  } else {
    qDebug() << "Segment not found: " << static_cast<int>(segment);
  }

  // Return a default value or an empty QString indicating that the value was
  // not found or an error occurred
  return QString(); // Or any other suitable default value
}

const QString UIInterface::getAddress(Segment segment, const QString &name)
{
    //Identical to getValue()
  auto neededSegment = mainwindow->getSegment(segment);//Gets segment using enum value of argument segment

  // Check if neededSegment is not nullptr
  if (neededSegment) {
    try {
      QString slotValue = neededSegment->getAdress(name);

      // Check if the slotValue is not empty
      if (!slotValue.isEmpty()) {
        return slotValue;
      } else {
        qDebug() << "Address not found for slot: " << name;
      }
    } catch (const std::exception &e) {
      qDebug() << "Exception while getting address: " << e.what();
    }
    } else {
        qDebug() << "Segment not found: " << static_cast<int>(segment);
    }

    // Return a default value or an empty QString indicating that the address
    // was not found or an error occurred
    return QString();  // Or any other suitable default value
}

std::size_t UIInterface::getSegmentSize(Segment segment) const
{
    return mainwindow->getSegment(segment)->slotCount();
}

std::size_t UIInterface::findSlotIndexbyName(Segment segment, const QString &name)
{
    auto neededSegment = mainwindow->getSegment(segment);//Gets segment using enum value of argument segment

    // Check if neededSegment is not nullptr
    if (neededSegment) {
        try {
      int index = neededSegment->getSlotIndexbyName(name);

      // Check if the index is valid
      if (index != -1) {
        return static_cast<std::size_t>(index);
      } else {
        qDebug() << "Slot not found: " << name;
      }
        } catch (const std::exception &e) {
      qDebug() << "Exception while finding slot index: " << e.what();
        }
    } else {
        qDebug() << "Segment not found: " << static_cast<int>(segment);
    }

    // Return a value indicating that the slot was not found or an error occurred
    return std::numeric_limits<std::size_t>::max();
}

std::size_t UIInterface::findSlotIndexbyAddress(Segment segment, const QString &address)
{
    auto neededSegment = mainwindow->getSegment(segment);//Gets segment using enum value of argument segment

    // Check if neededSegment is not nullptr
    if (neededSegment) {
        try {
      int index = neededSegment->getSlotIndexbyName(address);
      return static_cast<std::size_t>(index);

        } catch (const std::exception &e) {
      qDebug() << "Exception while finding slot index: " << e.what();
        }
    } else {
        qDebug() << "Segment not found: " << static_cast<int>(segment);
    }

    // Return a value indicating that the slot was not found or an error
    // occurred
    return std::numeric_limits<std::size_t>::max();
}

void UIInterface::erase(Segment segment, const QString &name)
{
  auto neededSegment = mainwindow->getSegment(segment);//Gets segment using enum value of argument segment
  if(neededSegment){
      try {
        int indexToRemove = neededSegment->getSlotIndexbyName(name);//Gets index if variable(Ramslot) which will be deleted
        neededSegment->removeSlot(indexToRemove);//Remove slot by index
      } catch (const std::exception& e) {
        qDebug() << "Exception while removing slot: " << e.what();
      }
  }
}

void UIInterface::eraseStartingFrom(Segment segment, int startingfrom)
{
    auto neededSegment = mainwindow->getSegment(segment);//Gets segment using enum value of argument segment
    int end = getSegmentSize(segment);//Gets Segment size
    if(neededSegment){
        try {
            for(int i = startingfrom; i < end; ++i){//Remove slots starting from position startingfrom
                neededSegment->removeLastSlot();//Remove last (end - startingfrom) variables
            }
        } catch (const std::exception& e) {
            qDebug() << "Exception while removing last slots: " << e.what();
        }
    }
}













