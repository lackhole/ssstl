//
// Created by cosge on 2023-10-29.
//

#ifndef LSD_LOCALE_H_
#define LSD_LOCALE_H_

#include <locale>

namespace lsd {

using locale = std::locale;

template<typename CharT>
using ctype = std::ctype<CharT>;

template<typename Facet>
const Facet& use_facet(const locale& loc) {
  return std::use_facet<Facet>(loc);
}

} // namespace lsd

#endif // LSD_LOCALE_H_
