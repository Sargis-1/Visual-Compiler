#ifndef RAMSLOT_H
#define RAMSLOT_H

//Ramslot is a slot that any segment of ram except for Function can contain
//It contains variable's address, value, name and size
class RAMSlot : public QGraphicsRectItem
{
public:
    RAMSlot(const QString& address, const QString& value, const QString& name, const QString& typesize);//Regular Ramslot Ctor
    RAMSlot(const QString& functionName);//Function segment contains only function slots, it can not contain regular slot,
                                         //Function slot contain only curent function's or condition's name
    QHBoxLayout* getLayout();//Returns pointer to ramslot's horizontal layout
    QVector<QPushButton*>& getRamSlotItems();//To access all Ramslots in Ram Segment
    void setSlotValue(QString value);
    void setSlotAddress(QString address);
    void setSlotValues(QString address, QString value, QString name, QString typesize);
    ~RAMSlot();
private:
    QHBoxLayout* slot;
    QVector<QPushButton*> items;//Contains all ramslots(variables) in segment
};

#endif // RAMSLOT_H

