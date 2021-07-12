//
// Created by YongGyu Lee on 2021/07/11.
//

#ifndef SS_TEST_H_
#define SS_TEST_H_

#include <sstream>
#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>

namespace ss {

class Tester {
 public:
  explicit Tester(std::string name) : test_name_(std::move(name)) {}
  ~Tester() {
    print_result();
  }

  void do_test(bool result, std::string source, int line) {
    test_data_.emplace_back(std::move(source), line, result ? test_result::success : test_result::fail);
  }

  void print_result() const {
    std::vector<decltype(test_data_)::const_iterator> fails;

    for (auto it = test_data_.cbegin(); it != test_data_.cend(); ++it) {
      if (it->result == test_result::fail)
        fails.emplace_back(it);
    }
    print_result_impl(fails.begin(), fails.end());
  }

  int test_succeed() const {
    for (const auto& elem : test_data_) {
      if (elem.result == test_result::fail)
        return 1;
    }
    return 0;
  }

 private:
  template<typename It>
  void print_result_impl(It begin, It end) const {
    static constexpr const char* star60 = "............................................................";

    int failed_count = std::distance(begin, end);
    int succeed_count = static_cast<int>(test_data_.size()) - failed_count;

    std::stringstream ss;
    ss << '(' << std::to_string(test_data_.size() - failed_count) << " / " << test_data_.size() << ')';
    auto status = ss.str();

    std::cout
      << test_name_
      << star60 + std::min(static_cast<int>(status.size() + test_name_.size()), 60)
      << status
      << "\n";

    for (auto it = begin; it != end; ++it) {
      std::cout << "Test failed at " << (*it)->source << ", line " << (*it)->line << '\n';
    }
  }

  enum class test_result { success, fail };
  struct tests {
    tests(std::string s, int line, test_result r) : source(std::move(s)), line(line), result(r) {}
    std::string source;
    int line;
    test_result result;
  };
  std::string test_name_;
  std::vector<tests> test_data_;
};

}

# define SS_TEST_FILE_LINE_IMPL2(f, l) #l
# define SS_TEST_FILE_LINE_IMPL(f, l) f ", line " #l
# define SS_TEST_FILE_LINE SS_TEST_FILE_LINE_IMPL(__FILE__, __LINE__)

# define SS_TEST_MAKE_DUMMY_NAME_IMPL2(x, y) x ## y
# define SS_TEST_MAKE_DUMMY_NAME_IMPL(x, y) SS_TEST_MAKE_DUMMY_NAME_IMPL2(x, y)
# define SS_TEST_MAKE_DUMMY_NAME(x) SS_TEST_MAKE_DUMMY_NAME_IMPL(x, __COUNTER__)

# define SS_TEST_DUMMY_NAME ss_$238be_$zzfe_

# define SS_INIT_TEST(name) ::ss::Tester SS_TEST_DUMMY_NAME(name);
# define SS_TEST(expr) SS_TEST_DUMMY_NAME.do_test((expr), __FILE__, __LINE__);

# define SS_TESTC(...) static_assert((__VA_ARGS__), " "); SS_TEST(true) // if false this doesn't even compiles.

# define SS_TEST_RETURN return SS_TEST_DUMMY_NAME.test_succeed();

// TODO: check real C++ language version

//# define SS_TEST_MAKE_EXPR_TEST(expr) \
//template<typename

# define SS_TEST_EXPR_VALID(expr)

#endif // SS_TEST_H_
