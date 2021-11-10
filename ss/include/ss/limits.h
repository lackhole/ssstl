# /*
#  * Created by YongGyu Lee on 2021/11/11.
#  */
#
# ifndef S_LIMITS_H_
# define S_LIMITS_H_
#
# include <cstdint>
# include <climits>
# include <cfloat>

namespace ss {

enum float_round_style {
  round_indeterminate       = -1,
  round_toward_zero         = 0,
  round_to_nearest          = 1,
  round_toward_infinity     = 2,
  round_toward_neg_infinity = 3
};

enum float_denorm_style {
  denorm_indeterminate = -1,
  denorm_absent        = 0,
  denorm_present       = 1
};

namespace detail {

template<typename T, bool v = /* false */ is_arithmetic<T>::value>
class numeric_limits_base {
 protected:
  static constexpr bool is_specialized = false;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = false;
  static constexpr bool is_exact = false;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = 0;
  static constexpr int digits10 = 0;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 0;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = false;
  static constexpr bool tinyness_before = false;

  static constexpr T min() noexcept { return T(); }
  static constexpr T lowest() noexcept { return T(); }
  static constexpr T max() noexcept { return T(); }
  static constexpr T epsilon() noexcept { return T(); }
  static constexpr T round_error() noexcept { return T(); }
  static constexpr T infinity() noexcept { return T(); }
  static constexpr T quiet_NaN() noexcept { return T(); }
  static constexpr T signaling_NaN() noexcept { return T(); }
  static constexpr T denorm_min() noexcept { return T(); }
};

template<typename T>
class numeric_limits_base<T, true> {
 protected:
  using type = T;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = (type(-1) < type(0));
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = !is_signed;
  static constexpr int digits = CHAR_BIT*sizeof(type) - is_signed;
  static constexpr int digits10 = 0;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 0;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = false;
  static constexpr bool tinyness_before = false;

  static constexpr T min() noexcept { return T(); }
  static constexpr T lowest() noexcept { return T(); }
  static constexpr T max() noexcept { return T(); }
  static constexpr T epsilon() noexcept { return T(); }
  static constexpr T round_error() noexcept { return T(); }
  static constexpr T infinity() noexcept { return T(); }
  static constexpr T quiet_NaN() noexcept { return T(); }
  static constexpr T signaling_NaN() noexcept { return T(); }
  static constexpr T denorm_min() noexcept { return T(); }
};

template<>
class numeric_limits_base<bool, true> {
 protected:
  using type = bool;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = is_integral<type>::value;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = !is_signed;
  static constexpr int digits = 1;
  static constexpr int digits10 = 0;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 0;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = false;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return type(); }
  static constexpr type lowest() noexcept { return type(); }
  static constexpr type max() noexcept { return type(); }
  static constexpr type epsilon() noexcept { return type(); }
  static constexpr type round_error() noexcept { return type(); }
  static constexpr type infinity() noexcept { return type(); }
  static constexpr type quiet_NaN() noexcept { return type(); }
  static constexpr type signaling_NaN() noexcept { return type(); }
  static constexpr type denorm_min() noexcept { return type(); }
};

template<>
class numeric_limits_base<float, true> {
 protected:
  using type = float;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = false;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = FLT_MANT_DIG;
  static constexpr int digits10 = FLT_DIG;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 0;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = false;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return type(); }
  static constexpr type lowest() noexcept { return type(); }
  static constexpr type max() noexcept { return type(); }
  static constexpr type epsilon() noexcept { return type(); }
  static constexpr type round_error() noexcept { return type(); }
  static constexpr type infinity() noexcept { return type(); }
  static constexpr type quiet_NaN() noexcept { return type(); }
  static constexpr type signaling_NaN() noexcept { return type(); }
  static constexpr type denorm_min() noexcept { return type(); }
};

template<>
class numeric_limits_base<double, true> {
 protected:
  using type = double;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = false;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = DBL_MANT_DIG;
  static constexpr int digits10 = DBL_DIG;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 0;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = false;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return type(); }
  static constexpr type lowest() noexcept { return type(); }
  static constexpr type max() noexcept { return type(); }
  static constexpr type epsilon() noexcept { return type(); }
  static constexpr type round_error() noexcept { return type(); }
  static constexpr type infinity() noexcept { return type(); }
  static constexpr type quiet_NaN() noexcept { return type(); }
  static constexpr type signaling_NaN() noexcept { return type(); }
  static constexpr type denorm_min() noexcept { return type(); }
};

template<>
class numeric_limits_base<long double, true> {
 protected:
  using type = long double;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = false;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = LDBL_MANT_DIG;
  static constexpr int digits10 = LDBL_DIG;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 0;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = false;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return type(); }
  static constexpr type lowest() noexcept { return type(); }
  static constexpr type max() noexcept { return type(); }
  static constexpr type epsilon() noexcept { return type(); }
  static constexpr type round_error() noexcept { return type(); }
  static constexpr type infinity() noexcept { return type(); }
  static constexpr type quiet_NaN() noexcept { return type(); }
  static constexpr type signaling_NaN() noexcept { return type(); }
  static constexpr type denorm_min() noexcept { return type(); }
};

} // namespace detail

template<typename T>
class numeric_limits : private detail::numeric_limits_base<remove_cv_t<T>> {

};



} // namespace ss

#endif // S_LIMITS_H_
