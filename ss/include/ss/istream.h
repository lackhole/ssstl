//
// Created by cosge on 2023-10-29.
//

#ifndef SS_ISTREAM_H_
#define SS_ISTREAM_H_

#include "ss/__string/char_traits.h"

namespace ss {

template<
    class CharT,
    class Traits = char_traits<CharT>
>
using basic_istream = std::basic_istream<CharT, Traits>;

using istream	= basic_istream<char>;
using wistream = basic_istream<wchar_t>;

} // namespace ss


#endif // SS_ISTREAM_H_
