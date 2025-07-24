#include "gmock/gmock.h"
#include "booking_scheduler.cpp"

TEST(BookingSchedulerTest, 예약은정시에만가능하다정시가아닌경우예약불가)
{

}

TEST(BookingSchedulerTest, 예약은정시에만가능하다정시인경우예약가능)
{

}

TEST(BookingSchedulerTest, 시간대별인원제한이있다같은시간대에Capacity초과할경우예외발생)
{

}

TEST(BookingSchedulerTest, 시간대별인원제한이있다같은시간대가다르면Capacity차있어도스케쥴추가성공)
{

}

TEST(BookingSchedulerTest, 예약완료시SMS는무조건발송)
{

}

TEST(BookingSchedulerTest, 이메일이없는경우에는이메일미발송)
{

}

TEST(BookingSchedulerTest, 이메일이있는경우에는이메일발송)
{

}

TEST(BookingSchedulerTest, 현재날짜가일요일인경우예약불가예외처리)
{

}

TEST(BookingSchedulerTest, 현재날짜가일요일이아닌경우예약가능)
{

}

//class BankMock : public BankInterface
//{
//public:
//  MOCK_METHOD(bool, check, (), (override));
//};


//TEST(TS, TC1)
//{
//  Bank bank;
//  Cal cal{&bank};
//
//  std::cout << cal.getSum(1, 2) << "\n";
//  std::cout << cal.getSum(1, 2) << "\n";
//}
//
//TEST(TS, WithMock)
//{
//  BankMock mk;
//
//  EXPECT_CALL(mk, check)
//    .WillRepeatedly(Return(true));
//
//  Cal cal{&mk};
//
//  std::cout << cal.getSum(1, 2) << "\n";
//  std::cout << cal.getSum(1, 2) << "\n";
//}

int main()
{
  ::testing::InitGoogleMock();
  return RUN_ALL_TESTS();
}