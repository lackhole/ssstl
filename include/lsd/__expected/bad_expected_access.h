//
// Created by YongGyu Lee on 3/20/24.
//

#ifndef LSD_EXPECTED_BAD_EXPECTED_ACCESS_HPP_
#define LSD_EXPECTED_BAD_EXPECTED_ACCESS_HPP_

#include <exception>
#include <utility>

namespace lsd {

template<typename E>
class bad_expected_access;

template<>
class bad_expected_access<void> : public std::exception {
 public:
  const char* what() const noexcept override {
    return "lsd::bad_expected_access";
  }

 protected:
  bad_expected_access() noexcept = default;
  bad_expected_access(const bad_expected_access&) = default;
  bad_expected_access(bad_expected_access&&) = default;
  bad_expected_access& operator=(const bad_expected_access&) = default;
  bad_expected_access& operator=(bad_expected_access&&) = default;
};

template<typename E>
class bad_expected_access : public bad_expected_access<void> {
 public:
  explicit bad_expected_access(E e)
      : error_(std::move(e)) {}

  const E& error() const& noexcept { return error_; }
  E& error() & noexcept { return error_; }
  const E&& error() const&& noexcept { return std::move(error_); }
  E&& error() && noexcept { return std::move(error_); }

 private:
  E error_;
};

} // namespace lsd

#endif // LSD_EXPECTED_BAD_EXPECTED_ACCESS_HPP_
