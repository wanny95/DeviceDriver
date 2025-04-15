#include "gmock/gmock.h"
#include "device_driver.h"
#include <string>

using namespace testing;
using std::string;

class MockFlashDevice : public FlashMemoryDevice {
public:

	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class DeviceDriverFixture : public Test {
public:
	MockFlashDevice mock;
};

TEST_F(DeviceDriverFixture, ReadFromHW5TimeSuccess) {

	EXPECT_CALL(mock, read(0xBB))
		.Times(5);

	DeviceDriver driver{ &mock };
	int data = driver.read(0xBB);

	EXPECT_EQ(0, data);
}

TEST_F(DeviceDriverFixture, ReadFromHW5TimeFail) {

	EXPECT_CALL(mock, read)
		.WillOnce(Return(0))
		.WillRepeatedly(Return(5));

	DeviceDriver driver{ &mock };
	//act
	try {
		int data = driver.read(0xBB);
		FAIL();
	}
	catch (const ReadFailException& e) {
		EXPECT_EQ(string{ e.what() }, string{ "ReadFailException" });
	}
}

int main()
{
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}