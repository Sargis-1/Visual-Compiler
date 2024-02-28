#include "../UIHeaders/ramslot.h"

RAMSlot::RAMSlot(const QString& address, const QString& value, const QString& name, const QString& typesize)
{
  items.push_back(new QPushButton(address));//Each one of ramslot's 4 elements is QPushButton
  items.back()->setStyleSheet("color: black;");
  items.push_back(new QPushButton(value));//Adding slot to QVector of buttons
  items.back()->setStyleSheet("color: black;");
  items.push_back(new QPushButton(name));
  items.back()->setStyleSheet("color: black;");
  items.push_back(new QPushButton(typesize));
  items.back()->setStyleSheet("color: black;");
  slot = new QHBoxLayout();//Creating horizontal layout to add buttons
  for(const auto& item : items){
      slot->addWidget(item);//Adding buttons(address, value, name, size) to layout
  }

}

RAMSlot::RAMSlot(const QString &functionName)
{
   items.push_back(new QPushButton(functionName));//Only one button(for function's/condition's name)
   items[0]->setStyleSheet("text-align: left;");//Set text in button to left side of it
   slot = new QHBoxLayout();//Creating horizontal layout to add button
   slot->addWidget(items[0]);
}

QHBoxLayout* RAMSlot::getLayout()
{
  return slot;
}

QVector<QPushButton*> &RAMSlot::getRamSlotItems()
{
  return items;
}

void RAMSlot::setSlotValue(QString value)
{
  items[1]->setText(value);
}

void RAMSlot::setSlotAddress(QString address)
{
  items[0]->setText(address);
}

void RAMSlot::setSlotValues(QString address, QString value, QString name, QString typesize)//Setting slot values
{
  items[0]->setText(address);
  items[1]->setText(value);
  items[2]->setText(name);
  items[3]->setText(typesize);
}


RAMSlot::~RAMSlot()
{
    for(auto& item : items){
        if(item)
            delete item;//Deleteing all buttons in slot
    }

    if(slot)
        delete slot;//deleting layout
}
