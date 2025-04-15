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
	const int NEED_READ_TIMES = 5;
};

TEST_F(DeviceDriverFixture, ReadFromHW5TimeSuccess) {
	//arrange
	EXPECT_CALL(mock, read(0xBB))
		.Times(NEED_READ_TIMES);

	DeviceDriver driver{ &mock };
	//act
	int data = driver.read(0xBB);
	//assert
	EXPECT_EQ(0, data);
}

TEST_F(DeviceDriverFixture, ReadFromHW5TimeFail) {
	//arrange
	EXPECT_CALL(mock, read)
		.WillOnce(Return(0))
		.WillRepeatedly(Return(5));

	DeviceDriver driver{ &mock };
	try {
		//act
		int data = driver.read(0xBB);
		FAIL();
	}
	catch (const ReadFailException& e) {
		//assert
		EXPECT_EQ(string{ e.what() }, string{ "ReadFailException" });
	}
}

TEST_F(DeviceDriverFixture, ReadFromHW5TimeValueSuccess) {
	//arrange
	EXPECT_CALL(mock, read)
		.Times(NEED_READ_TIMES)
		.WillRepeatedly(Return(0));

	DeviceDriver driver{ &mock };
	int data = driver.read(0xBB);
	//assert
	EXPECT_EQ(0, data);
}


int main()
{
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}