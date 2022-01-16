# /*
#  * Created by YongGyu Lee on 2021/08/14.
#  */
#
# ifndef SS_TUPLE_H_
# define SS_TUPLE_H_
#
# include "ss/detail/allocator_arg.h"
# include "ss/detail/uses_allocator.h"
# include "ss/detail/macro.h"
# include "ss/detail/tuple_helper.h"
# include "ss/utility.h"
# if SS_CXX_VER >= 20
#   include "ss/compare.h"
# endif

namespace ss {

template<typename...> class tuple;

namespace detail {

template<typename T, typename = void>
struct is_copy_list_initializable : false_type {};

template<typename T>
struct is_copy_list_initializable<T, void_t<decltype(ss::declval<T&>() = {})>> : true_type {};

template<typename T>
using make_tuple_sequence = make_index_sequence<tuple_size<T>::value>;

// TODO: Empty base optimization?
template<size_t I, typename T>
struct tuple_leaf {
  using type = T;

  constexpr tuple_leaf() : element{} {}

  constexpr tuple_leaf(const T& arg) : element(arg) {}

  template<typename U>
  constexpr tuple_leaf(U&& arg) : element(ss::forward<U>(arg)) {}

  template<typename Alloc, typename... U,
    enable_if_t<
      uses_allocator<T, Alloc>::value,
    int> = 0>
  constexpr tuple_leaf(allocator_arg_t, const Alloc& alloc, U&&... arg)
      : element(allocator_arg_t{}, alloc, ss::forward<U>(arg)...) {}

  template<typename Alloc, typename... U,
    enable_if_t<
      !uses_allocator<T, Alloc>::value,
    int> = 0>
  constexpr tuple_leaf(allocator_arg_t, const Alloc& alloc, U&&... arg)
      : element(ss::forward<U>(arg)...) {}

  T element;
};

template<typename Indices, typename... Types>
struct tuple_impl;

template<size_t... I, typename... Types>
struct tuple_impl<index_sequence<I...>, Types...> : public tuple_leaf<I, Types>... {
  constexpr tuple_impl() : tuple_leaf<I, Types>()... {}

  constexpr tuple_impl(const Types&... args) : tuple_leaf<I, Types>(args)... {}

  template<typename... UTypes>
  constexpr tuple_impl(UTypes&&... args) : tuple_leaf<I, Types>(ss::forward<UTypes>(args))... {}

  template<typename Alloc, typename... UTypes>
  constexpr tuple_impl(allocator_arg_t, const Alloc& alloc, UTypes&&... args)
      : tuple_leaf<I, Types>(allocator_arg_t{}, alloc, ss::forward<UTypes>(args))... {}

};

struct tuple_tag_unpack_tuple_t {};

template<typename Tuple, typename Pair>
struct pair_to_tuple_constructible {
  using copyable = false_type;
  using moveable = false_type;
  using copyable_implicit = false_type;
  using moveable_implicit = false_type;
};

template<typename T1, typename T2, typename U1, typename U2>
struct pair_to_tuple_constructible<tuple<T1, T2>, pair<U1, U2>> {
  using copyable = conjunction<is_constructible<T1, const U1&>, is_constructible<T2, const U2&>>;
  using moveable = conjunction<is_constructible<T1, U1&&>, is_constructible<T2, U2&&>>;
  using copyable_implicit = conjunction<is_convertible<const U1&, T1>, is_convertible<const U2&, T2>>;
  using moveable_implicit = conjunction<is_convertible<U1&&, T1>, is_convertible<U2&&, T2>>;
};

template<typename Dst, typename Src, size_t... I>
SS_CONSTEXPR_AFTER_14 void tuple_element_wise_copy(Dst& dst, const Src& src, index_sequence<I...>);

template<typename Dst, typename Src, size_t... I>
SS_CONSTEXPR_AFTER_14 void tuple_element_wise_forward(Dst& dst, Src&& src, index_sequence<I...>);

} // namespace detail

/**
 * tuple_size
 * @tparam T
 */
template<typename... T>
struct tuple_size<tuple<T...>> : integral_constant<size_t, sizeof...(T)> {};



/**
 * tuple_element
 * @tparam I
 */
template<size_t I>
struct tuple_element<I, tuple<>> {
  static_assert(detail::always_false<bool_constant<bool(I)>>::value,
    "ss::tuple : Index out of bounds");
};

template<typename T, typename... Rest>
struct tuple_element<0, tuple<T, Rest...>> {
  using type = T;
};

template<size_t I, typename T, typename... Rest>
struct tuple_element<I, tuple<T, Rest...>> : tuple_element<I - 1, tuple<Rest...>> {};

namespace detail {

template<size_t I, typename T, typename Tuple>
struct tuple_index_impl;

template<size_t I, typename T>
struct tuple_index_impl<I, T, tuple<>> {
  static constexpr size_t index = I;
  static constexpr bool found = false;
};

template<size_t I, typename T, typename... Rest>
struct tuple_index_impl<I, T, tuple<T, Rest...>> {
  static constexpr size_t index = I;
  static constexpr bool found = true;
  static_assert(tuple_index_impl<I + 1, T, tuple<Rest...>>::found == false,
    "ss::get(ss::tuple) : Duplicated type T in ss::tuple");
};

template<size_t I, typename T, typename U, typename... Rest>
struct tuple_index_impl<I, T, tuple<U, Rest...>> : tuple_index_impl<I + 1, T, tuple<Rest...>> {};

template<typename T, typename Tuple>
struct tuple_index {
  static constexpr size_t value = tuple_index_impl<0, T, Tuple>::index;
  static constexpr bool found = tuple_index_impl<0, T, Tuple>::found;
  static_assert(found, "ss::get(ss::tuple) : No type T in ss::tuple");
};

template<typename T, typename Tuple>
using tuple_leaf_by_type = tuple_leaf<tuple_index<T, Tuple>::value, T>;

} // namespace detail


/**
 * get(ss::tuple)
 * @tparam I
 * @param t
 * @return
 */
template<size_t I, typename... Types>
constexpr tuple_element_t<I, tuple<Types...>>& get(tuple<Types...>& t) noexcept;

template<size_t I, typename... Types>
constexpr const tuple_element_t<I, tuple<Types...>>& get(const tuple<Types...>& t) noexcept;

template<size_t I, typename... Types>
constexpr tuple_element_t<I, tuple<Types...>>&& get(tuple<Types...>&& t) noexcept;

template<size_t I, typename... Types>
constexpr const tuple_element_t<I, tuple<Types...>>&& get(const tuple<Types...>&& t) noexcept;

template<typename T, typename... Types>
constexpr T& get(tuple<Types...>& t) noexcept;

template<typename T, typename... Types>
constexpr T&& get(tuple<Types...>&& t) noexcept;

template<typename T, typename... Types>
constexpr const T& get(const tuple<Types...>& t) noexcept;

template<typename T, typename... Types>
constexpr const T&& get(const tuple<Types...>&& t) noexcept;



/**
 * tuple
 */
template<>
class tuple<> {
 public:
  constexpr tuple() = default;

};

template<typename... Types>
class tuple {
  using tuple_impl = detail::tuple_impl<index_sequence_for<Types...>, Types...>;
  using tuple_tag_unpack_tuple_t = detail::tuple_tag_unpack_tuple_t;
  tuple_impl base;

  template<size_t ...I, typename Tuple>
  constexpr tuple(tuple_tag_unpack_tuple_t, index_sequence<I...>, Tuple&& other)
    : base(ss::get<I>(other)...) {}

  template<typename Tuple>
  constexpr tuple(tuple_tag_unpack_tuple_t, Tuple&& other)
    : tuple(tuple_tag_unpack_tuple_t{}, make_index_sequence<sizeof...(Types)>{}, ss::forward<Tuple>(other)) {}

  template<size_t ...I, typename Alloc, typename Tuple>
  constexpr tuple(tuple_tag_unpack_tuple_t, index_sequence<I...>, const Alloc& alloc, Tuple&& other)
    : base(allocator_arg_t{}, alloc, ss::get<I>(other)...) {}

  template<typename Alloc, typename Tuple>
  constexpr tuple(tuple_tag_unpack_tuple_t, const Alloc& alloc, Tuple&& other)
    : tuple(tuple_tag_unpack_tuple_t{}, make_index_sequence<sizeof...(Types)>{}, alloc, ss::forward<Tuple>(other)) {}

 public:
  template<typename Dummy = void,
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        is_default_constructible<Types>...,
        detail::is_copy_list_initializable<Types>...
      >::value,
    int> = 0>
  constexpr tuple() : base() {}

  template<typename Dummy = void,
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        is_default_constructible<Types>...,
        disjunction<negation<detail::is_copy_list_initializable<Types>>...>
      >::value,
    int> = 0>
  constexpr explicit tuple() : base() {}

  template<typename Alloc,
    enable_if_t<
      conjunction<
        detail::always_true<Alloc>,
        is_default_constructible<Types>...,
        detail::is_copy_list_initializable<Types>...
      >::value,
    int> = 0>
  constexpr tuple(allocator_arg_t, const Alloc& alloc) : base(allocator_arg_t{}, alloc) {}

  template<typename Alloc,
    enable_if_t<
      conjunction<
        detail::always_true<Alloc>,
        is_default_constructible<Types>...,
        disjunction<negation<detail::is_copy_list_initializable<Types>>...>
      >::value,
    int> = 0>
  constexpr explicit tuple(allocator_arg_t, const Alloc& alloc) : base(allocator_arg_t{}, alloc) {}

  template<typename Dummy = void,
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        is_copy_constructible<Types>...,
        is_convertible<const Types&, Types>...
      >::value,
    int> = 0>
  constexpr tuple(const Types&... args) : base(args...) {}

  template<typename Dummy = void,
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        is_copy_constructible<Types>...,
        disjunction<negation<is_convertible<const Types&, Types>>...>
      >::value,
    int> = 0>
  constexpr explicit tuple(const Types&... args) : base(args...) {}

  template<typename Alloc,
    enable_if_t<
      conjunction<
        detail::always_true<Alloc>,
        is_copy_constructible<Types>...,
        is_convertible<const Types&, Types>...
      >::value,
    int> = 0>
  constexpr tuple(allocator_arg_t, const Alloc& alloc, const Types&... args) : base(allocator_arg_t{}, alloc, args...) {}

  template<typename Alloc,
    enable_if_t<
      conjunction<
        detail::always_true<Alloc>,
        is_copy_constructible<Types>...,
        disjunction<negation<is_convertible<const Types&, Types>>...>
      >::value,
    int> = 0>
  constexpr explicit tuple(allocator_arg_t, const Alloc& alloc, Types&... args) : base(allocator_arg_t{}, alloc, args...) {}

  template<typename... UTypes,
    enable_if_t<
      conjunction<
        bool_constant<sizeof...(Types) == sizeof...(UTypes)>,
        is_constructible<Types, UTypes&&>...,
        is_convertible<UTypes&&, Types>...
      >::value,
    int> = 0>
  constexpr tuple(UTypes&&... args) : base(ss::forward<UTypes>(args)...) {}

  template<typename... UTypes,
    enable_if_t<
      conjunction<
        bool_constant<sizeof...(Types) == sizeof...(UTypes)>,
        is_constructible<Types, UTypes&&>...,
        disjunction<negation<is_convertible<UTypes&&, Types>>...>
      >::value,
    int> = 0>
  constexpr explicit tuple(UTypes&&... args) : base(ss::forward<UTypes>(args)...) {}

  template<typename Alloc, typename... UTypes,
    enable_if_t<
      conjunction<
        bool_constant<sizeof...(Types) == sizeof...(UTypes)>,
        is_constructible<Types, UTypes&&>...,
        is_convertible<UTypes&&, Types>...
      >::value,
    int> = 0>
  constexpr tuple(allocator_arg_t, const Alloc& alloc, UTypes&&... args)
      : base(allocator_arg_t{}, alloc, ss::forward<UTypes>(args)...) {}

  template<typename Alloc, typename... UTypes,
    enable_if_t<
      conjunction<
        bool_constant<sizeof...(Types) == sizeof...(UTypes)>,
        is_constructible<Types, UTypes&&>...,
        disjunction<negation<is_convertible<UTypes&&, Types>>...>
      >::value,
    int> = 0>
  constexpr explicit tuple(allocator_arg_t, const Alloc& alloc, UTypes&&... args)
      : base(allocator_arg_t{}, alloc, ss::forward<UTypes>(args)...) {}

  template<typename... UTypes,
    enable_if_t<
      conjunction<
        bool_constant<sizeof...(Types) == sizeof...(UTypes)>,
        is_constructible<Types, const UTypes&>...,
        disjunction<
          bool_constant<sizeof...(Types) != 1>,
          negation< // all false -> NOT(OR(CONDS...))
            disjunction<
              is_convertible<const tuple<UTypes...>&, Types>...,
              is_constructible<Types, const tuple<UTypes...>&>...,
              is_same<Types, UTypes>...
            >
          >
        >,
        is_convertible<const UTypes&, Types>...
      >::value,
    int> = 0>
  constexpr tuple(const tuple<UTypes...>& other) : tuple(tuple_tag_unpack_tuple_t{}, other) {}

  template<typename... UTypes,
    enable_if_t<
      conjunction<
        bool_constant<sizeof...(Types) == sizeof...(UTypes)>,
        is_constructible<Types, const UTypes&>...,
        disjunction<
          bool_constant<sizeof...(Types) != 1>,
          negation<
            disjunction<
              is_convertible<const tuple<UTypes...>&, Types>...,
              is_constructible<Types, const tuple<UTypes...>&>...,
              is_same<Types, UTypes>...
            >
          >
        >,
        negation<conjunction<is_convertible<const UTypes&, Types>...>>
      >::value,
    int> = 0>
  constexpr explicit tuple(const tuple<UTypes...>& other) : tuple(tuple_tag_unpack_tuple_t{}, other) {}

  template<typename Alloc, typename... UTypes,
    enable_if_t<
      conjunction<
        bool_constant<sizeof...(Types) == sizeof...(UTypes)>,
        is_constructible<Types, const UTypes&>...,
        disjunction<
          bool_constant<sizeof...(Types) != 1>,
          negation< // all false -> NOT(OR(CONDS...))
            disjunction<
              is_convertible<const tuple<UTypes...>&, Types>...,
              is_constructible<Types, const tuple<UTypes...>&>...,
              is_same<Types, UTypes>...
            >
          >
        >,
        is_convertible<const UTypes&, Types>...
      >::value,
    int> = 0>
  constexpr tuple(allocator_arg_t, const Alloc& alloc, const tuple<UTypes...>& other)
      : tuple(tuple_tag_unpack_tuple_t{}, alloc, other) {}

  template<typename Alloc, typename... UTypes,
    enable_if_t<
      conjunction<
        bool_constant<sizeof...(Types) == sizeof...(UTypes)>,
        is_constructible<Types, const UTypes&>...,
        disjunction<
          bool_constant<sizeof...(Types) != 1>,
          negation<
            disjunction<
              is_convertible<const tuple<UTypes...>&, Types>...,
              is_constructible<Types, const tuple<UTypes...>&>...,
              is_same<Types, UTypes>...
            >
          >
        >,
        negation<conjunction<is_convertible<const UTypes&, Types>...>>
      >::value,
    int> = 0>
  constexpr explicit tuple(allocator_arg_t, const Alloc& alloc, const tuple<UTypes...>& other)
      : tuple(tuple_tag_unpack_tuple_t{}, alloc, other) {}

  template<typename... UTypes,
    enable_if_t<
      conjunction<
        bool_constant<sizeof...(Types) == sizeof...(UTypes)>,
        is_constructible<Types, UTypes&&>...,
        disjunction<
          bool_constant<sizeof...(Types) != 1>,
          negation<
            disjunction<
              is_convertible<tuple<UTypes...>, Types>...,
              is_constructible<Types, tuple<UTypes...>>...,
              is_same<Types, UTypes>...
            >
          >
        >,
        is_convertible<UTypes&&, Types>...
      >::value,
    int> = 0>
  constexpr tuple(tuple<UTypes...>&& other) : tuple(tuple_tag_unpack_tuple_t{}, ss::move(other)) {}

  template<typename... UTypes,
    enable_if_t<
      conjunction<
        bool_constant<sizeof...(Types) == sizeof...(UTypes)>,
        is_constructible<Types, UTypes&&>...,
        disjunction<
          bool_constant<sizeof...(Types) != 1>,
          negation<
            disjunction<
              is_convertible<tuple<UTypes...>, Types>...,
              is_constructible<Types, tuple<UTypes...>>...,
              is_same<Types, UTypes>...
            >
          >
        >,
        negation<conjunction<is_convertible<UTypes&&, Types>...>>
      >::value,
    int> = 0>
  constexpr explicit tuple(tuple<UTypes...>&& other) : tuple(tuple_tag_unpack_tuple_t{}, ss::move(other)) {}

  template<typename Alloc, typename... UTypes,
    enable_if_t<
      conjunction<
        bool_constant<sizeof...(Types) == sizeof...(UTypes)>,
        is_constructible<Types, UTypes&&>...,
        disjunction<
          bool_constant<sizeof...(Types) != 1>,
          negation<
            disjunction<
              is_convertible<tuple<UTypes...>, Types>...,
              is_constructible<Types, tuple<UTypes...>>...,
              is_same<Types, UTypes>...
            >
          >
        >,
        is_convertible<UTypes&&, Types>...
      >::value,
    int> = 0>
  constexpr tuple(allocator_arg_t, const Alloc& alloc, tuple<UTypes...>&& other)
      : tuple(tuple_tag_unpack_tuple_t{}, alloc, ss::move(other)) {}

  template<typename Alloc, typename... UTypes,
    enable_if_t<
      conjunction<
        bool_constant<sizeof...(Types) == sizeof...(UTypes)>,
        is_constructible<Types, UTypes&&>...,
        disjunction<
          bool_constant<sizeof...(Types) != 1>,
          negation<
            disjunction<
              is_convertible<tuple<UTypes...>, Types>...,
              is_constructible<Types, tuple<UTypes...>>...,
              is_same<Types, UTypes>...
            >
          >
        >,
        negation<conjunction<is_convertible<UTypes&&, Types>...>>
      >::value,
    int> = 0>
  constexpr explicit tuple(allocator_arg_t, const Alloc& alloc, tuple<UTypes...>&& other)
      : tuple(tuple_tag_unpack_tuple_t{}, alloc, ss::move(other)) {}

  template<typename U1, typename U2,
    enable_if_t<
      conjunction<
        typename detail::pair_to_tuple_constructible<tuple, pair<U1, U2>>::copyable,
        typename detail::pair_to_tuple_constructible<tuple, pair<U1, U2>>::copyable_implicit
      >::value,
    int> = 0>
  constexpr tuple(const pair<U1, U2>& p) : base(p.first, p.second) {}

  template<typename U1, typename U2,
    enable_if_t<
      conjunction<
        typename detail::pair_to_tuple_constructible<tuple, pair<U1, U2>>::copyable,
        negation<typename detail::pair_to_tuple_constructible<tuple, pair<U1, U2>>::copyable_implicit>
      >::value,
    int> = 0>
  constexpr explicit tuple(const pair<U1, U2>& p) : base(p.first, p.second) {}

  template<typename Alloc, typename U1, typename U2,
    enable_if_t<
      conjunction<
        typename detail::pair_to_tuple_constructible<tuple, pair<U1, U2>>::copyable,
        typename detail::pair_to_tuple_constructible<tuple, pair<U1, U2>>::copyable_implicit
      >::value,
    int> = 0>
  constexpr tuple(allocator_arg_t, const Alloc& alloc, const pair<U1, U2>& p)
      : base(allocator_arg_t{}, alloc, p.first, p.second) {}

  template<typename Alloc, typename U1, typename U2,
    enable_if_t<
      conjunction<
        typename detail::pair_to_tuple_constructible<tuple, pair<U1, U2>>::copyable,
        negation<typename detail::pair_to_tuple_constructible<tuple, pair<U1, U2>>::copyable_implicit>
      >::value,
    int> = 0>
  constexpr explicit tuple(allocator_arg_t, const Alloc& alloc, const pair<U1, U2>& p)
      : base(allocator_arg_t{}, alloc, p.first, p.second) {}

  template<typename U1, typename U2,
    enable_if_t<
      conjunction<
        typename detail::pair_to_tuple_constructible<tuple, pair<U1, U2>>::moveable,
        typename detail::pair_to_tuple_constructible<tuple, pair<U1, U2>>::moveable_implicit
      >::value,
    int> = 0>
  constexpr tuple(pair<U1, U2>&& p) : base(ss::move(p.first), ss::move(p.second)) {}

  template<typename U1, typename U2,
    enable_if_t<
      conjunction<
        typename detail::pair_to_tuple_constructible<tuple, pair<U1, U2>>::moveable,
        negation<typename detail::pair_to_tuple_constructible<tuple, pair<U1, U2>>::moveable_implicit>
      >::value,
    int> = 0>
  constexpr explicit tuple(pair<U1, U2>&& p) : base(ss::move(p.first), ss::move(p.second)) {}

  template<typename Alloc, typename U1, typename U2,
    enable_if_t<
      conjunction<
        typename detail::pair_to_tuple_constructible<tuple, pair<U1, U2>>::moveable,
        typename detail::pair_to_tuple_constructible<tuple, pair<U1, U2>>::moveable_implicit
      >::value,
    int> = 0>
  constexpr tuple(allocator_arg_t, const Alloc& alloc, pair<U1, U2>&& p)
      : base(allocator_arg_t{}, alloc, ss::move(p.first), ss::move(p.second)) {}

  template<typename Alloc, typename U1, typename U2,
    enable_if_t<
      conjunction<
        typename detail::pair_to_tuple_constructible<tuple, pair<U1, U2>>::moveable,
        negation<typename detail::pair_to_tuple_constructible<tuple, pair<U1, U2>>::moveable_implicit>
      >::value,
    int> = 0>
  constexpr explicit tuple(allocator_arg_t, const Alloc& alloc, pair<U1, U2>&& p)
      : base(allocator_arg_t{}, alloc, ss::move(p.first), ss::move(p.second)) {}

  constexpr tuple(const tuple&) = default;
  constexpr tuple(tuple&&) = default;

  template<typename Alloc>
  constexpr tuple(allocator_arg_t, const Alloc& alloc, const tuple& other)
    : tuple(tuple_tag_unpack_tuple_t{}, alloc, other) {
    static_assert(conjunction<is_copy_constructible<Types>...>::value,
                  "ss::tuple(allocator_arg_t, const Alloc&, const tuple&) : All types must be copy constructible");
  }

  template<typename Alloc,
    enable_if_t<
      conjunction<
        detail::always_true<Alloc>,
        is_move_constructible<Types>...
      >::value,
    int> = 0>
  constexpr tuple(allocator_arg_t, const Alloc& alloc, tuple&& other)
    : tuple(tuple_tag_unpack_tuple_t{}, alloc, ss::move(other)) {}

  SS_CONSTEXPR_AFTER_14 tuple& operator=(const tuple& other) = default;

//  SS_CONSTEXPR_AFTER_14 tuple& operator=(const tuple& other) {
//    detail::tuple_element_wise_copy(*this, other, detail::make_tuple_sequence<tuple>{});
//    return *this;
//  }

//  SS_CONSTEXPR_AFTER_14 tuple& operator=(tuple&& other) {
//    detail::tuple_element_wise_forward(*this, ss::move(other), detail::make_tuple_sequence<tuple>{});
//    return *this;
//  }

 private:
  template<size_t I, typename... T>
  friend constexpr tuple_element_t<I, tuple<T...>>& get(tuple<T...>& t) noexcept;

  template<size_t I, typename... T>
  friend constexpr const tuple_element_t<I, tuple<T...>>& get(const tuple<T...>& t) noexcept;

  template<size_t I, typename... T>
  friend constexpr tuple_element_t<I, tuple<T...>>&& get(tuple<T...>&& t) noexcept;

  template<size_t I, typename... T>
  friend constexpr const tuple_element_t<I, tuple<T...>>&& get(const tuple<T...>&& t) noexcept;

  template<typename T, typename... UTypes>
  friend constexpr T& get(tuple<UTypes...>& t) noexcept;

  template<typename T, typename... UTypes>
  friend constexpr T&& get(tuple<UTypes...>&& t) noexcept;

  template<typename T, typename... UTypes>
  friend constexpr const T& get(const tuple<UTypes...>& t) noexcept;

  template<typename T, typename... UTypes>
  friend constexpr const T&& get(const tuple<UTypes...>&& t) noexcept;
};



template<size_t I, typename... T>
constexpr tuple_element_t<I, tuple<T...>>& get(tuple<T...>& t) noexcept {
  using type = tuple_element_t<I, tuple<T...>>;
  return static_cast<detail::tuple_leaf<I, type>&>(t.base).element;
}

template<size_t I, typename... T>
constexpr const tuple_element_t<I, tuple<T...>>& get(const tuple<T...>& t) noexcept {
  using type = tuple_element_t<I, tuple<T...>>;
  return static_cast<const detail::tuple_leaf<I, type>&>(t.base).element;
}

template<size_t I, typename... T>
constexpr tuple_element_t<I, tuple<T...>>&& get(tuple<T...>&& t) noexcept {
  using type = tuple_element_t<I, tuple<T...>>;
  return static_cast<type&&>(static_cast<detail::tuple_leaf<I, type>&&>(t.base).element);
}

template<size_t I, typename... T>
constexpr const tuple_element_t<I, tuple<T...>>&& get(const tuple<T...>&& t) noexcept {
  using type = tuple_element_t<I, tuple<T...>>;
  return static_cast<const type&&>(static_cast<const detail::tuple_leaf<I, type>&&>(t.base).element);
}

template<typename T, typename... Types>
constexpr T& get(tuple<Types...>& t) noexcept {
  return static_cast<detail::tuple_leaf_by_type<T, tuple<Types...>>&>(t.base).element;
}

template<typename T, typename... Types>
constexpr const T& get(const tuple<Types...>& t) noexcept {
  return static_cast<detail::tuple_leaf_by_type<T, tuple<Types...>>const &>(t.base).element;
}

template<typename T, typename... Types>
constexpr T&& get(tuple<Types...>&& t) noexcept {
  return ss::move(static_cast<detail::tuple_leaf_by_type<T, tuple<Types...>>&&>(t.base).element);
}

template<typename T, typename... Types>
constexpr const T&& get(const tuple<Types...>&& t) noexcept {
  return ss::move(static_cast<detail::tuple_leaf_by_type<T, tuple<Types...>>const &&>(t.base).element);
}


namespace detail {
template<typename T>
struct make_tuple_element_type_impl {
  using type = T;
};

template<typename T>
struct make_tuple_element_type_impl<reference_wrapper<T>> {
  using type = T&;
};

template<typename T>
struct make_tuple_element_type {
  using type = make_tuple_element_type_impl<decay_t<T>>;
};

template<typename... Types>
struct make_tuple_type {
  using type = tuple<typename make_tuple_element_type<Types>::type...>;
};

} // namespace detail

/**
 * make_tuple
 * @param types
 * @return
 */
template<typename... Types>
typename detail::make_tuple_type<Types...>::type make_tuple(Types&&... types) {
  using type = typename detail::make_tuple_type<Types...>::type;
  return type(ss::forward<Types>(types)...);
}



/**
 * tie
 * @param types
 * @return
 */
template<typename... Types>
constexpr tuple<Types&...> tie(Types&... types) noexcept {
  return tuple<Types&...>(types...);
}



/**
 * forward_as_tuple
 * @param types
 * @return
 */
template<typename... Types>
constexpr tuple<Types&&...> forward_as_tuple(Types&&... types) noexcept {
  return tuple<Types&&...>(ss::forward<Types>(types)...);
}


namespace detail {

template<typename T, typename I = make_index_sequence<tuple_size<T>::value>>
struct tuple_cat_type_one;

template<typename T, size_t... I>
struct tuple_cat_type_one<T, index_sequence<I...>> {
  using type = tuple<tuple_element_t<I, T>...>;
};

template<typename T1, typename T2,
         typename I1 = make_index_sequence<tuple_size<T1>::value>,
         typename I2 = make_index_sequence<tuple_size<T2>::value>>
struct tuple_cat_type_two;

template<typename T1, typename T2, size_t... I1, size_t... I2>
struct tuple_cat_type_two<T1, T2, index_sequence<I1...>, index_sequence<I2...>> {
  using type = tuple<tuple_element_t<I1, T1>..., tuple_element_t<I2, T2>...>;
};

template<typename... Tuples>
struct tuple_cat_type_impl;

template<>
struct tuple_cat_type_impl<> {
  using type = tuple<>;
};

template<typename Tuple>
struct tuple_cat_type_impl<Tuple> {
  using type = typename tuple_cat_type_one<Tuple>::type;
};

template<typename Tuple, typename... Rest>
struct tuple_cat_type_impl<Tuple, Rest...> {
  using type = typename tuple_cat_type_two<Tuple, typename tuple_cat_type_impl<Rest...>::type>::type;
};

template<typename... Tuples>
struct tuple_cat_type {
  using type = typename tuple_cat_type_impl<decay_t<Tuples>...>::type;
};

template<typename... T>
struct cat_sequence;

template<typename T, T... v>
struct cat_sequence<integer_sequence<T, v...>> {
  using type = integer_sequence<T, v...>;
};

template<typename T, T... v1, T... v2, typename... Rest>
struct cat_sequence<integer_sequence<T, v1...>, integer_sequence<T, v2...>, Rest...> {
  using type = typename cat_sequence<integer_sequence<T, v1..., v2...>, Rest...>::type;
};

template<typename Indices> struct repeat_sequence_impl;
template<typename T, T... I>
struct repeat_sequence_impl<integer_sequence<T, I...>> {
  template<T v>
  using type = integer_sequence<T, (I, v)...>;
};

template<typename T, T v, T n>
using repeat_sequence = typename repeat_sequence_impl<make_integer_sequence<T, n>>::template type<v>;

template<size_t I, typename... Tuples>
struct tuple_cat_indices;

template<size_t I>
struct tuple_cat_indices<I> {
  using outer = index_sequence<>;
  using inner = index_sequence<>;
};

template<size_t I, typename Tuple>
struct tuple_cat_indices<I, Tuple> {
  using inner = make_tuple_sequence<Tuple>;
  using outer = repeat_sequence<size_t, I, tuple_size<Tuple>::value>;
};

template<size_t I, typename Tuple, typename... Rest>
struct tuple_cat_indices<I, Tuple, Rest...> {
  using inner = typename cat_sequence<make_tuple_sequence<Tuple>, make_tuple_sequence<Rest>...>::type;
  using outer = typename cat_sequence<
    repeat_sequence<size_t, I, tuple_size<Tuple>::value>,
    typename tuple_cat_indices<I+1, Rest...>::outer>::type;
};

template<typename R, typename Tuple, size_t... I1, size_t... I2>
constexpr R tuple_cat_impl(Tuple&& t, index_sequence<I1...>, index_sequence<I2...>) {
  return R(ss::get<I2>(ss::get<I1>(ss::forward<Tuple>(t)))...);
}

} // namespace detail

/**
 * tuple_cat
 * @param args
 * @return
 */
template<typename... Tuples>
typename detail::tuple_cat_type<Tuples...>::type tuple_cat(Tuples&&... args) {
  using return_type = typename detail::tuple_cat_type<decay_t<Tuples>...>::type;
  using tuple_cat_indices = detail::tuple_cat_indices<0, decay_t<Tuples>...>;
  return detail::tuple_cat_impl<return_type>(
    ss::forward_as_tuple(ss::forward<Tuples>(args)...),
    typename tuple_cat_indices::outer{},
    typename tuple_cat_indices::inner{}
  );
}

namespace detail {

struct ignore_t {
  template<typename T>
  SS_CONSTEXPR_AFTER_14 void operator=(T&&) const noexcept {}
};

} // namespace detail


/**
 * ignore
 */
SS_INLINE_VAR constexpr detail::ignore_t ignore;


namespace detail {

inline SS_CONSTEXPR_AFTER_14 void dev_null(...) noexcept {}

template<typename Dst, typename Src, size_t... I>
SS_CONSTEXPR_AFTER_14 void tuple_element_wise_copy(Dst& dst, const Src& src, index_sequence<I...>) {
  dev_null(((ss::get<I>(dst) = ss::get<I>(src)), 0)...);
}

template<typename Dst, typename Src, size_t... I>
SS_CONSTEXPR_AFTER_14 void tuple_element_wise_forward(Dst& dst, Src&& src, index_sequence<I...>) {
  dev_null(((ss::get<I>(dst) = ss::get<I>(ss::forward<Src>(src))), 0)...);
}

} // namespace detail


/**
 * uses_allocator<ss::tuple>
 * @tparam Types
 * @tparam Alloc
 */
template<typename... Types, typename Alloc>
struct uses_allocator<tuple<Types...>, Alloc> : true_type {};



namespace detail {

template<typename F, typename Tuple, size_t... I>
constexpr auto apply_impl(F&& f, Tuple&& t, index_sequence<I...>)
    -> decltype(ss::invoke(ss::forward<F>(f), ss::get<I>(ss::forward<Tuple>(t))...))
{
  return ss::invoke(ss::forward<F>(f), ss::get<I>(ss::forward<Tuple>(t))...);
}

} // namespace detail


/**
 * apply
 * @tparam F
 * @tparam Tuple
 * @param f
 * @param t
 * @return
 */
template<typename F, typename Tuple>
constexpr auto apply(F&& f, Tuple&& t)
    -> decltype(detail::apply_impl(ss::forward<F>(f), ss::forward<Tuple>(t), detail::make_tuple_sequence<decay_t<Tuple>>{}))
{
  return detail::apply_impl(ss::forward<F>(f), ss::forward<Tuple>(t), detail::make_tuple_sequence<decay_t<Tuple>>{});
}


namespace detail {
template<typename T, typename Tuple, size_t... I>
constexpr T make_from_tuple_impl(Tuple&& t, index_sequence<I...>) {
  return T(ss::get<I>(ss::forward<Tuple>(t))...);
}
} // namespace detail


/**
 * make_from_tuple
 * @tparam T
 * @tparam Tuple
 * @param t
 * @return
 */
template<typename T, typename Tuple>
constexpr T make_from_tuple(Tuple&& t) {
  return detail::make_from_tuple_impl<T>(ss::forward<Tuple>(t), detail::make_tuple_sequence<decay_t<Tuple>>{});
}

} // namespace ss

# endif // SS_TUPLE_H_
