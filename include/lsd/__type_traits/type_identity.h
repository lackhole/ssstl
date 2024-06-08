//
// Created by yonggyulee on 2023/09/29.
//

#ifndef LSD_TYPE_TRAITS_TYPE_IDENTITY_H_
#define LSD_TYPE_TRAITS_TYPE_IDENTITY_H_

namespace lsd {

template<typename T>
struct type_identity {
  using type = T;
};

template<typename T>
using type_identity_t = typename type_identity<T>::type;

} // namespace lsd

#endif // LSD_TYPE_TRAITS_TYPE_IDENTITY_H_
