#include <gmock/gmock.h>
#include <memory>
#include "mylib.h"

using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArgPointee;
using ::testing::_;

class MockFoo : public IFoo {
 public:
  MOCK_METHOD(int, Do, (int), (override));
  MOCK_METHOD(void, Out, (int, std::string*), (override));
};

TEST(ProcessorTest, ProcessValue_SuccessPath) {
  auto mock = std::make_shared<MockFoo>();
  Processor p(mock);

  EXPECT_CALL(*mock, Do(10)).WillOnce(Return(21));
  EXPECT_CALL(*mock, Out(21, _))
      .WillOnce(DoAll(SetArgPointee<1>(std::string("ok:done")), Return()));

  int res = p.ProcessValue(10);
  EXPECT_EQ(res, 42);
}

TEST(ProcessorTest, ProcessValue_DoNegative) {
  auto mock = std::make_shared<MockFoo>();
  Processor p(mock);

  EXPECT_CALL(*mock, Do(_)).WillOnce(Return(-5));
  int res = p.ProcessValue(7);
  EXPECT_EQ(res, -1);
}
