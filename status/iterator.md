## Header `<iterator>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/iterator)  
[Implementation](../include/lsd/iterator.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented


| C++ ≤ 11 Features                | Implemented in          |
|----------------------------------|:-----------------------:|
| **Classes**                      |                         |
| **Primitives**                   |                         |
|iterator_traits                   | ![][cpp11]              |
|input_iterator_tag <br/> output_iterator_tag <br/> forward_iterator_tag <br/> bidirectional_iterator_tag <br/> random_access_iterator_tag | ![][cpp11] |
|iterator                          | Deprecated in C++17     |
| **Adaptors**                     |                         |
|reverse_iterator                  | ![][cpp11] ![][cpppt20] |
|move_iterator                     | ![][notyet]             |
|back_insert_iterator              | ![][notyet]             |
|front_insert_iterator             | ![][notyet]             |
|insert_iterator                   | ![][notyet]             |
| **Stream Iterators**             |                         |
|istream_iterator                  | ![][notyet]             |
|ostream_iterator                  | ![][notyet]             |
|istreambuf_iterator               | ![][notyet]             |
|ostreambuf_iterator               | ![][notyet]             |
|                                  |                         |
| **Functions**                    |                         |
| **Adaptors**                     |                         |
|make_move_iterator                | ![][notyet]             |
|front_inserter                    | ![][notyet]             |
|back_inserter                     | ![][notyet]             |
|inserter                          | ![][notyet]             |
| **Non-member operators**         |                         |
|(lsd::move_iterator) <br/> operator== <br/> operator!= <br/> operator< <br/> operator<= <br/> operator> <br/> operator>= | ![][notyet] |
|operator+(lsd::move_iterator)      | ![][notyet]             |
|operator-(lsd::move_iterator)      | ![][notyet]             |
|(lsd::reverse_iterator) <br/> operator== <br/> operator!= <br/> operator< <br/> operator<= <br/> operator> <br/> operator>= | ![][cpp11] |
|operator+(lsd::reverse_iterator)   | ![][cpp11]              |
|operator-(lsd::reverse_iterator)   | ![][cpp11]              |
|(lsd::istream_iterator) <br/> operator== <br/> operator != <br/>    | ![][notyet] |
|(lsd::istreambuf_iterator) <br/> operator== <br/> operator != <br/> | ![][notyet] |
| **Operations**                   |                         |
|advance                           | ![][cpp11]              |
|distance                          | ![][cpp11]              |
|next                              | ![][notyet]             |
|prev                              | ![][cpp11]              |
| **Range access**                 |                         |
|begin                             | ![][cpp11]              |
|end                               | ![][cpp11]              |


| C++14 Features                   | Implemented in          |
|----------------------------------|:-----------------------:|
| **Functions**                    |                         |
| **Adaptors**                     |                         |
| make_reverse_iterator            | ![][cpp11]              |
| **Range access**                 |                         |
|cbegin                            | ![][cpp11]              |
|cend                              | ![][cpp11]              |
|rbegin <br/> crbegin              | ![][cpp11]              |
|end <br/> crend                   | ![][cpp11]              |


| C++17 Features                   | Implemented in          |
|----------------------------------|:-----------------------:|
| **Functions**                    |                         |
| **Range access**                 |                         |
|size                              | ![][cpp11]              |
|empty                             | ![][cpp11]              |
|data                              | ![][cpp11]              |

| C++20 Features                   | Implemented in          |
|----------------------------------|:-----------------------:|
| **Concepts**                     |                         |
| **Iterator concepts**            | ![][notyet]             |
|indirectly_readable               | ![][notyet]             |
|indirectly_writable               | ![][notyet]             |
|weakly_incrementable              | ![][notyet]             |
|incrementable                     | ![][notyet]             |
|input_or_output_iterator          | ![][notyet]             |
|sentinel_for                      | ![][notyet]             |
|sized_sentinel_for                | ![][notyet]             |
|input_iterator                    | ![][notyet]             |
|output_iterator                   | ![][notyet]             |
|forward_iterator                  | ![][notyet]             |
|bidirectional_iterator            | ![][notyet]             |
|random_access_iterator            | ![][notyet]             |
| **Indirect callable concepts**   |                         |
|indirectly_unary_invocable        | ![][notyet]             |
|indirectly_regular_unary_invocable | ![][notyet]            |
|indirect_unary_predicate          | ![][notyet]             |
|indirect_binary_predicate         | ![][notyet]             |
|indirect_equivalence_relation     | ![][notyet]             |
|indirect_strict_weak_order        | ![][notyet]             |
| **Common algorithm requirements** |                        |
|indirectly_movable                | ![][notyet]             |
|indirectly_movable_storable       | ![][notyet]             |
|indirectly_copyable               | ![][notyet]             |
|indirectly_copyable_storable      | ![][notyet]             |
|indirectly_swappable              | ![][notyet]             |
|indirectly_comparable             | ![][notyet]             |
|permutable                        | ![][notyet]             |
|mergeable                         | ![][notyet]             |
|sortable                          | ![][notyet]             |
|                                  |                         |
| **Classes**                      |                         |
| **Algorithm utilities**          |                         |
|indirect_result_t                 | ![][notyet]             |
|projected                         | ![][notyet]             |
| **Associated types**             |                         |
|incrementable_traits              | ![][notyet]             |
|indirectly_readable_traits        | ![][notyet]             |
|iter_value_t <br/> iter_reference_t <br/> iter_difference_t <br/> iter_rvalue_reference_t <br/> iter_common_reference_t | ![][notyet] |
| **Primitives**                   |                         |
|contiguous_iterator_tag           | ![][cpp11]              |
| **Adaptors**                     |                         |
|move_sentinel                     | ![][notyet]             |
|common_iterator                   | ![][notyet]             |
|default_sentinel_t                | ![][notyet]             |
|counted_iterator                  | ![][notyet]             |
|unreachable_sentinel_t            | ![][notyet]             |
|                                  |                         |
| **Customization point objects**  | Defined in namespace lsd::ranges |
|iter_move                         | ![][notyet]             |
|iter_swap                         | ![][notyet]             |
|                                  |                         |
| **Functions**                    | Defined in namespace lsd::ranges |
| **Non-member operators**         |                         |
|operator<=>(lsd::move_iterator)    | ![][notyet]             |
|operator<=>(lsd::reverse_iterator) | ![][cpp20]              |
|(lsd::counted_iterator) <br/> operator== <br/> operator<=> | ![][notyet] |
|operator+(lsd::counted_iterator)   | ![][notyet]             |
|operator-(lsd::counted_iterator)   | ![][notyet]             |
| **Operations**                   |                         |
|ranges::advance                   | ![][notyet]             |
|ranges::distance                  | ![][notyet]             |
|ranges::next                      | ![][notyet]             |
|ranges::prev                      | ![][notyet]             |
| **Range access**                 |                         |
|ssize                             | ![][cpp11]              |


<!--
	C++11: 29	| 11
	C++14: 5	| 5
	C++17: 3	| 3
	C++20: 51	| 3

	Total: 87	| 17-->

[notyet]: https://img.shields.io/badge/Not_yet-orange
[removed]: https://img.shields.io/badge/Removed-red

[cppno11]: https://img.shields.io/badge/C%2B%2B-11-red
[cppno14]: https://img.shields.io/badge/C%2B%2B-14-red
[cppno17]: https://img.shields.io/badge/C%2B%2B-17-red
[cppno20]: https://img.shields.io/badge/C%2B%2B-20-red
[cppno23]: https://img.shields.io/badge/C%2B%2B-23-red

[cpppt11]: https://img.shields.io/badge/C%2B%2B-11-blue
[cpppt14]: https://img.shields.io/badge/C%2B%2B-14-blue
[cpppt17]: https://img.shields.io/badge/C%2B%2B-17-blue
[cpppt20]: https://img.shields.io/badge/C%2B%2B-20-blue
[cpppt23]: https://img.shields.io/badge/C%2B%2B-23-blue

[cpp11]: https://img.shields.io/badge/C%2B%2B-11-green

[cpp14]: https://img.shields.io/badge/C%2B%2B-14-green

[cpp17]: https://img.shields.io/badge/C%2B%2B-17-green

[cpp20]: https://img.shields.io/badge/C%2B%2B-20-green

[cpp23]: https://img.shields.io/badge/C%2B%2B-23-green
