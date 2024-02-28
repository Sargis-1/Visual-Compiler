#ifndef UIINTERFACE_H
#define UIINTERFACE_H

#include "mainwindow.h"

//Class UIInterface provides functionality for Server to interact with UI part of the program
//Singleton pattern was used
//Segment enum is used to differ between Ram Segments by names, not by indexes of them
class UIInterface{
public:
  static UIInterface* getUiInterface(MainWindow* window);//To get instance of UIInterface
  void pushSlot(Segment segment, const QString& address, const QString& value, const QString& name, const QString& size);//Adds ne slot to Segment segment
  void setSlotValue(Segment segment, int position, const QString& value);//In Segment segment, sets variable's value to value, variable is under position position
  const QString getValue(Segment segment, const QString&  name);//Get value of name variable in Segment segment
  const QString getAddress(Segment segment, const QString& name);//Get address of name variable in Segment segment
  std::size_t getSegmentSize(Segment segment) const;//Return Segment segment's size
  std::size_t findSlotIndexbyName(Segment segment, const QString& name);//Returns variable name's index in Segment segment
  std::size_t findSlotIndexbyAddress(Segment segment, const QString& address);//Returns variable's index in Segment segment by address
  void erase(Segment segment, const QString& name);//Deletes variable named name in Segment segment
  void eraseStartingFrom(Segment segment, int startingfrom);//Erases all varibales in Segment segment starting from given index
private:
  UIInterface(MainWindow* window);// Private constructor to enforce singleton pattern
  static UIInterface *instance;// Static instance variable
  MainWindow *mainwindow;//Pointer to mainwindow, which functionality is wrapped in UIInterface
};

#endif // UIINTERFACE_H
