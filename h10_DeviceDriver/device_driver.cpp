#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int result = (int)(m_hardware->read(address));;
    for (int i = 0; i < 4; ++i) {
        int tempRead = (int)(m_hardware->read(address));
        if (tempRead != result) {
            throw ReadFailException("ReadFailException");
        }
    }
    return result;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}

ReadFailException::ReadFailException(char const* _Message) :
    std::exception(_Message) {
}

char const* ReadFailException::what() const {
    return "ReadFailException";
}