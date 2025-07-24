#include "gmock/gmock.h"
#include "booking_scheduler.cpp"
#include "testable_sms_sender.cpp"
#include "testable_mail_sender.cpp"
#include "testable_booking_scheduler.cpp"

using namespace testing;

class MockCustomer : public Customer
{
public:
  MOCK_METHOD(string, getEmail, (), (override));
};

class BookingItem : public Test
{
protected:
  void SetUp() override
  {
    NOT_ON_THE_HOUR = getTime(2021, 3, 26, 9, 5);
    ON_THE_HOUR = getTime(2021, 3, 26, 9, 0);
    SUNDAY_ON_THE_HOUR = getTime(2021, 3, 28, 17, 0);
    MONDAY_ON_THE_HOUR = getTime(2024, 6, 3, 17, 0);

    bookingScheduler.setSmsSender(&testableSmsSender);
    bookingScheduler.setMailSender(&testableMailSender);

    EXPECT_CALL(CUSTOMER, getEmail)
      .WillRepeatedly(testing::Return(""));

    EXPECT_CALL(CUSTOMER_WITH_MAIL, getEmail)
      .WillRepeatedly(testing::Return("test@test.com"));
  }

public:
  tm getTime(int year, int mon, int day, int hour, int min)
  {
    tm result = { 0, min, hour, day, mon - 1, year - 1900, 0, 0, -1 };
    mktime(&result);
    return result;
  }

  tm plusHour(tm base, int hour)
  {
    base.tm_hour += hour;
    mktime(&base);
    return base;
  }

  tm NOT_ON_THE_HOUR;
  tm ON_THE_HOUR;
  tm SUNDAY_ON_THE_HOUR;
  tm MONDAY_ON_THE_HOUR;

  MockCustomer CUSTOMER;
  MockCustomer CUSTOMER_WITH_MAIL;

  const int UNDER_CAPACITY = 1;
  const int CAPACITY_PER_HOUR = 3;

  BookingScheduler bookingScheduler{CAPACITY_PER_HOUR};
  NiceMock<TestableSmsSender> testableSmsSender;
  NiceMock<TestableMailSender> testableMailSender;
};

TEST_F(BookingItem, ���������ÿ��������ϴ����ð��ƴѰ�쿹��Ұ�)
{
  Schedule* schedule = new Schedule{ NOT_ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER};

  EXPECT_THROW({bookingScheduler.addSchedule(schedule);}, std::runtime_error);

}

TEST_F(BookingItem, ���������ÿ��������ϴ������ΰ�쿹�డ��)
{
  Schedule* schedule = new Schedule{ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER};

  bookingScheduler.addSchedule(schedule);

  EXPECT_EQ(true, bookingScheduler.hasSchedule(schedule));
}

TEST_F(BookingItem, �ð��뺰�ο��������ִٰ����ð��뿡Capacity�ʰ��Ұ�쿹�ܹ߻�)
{
  Schedule* schedule = new Schedule{ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER};
  bookingScheduler.addSchedule(schedule);

  try
  {
    Schedule* newSchedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER };
    bookingScheduler.addSchedule(newSchedule);
    FAIL(); // exception���� ���� ���� ��Ž
  }
  catch (std::runtime_error& e)
  {
    EXPECT_EQ(string{ e.what() }, string{ "Number of people is over restaurant capacity per hour" });
  }
}

TEST_F(BookingItem, �ð��뺰�ο��������ִٰ����ð��밡�ٸ���Capacity���־�������߰�����)
{
  Schedule* schedule = new Schedule{ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER};
  bookingScheduler.addSchedule(schedule);

  tm differentHour = plusHour(ON_THE_HOUR, 1);
  Schedule* newSchedule = new Schedule{differentHour, UNDER_CAPACITY, CUSTOMER};
  bookingScheduler.addSchedule(newSchedule);
  
  EXPECT_EQ(true, bookingScheduler.hasSchedule(schedule));
}

TEST_F(BookingItem, ����Ϸ��SMS�¹����ǹ߼�)
{
  Schedule* schedule = new Schedule{ ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER };

  EXPECT_CALL(testableSmsSender, send(schedule))
    .Times(1);

  bookingScheduler.addSchedule(schedule);
}

TEST_F(BookingItem, �̸����̾��°�쿡���̸��Ϲ̹߼�)
{
  Schedule* schedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER };

  EXPECT_CALL(testableMailSender, sendMail(schedule))
    .Times(0);

  bookingScheduler.addSchedule(schedule);
}

TEST_F(BookingItem, �̸������ִ°�쿡���̸��Ϲ߼�)
{
  Schedule* schedule = new Schedule{ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER_WITH_MAIL};

  EXPECT_CALL(testableMailSender, sendMail(schedule))
    .Times(1);

  bookingScheduler.addSchedule(schedule);
}

TEST_F(BookingItem, ���糯¥���Ͽ����ΰ�쿹��Ұ�����ó��)
{
  BookingScheduler* bookingScheduler = new TestableBookingScheduler{ CAPACITY_PER_HOUR, SUNDAY_ON_THE_HOUR };

  try
  {
    Schedule* schedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER_WITH_MAIL };
    bookingScheduler->addSchedule(schedule);
    FAIL();
  }
  catch (std::runtime_error& e)
  {
    EXPECT_EQ(string{ e.what() }, string{ "Booking system is not available on sunday" });
  }
}

TEST_F(BookingItem, ���糯¥���Ͽ����̾ƴѰ�쿹�డ��)
{
  BookingScheduler* bookingScheduler = new TestableBookingScheduler{CAPACITY_PER_HOUR, MONDAY_ON_THE_HOUR};

  Schedule* schedule = new Schedule{ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER_WITH_MAIL};
  bookingScheduler->addSchedule(schedule);

  EXPECT_EQ(true, bookingScheduler->hasSchedule(schedule));
}

int main()
{
  ::testing::InitGoogleMock();
  return RUN_ALL_TESTS();
}