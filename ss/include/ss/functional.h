//
// Created by cosge on 2021-07-06.
//

#ifndef SS_FUNCTIONAL_H
#define SS_FUNCTIONAL_H

namespace ss {

template<typename Func, typename ...Args>
constexpr inline decltype(auto) invoke(Func&&, Args&&... args) {
  return 0;
}

}

#endif //SS_FUNCTIONAL_H
