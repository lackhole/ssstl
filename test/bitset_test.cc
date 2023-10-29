#include <iostream>
#include <utility>
#include <array>
#include <bitset>
#include <sstream>

#include "ss/bitset.h"

#include "ss_test.h"

#ifdef NDEBUG
#define NDEBUG_DEFINED 1
#else
#define NDEBUG_DEFINED 0
#endif

int main() {
  SS_INIT_TEST("bitset")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';

  { // test access
    constexpr ss::bitset<1> b1(1);

    SS_TEST(1, "foobar")
    SS_TESTC(b1[0] == 1)
    SS_TESTC(b1[0] != 0)

    SS_TEST_NOTHROW(b1.test(0))
    SS_TEST(b1.test(0) == 1)

    SS_TEST_THROW(b1.test(1), ss::out_of_range)
    SS_TEST_THROW(b1.test(2), ss::out_of_range)
    SS_TEST_THROW(b1.test(3), ss::out_of_range)
    SS_TEST_THROW(b1.test(4), ss::out_of_range)

    SS_TESTC(b1.size() == 1)

    ss::bitset<1> b2(1);
    SS_TEST(b2[0] == 1)
    SS_TEST(~b2[0] == 0)
    SS_TEST(b2[0].flip() == 0)

    SS_TEST(b2[0] == 0)
    SS_TEST(~b2[0] == 1)
    SS_TEST(b2[0].flip() == 1)

    ss::bitset<1> b3(0);
    SS_TEST(b3[0] == 0)
    b3[0] = b2[0];
    SS_TEST(b3[0] == 1)
  }

  { // test string
    using bit4 = ss::bitset<4>;
    SS_TEST(bit4("0000") == 0)
    SS_TEST(bit4("0001") == 1)
    SS_TEST(bit4("0010") == 2)
    SS_TEST(bit4("0011") == 3)
    SS_TEST(bit4("0100") == 4)
    SS_TEST(bit4("1000") == 8)
    SS_TEST(bit4("1010") == 10)
    SS_TEST(bit4("1111") == 15)

    SS_TEST(bit4("00001") == 0)
    SS_TEST(bit4("0000111") == 0)

    //                 012345678
    std::string str = "001101010";
    SS_TEST(bit4(str).to_string() == "0011")
    SS_TEST(bit4(str, 1).to_string() == "0110")
    SS_TEST(bit4(str, 2).to_string() == "1101")
    SS_TEST(bit4(str, 2, 2).to_string() == "0011")
    SS_TEST(bit4(str, 2, 3).to_string() == "0110")
    SS_TEST(bit4(str, 7).to_string() == "0010")
    SS_TEST(bit4(str, 7, 99).to_string() == "0010")

    SS_TEST_THROW(bit4(str, 99), ss::out_of_range)

    SS_TEST_THROW(bit4("abcd"), ss::invalid_argument)
    SS_TEST_THROW(bit4("000a"), ss::invalid_argument)
    SS_TEST_THROW(bit4("a000"), ss::invalid_argument)
    SS_TEST_NOTHROW(bit4("0000a"))

    SS_TEST(bit4().to_string()   == "0000")
    SS_TEST(bit4(1).to_string()  == "0001")
    SS_TEST(bit4(5).to_string()  == "0101")
    SS_TEST(bit4(15).to_string() == "1111")
    SS_TEST(bit4(5).to_string('A','B') == "ABAB")
    SS_TEST(ss::bitset<8>(42).to_string() == "00101010")
  }

  { // all, any, none, count
    SS_TEST(ss::bitset<8>("11111111").all())
    SS_TEST(ss::bitset<8>("111111111").all())
    SS_TEST(!ss::bitset<8>("11111110").all())
    SS_TEST(!ss::bitset<8>("01111111").all())
    SS_TEST(!ss::bitset<8>("11110111").all())

    SS_TEST(!ss::bitset<8>().any())
    SS_TEST(!ss::bitset<99>().any())
    SS_TEST(!ss::bitset<999>().any())
    SS_TEST(ss::bitset<8>(1).any())
    SS_TEST(ss::bitset<99>(1).any())

    SS_TEST(ss::bitset<99>().none())
    SS_TEST(!ss::bitset<99>("101000101").none())
    SS_TEST(!ss::bitset<99>(123).none())

    SS_TEST(ss::bitset<8>().count() == 0)
    SS_TEST(ss::bitset<8>(std::string(4, '1')).count() == 4)
    SS_TEST(ss::bitset<8>(std::string(8, '1')).count() == 8)
    SS_TEST(ss::bitset<8>(std::string(10, '1')).count() == 8)

    SS_TEST(ss::bitset<65>(1).to_string()
                == "00000000000000000000000000000000000000000000000000000000000000001")
    SS_TEST(ss::bitset<65>(1).flip().to_string()
                == "11111111111111111111111111111111111111111111111111111111111111110")
  }

  { // op
    using bit8 = ss::bitset<8>;

    auto b = bit8("00001111");
    b &= bit8("11001100");
    SS_TEST(b == bit8("00001100"))
    SS_TEST((bit8("00001111") & bit8("11001100")) == bit8("00001100"))

    b = bit8("00001111");
    b |= bit8("11001100");
    SS_TEST(b == bit8("11001111"))
    SS_TEST((bit8("00001111") | bit8("11001100")) == bit8("11001111"))

    b = bit8("00001111");
    b ^= bit8("11001100");
    SS_TEST(b == bit8("11000011"))
    SS_TEST((bit8("00001111") ^ bit8("11001100")) == bit8("11000011"))

    b = bit8("00001111");
    b = ~b;
    SS_TEST(b == bit8("11110000"))
    SS_TEST(~bit8("00001111") == bit8("11110000"))

    b = bit8("00001111");
    b <<= 2;
    SS_TEST(b == bit8("00111100"))
    SS_TEST((bit8("00001111") << 2) == bit8("00111100"))

    b = bit8("00001111");
    b >>= 2;
    SS_TEST(b == bit8("00000011"))
    SS_TEST((bit8("00001111") >> 2) == bit8("00000011"))
    std::cout << "LHS : " << (bit8("00001111") >> 2) << " | " << (bit8("00001111") >> 2).to_string() << std::endl;
    std::cout << "RHS : " << bit8("00000011") << " | " << bit8("00000011").to_string() << std::endl;
  }

  { // set, reset, flip
    using bit8 = ss::bitset<8>;
    auto b = bit8("00001111");

    b.set();
    SS_TEST(b == bit8("11111111"))

    b.set(0, false);
    b.set(7, true);
    SS_TEST(b == bit8("11111110"))
    SS_TEST_THROW(b.set(99, false), ss::out_of_range)

    b.reset();
    SS_TEST(b == 0)

    b = bit8("00001111");
    b.reset(0);
    b.reset(7);
    SS_TEST(b == bit8("00001110"))
    SS_TEST_THROW(b.reset(999), ss::out_of_range)

    b = bit8("00001111");
    const auto c = ~b;
    SS_TEST(c == b.flip())
    b.flip();

    b.flip(7);
    b.flip(0);
    SS_TEST(b == bit8("10001110"))
    SS_TEST_THROW(b.flip(9), ss::out_of_range)
  }

  { // conversion
    constexpr auto ulong_bit = sizeof(unsigned long) * CHAR_BIT;
    constexpr auto ullong_bit = sizeof(unsigned long long) * CHAR_BIT;

    ss::bitset<ulong_bit + 1> b1;
    SS_TEST(b1.to_ulong() == 0)
    b1.flip();
    SS_TEST_THROW(b1.to_ulong(), ss::overflow_error)

    ss::bitset<ullong_bit + 1> b2;
    SS_TEST(b2.to_ulong() == 0)
    b2.flip();
    SS_TEST_THROW(b2.to_ulong(), ss::overflow_error)
  }

  {
    std::istringstream ss;

    std::bitset<10> b;
    ss >> b;
  }

  SS_TEST_RETURN
}
