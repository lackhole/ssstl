//
// Created by YongGyu Lee on 02/01/24.
//

#ifndef LSD_VARIANT_HASH_HPP
#define LSD_VARIANT_HASH_HPP

#include <functional>

#include "lsd/__functional/hash_array.h"
#include "lsd/__variant/variant.h"
#include "lsd/__variant/variant_npos.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/is_invocable.h"
#include "lsd/__type_traits/remove_cvref.h"

namespace lsd {
namespace detail {

struct variant_hash_visitor {
  template<typename T, std::size_t I>
  constexpr std::size_t operator()(const T& x, in_place_index_t<I>) const {
    return lsd::FNV_1a(std::hash<T>{}(x), I);
  }

  template<typename T>
  constexpr std::size_t operator()(const T& x, in_place_index_t<variant_npos>) const {
    return 0;
  }
};

template<typename Variant, bool Hashable /* false */>
struct variant_hash {};

template<typename Variant>
struct variant_hash<Variant, true> {
  std::size_t operator()(const Variant& var) const {
    return variant_raw_visit(var.index(), var._base().union_, variant_hash_visitor{});
  }
};

} // namespace detail
} // namespace lsd

template<typename... Ts>
struct std::hash<lsd::variant<Ts...>>
    : lsd::detail::variant_hash<
        lsd::variant<Ts...>,
        lsd::conjunction<lsd::is_invocable<std::hash<Ts>, const lsd::remove_cvref_t<Ts>&>...>::value
      > {};

#endif // LSD_VARIANT_HASH_HPP
