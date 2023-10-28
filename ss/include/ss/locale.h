//
// Created by cosge on 2023-10-29.
//

#ifndef SS_LOCALE_H_
#define SS_LOCALE_H_

#include <locale>

namespace ss {

using locale = std::locale;

template<typename CharT>
using ctype = std::ctype<CharT>;

template<typename Facet>
const Facet& use_facet(const locale& loc) {
  return std::use_facet<Facet>(loc);
}

} // namespace ss

#endif // SS_LOCALE_H_
