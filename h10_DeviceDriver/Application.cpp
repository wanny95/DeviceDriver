#include "Application.h"

void Application::readAndPrint(long startAddr, long endAddr) {
	for (long addr = startAddr; addr <= endAddr; ++addr) {
		driver->read(addr);
	}
}
void Application::writeAll(unsigned char value) {
	for (auto addr = 0x00; addr <= 0x04; addr++) {
		driver->write(addr, value);
	}
}
