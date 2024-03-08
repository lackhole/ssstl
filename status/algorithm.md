## Header `<algorithm>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/algorithm)  
[Implementation](../include/lsd/algorithm.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in |
|----------------------------------------------|:--------------------:|:--------------:|
| **Includes**                                 |                      |                |
| \<initializer_list>                          | ![][cpp11]           |  ![][notyet]   |
|                                              |                      |                |
| **Classes**                                  |                      |                |
| **Return types**                             |                      |                |
| ranges::in_fun_result                        | ![][cpp20]           |  ![][notyet]   |
| ranges::in_in_result                         | ![][cpp20]           |  ![][notyet]   |
| ranges::in_out_result                        | ![][cpp20]           |  ![][notyet]   |
| ranges::in_in_out_result                     | ![][cpp20]           |  ![][notyet]   |
| ranges::in_out_out_result                    | ![][cpp20]           |  ![][notyet]   |
| ranges::min_max_result                       | ![][cpp20]           |  ![][notyet]   |
| ranges::in_found_result                      | ![][cpp20]           |  ![][notyet]   |
| ranges::in_value_result                      | ![][cpp23]           |  ![][notyet]   |
| ranges::out_value_result                     | ![][cpp23]           |  ![][notyet]   |
|                                              |                      |                |
| **Functions**                                |                      |                |
| **Non-modifying sequence operations**        |                      |                |
| all_of <br/>any_of <br/>none_of              | ![][cpp11] <br/>![][cpp11] <br/>![][cpp11] |  ![][notyet]   |
| for_each                                     | ![][legacy]          |  ![][notyet]   |
| for_each_n                                   | ![][cpp17]           |  ![][notyet]   |
| count <br/>count_if                          | ![][legacy]          |  ![][notyet]   |
| mismatch                                     | ![][legacy]          |  ![][notyet]   |
| find <br/>find_if <br/>find_if_not           | ![][legacy] <br/>![][legacy] <br/>![][cpp11] |  ![][notyet]   |
| find_end                                     | ![][legacy]          |  ![][notyet]   |
| find_first_of                                | ![][legacy]          |  ![][notyet]   |
| adjacent_find                                | ![][legacy]          |  ![][notyet]   |
| search                                       | ![][legacy]          |  ![][notyet]   |
| search_n                                     | ![][legacy]          |  ![][notyet]   |
| **Modifying sequence operations**            |                      |                |
| copy <br/>copy_if                            | ![][legacy] <br/>![][cpp11] |  ![][notyet]   |
| copy_n                                       | ![][cpp11]           |  ![][notyet]   |
| copy_backward                                | ![][legacy]          |  ![][notyet]   |
| move                                         | ![][cpp11]           |  ![][notyet]   |
| move_backward                                | ![][cpp11]           |  ![][notyet]   |
| fill                                         | ![][legacy]          |  ![][notyet]   |
| fill_n                                       | ![][legacy]          |  ![][cpp11]    |
| transform                                    | ![][legacy]          |  ![][notyet]   |
| generate                                     | ![][legacy]          |  ![][notyet]   |
| generate_n                                   | ![][legacy]          |  ![][notyet]   |
| remove <br/>remove_if                        | ![][legacy]          |  ![][notyet]   |
| remove_copy <br/>remove_copy_if              | ![][legacy]          |  ![][notyet]   |
| replace <br/>replace_if                      | ![][legacy]          |  ![][notyet]   |
| replace_copy <br/>replace_copy_if            | ![][legacy]          |  ![][notyet]   |
| swap                                         | ![][legacy]          |  ![][cpp11]    |
| swap_ranges                                  | ![][legacy]          |  ![][cpp11]    |
| iter_swap                                    | ![][legacy]          |  ![][cpp11]    |
| reverse                                      | ![][legacy]          |  ![][notyet]   |
| reverse_copy                                 | ![][legacy]          |  ![][notyet]   |
| rotate                                       | ![][legacy]          |  ![][notyet]   |
| rotate_copy                                  | ![][legacy]          |  ![][notyet]   |
| shift_left <br/>shift_right                  | ![][cpp20]           |  ![][notyet]   |
| ~~random_shuffle~~ <br/>shuffle              | ![][legacy] <br/>![][cpp11] |  ![][notyet]   |
| sample                                       | ![][cpp17]           |  ![][notyet]   |
| unique                                       | ![][legacy]          |  ![][notyet]   |
| unique_copy                                  | ![][legacy]          |  ![][notyet]   |
| **Partitioning operations**                  |                      |                |
| is_partitioned                               | ![][cpp11]           |  ![][notyet]   |
| partition                                    | ![][legacy]          |  ![][notyet]   |
| partition_copy                               | ![][cpp11]           |  ![][notyet]   |
| stable_partition                             | ![][legacy]          |  ![][notyet]   |
| partition_point                              | ![][cpp11]           |  ![][notyet]   |
| **Sorting operations**                       |                      |                |
| is_sorted                                    | ![][cpp11]           |  ![][notyet]   |
| is_sorted_until                              | ![][cpp11]           |  ![][notyet]   |
| sort                                         | ![][legacy]          |  ![][notyet]   |
| partial_sort                                 | ![][legacy]          |  ![][notyet]   |
| partial_sort_copy                            | ![][legacy]          |  ![][notyet]   |
| stable_sort                                  | ![][legacy]          |  ![][notyet]   |
| nth_element                                  | ![][legacy]          |  ![][notyet]   |
| **Binary search operations (on sorted ranges)** |                      |                |
| lower_bound                                  | ![][legacy]          |  ![][notyet]   |
| upper_bound                                  | ![][legacy]          |  ![][notyet]   |
| binary_search                                | ![][legacy]          |  ![][notyet]   |
| equal_range                                  | ![][legacy]          |  ![][notyet]   |
| **Other operations on sorted ranges**        |                      |                |
| merge                                        | ![][legacy]          |  ![][notyet]   |
| inplace_merge                                | ![][legacy]          |  ![][notyet]   |
| **Set operations (on sorted ranges)**        |                      |                |
| includes                                     | ![][legacy]          |  ![][notyet]   |
| set_difference                               | ![][legacy]          |  ![][notyet]   |
| set_intersection                             | ![][legacy]          |  ![][notyet]   |
| set_symmetric_difference                     | ![][legacy]          |  ![][notyet]   |
| set_union                                    | ![][legacy]          |  ![][notyet]   |
| **Heap operations**                          |                      |                |
| is_heap                                      | ![][cpp11]           |  ![][notyet]   |
| is_heap_until                                | ![][cpp11]           |  ![][notyet]   |
| make_heap                                    | ![][legacy]          |  ![][notyet]   |
| push_heap                                    | ![][legacy]          |  ![][notyet]   |
| pop_heap                                     | ![][legacy]          |  ![][notyet]   |
| sort_heap                                    | ![][legacy]          |  ![][notyet]   |
| **Minimum/maximum operations**               |                      |                |
| max                                          | ![][legacy]          |  ![][cpp11]    |
| max_element                                  | ![][legacy]          |  ![][cpp11]    |
| min                                          | ![][legacy]          |  ![][cpp11]    |
| min_element                                  | ![][legacy]          |  ![][cpp11]    |
| minmax                                       | ![][cpp11]           |  ![][cpp11]    |
| minmax_element                               | ![][cpp11]           |  ![][cpp11]    |
| clamp                                        | ![][cpp17]           |  ![][notyet]   |
| **Comparison operations**                    |                      |                |
| equal                                        | ![][legacy]          |  ![][cpp11]    |
| lexicographical_compare                      | ![][legacy]          |  ![][cpp11]    |
| lexicographical_compare_three_way            | ![][cpp20]           |  ![][notyet]   |
| **Permutation operations**                   |                      |                |
| is_permutation                               | ![][cpp11]           |  ![][notyet]   |
| next_permutation                             | ![][legacy]          |  ![][notyet]   |
| prev_permutation                             | ![][legacy]          |  ![][notyet]   |
|                                              |                      |                |
| **Function-like entities**                   |                      |                |
| **Non-modifying sequence operations**        |                      |                |
| ranges::all_of <br/>ranges::any_of <br/>ranges::none_of | ![][cpp20] <br/>![][cpp20] <br/>![][cpp20] |  ![][notyet]   |
| ranges::for_each                             | ![][cpp20]           |  ![][notyet]   |
| ranges::for_each_n                           | ![][cpp20]           |  ![][notyet]   |
| ranges::count <br/>ranges::count_if          | ![][cpp20] <br/>![][cpp20] |  ![][notyet]   |
| ranges::mismatch                             | ![][cpp20]           |  ![][notyet]   |
| ranges::find <br/>ranges::find_if <br/>ranges::find_if_not | ![][cpp20] <br/>![][cpp20] <br/>![][cpp20] |  ![][notyet]   |
| ranges::find_last <br/>ranges::find_last_if <br/>ranges::find_last_if_not | ![][cpp23] <br/>![][cpp23] <br/>![][cpp23] |  ![][notyet]   |
| ranges::find_end                             | ![][cpp20]           |  ![][notyet]   |
| ranges::find_first_of                        | ![][cpp20]           |  ![][notyet]   |
| ranges::adjacent_find                        | ![][cpp20]           |  ![][notyet]   |
| ranges::search                               | ![][cpp20]           |  ![][notyet]   |
| ranges::search_n                             | ![][cpp20]           |  ![][notyet]   |
| ranges::contains <br/>ranges::contains_subrange | ![][cpp23] <br/>![][cpp23] |  ![][notyet]   |
| ranges::starts_with                          | ![][cpp23]           |  ![][notyet]   |
| ranges::ends_with                            | ![][cpp23]           |  ![][notyet]   |
| **Fold operations**                          |                      |                |
| ranges::fold_left                            | ![][cpp23]           |  ![][notyet]   |
| ranges::fold_left_first                      | ![][cpp23]           |  ![][notyet]   |
| ranges::fold_right                           | ![][cpp23]           |  ![][notyet]   |
| ranges::fold_right_last                      | ![][cpp23]           |  ![][notyet]   |
| ranges::fold_left_with_iter                  | ![][cpp23]           |  ![][notyet]   |
| ranges::fold_left_first_with_iter            | ![][cpp23]           |  ![][notyet]   |
| **Modifying sequence operations**            |                      |                |
| ranges::copy <br/>ranges::copy_if            | ![][cpp20] <br/>![][cpp20] |  ![][notyet]   |
| ranges::copy_n                               | ![][cpp20]           |  ![][notyet]   |
| ranges::copy_backward                        | ![][cpp20]           |  ![][notyet]   |
| ranges::move                                 | ![][cpp20]           |  ![][notyet]   |
| ranges::move_backward                        | ![][cpp20]           |  ![][notyet]   |
| ranges::fill                                 | ![][cpp20]           |  ![][notyet]   |
| ranges::fill_n                               | ![][cpp20]           |  ![][notyet]   |
| ranges::transform                            | ![][cpp20]           |  ![][notyet]   |
| ranges::generate                             | ![][cpp20]           |  ![][notyet]   |
| ranges::generate_n                           | ![][cpp20]           |  ![][notyet]   |
| ranges::remove <br/>ranges::remove_if        | ![][cpp20] <br/>![][cpp20] |  ![][notyet]   |
| ranges::remove_copy <br/>ranges::remove_copy_if | ![][cpp20] <br/>![][cpp20] |  ![][notyet]   |
| ranges::replace <br/>ranges::replace_if      | ![][cpp20] <br/>![][cpp20] |  ![][notyet]   |
| ranges::replace_copy <br/>ranges::replace_copy_if | ![][cpp20] <br/>![][cpp20] |  ![][notyet]   |
| ranges::swap_ranges                          | ![][cpp20]           |  ![][notyet]   |
| ranges::reverse                              | ![][cpp20]           |  ![][notyet]   |
| ranges::reverse_copy                         | ![][cpp20]           |  ![][notyet]   |
| ranges::rotate                               | ![][cpp20]           |  ![][notyet]   |
| ranges::rotate_copy                          | ![][cpp20]           |  ![][notyet]   |
| ranges::shift_left <br/>ranges::shift_right  | ![][cpp23]           |  ![][notyet]   |
| ranges::sample                               | ![][cpp20]           |  ![][notyet]   |
| ranges::shuffle                              | ![][cpp20]           |  ![][notyet]   |
| ranges::unique                               | ![][cpp20]           |  ![][notyet]   |
| ranges::unique_copy                          | ![][cpp20]           |  ![][notyet]   |
| **Partitioning operations**                  |                      |                |
| ranges::is_partitioned                       | ![][cpp20]           |  ![][notyet]   |
| ranges::partition                            | ![][cpp20]           |  ![][notyet]   |
| ranges::partition_copy                       | ![][cpp20]           |  ![][notyet]   |
| ranges::stable_partition                     | ![][cpp20]           |  ![][notyet]   |
| ranges::partition_point                      | ![][cpp20]           |  ![][notyet]   |
| **Sorting operations**                       |                      |                |
| ranges::is_sorted                            | ![][cpp20]           |  ![][notyet]   |
| ranges::is_sorted_until                      | ![][cpp20]           |  ![][notyet]   |
| ranges::sort                                 | ![][cpp20]           |  ![][notyet]   |
| ranges::partial_sort                         | ![][cpp20]           |  ![][notyet]   |
| ranges::partial_sort_copy                    | ![][cpp20]           |  ![][notyet]   |
| ranges::stable_sort                          | ![][cpp20]           |  ![][notyet]   |
| ranges::nth_element                          | ![][cpp20]           |  ![][notyet]   |
| **Binary search operations (on sorted ranges)** |                      |                |
| ranges::lower_bound                          | ![][cpp20]           |  ![][notyet]   |
| ranges::upper_bound                          | ![][cpp20]           |  ![][notyet]   |
| ranges::binary_search                        | ![][cpp20]           |  ![][notyet]   |
| ranges::equal_range                          | ![][cpp20]           |  ![][notyet]   |
| **Other operations on sorted ranges**        |                      |                |
| ranges::merge                                | ![][cpp20]           |  ![][notyet]   |
| ranges::inplace_merge                        | ![][cpp20]           |  ![][notyet]   |
| **Set operations (on sorted ranges)**        |                      |                |
| ranges::includes                             | ![][cpp20]           |  ![][notyet]   |
| ranges::set_difference                       | ![][cpp20]           |  ![][notyet]   |
| ranges::set_intersection                     | ![][cpp20]           |  ![][notyet]   |
| ranges::set_symmetric_difference             | ![][cpp20]           |  ![][notyet]   |
| ranges::set_union                            | ![][cpp20]           |  ![][notyet]   |
| **Heap operations**                          |                      |                |
| ranges::is_heap                              | ![][cpp20]           |  ![][notyet]   |
| ranges::is_heap_until                        | ![][cpp20]           |  ![][notyet]   |
| ranges::make_heap                            | ![][cpp20]           |  ![][notyet]   |
| ranges::push_heap                            | ![][cpp20]           |  ![][notyet]   |
| ranges::pop_heap                             | ![][cpp20]           |  ![][notyet]   |
| ranges::sort_heap                            | ![][cpp20]           |  ![][notyet]   |
| **Minimum/maximum operations**               |                      |                |
| ranges::max                                  | ![][cpp20]           |  ![][notyet]   |
| ranges::max_element                          | ![][cpp20]           |  ![][notyet]   |
| ranges::min                                  | ![][cpp20]           |  ![][notyet]   |
| ranges::min_element                          | ![][cpp20]           |  ![][notyet]   |
| ranges::minmax                               | ![][cpp20]           |  ![][notyet]   |
| ranges::minmax_element                       | ![][cpp20]           |  ![][notyet]   |
| ranges::clamp                                | ![][cpp20]           |  ![][notyet]   |
| **Comparison operations**                    |                      |                |
| ranges::equal                                | ![][cpp20]           |  ![][notyet]   |
| ranges::lexicographical_compare              | ![][cpp20]           |  ![][notyet]   |
| **Permutation operations**                   |                      |                |
| ranges::is_permutation                       | ![][cpp20]           |  ![][notyet]   |
| ranges::next_permutation                     | ![][cpp20]           |  ![][notyet]   |
| ranges::prev_permutation                     | ![][cpp20]           |  ![][notyet]   |


<!--
	C++11: 71	| 12
	C++17: 3	| 0
	C++20: 76	| 0
	C++23: 11	| 0

	Total: 161	| 0-->

[notyet]: https://img.shields.io/badge/Not_yet-orange
[removed]: https://img.shields.io/badge/Removed-red
[legacy]: https://img.shields.io/badge/legacy-grey

[cppno11]: https://img.shields.io/badge/C%2B%2B-11-red
[cppno14]: https://img.shields.io/badge/C%2B%2B-14-red
[cppno17]: https://img.shields.io/badge/C%2B%2B-17-red
[cppno20]: https://img.shields.io/badge/C%2B%2B-20-red
[cppno23]: https://img.shields.io/badge/C%2B%2B-23-red
[cppno26]: https://img.shields.io/badge/C%2B%2B-23-red

[cpppt11]: https://img.shields.io/badge/C%2B%2B-11-blue
[cpppt14]: https://img.shields.io/badge/C%2B%2B-14-blue
[cpppt17]: https://img.shields.io/badge/C%2B%2B-17-blue
[cpppt20]: https://img.shields.io/badge/C%2B%2B-20-blue
[cpppt23]: https://img.shields.io/badge/C%2B%2B-23-blue
[cpppt26]: https://img.shields.io/badge/C%2B%2B-23-blue

[cpp11]: https://img.shields.io/badge/C%2B%2B-11-green
[cpp14]: https://img.shields.io/badge/C%2B%2B-14-green
[cpp17]: https://img.shields.io/badge/C%2B%2B-17-green
[cpp20]: https://img.shields.io/badge/C%2B%2B-20-green
[cpp23]: https://img.shields.io/badge/C%2B%2B-23-green
