#include "absram.h"
//#include "../../../UIHeaders/uiinterface.h"

AbsRam::AbsRam(Segment segment, int currentAddress, int startAddress, bool enableAdressgGen) :
    ui(), segmentId_(segment), currentAddress_(currentAddress), startAddress_(startAddress)
{
}


void AbsRam::pushSlot(const std::string &value, const std::string &name, const std::string &size)
{
  try {
    int variablesize = std::stoi(size);//convert given size string to integer
    const QString address = QString::fromStdString(generateAddress(variablesize));//Generate address for given variable with given size
    ui->pushSlot(segmentId_, address , QString::fromStdString(value), QString::fromStdString(name), QString::fromStdString(size));
  } catch (const std::exception& e) {
    qDebug() << e.what();
  }
}

void AbsRam::setSlotValue(int position, const std::string &value)
{
  try {
    ui->setSlotValue(segmentId_, position, QString::fromStdString(value));
  } catch (const std::exception& e) {
    qDebug() << e.what();
  }
}

const std::string AbsRam::getValue(const std::string &name) const
{

  try {
    auto value = ui->getValue(segmentId_, QString::fromStdString(name));
    return value.toStdString();
  } catch (const std::exception& e) {
    qDebug() << e.what();
  }
  return "";
}

const std::string AbsRam::getAddress(const std::string &name) const
{
  try {
    auto address = ui->getAddress(segmentId_, QString::fromStdString(name));
    return address.toStdString();
  } catch (const std::exception& e) {
    qDebug() << e.what();
  }
  return "";
}

std::size_t AbsRam::getSegmentSize() const//Added to be used in Scopes
{
    try {
        return ui->getSegmentSize(segmentId_);
    } catch (const std::exception& e) {
        qDebug() << e.what();
    }
    return std::numeric_limits<std::size_t>::max();
}

std::size_t AbsRam::findSlotIndexbyName(const std::string &name)
{
  try {
    std::size_t index = ui->findSlotIndexbyName(segmentId_, QString::fromStdString(name));
    return index;
  } catch (const std::exception& e) {
    qDebug() << e.what();
  }
  return std::numeric_limits<std::size_t>::max();
}

std::size_t AbsRam::findSlotIndexbyAddress(const std::string &address)
{
  try {
    std::size_t index = ui->findSlotIndexbyAddress(segmentId_, QString::fromStdString(address));
    return index;
  } catch (const std::exception& e) {
    qDebug() << e.what();
  }
  return std::numeric_limits<std::size_t>::max();
}

void AbsRam::erase(const std::string &name)
{
  try {
    ui->erase(segmentId_, QString::fromStdString(name));
  } catch (const std::exception &e) {
    qDebug() << e.what();
  }
}

void AbsRam::eraseStartingFrom(int start)
{
    try {
        ui->eraseStartingFrom(segmentId_, start);
    } catch (const std::exception &e) {
        qDebug() << "Error from eraseStartingFrom() method" << e.what();
    }
}

std::string AbsRam::generateAddress(int size)
{
    if(!addressGenenabled){//if adress generation is not enabled, give segments first address as current addres
                           //then set addressGenEnabled true, so later each address will be calculated using previous one
        std::stringstream ss;

        ss << std::hex << "0x"<< std::setw(8) << std::setfill('0') << startAddress_;
        addressGenenabled = true;
        return ss.str();
    }

    currentAddress_ += size;

    std::stringstream ss;//std::stringstream is a class that allows you to work with strings in a stream-like manner.
    //It acts as an in-memory output stream, meaning you can write data to it

    //std::hex sets the stream's output formatting to hexadecimal
    //std::setw(8) sets the width of the output to 8 characters.
    //std::setfill('0') sets the fill character to '0'.
    //This ensures that if the number is shorter than 8 digits, it will be padded with leading zeros.

    ss << std::hex << "0x"<< std::setw(8) << std::setfill('0') << currentAddress_;

    return ss.str(); //return the contents of the std::stringstream object as a std::string

    //   Adress distribution among all Ram Segments
    //     //0000 0000 - 5999 9994  - 35%
    //     //5999 9995 - B333 332A  - 35%
    //     //B333 332B - CCCC CCC3  - 10%
    //     //CCCC CCC4 - E666 665C  - 10%
    //     //E666 665D _ FFFF FFFF  - 10%
}
