//
// Created by YongGyu Lee on 2021/07/11.
//

#ifndef SS_TEST_H_
#define SS_TEST_H_

#include <cstdio>
#include <cmath>

#include <algorithm>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

namespace ss {

class Tester {
 public:
  struct TestData {
    explicit TestData(bool r) : success_(r) {}
    TestData(bool r, std::string message) : success_(r), message_(std::move(message)) {}

    TestData& SetMessage(std::string message) {
      message_ = std::move(message);
      return *this;
    }

    TestData& SetSource(const char* source, int line) {
      source_ = source;
      line_ = line;
      return *this;
    }

    std::string source_;
    int line_;
    bool success_;
    std::string message_;
  };

  explicit Tester(std::string name) : test_name_(std::move(name)) {}
  ~Tester() {
    print_result();
  }

  TestData& AddTest(bool v) {
    tests_.emplace_back(v);
    return tests_.back();
  }

  TestData& AddTest(bool v, std::string message) {
    tests_.emplace_back(v, std::move(message));
    return tests_.back();
  }

  void print_result() const {
    std::vector<decltype(tests_)::const_iterator> fails;

    for (auto it = tests_.cbegin(); it != tests_.cend(); ++it) {
      if (!it->success_)
        fails.emplace_back(it);
    }
    print_result_impl(fails.begin(), fails.end());
  }

  int test_succeed() const {
    for (const auto& elem : tests_) {
      if (!elem.success_)
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }

 private:
  template<typename It>
  void print_result_impl(It begin, It end) const {
    static constexpr const char* star60 = "............................................................";

    int failed_count = std::distance(begin, end);
    int succeed_count = static_cast<int>(tests_.size()) - failed_count;

    std::stringstream ss;
    ss << '(' << std::to_string(tests_.size() - failed_count) << " / " << tests_.size() << ')';
    auto status = ss.str();

    std::cout
      << test_name_
      << star60 + std::min(static_cast<int>(status.size() + test_name_.size()), 60)
      << status
      << "\n";

    for (auto it = begin; it != end; ++it) {
      std::cout
          << "Test failed at " << (*it)->source_
          << ", line " << (*it)->line_;
      if (!(*it)->message_.empty())
          std::cout << " (" << (*it)->message_ <<  ")";
      std::cout << '\n';
    }
  }

  std::string test_name_;
  std::vector<TestData> tests_;
};

} // namespace ss

#define SS_TEST_GET_HEAD_IMPL_1(x) x
#define SS_TEST_GET_HEAD_IMPL_2(x, ...) x
#define SS_TEST_GET_HEAD_IMPL(_1,_2,N,...) SS_TEST_GET_FIRST_IMPL_##N
#define SS_TEST_GET_HEAD(...) SS_TEST_GET_FIRST_IMPL(__VA_ARGS__,2,1,0)(__VA_ARGS__)

#define SS_TEST_GET_TAIL_IMPL_1(x)
#define SS_TEST_GET_TAIL_IMPL_2(x, ...) __VA_ARGS__
#define SS_TEST_GET_TAIL_IMPL(_1,_2,N,...) SS_TEST_GET_SECOND_OR_EMPTY_IMPL_##N
#define SS_TEST_GET_TAIL(...) SS_TEST_GET_SECOND_OR_EMPTY_IMPL(__VA_ARGS__,2,1,0)(__VA_ARGS__)

# define SS_TEST_MAKE_DUMMY_NAME_IMPL2(x, y) x ## y
# define SS_TEST_MAKE_DUMMY_NAME_IMPL(x, y) SS_TEST_MAKE_DUMMY_NAME_IMPL2(x, y)
# define SS_TEST_MAKE_DUMMY_NAME(x) SS_TEST_MAKE_DUMMY_NAME_IMPL(x, __COUNTER__)

# define SS_TEST_DUMMY_NAME ss_$238be_$zzfe_

# define SS_INIT_TEST(name) ::ss::Tester SS_TEST_DUMMY_NAME(name);
# define SS_TEST(...) SS_TEST_DUMMY_NAME.AddTest(__VA_ARGS__).SetSource(__FILE__, __LINE__);
# define SS_TEST_EQ(x, y) SS_TEST_DUMMY_NAME.AddTest((x) == (y)).SetSource(__FILE__, __LINE__);

# define SS_TESTC(...) static_assert((__VA_ARGS__), " "); SS_TEST(true) // if false this doesn't even compile.

# define SS_TEST_THROW(expr, excep)         \
try {                                       \
  (expr);                                   \
  SS_TEST(false, "exception not thrown")    \
} catch (const excep&) {                    \
  SS_TEST(true)                             \
} catch (...) {                             \
  SS_TEST(false, "wrong exception thrown")  \
}

# define SS_TEST_THROW_ANY(expr)          \
try {                                     \
  (expr);                                 \
  SS_TEST(false, "exception not thrown")  \
} catch (...) {                           \
  SS_TEST(true)                           \
}

# define SS_TEST_NOTHROW(expr)        \
try {                                 \
  (expr);                             \
  SS_TEST(true)                       \
} catch (...) {                       \
  SS_TEST(false, "exception thrown")  \
}

# define SS_TEST_RETURN return SS_TEST_DUMMY_NAME.test_succeed();

// TODO: check real C++ language version

//# define SS_TEST_MAKE_EXPR_TEST(expr) \
//template<typename

# define SS_TEST_EXPR_VALID(expr)

#endif // SS_TEST_H_
