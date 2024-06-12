#include "lsd_test.h"
#include "lsd/algorithm.h"

#include <algorithm>
#include <cctype>
#include <forward_list>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "lsd/array.h"
#include "lsd/string_view.h"
#include "lsd/ranges.h"
#include "lsd/utility.h"

struct foo {};

template<>
struct std::iterator_traits<foo> : std::iterator_traits<std::list<int>::iterator> {
  using __primary_template = std::iterator_traits<foo>;
};

void bar() {
  static_assert(std::__is_primary_template<std::iterator_traits<foo>>::value);
  static_assert(std::same_as<std::_ITER_TRAITS<foo>, std::iterator_traits<foo>>);

//  std::iterator_traits<foo>::__primary_template;

  using I = std::list<int>::iterator;
  static_assert(std::same_as<std::_ITER_TRAITS<I>, std::iterator_traits<I>>);
}

namespace lsd {

int Test() {
  LSD_INIT_TEST("lsd::algorithm")


  using namespace lsd::string_view_literals;
  {
    LSD_TEST((ranges::min(1, 9999) == 1));
    LSD_TEST((ranges::min('a', 'b') == 'a'));
    LSD_TEST(ranges::min({"foo"_sv, "bar"_sv, "hello"_sv}, {}, &lsd::string_view::size) == "foo"_sv);

    std::vector<int> v = {1, 2, 3, 4};
    LSD_TEST(ranges::min_element(v) == v.begin());
    LSD_TEST(ranges::min(v) == 1);
  }

  { // ranges::for_each
    std::vector<int> nums = {1, 2, 3, 4, 5};
    auto print = [](const auto& x) { std::cout << ' ' << x; };

    ranges::for_each(lsd::as_const(nums), print);
    print('\n');
    struct Sum {
      void operator()(int n) { sum += n; }
      int sum {0};
    };

    ranges::for_each(nums, [](auto& x) { ++x; });
    LSD_TEST(nums.front() == 2);
    LSD_TEST(nums.back() == 6);

    auto result = ranges::for_each(nums.begin(), nums.end(), Sum{});
    LSD_TEST(result.in == nums.end());
    LSD_TEST(result.fun.sum == 20);

    ranges::for_each(lsd::as_const(nums), print);
    print('\n');

    using pair = lsd::compressed_pair<int, std::string>;
    std::vector<pair> pairs = {{1, "one"}, {2, "two"}, {3, "three"}};

    std::cout << "project the pair::first";
    ranges::for_each(pairs, print, [](const pair& p) { return p.first(); });
    print('\n');

    using std_pair = std::pair<int, std::string>;
    std::vector<std_pair> pairs2 = {{1, "one"}, {2, "two"}, {3, "three"}};
    std::cout << "project the pair::second";
    ranges::for_each(pairs2, print, &std_pair::second);
    print('\n');
  }

  {
    std::vector<std::string> v = {"a", "b", "c", "d", "e", "f", "g"};
    const std::vector<std::string> v1 = {"d", "e", "f", "g", "", "", ""};
    const std::vector<std::string> v2 = {"", "", "d", "e", "f", "g", ""};

    lsd::shift_left(begin(v), end(v), 3);
    LSD_TEST((lsd::ranges::equal(v, v1)));

    lsd::shift_right(begin(v), end(v), 2);
    LSD_TEST((lsd::ranges::equal(v, v2)));

    lsd::shift_left(begin(v), end(v), 8);
    LSD_TEST((lsd::ranges::equal(v, v2)));
  }

  { // fold_left
    std::cout << "Line " << __LINE__ << ", fold_left:\n";

    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};

    int sum = ranges::fold_left(v.begin(), v.end(), 0, std::plus<>{});
    LSD_TEST(sum == 36);

    int mul = ranges::fold_left(v, 1, std::multiplies<>{});
    LSD_TEST(mul == 1*2*3*4*5*6*7*8);

    std::vector<std::pair<char, int>> data {{'A', 2}, {'B', 3}, {'C', 4}};
    auto sec = ranges::fold_left(
        data | ranges::views::values, 2, std::multiplies<>()
    );
    LSD_TEST(sec == 48);

    std::string str = ranges::fold_left(
        v, "A", [](std::string s, int x) { return s + ':' + std::to_string(x); }
    );
    std::cout << "str: " << str << '\n';
    LSD_TEST(str == "A:1:2:3:4:5:6:7:8");
  }

  { // ranges::max_element
    const auto v = {3, 1, -14, 1, 5, 9, -14, 9};

    auto result = ranges::max_element(v.begin(), v.end());
    LSD_TEST(ranges::distance(v.begin(), result) == 5);

    auto abs_compare = [](int a, int b) { return std::abs(a) < std::abs(b); };
    LSD_TEST(ranges::max_element(v, abs_compare) == ranges::begin(v) + 2);
  }

  { // ranges::max
    LSD_TEST(ranges::max({0B10, 0X10, 010, 10}) == 16);
    LSD_TEST(ranges::max(1, 9999) == 9999);
    LSD_TEST(ranges::max('a', 'b') == 'b');
    LSD_TEST(ranges::max({"foo"_sv, "bar"_sv, "hello"_sv}, {}, &lsd::string_view::size) == "hello"_sv);
  }

  { // ranges::search
    std::cout << "Line " << __LINE__ << ", ranges::search:\n";

    constexpr auto haystack {"abcd abcd"_sv};
    constexpr auto needle {"bcd"_sv};

    // the search uses iterator pairs begin()/end():
    constexpr auto found1 = lsd::ranges::search(
        haystack.begin(), haystack.end(),
        needle.begin(), needle.end());
    LSD_TEST(found1 && lsd::ranges::distance(haystack.begin(), found1.begin()) == 1);

    constexpr auto found2 = lsd::ranges::search(haystack, needle);
    LSD_TEST(found2 && lsd::ranges::distance(haystack.begin(), found1.begin()) == 1);

    constexpr auto none {""_sv};
    constexpr auto found3 = lsd::ranges::search(haystack, none);
    LSD_TEST(found3.empty());

    constexpr auto awl {"efg"_sv};
    constexpr auto found4 = lsd::ranges::search(haystack, awl);
    LSD_TEST(found4.empty());

    constexpr auto bodkin {"234"_sv};
    auto found5 = lsd::ranges::search(haystack, bodkin,
        [](const int x, const int y) { return x == y; }, // pred
        [](const int x) { return std::toupper(x); }, // proj1
        [](const int y) { return y + 'A' - '1'; }); // proj2
    LSD_TEST(found5 && lsd::ranges::distance(haystack.begin(), found5.begin()) == 1);
  }

  { // ranges::lexicographical_compare
    std::cout << "Line " << __LINE__ << ", ranges::lexicographical_compare:\n";

    std::vector<char> v1 {'a', 'b', 'c', 'd'};
    std::vector<char> v2 {'a', 'b', 'c', 'd'};

    LSD_TEST(ranges::lexicographical_compare(v1, v2) == false);
    LSD_TEST(ranges::lexicographical_compare("dabc"_sv, "cbda"_sv) == false);
    LSD_TEST(ranges::lexicographical_compare("bdac"_sv, "adcb"_sv) == false);
    LSD_TEST(ranges::lexicographical_compare("acdb"_sv, "cdab"_sv) == true);
  }

  { // ranges::set_intersection
    const auto in1 = {1, 2, 2, 3, 4, 5, 6};
    const auto in2 = {2, 2, 3, 3, 5, 7};
    std::vector<int> out {};

    ranges::set_intersection(in1, in2, std::back_inserter(out));

    LSD_TEST(ranges::equal(out, {2, 2, 3, 5}));

    std::vector<int> v1{7, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> v2{5, 7, 9, 7};
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::vector<int> v_intersection;
    ranges::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                             std::back_inserter(v_intersection));
    LSD_TEST(ranges::equal(v_intersection, {5, 7, 7}));
  }

  {
    constexpr static auto v = {1, 2, 3, 1, 2, 3, 1, 2};

    {
      auto i1 = ranges::find_last(v.begin(), v.end(), 3);
      auto i2 = ranges::find_last(v, 3);
      LSD_TEST(ranges::distance(v.begin(), i1.begin()) == 5);
      LSD_TEST(ranges::distance(v.begin(), i2.begin()) == 5);
    }
    {
      auto i1 = ranges::find_last(v.begin(), v.end(), -3);
      auto i2 = ranges::find_last(v, -3);
      LSD_TEST(i1.begin() == v.end());
      LSD_TEST(i2.begin() == v.end());
    }

    auto abs = [](int x) { return x < 0 ? -x : x; };

    {
      auto pred = [](int x) { return x == 3; };
      auto i1 = ranges::find_last_if(v.begin(), v.end(), pred, abs);
      auto i2 = ranges::find_last_if(v, pred, abs);
      LSD_TEST(ranges::distance(v.begin(), i1.begin()) == 5);
      LSD_TEST(ranges::distance(v.begin(), i2.begin()) == 5);
    }
    {
      auto pred = [](int x) { return x == -3; };
      auto i1 = ranges::find_last_if(v.begin(), v.end(), pred, abs);
      auto i2 = ranges::find_last_if(v, pred, abs);
      LSD_TEST(i1.begin() == v.end());
      LSD_TEST(i2.begin() == v.end());
    }

    {
      auto pred = [](int x) { return x == 1 or x == 2; };
      auto i1 = ranges::find_last_if_not(v.begin(), v.end(), pred, abs);
      auto i2 = ranges::find_last_if_not(v, pred, abs);
      LSD_TEST(ranges::distance(v.begin(), i1.begin()) == 5);
      LSD_TEST(ranges::distance(v.begin(), i2.begin()) == 5);
    }
    {
      auto pred = [](int x) { return x == 1 or x == 2 or x == 3; };
      auto i1 = ranges::find_last_if_not(v.begin(), v.end(), pred, abs);
      auto i2 = ranges::find_last_if_not(v, pred, abs);
      LSD_TEST(i1.begin() == v.end());
      LSD_TEST(i2.begin() == v.end());
    }

    using P = std::pair<lsd::string_view, int>;
    std::forward_list<P> list
        {
            {"one", 1}, {"two", 2}, {"three", 3},
            {"one", 4}, {"two", 5}, {"three", 6},
        };
    auto cmp_one = [](const lsd::string_view &s) { return s == "one"; };

    // find latest element that satisfy the comparator, and projecting pair::first
    const auto subrange = ranges::find_last_if(list, cmp_one, &P::first);
    LSD_TEST(ranges::equal(subrange, std::vector<P>{{"one", 4}, {"two", 5}, {"three", 6}}));
  }

  { // ranges::find_end
    constexpr auto secret{"password password word..."_sv};
    constexpr auto wanted{"password"_sv};

    auto s1 = ranges::find_end(secret.cbegin(), secret.cend(), wanted.cbegin(), wanted.cend());
    LSD_TEST(std::distance(secret.begin(), s1.begin()) == 9 && s1.size() == 8);

    auto s2 = ranges::find_end(secret, "word"_sv);
    LSD_TEST(std::distance(secret.begin(), s2.begin()) == 18 && s2.size() == 4);

    auto s3 = ranges::find_end(secret, "ORD"_sv, [](const char x, const char y) {
      return std::tolower(x) == std::tolower(y);
    });
    LSD_TEST(std::distance(secret.begin(), s3.begin()) == 19 && s3.size() == 3);

    auto s4 = ranges::find_end(secret, "SWORD"_sv, {}, {}, [](char c) { return std::tolower(c); });
    LSD_TEST(std::distance(secret.begin(), s4.begin()) == 12 && s4.size() == 5);
  }

  { // ranges::find_first_of
    constexpr static auto haystack = {1, 2, 3, 4};
    constexpr static auto needles  = {0, 3, 4, 3};

    auto found1 = ranges::find_first_of(haystack.begin(), haystack.end(),
                                               needles.begin(), needles.end());
    LSD_TEST(std::distance(haystack.begin(), found1) == 2);

    auto found2 = ranges::find_first_of(haystack, needles);
    LSD_TEST(std::distance(haystack.begin(), found2) == 2);

    constexpr static auto negatives = {-6, -3, -4, -3};
    auto not_found = ranges::find_first_of(haystack, negatives);
    LSD_TEST(not_found == haystack.end());

    auto found3 = ranges::find_first_of(haystack, negatives,
                                               [](int x, int y) { return x == -y; }); // uses a binary comparator
    LSD_TEST(std::distance(haystack.begin(), found3) == 2);

    struct P { int x, y; };
    constexpr static auto p1 = {P{1, -1}, P{2, -2}, P{3, -3}, P{4, -4}};
    constexpr static auto p2 = {P{5, -5}, P{6, -3}, P{7, -5}, P{8, -3}};
    const auto found4 = ranges::find_first_of(p1, p2, {}, &P::y, &P::y);
    LSD_TEST(std::distance(p1.begin(), found4) == 2);
  }

  { // ranges::make_heap
    std::vector<int> h{1, 6, 1, 8, 0, 3, 3, 9, 8, 8, 7, 4, 9, 8, 9};

    lsd::ranges::make_heap(h);
    LSD_TEST(std::is_heap(h.begin(), h.end()));

    lsd::ranges::make_heap(h, std::greater<>{});
    LSD_TEST(std::is_heap(h.begin(), h.end()) == false);
    LSD_TEST(std::is_heap(h.begin(), h.end(), std::greater<>{}));
  }

  { // ranges::pop_heap
    auto v = lsd::to_array({3, 1, 4, 1, 5, 9, 2, 6, 5, 3});

    lsd::ranges::make_heap(v);
    for (auto n {lsd::ssize(v)}; n >= 0; --n) {
      lsd::ranges::pop_heap(v.begin(), v.begin() + n);
      LSD_TEST(std::is_sorted(v.cbegin() + n, v.cend()));
    }

    lsd::ranges::make_heap(v, lsd::ranges::greater{});
    for (auto n {lsd::ssize(v)}; n >= 0; --n) {
      lsd::ranges::pop_heap(v.begin(), v.begin() + n, lsd::ranges::greater{});
      LSD_TEST(std::is_sorted(v.cbegin() + n, v.cend(), lsd::ranges::greater{}));
    }
  }

  { // ranges::sort_heap
    auto v = lsd::to_array({3, 1, 4, 1, 5, 9});
    lsd::ranges::make_heap(v);
    lsd::ranges::sort_heap(v);
    LSD_TEST(std::is_sorted(v.begin(), v.end()));

    lsd::ranges::make_heap(v, lsd::ranges::greater{});
    lsd::ranges::sort_heap(v, lsd::ranges::greater{});
    LSD_TEST(std::is_sorted(v.begin(), v.end(), lsd::ranges::greater{}));
  }

  { // ranges::sort
    struct Particle {
      std::string name;
      double mass; // MeV
    };

    auto s = lsd::to_array({5, 7, 4, 2, 8, 6, 1, 9, 0, 3});
    namespace ranges = lsd::ranges;

    ranges::sort(s);
    LSD_TEST(std::is_sorted(s.begin(), s.end()));

    ranges::sort(s, ranges::greater());
    LSD_TEST(std::is_sorted(s.begin(), s.end(), std::greater<>{}));

    Particle particles[] {
        {"Electron", 0.511}, {"Muon", 105.66}, {"Tau", 1776.86},
        {"Positron", 0.511}, {"Proton", 938.27}, {"Neutron", 939.57}
    };

    // Sort by name using a projection
    ranges::sort(particles, {}, &Particle::name);
    LSD_TEST(ranges::equal(particles, {"Electron"_sv, "Muon"_sv, "Neutron"_sv, "Positron"_sv, "Proton"_sv, "Tau"_sv}, {}, &Particle::name));

    // Sort by mass using a projection
    ranges::sort(particles, {}, &Particle::mass);
    LSD_TEST(ranges::equal(particles, {0.511, 0.511, 105.66, 938.27, 939.57, 1776.86}, {}, &Particle::mass));
  }

  { // ranges::contains, ranges::contains_subrange
    constexpr auto haystack = lsd::to_array({3, 1, 4, 1, 5});
    constexpr auto needle = lsd::to_array({1, 4, 1});
    constexpr auto bodkin = lsd::to_array({2, 5, 2});
    auto increment = [](int x) { return ++x; };
    auto decrement = [](int x) { return --x; };

    LSD_TEST(lsd::ranges::contains(haystack, 4));
    LSD_TEST(!lsd::ranges::contains(haystack, 6));
    LSD_TEST(lsd::ranges::contains(haystack, 6, increment));
    LSD_TEST(!lsd::ranges::contains(haystack, 1, increment));

    LSD_TEST(lsd::ranges::contains_subrange(haystack, needle));
    LSD_TEST(!lsd::ranges::contains_subrange(haystack, bodkin));
    LSD_TEST(lsd::ranges::contains_subrange(haystack, bodkin, {}, increment));
    LSD_TEST(!lsd::ranges::contains_subrange(haystack, bodkin, {}, decrement));
    LSD_TEST(lsd::ranges::contains_subrange(haystack, bodkin, {}, {}, decrement));
  }

  LSD_TEST_RETURN;
}

} // namespace

int main() {
  return lsd::Test();
}
