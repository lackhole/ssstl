//
// Created by yonggyulee on 2024/01/04.
//

#ifndef LSD_RANGES_SUBRANGE_KIND_HPP
#define LSD_RANGES_SUBRANGE_KIND_HPP

namespace lsd {
namespace ranges {

enum
#if !defined(_MSC_VER) || __cplusplus >= 201703L
class
#endif
subrange_kind : bool {
    unsized,
    sized
};

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_SUBRANGE_KIND_HPP
