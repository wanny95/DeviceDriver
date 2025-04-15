#pragma once
#include "device_driver.h"
class Application {
public:
	explicit Application(DeviceDriver* driver) : driver{ driver } {}
	void readAndPrint(long startAddr, long endAddr);
	void writeAll(unsigned char value);
private:
	DeviceDriver* driver;
};