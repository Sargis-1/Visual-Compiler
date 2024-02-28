#include "../UIHeaders/ramsegment.h"
#include "../UIHeaders/ramslot.h"
#include "../UIHeaders/styleutils.h"

RAMSegment::RAMSegment(const QString& title, QGraphicsScene* scene, QObject* parent)
  : QObject(parent), scene(scene)
{


          layout = new QVBoxLayout();

          // Add a widget containing the QGraphicsView and title
          widget = new QWidget();//layout to contain title bar
          widgetLayout = new QVBoxLayout(widget);//layout to contain all Ramslots(variables)

          title_ = StyleUtils::createSmallStyledGroupBox(title, "#343a40", "#D3D3D3", widget);//creates custom title
          layout->addWidget(title_);

          widget->setStyleSheet("border: 2px solid gray; "
                                "border-radius: 5px; "
                                "padding: 5px;");


          layout->addWidget(widget);
}

QVBoxLayout* RAMSegment::getLayout() { return layout; }


void RAMSegment::addFunctionSlot(const QString &funcname)
{
    if(title_->title() != "Function")
        return;

    RAMSlot* slot = new RAMSlot(funcname);
    ramSlots.push_back(slot);
    widgetLayout->addLayout(slot->getLayout());
}

RAMSegment::~RAMSegment()//Releasing pointer members
{
  if(layout) delete layout;
  if(scene) delete scene;
  if(title_) delete title_;
  for(auto& slot : ramSlots){
      if(slot) delete slot;
      slot = nullptr;
    }

}

void RAMSegment::addSlot(const QString &address, const QString &value, const QString &variableName, const QString &typesize)
{
    if(title_->title() == "Function"){
        qDebug() << "Can't add a regular slot to Function segment\n";
        return;
    }

    RAMSlot* newSlot = new RAMSlot(address, value, variableName, typesize);
    ramSlots.push_back(newSlot);
    widgetLayout->blockSignals(1);
    widgetLayout->addLayout(newSlot->getLayout());//This line adds new slot in UI
    widget->update();
    widgetLayout->blockSignals(0);
}

void RAMSegment::setDefaultValues()
{
  for(auto& slot : ramSlots){
     if(slot) delete slot;
     slot = nullptr;
    }
  for(int i = 0; i < ramSlots.size(); ++i){
      ramSlots.pop_back();
    }

}

void RAMSegment::removeLastSlot()
{
  int i = ramSlots.size() - 1;
  if(ramSlots[i]) delete ramSlots[i];
  ramSlots[i] = nullptr;
  ramSlots.pop_back();
}
const QString RAMSegment::getValue(const QString &name) const
{
    for (const auto& elem : ramSlots) {
        if (elem->getRamSlotItems()[2]->text() == name) {
            return elem->getRamSlotItems()[1]->text();
        }
    }

    throw std::runtime_error("Value not found for slot: " + name.toStdString());
}

const QString RAMSegment::getAdress(const QString &name) const
{
    for(const auto& elem : ramSlots){
        if(elem->getRamSlotItems()[2]->text() == name)
            return elem->getRamSlotItems()[0]->text();
    }

    std::ostringstream errorMsg;
    errorMsg << "No slot named: " << name.toStdString() << " in Segment " << (title_ ? title_->title().toStdString() : "Unknown");
    throw std::runtime_error(errorMsg.str());
}

std::size_t RAMSegment::getSlotIndexbyName(const QString &name) const
{
  for(const auto& elem : ramSlots){
      if(elem->getRamSlotItems()[2]->text() == name){
          auto it = std::find(ramSlots.begin(), ramSlots.end(), elem);
          std::size_t index = std::distance(ramSlots.begin(), it);
          return index;
        }
    }
  std::ostringstream errorMsg;
  errorMsg << "No slot named: " << name.toStdString() << " in Segment " << (title_ ? title_->title().toStdString() : "Unknown");
  throw std::runtime_error(errorMsg.str());

}

std::size_t RAMSegment::getSlotIndexbyAddress(const QString &address) const
{
  for(const auto& elem : ramSlots){
      if(elem->getRamSlotItems()[0]->text() == address){
          auto it = std::find(ramSlots.begin(), ramSlots.end(), elem);
          std::size_t index = std::distance(ramSlots.begin(), it);
          return index;
        }
    }
  std::ostringstream errorMsg;
  errorMsg << "No slot under address: " << address.toStdString() << " in Segment " << (title_ ? title_->title().toStdString() : "Unknown");
  throw std::runtime_error(errorMsg.str());

}

void RAMSegment::removeSlot(int index)
{

    if(index >= ramSlots.size()){
        //qDebug() << index  << "   " <<  ramSlots.size() << "\n";
      throw std::out_of_range("index out of bounds");
    }

    QVector<RAMSlot*>::iterator it = ramSlots.begin() + index;


    delete *it;
    ramSlots.erase(it);
    //qDebug() << index << " th slot waas deleted " << ramSlots.size() << "\n";
}

RAMSlot *RAMSegment::getSlotByIndex(int index)
{
  if(index >= ramSlots.size()){
      throw std::out_of_range("index out of bounds");
    }
  return ramSlots[index];
}


int RAMSegment::slotCount() const
{
    return ramSlots.size();
}















