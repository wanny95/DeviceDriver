#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int readValue = (int)(m_hardware->read(address));;
    for (int i = 0; i < MAX_TRY_READ; ++i) {
        int tempRead = (int)(m_hardware->read(address));
        if (tempRead != readValue) {
            throw ReadFailException("ReadFailException");
        }
    }
    return readValue;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    int readValue = (int)(m_hardware->read(address));
    if (readValue != EMPTY_DEVICE_VALUE) {
        throw WriteFailException("WriteFailException");
    }

    m_hardware->write(address, (unsigned char)data);
}

ReadFailException::ReadFailException(char const* _Message) :
    std::exception(_Message) {
}

char const* ReadFailException::what() const {
    return "ReadFailException";
}

WriteFailException::WriteFailException(char const* _Message) :
    std::exception(_Message) {
}

char const* WriteFailException::what() const {
    return "WriteFailException";
}