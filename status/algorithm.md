## Header `<algorithm>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/algorithm)  
[Implementation](../ss/include/ss/algorithm.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented


| C++ ≤ 11 Features                | Implemented in          |
|----------------------------------|:-----------------------:|
| **Functions**                    |                         |
| **Non-modifying sequence operations** |                    |
|all_of <br/> any_of <br/> none_of | ![][notyet]             |
|for_each                          | ![][notyet]             |
|count <br/> count_if              | ![][notyet]             |
|mismatch                          | ![][notyet]             |
|find <br/> find_if                | ![][notyet]             |
|find_if_not                       | ![][notyet]             |
|find_end                          | ![][notyet]             |
|find_first_of                     | ![][notyet]             |
|adjacent_field                    | ![][notyet]             |
|search                            | ![][notyet]             |
|search_n                          | ![][notyet]             |
| **Modifying sequence operations** |                        |
|copy <br/> copy_if                | ![][notyet]             |
|copy_n                            | ![][notyet]             |
|copy_backward                     | ![][notyet]             |
|move                              | ![][notyet]             |
|move_backward                     | ![][notyet]             |
|fill                              | ![][notyet]             |
|fill_n                            | ![][notyet]             |
|transform                         | ![][notyet]             |
|generate                          | ![][notyet]             |
|generate_n                        | ![][notyet]             |
|remove <br/> remove_if            | ![][notyet]             |
|remove_copy <br/> remove_copy_if  | ![][notyet]             |
|replace <br/> replace_if          | ![][notyet]             |
|replace_copy <br/> replace_copy_if | ![][notyet]            |
|swap                              | ![][cpp11]              |
|swap_ranges                       | ![][cpp11]              |
|iter_swap                         | ![][cpp11]              |
|reverse                           | ![][notyet]             |
|reverse_copy                      | ![][notyet]             |
|rotate                            | ![][notyet]             |
|rotate_copy                       | ![][notyet]             |
|shuffle                           | ![][notyet]             |
|unique                            | ![][notyet]             |
|unique_copy                       | ![][notyet]             |
|search_n                          | ![][notyet]             |
|search_n                          | ![][notyet]             |
|search_n                          | ![][notyet]             |
| **Partitioning  operations**     |                         |
|is_partitioned                    | ![][notyet]             |
|partition                         | ![][notyet]             |
|partition_copy                    | ![][notyet]             |
|stable_partition                  | ![][notyet]             |
|partition_point                   | ![][notyet]             |
| **Sorting  operations**          |                         |
|is_sorted                         | ![][notyet]             |
|is_sorted_until                   | ![][notyet]             |
|sort                              | ![][notyet]             |
|partial_sort                      | ![][notyet]             |
|partial_sort_copy                 | ![][notyet]             |
|stable_sort                       | ![][notyet]             |
|nth_element                       | ![][notyet]             |
| **Binary search  operations**    |                         |
|lower_bound                       | ![][notyet]             |
|upper_bound                       | ![][notyet]             |
|binary_search                     | ![][notyet]             |
|equal_range                       | ![][notyet]             |
| **Other operations on sorted ranges** |                    |
|merge                             | ![][notyet]             |
|inplace_merge                     | ![][notyet]             |
| **Set operations (on sorted ranges)** |                    |
|includes                          | ![][notyet]             |
|set_difference                    | ![][notyet]             |
|set_intersection                  | ![][notyet]             |
|set_symmetric_difference          | ![][notyet]             |
|set_union                         | ![][notyet]             |
| ** Heap operations**             | ![][notyet]             |
|is_heap                           | ![][notyet]             |
|is_heap_until                     | ![][notyet]             |
|make_heap                         | ![][notyet]             |
|push_heap                         | ![][notyet]             |
|pop_heap                          | ![][notyet]             |
|sort_heap                         | ![][notyet]             |
| **Minimum/maximun operations**   |                         |
|max                               | ![][notyet]             |
|max_element                       | ![][notyet]             |
|min                               | ![][notyet]             |
|min_element                       | ![][notyet]             |
|minmax                            | ![][notyet]             |
|minmax_element                    | ![][notyet]             |
| **Comparison operations**        |                         |
|equal                             | ![][notyet]             |
|lexicographical_compare           | ![][notyet]             |
| **Permutation operations**       |                         |
|is_permutation                    | ![][notyet]             |
|next_permutation                  | ![][notyet]             |
|prev_permutation                  | ![][notyet]             |


| C++ 17 Features                  | Implemented in          |
|----------------------------------|:-----------------------:|
| **Functions**                    |                         |
| **Non-modifying sequence operations** |                    |
|for_each_n                        | ![][notyet]             |
| **Modifying sequence operations** |                        |
|sample                            | ![][notyet]             |
| **Minimum/maximun operations**   |                         |
|clamp                             | ![][notyet]             |


| C++ 20 Features                  | Implemented in          |
|----------------------------------|:-----------------------:|
| **Classes**                      | Defined in namespace ss::ranges |
|ranges::in_fun_result             | ![][notyet]             |
|ranges::in_in_result              | ![][notyet]             |
|ranges::in_out_result             | ![][notyet]             |
|ranges::in_in_out_result          | ![][notyet]             |
|ranges::in_out_out_result         | ![][notyet]             |
|ranges::min_max_result            | ![][notyet]             |
|ranges::in_found_result           | ![][notyet]             |
|                                  |                         |
| **Functions**                    |                         |
| **Modifying sequence operations** |                        |
|shift_left <br/> shift_right      | ![][notyet]             |
| **Comparison operations**        |                         |
|lexicopraphical_compare_three_way | ![][notyet]             |
|                                  |                         |
| **Function-like entities**       | Defined in namespace ss::ranges |
|ranges::all_of <br/> ranges::any_of <br/> ranges::none_of | ![][notyet] |
|ranges::for_each                  | ![][notyet]             |
|ranges::for_each_n                | ![][notyet]             |
|ranges::count <br/> ranges::count_if | ![][notyet]          |
|ranges::mismatch                  | ![][notyet]             |
|ranges::find <br/> ranges::find_if <br/> find_if_not | ![][notyet] |
|ranges::find_end                  | ![][notyet]             |
|ranges::find_first_of             | ![][notyet]             |
|ranges::adjacent_field            | ![][notyet]             |
|ranges::search                    | ![][notyet]             |
|ranges::search_n                  | ![][notyet]             |
|ranges::starts_with               | ![][notyet]             |
|ranges::ends_with                 | ![][notyet]             |
| **Modifying sequence operations** |                        |
|ranges::copy <br/> ranges::copy_if | ![][notyet]            |
|ranges::copy_n                    | ![][notyet]             |
|ranges::copy_backward             | ![][notyet]             |
|ranges::move                      | ![][notyet]             |
|ranges::move_backward             | ![][notyet]             |
|ranges::fill                      | ![][notyet]             |
|ranges::fill_n                    | ![][notyet]             |
|ranges::transform                 | ![][notyet]             |
|ranges::generate                  | ![][notyet]             |
|ranges::generate_n                | ![][notyet]             |
|ranges::remove <br/> ranges::remove_if | ![][notyet]        |
|ranges::remove_copy <br/> ranges::remove_copy_if | ![][notyet] |
|ranges::replace <br/> ranges::replace_if | ![][notyet]      |
|ranges::replace_copy <br/> ranges::replace_copy_if | ![][notyet] |
|ranges::swap_ranges               | ![][notyet]             |
|ranges::reverse                   | ![][notyet]             |
|ranges::reverse_copy              | ![][notyet]             |
|ranges::rotate                    | ![][notyet]             |
|ranges::rotate_copy               | ![][notyet]             |
|ranges::sample                    | ![][notyet]             |
|ranges::shuffle                   | ![][notyet]             |
|ranges::unique                    | ![][notyet]             |
|ranges::unique_copy               | ![][notyet]             |
| **Partitioning  operations**     |                         |
|ranges::is_partitioned            | ![][notyet]             |
|ranges::partition                 | ![][notyet]             |
|ranges::partition_copy            | ![][notyet]             |
|ranges::stable_partition          | ![][notyet]             |
|ranges::partition_point           | ![][notyet]             |
| **Sorting  operations**          |                         |
|ranges::is_sorted                 | ![][notyet]             |
|ranges::is_sorted_until           | ![][notyet]             |
|ranges::sort                      | ![][notyet]             |
|ranges::partial_sort              | ![][notyet]             |
|ranges::partial_sort_copy         | ![][notyet]             |
|ranges::stable_sort               | ![][notyet]             |
|ranges::nth_element               | ![][notyet]             |
| **Binary search  operations**    |                         |
|ranges::lower_bound               | ![][notyet]             |
|ranges::upper_bound               | ![][notyet]             |
|ranges::binary_search             | ![][notyet]             |
|ranges::equal_range               | ![][notyet]             |
| **Other operations on sorted ranges** |                    |
|ranges::merge                     | ![][notyet]             |
|ranges::inplace_merge             | ![][notyet]             |
| **Set operations (on sorted ranges)** |                    |
|ranges::includes                  | ![][notyet]             |
|ranges::set_difference            | ![][notyet]             |
|ranges::set_intersection          | ![][notyet]             |
|ranges::set_symmetric_difference  | ![][notyet]             |
|ranges::set_union                 | ![][notyet]             |
| **Heap operations**              |                         |
|ranges::is_heap                   | ![][notyet]             |
|ranges::is_heap_until             | ![][notyet]             |
|ranges::make_heap                 | ![][notyet]             |
|ranges::push_heap                 | ![][notyet]             |
|ranges::pop_heap                  | ![][notyet]             |
|ranges::sort_heap                 | ![][notyet]             |
| **Minimum/maximun operations**   |                         |
|ranges::max                       | ![][notyet]             |
|ranges::max_element               | ![][notyet]             |
|ranges::min                       | ![][notyet]             |
|ranges::min_element               | ![][notyet]             |
|ranges::minmax                    | ![][notyet]             |
|ranges::minmax_element            | ![][notyet]             |
|ranges::clamp                     | ![][notyet]             |
| **Comparison operations**        |                         |
|ranges::equal                     | ![][notyet]             |
|ranges::lexicographical_compare   | ![][notyet]             |
| **Permutation operations**       |                         |
|ranges::is_permutation            | ![][notyet]             |
|ranges::next_permutation          | ![][notyet]             |
|ranges::prev_permutation          | ![][notyet]             |


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
