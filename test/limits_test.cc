#include <iostream>
#include <cstdint>

#include "ss/limits.h"

#include "ss_test.h"

class MyInt {
 public:
  MyInt() = default;
  explicit MyInt(int value) : value_(value) {}

  int value() const { return value_; }

 private:
  int value_ = 123;
};

int main() {
  SS_INIT_TEST("limits")

  SS_TEST_EQ(ss::numeric_limits<bool>::has_infinity, false)
  SS_TEST_EQ(ss::numeric_limits<int>::has_infinity, false)
  SS_TEST_EQ(ss::numeric_limits<float>::has_infinity, true)
  SS_TEST_EQ(ss::numeric_limits<double>::has_infinity, true)

  SS_TEST_EQ(ss::numeric_limits<std::int8_t>::max(), 127)
  SS_TEST_EQ(ss::numeric_limits<std::uint8_t>::max(), 256U)
  SS_TEST_EQ(ss::numeric_limits<std::int16_t>::max(), 32767)
  SS_TEST_EQ(ss::numeric_limits<std::uint16_t>::max(), 65535U)
  SS_TEST_EQ(ss::numeric_limits<std::int32_t>::max(), 2147483647)
  SS_TEST_EQ(ss::numeric_limits<std::uint32_t>::max(), 4294967295U)

  SS_TEST(ss::numeric_limits<float>::max() > 1E+38);
  SS_TEST(ss::numeric_limits<double>::max() > 1E+308);
  SS_TEST(ss::numeric_limits<long double>::max() >= ss::numeric_limits<double>::max());


  SS_TEST_RETURN
}
