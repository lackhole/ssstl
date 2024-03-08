//
// Created by cosge on 2023-10-29.
//

#ifndef LSD_STRING_H_
#define LSD_STRING_H_

#include <string>

#include "lsd/__string/char_traits.h"
#include "lsd/memory.h"

namespace lsd {

template<
    class CharT,
    class Traits = char_traits<CharT>,
    class Allocator = allocator<CharT>
>
using basic_string = std::basic_string<CharT, Traits, Allocator>;

using string =	basic_string<char>;
using wstring =	basic_string<wchar_t>;
#if LSD_HAS_TYPE_CHAR8_T_CXX20
using u8string = basic_string<char8_t>;
#endif
#if LSD_HAS_TYPE_CHAR16_T
using u16string = basic_string<char16_t>;
#endif
#if LSD_HAS_TYPE_CHAR32_T
using u32string = basic_string<char32_t>;
#endif

} // namespace lsd

#endif // LSD_STRING_H_
