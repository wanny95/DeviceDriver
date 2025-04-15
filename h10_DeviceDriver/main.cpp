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
	const int NEED_READ_TIMES = 5;
	const int NEED_WRITE_TIMES = 1;
	MockFlashDevice mock;
	DeviceDriver driver{ &mock };
};

TEST_F(DeviceDriverFixture, ReadFromHW5TimeSuccess) {
	//arrange
	EXPECT_CALL(mock, read(0xBB))
		.Times(NEED_READ_TIMES);

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

	//act
	int data = driver.read(0xBB);
	//assert
	EXPECT_EQ(0, data);
}

TEST_F(DeviceDriverFixture, WriteToHWCallSuccess) {
	//arrange
	EXPECT_CALL(mock, read)
		.WillRepeatedly(Return(0xFF));

	EXPECT_CALL(mock, write)
		.Times(1);

	//act
	driver.write(0xBB, 0);

	//assert
	EXPECT_EQ(true, true);
}

TEST_F(DeviceDriverFixture, WriteToHWCallFail) {
	//arrange
	EXPECT_CALL(mock, read)
		.WillRepeatedly(Return(0xBB));

	EXPECT_CALL(mock, write)
		.Times(0);

	try {
		//act
		driver.write(0xBB, 0);
		FAIL();
	}
	catch (const WriteFailException& e) {
		//assert
		EXPECT_EQ(string{ e.what() }, string{ "WriteFailException" });
	}
}

int main()
{
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}