//
// Created by YongGyu Lee on 11/3/23.
//

#ifndef LSD_VARIANT_BAD_VARIANT_ACCESS_HPP
#define LSD_VARIANT_BAD_VARIANT_ACCESS_HPP

#include <exception>

namespace lsd {

class bad_variant_access : public std::exception {
 public:
  bad_variant_access() noexcept = default;
  bad_variant_access(const bad_variant_access&) noexcept = default;

  const char* what() const noexcept override {
    return "lsd::variant: Bad variant access";
  }
};

} // namespace lsd

#endif // LSD_VARIANT_BAD_VARIANT_ACCESS_HPP
