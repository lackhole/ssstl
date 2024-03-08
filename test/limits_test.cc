#include <iostream>
#include <cstdint>

#include "lsd/limits.h"

#include "lsd_test.h"

class MyInt {
 public:
  MyInt() = default;
  explicit MyInt(int value) : value_(value) {}

  int value() const { return value_; }

 private:
  int value_ = 123;
};

int main() {
  LSD_INIT_TEST("limits")

  LSD_TEST_EQ(lsd::numeric_limits<bool>::has_infinity, false)
  LSD_TEST_EQ(lsd::numeric_limits<int>::has_infinity, false)
  LSD_TEST_EQ(lsd::numeric_limits<float>::has_infinity, true)
  LSD_TEST_EQ(lsd::numeric_limits<double>::has_infinity, true)

  LSD_TEST_EQ(lsd::numeric_limits<std::int8_t>::max(), 127)
  LSD_TEST_EQ(lsd::numeric_limits<std::uint8_t>::max(), 255U)
  LSD_TEST_EQ(lsd::numeric_limits<std::int16_t>::max(), 32767)
  LSD_TEST_EQ(lsd::numeric_limits<std::uint16_t>::max(), 65535U)
  LSD_TEST_EQ(lsd::numeric_limits<std::int32_t>::max(), 2147483647)
  LSD_TEST_EQ(lsd::numeric_limits<std::uint32_t>::max(), 4294967295U)

  LSD_TEST(lsd::numeric_limits<float>::max() > 1E+38);
  LSD_TEST(lsd::numeric_limits<double>::max() > 1E+308);
  LSD_TEST(lsd::numeric_limits<long double>::max() >= lsd::numeric_limits<double>::max());


  LSD_TEST_RETURN
}
