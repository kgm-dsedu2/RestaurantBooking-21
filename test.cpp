#include "gmock/gmock.h"
#include "booking_scheduler.cpp"

TEST(BookingSchedulerTest, ���������ÿ��������ϴ����ð��ƴѰ�쿹��Ұ�)
{

}

TEST(BookingSchedulerTest, ���������ÿ��������ϴ������ΰ�쿹�డ��)
{

}

TEST(BookingSchedulerTest, �ð��뺰�ο��������ִٰ����ð��뿡Capacity�ʰ��Ұ�쿹�ܹ߻�)
{

}

TEST(BookingSchedulerTest, �ð��뺰�ο��������ִٰ����ð��밡�ٸ���Capacity���־�������߰�����)
{

}

TEST(BookingSchedulerTest, ����Ϸ��SMS�¹����ǹ߼�)
{

}

TEST(BookingSchedulerTest, �̸����̾��°�쿡���̸��Ϲ̹߼�)
{

}

TEST(BookingSchedulerTest, �̸������ִ°�쿡���̸��Ϲ߼�)
{

}

TEST(BookingSchedulerTest, ���糯¥���Ͽ����ΰ�쿹��Ұ�����ó��)
{

}

TEST(BookingSchedulerTest, ���糯¥���Ͽ����̾ƴѰ�쿹�డ��)
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