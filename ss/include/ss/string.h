//
// Created by cosge on 2023-10-29.
//

#ifndef SS_STRING_H_
#define SS_STRING_H_

#include <string>

#include "ss/__config.h"
#include "ss/__string/char_traits.h"
#include "ss/memory.h"

namespace ss {

template<
    class CharT,
    class Traits = char_traits<CharT>,
    class Allocator = allocator<CharT>
>
using basic_string = std::basic_string<CharT, Traits, Allocator>;

using string =	basic_string<char>;
using wstring =	basic_string<wchar_t>;
#if SS_HAS_TYPE_CHAR8_T_CXX20
using u8string = basic_string<char8_t>
#endif
#if SS_HAS_TYPE_CHAR16_T
using u16string = basic_string<char16_t>;
#endif
#if SS_HAS_TYPE_CHAR32_T
using u32string = basic_string<char32_t>;
#endif

} // namespace ss

#endif // SS_STRING_H_
