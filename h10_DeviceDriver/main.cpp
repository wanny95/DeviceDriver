#include "gmock/gmock.h"
#include "device_driver.h"

using namespace testing;

class MockFlashDevice : public FlashMemoryDevice {
public:

	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriver, ReadFromHW5TimeSuccess) {

	MockFlashDevice mock;
	EXPECT_CALL(mock, read(0xBB))
		.Times(5);

	DeviceDriver driver{ &mock };
	int data = driver.read(0xBB);

	EXPECT_EQ(0, data);
}

int main()
{
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}