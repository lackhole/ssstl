//
// Created by cosge on 2023-10-29.
//

#ifndef LSD_ISTREAM_H_
#define LSD_ISTREAM_H_

#include "lsd/__string/char_traits.h"

namespace lsd {

template<
    class CharT,
    class Traits = char_traits<CharT>
>
using basic_istream = std::basic_istream<CharT, Traits>;

using istream	= basic_istream<char>;
using wistream = basic_istream<wchar_t>;

} // namespace lsd


#endif // LSD_ISTREAM_H_
