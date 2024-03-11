//
// Created by yonggyulee on 2023/12/23.
//

#ifndef LSD_ITERATOR_HPP_
#define LSD_ITERATOR_HPP_

#include "lsd/__iterator/detail/iter_concept.h"
#include "lsd/__iterator/detail/iter_move_std.h"

#include "lsd/__iterator/iterator_traits/forward_declare.h"
#include "lsd/__iterator/iterator_traits/cxx20_iterator_traits.h"
#include "lsd/__iterator/iterator_traits/legacy_bidirectional_iterator.h"
#include "lsd/__iterator/iterator_traits/legacy_forward_iterator.h"
#include "lsd/__iterator/iterator_traits/legacy_input_iterator.h"
#include "lsd/__iterator/iterator_traits/legacy_iterator.h"
#include "lsd/__iterator/iterator_traits/legacy_random_access_iterator.h"

#include "lsd/__iterator/advance.h"
#include "lsd/__iterator/basic_const_iterator.h"
#include "lsd/__iterator/bidirectional_iterator.h"
#include "lsd/__iterator/common_iterator.h"
#include "lsd/__iterator/contiguous_iterator.h"
#include "lsd/__iterator/counted_iterator.h"
#include "lsd/__iterator/default_sentinel_t.h"
#include "lsd/__iterator/forward_iterator.h"
#include "lsd/__iterator/incrementable.h"
#include "lsd/__iterator/incrementable_traits.h"
#include "lsd/__iterator/indirect_binary_predicate.h"
#include "lsd/__iterator/indirect_equivalence_relation.h"
#include "lsd/__iterator/indirect_result_t.h"
#include "lsd/__iterator/indirect_strict_weak_order.h"
#include "lsd/__iterator/indirect_unary_predicate.h"
#include "lsd/__iterator/indirectly_comparable.h"
#include "lsd/__iterator/indirectly_copyable.h"
#include "lsd/__iterator/indirectly_copyable_storable.h"
#include "lsd/__iterator/indirectly_movable.h"
#include "lsd/__iterator/indirectly_movable_storable.h"
#include "lsd/__iterator/indirectly_readable.h"
#include "lsd/__iterator/indirectly_readable_traits.h"
#include "lsd/__iterator/indirectly_regular_unary_invocable.h"
#include "lsd/__iterator/indirectly_swappable.h"
#include "lsd/__iterator/indirectly_unary_invocable.h"
#include "lsd/__iterator/indirectly_writable.h"
#include "lsd/__iterator/input_iterator.h"
#include "lsd/__iterator/input_or_output_iterator.h"
#include "lsd/__iterator/iter_common_reference_t.h"
#include "lsd/__iterator/iter_const_reference_t.h"
#include "lsd/__iterator/iter_difference_t.h"
#include "lsd/__iterator/iter_key_t.h"
#include "lsd/__iterator/iter_mapped_t.h"
#include "lsd/__iterator/iter_move.h"
#include "lsd/__iterator/iter_reference_t.h"
#include "lsd/__iterator/iter_rvalue_reference_t.h"
#include "lsd/__iterator/iter_swap.h"
#include "lsd/__iterator/iter_val_t.h"
#include "lsd/__iterator/iter_value_t.h"
#include "lsd/__iterator/iterator_tag.h"
#include "lsd/__iterator/mergeable.h"
#include "lsd/__iterator/move_sentinel.h"
#include "lsd/__iterator/next.h"
#include "lsd/__iterator/output_iterator.h"
#include "lsd/__iterator/permutable.h"
#include "lsd/__iterator/prev.h"
#include "lsd/__iterator/projected.h"
#include "lsd/__iterator/random_access_iterator.h"
#include "lsd/__iterator/sentinel_for.h"
#include "lsd/__iterator/sized_sentinel_for.h"
#include "lsd/__iterator/sortable.h"
#include "lsd/__iterator/unreachable_sentinel.h"
#include "lsd/__iterator/weakly_incrementable.h"

#include "lsd/__ranges/begin.h"
#include "lsd/__ranges/cbegin.h"
#include "lsd/__ranges/cend.h"
#include "lsd/__ranges/data.h"
#include "lsd/__ranges/empty.h"
#include "lsd/__ranges/end.h"
#include "lsd/__ranges/size.h"
#include "lsd/__ranges/ssize.h"

#endif // LSD_ITERATOR_HPP_
