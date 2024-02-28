#ifndef RAMSEGMENT_H
#define RAMSEGMENT_H

#include "ramslot.h"

//RAMSegment is class, which objects are all 6 segments you can see in UI
class RAMSegment : public QObject
{
  Q_OBJECT
public:
  RAMSegment(const QString& title, QGraphicsScene* scene, QObject* parent = nullptr);
//  explicit RAMSegment(QWidget *parent, const QString& title);
  ~RAMSegment();

  void addSlot(const QString& address, const QString& value, const QString& variableName, const QString& typesize);//Add ne slot to segment
  void setDefaultValues();//To empty the segment
  void removeLastSlot();//Removes last added slot
  const QString getValue(const QString& name) const;//To find and return some variable's value by name
  const QString getAdress(const QString& name) const;//To find and return some variable's address by name
  std::size_t getSlotIndexbyName(const QString& name) const;//Returns the index of variable - name
  std::size_t getSlotIndexbyAddress(const QString& address) const;//Returns the index of variable with address
  void removeSlot(int index);//Remove index'th slot
  RAMSlot* getSlotByIndex(int index);//Get slot ptr by index
  int slotCount() const;//Return slot count(variable number) in segment
  QVBoxLayout* getLayout();//
  void addFunctionSlot(const QString& funcname);
private:
  QWidget* widget;//Widget which contains all segment
  QGroupBox* title_;//QGroupBox to create custom title bar
  QVBoxLayout* layout;//layout to contain title bar
  QVBoxLayout* widgetLayout;//layout to contain all Ramslots(variables)
  QTimer *timer;
  QScrollArea* ramScrollArea;//To enable scrolling up and down
  QVector<RAMSlot*> ramSlots;//Contains all ramslots
  QGraphicsScene *scene;//Pointer to scene where RamSegment will be seen in UI
};

#endif // RAMSEGMENT_H
