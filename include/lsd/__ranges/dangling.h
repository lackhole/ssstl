//
// Created by yonggyulee on 2023/12/29.
//

#ifndef LSD_RANGES_DANGLING_HPP
#define LSD_RANGES_DANGLING_HPP

namespace lsd {
namespace ranges {

struct dangling {
  constexpr dangling() noexcept = default;

  template<typename... Args>
  constexpr dangling(Args&&...) noexcept {}
};

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_DANGLING_HPP
