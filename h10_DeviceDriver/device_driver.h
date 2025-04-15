#pragma once
#include "flash_memory_device.h"
#include <stdexcept>

class ReadFailException : public std::exception {
public:
    explicit ReadFailException(char const* _Message);
    char const* what() const override;
};

class WriteFailException : public std::exception {
public:
    explicit WriteFailException(char const* _Message);
    char const* what() const override;
};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
    static const int EMPTY_DEVICE_VALUE = 0xFF;
    static const int MAX_TRY_READ = 4;
};