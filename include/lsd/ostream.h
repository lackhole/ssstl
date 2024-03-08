//
// Created by cosge on 2023-10-29.
//

#ifndef LSD_OSTREAM_H_
#define LSD_OSTREAM_H_

#include "lsd/__string/char_traits.h"

#include <ostream>

namespace lsd {

template<
    class CharT,
    class Traits = char_traits<CharT>
> using basic_ostream = std::basic_ostream<CharT, Traits>;

using ostream = basic_ostream<char>;
using wostream = basic_ostream<wchar_t>;

} // namespace lsd

#endif // LSD_OSTREAM_H_
