# /*
#  * Created by YongGyu Lee on 2022/01/21.
#  */
#
# ifndef SS_VECTOR_H_
# define SS_VECTOR_H_
# 
# include <cstddef>
# 
# include "ss/compressed_pair.h"
# include "ss/initializer_list.h"
# include "ss/iterator.h"
# include "ss/memory.h"
# include "ss/type_traits.h"

namespace ss {

/**
 * hash(forward declaration)
 * @tparam T 
 */
template<typename T>
struct hash;

struct vector_base {
  vector_base() : begin_{nullptr}, end_{nullptr}, end_cap_{nullptr} {}

  SS_CONSTEXPR_AFTER_14 void* begin()       noexcept { return begin_; }
  constexpr       const void* begin() const noexcept { return begin_; }

  SS_CONSTEXPR_AFTER_14 void* end()       noexcept{ return end_; }
  constexpr       const void* end() const noexcept{ return end_; }

  SS_CONSTEXPR_AFTER_14 void* end_cap()       noexcept{ return end_cap_; }
  constexpr       const void* end_cap() const noexcept{ return end_cap_; }
  
  void* begin_;
  void* end_;
  void* end_cap_;
};

template<typename T, typename Allocator = allocator<T>>
class vector : private compressed_pair<vector_base, Allocator> {
  using base = compressed_pair<vector_base, Allocator>;
  using vbase = typename base::first_type;
  
 public:
  static_assert(is_same<T, typename Allocator::value_type>::value, 
      "T and Allocator::value_type must be same type");
  static_assert(detail::is_complete<T>::value ||
                detail::is_allocator_completeness<T>::value,
      "allocator<T> must satisfy allocator completeness requirements if T is incomplete type"); 
  
  using value_type        = T;
  using allocator_type    = Allocator;
  using size_type         = size_t;
  using difference_type   = ptrdiff_t;
  using reference         = value_type&;
  using const_reference   = const value_type&;
  using pointer           = typename allocator_traits<Allocator>::pointer;
  using const_pointer     = typename allocator_traits<Allocator>::const_pointer;
  using iterator          = pointer;
  using const_iterator    = const_pointer;
  using reverse_iterator       = ss::reverse_iterator<iterator>;
  using const_reverse_iterator = ss::reverse_iterator<const_iterator>;
  
  constexpr vector() noexcept(noexcept(allocator_type())) : base() {}
  
 private:
};


} // namespace ss

# endif // SS_VECTOR_H_
