#ifndef LSD_TYPE_TRAITS_META_H_
#define LSD_TYPE_TRAITS_META_H_

#include <type_traits>

namespace lsd {
namespace meta {

template<typename B, typename IfRes, typename ElseIfRes, typename...>
struct conditional_chain;

template<typename B, typename IfRes, typename ElseRes>
struct conditional_chain<B, IfRes, ElseRes> {
  using type = std::conditional_t<bool(B::value), IfRes, ElseRes>;
};

template<typename B1, typename IfRes, typename B2, typename ElseIfRes, typename... Rest>
struct conditional_chain<B1, IfRes, B2, ElseIfRes, Rest...> {
  using type = std::conditional_t<
      bool(B1::value), IfRes,
      typename conditional_chain<B2, ElseIfRes, Rest...>::type
  >;
};

template<typename B, typename IfRes, typename B2, typename... ElseIfRes>
using conditional_chain_t = typename conditional_chain<B, IfRes, B2, ElseIfRes...>::type;

} // namespace meta
} // namespace lsd

#endif // LSD_TYPE_TRAITS_META_H_
