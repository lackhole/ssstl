//
// Created by cosge on 2023-10-29.
//

#ifndef SS_OSTREAM_H_
#define SS_OSTREAM_H_

#include "ss/__string/char_traits.h"

#include <ostream>

namespace ss {

template<
    class CharT,
    class Traits = char_traits<CharT>
> using basic_ostream = std::basic_ostream<CharT, Traits>;

using ostream = basic_ostream<char>;
using wostream = basic_ostream<wchar_t>;

} // namespace ss

#endif // SS_OSTREAM_H_
