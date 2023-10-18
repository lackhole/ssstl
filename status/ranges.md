## Header `<ranges>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/ranges)  
[Implementation](../ss/include/ss/ranges.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Includes**                                 |                      |                                   |
| \<compare>                                   | ![][cpp20]           | ![][notyet]                       |
| \<initializer_list>                          | ![][cpp11]           | ![][notyet]                       |
| \<iterator>                                  | ![][legacy]          | ![][notyet]                       |
|                                              |                      |                                   |
| **Concepts**                                 |                      |                                   |
| **Range concepts**                           |                      |                                   |
| ranges::range                                | ![][cpp20]           | ![][notyet]                       |
| ranges::borrowed_range                       | ![][cpp20]           | ![][notyet]                       |
| ranges::sized_range                          | ![][cpp20]           | ![][notyet]                       |
| ranges::view                                 | ![][cpp20]           | ![][notyet]                       |
| ranges::input_range                          | ![][cpp20]           | ![][notyet]                       |
| ranges::output_range                         | ![][cpp20]           | ![][notyet]                       |
| ranges::forward_range                        | ![][cpp20]           | ![][notyet]                       |
| ranges::bidirectional_range                  | ![][cpp20]           | ![][notyet]                       |
| ranges::random_access_range                  | ![][cpp20]           | ![][notyet]                       |
| ranges::contiguous_range                     | ![][cpp20]           | ![][notyet]                       |
| ranges::common_range                         | ![][cpp20]           | ![][notyet]                       |
| ranges::viewable_range                       | ![][cpp20]           | ![][notyet]                       |
| ranges::constant_range                       | ![][cpp23]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| **Range conversions**                        |                      |                                   |
| ranges::to                                   | ![][cpp23]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Classes**                                  |                      |                                   |
| **Range primitives**                         |                      |                                   |
| ranges::iterator_t <br/>ranges::const_iterator_t <br/>ranges::sentinel_t <br/>ranges::const_sentinel_t <br/>ranges::range_difference_t <br/>ranges::range_size_t  <br/>ranges::range_value_t <br/>ranges::range_reference_t <br/>ranges::range_const_reference_t <br/>ranges::range_rvalue_reference_t <br/>ranges::range_common_reference_t | ![][cpp20] <br/>![][cpp23] <br/>![][cpp20] <br/>![][cpp23] <br/>![][cpp20] <br/>![][cpp20] <br/>![][cpp20] <br/>![][cpp20] <br/>![][cpp23] <br/>![][cpp20] <br/>![][cpp20] | ![][notyet]                       |
| **Views**                                    |                      |                                   |
| ranges::view_interface                       | ![][cpp20]           | ![][notyet]                       |
| ranges::subrange                             | ![][cpp20]           | ![][notyet]                       |
| **Dangling iterator handling**               |                      |                                   |
| ranges::dangling                             | ![][cpp20]           | ![][notyet]                       |
| ranges::borrowed_iterator_t <br/>ranges::borrowed_subrange_t | ![][cpp20]           | ![][notyet]                       |
| **Range adaptor objects utility**            |                      |                                   |
| ranges::range_adaptor_closure                | ![][cpp23]           | ![][notyet]                       |
| **Factories**                                |                      |                                   |
| ranges::empty_view <br/>views::empty         | ![][cpp20]           | ![][notyet]                       |
| ranges::single_view <br/>views::single       | ![][cpp20]           | ![][notyet]                       |
| ranges::iota_view <br/>views::iota           | ![][cpp20]           | ![][notyet]                       |
| ranges::basic_istream_view <br/>views::istream | ![][cpp20]           | ![][notyet]                       |
| ranges::repeat_view <br/>views::repeat       | ![][cpp23]           | ![][notyet]                       |
| ranges::cartesian_product_view <br/>views::cartesian_product | ![][cpp23]           | ![][notyet]                       |
| **Adaptors**                                 |                      |                                   |
| views::all_t <br/>views::all                 | ![][cpp20]           | ![][notyet]                       |
| ranges::ref_view                             | ![][cpp20]           | ![][notyet]                       |
| ranges::owning_view                          | ![][cpp20]           | ![][notyet]                       |
| ranges::filter_view <br/>views::filter       | ![][cpp20]           | ![][notyet]                       |
| ranges::transform_view <br/>views::transform | ![][cpp20]           | ![][notyet]                       |
| ranges::take_view <br/>views::take           | ![][cpp20]           | ![][notyet]                       |
| ranges::take_while_view <br/>views::take_while | ![][cpp20]           | ![][notyet]                       |
| ranges::drop_view <br/>views::drop           | ![][cpp20]           | ![][notyet]                       |
| ranges::drop_while_view <br/>views::drop_while | ![][cpp20]           | ![][notyet]                       |
| ranges::join_view <br/>views::join           | ![][cpp20]           | ![][notyet]                       |
| ranges::lazy_split_view <br/>views::lazy_split | ![][cpp20]           | ![][notyet]                       |
| ranges::split_view <br/>views::split         | ![][cpp20]           | ![][notyet]                       |
| views::counted                               | ![][cpp20]           | ![][notyet]                       |
| ranges::common_view <br/>views::common       | ![][cpp20]           | ![][notyet]                       |
| ranges::reverse_view <br/>views::reverse     | ![][cpp20]           | ![][notyet]                       |
| ranges::as_const_view <br/>views::as_const   | ![][cpp23]           | ![][notyet]                       |
| ranges::as_rvalue_view <br/>views::as_rvalue | ![][cpp23]           | ![][notyet]                       |
| ranges::elements_view <br/>views::elements   | ![][cpp20]           | ![][notyet]                       |
| ranges::keys_view <br/>views::keys           | ![][cpp20]           | ![][notyet]                       |
| ranges::values_view <br/>views::values       | ![][cpp20]           | ![][notyet]                       |
| ranges::enumerate_view <br/>views::enumerate | ![][cpp23]           | ![][notyet]                       |
| ranges::zip_view <br/>views::zip             | ![][cpp23]           | ![][notyet]                       |
| ranges::zip_transform_view <br/>views::zip_transform | ![][cpp23]           | ![][notyet]                       |
| ranges::adjacent_view <br/>views::adjacent   | ![][cpp23]           | ![][notyet]                       |
| ranges::adjacent_transform_view <br/>views::adjacent_transform | ![][cpp23]           | ![][notyet]                       |
| ranges::join_with_view <br/>views::join_with | ![][cpp23]           | ![][notyet]                       |
| ranges::stride_view <br/>views::stride       | ![][cpp23]           | ![][notyet]                       |
| ranges::slide_view <br/>views::slide         | ![][cpp23]           | ![][notyet]                       |
| ranges::chunk_view <br/>views::chunk         | ![][cpp23]           | ![][notyet]                       |
| ranges::chunk_by_view <br/>views::chunk_by   | ![][cpp23]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Customization point objects**              |                      |                                   |
| **Range access**                             |                      |                                   |
| ranges::begin                                | ![][cpp20]           | ![][notyet]                       |
| ranges::end                                  | ![][cpp20]           | ![][notyet]                       |
| ranges::cbegin                               | ![][cpp20]           | ![][notyet]                       |
| ranges::cend                                 | ![][cpp20]           | ![][notyet]                       |
| ranges::rbegin                               | ![][cpp20]           | ![][notyet]                       |
| ranges::rend                                 | ![][cpp20]           | ![][notyet]                       |
| ranges::crbegin                              | ![][cpp20]           | ![][notyet]                       |
| ranges::crend                                | ![][cpp20]           | ![][notyet]                       |
| ranges::size                                 | ![][cpp20]           | ![][notyet]                       |
| ranges::ssize                                | ![][cpp20]           | ![][notyet]                       |
| ranges::empty                                | ![][cpp20]           | ![][notyet]                       |
| ranges::data                                 | ![][cpp20]           | ![][notyet]                       |
| ranges::cdata                                | ![][cpp20]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Enumerations**                             |                      |                                   |
| ranges::subrange_kind                        | ![][cpp20]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Helpers**                                  |                      |                                   |
| ss::tuple_size\<ss::ranges::subrange>        | ![][cpp20]           | ![][notyet]                       |
| ss::tuple_element\<ss::ranges::subrange>     | ![][cpp20]           | ![][notyet]                       |
| get(ss::ranges::subrange)                    | ![][cpp20]           | ![][notyet]                       |
| from_range_t <br/>from_range                 | ![][cpp23]           | ![][notyet]                       |


<!--
	C++11: 2	| 0
	C++20: 56	| 0
	C++23: 18	| 0

	Total: 76	| 0-->

[notyet]: https://img.shields.io/badge/Not_yet-orange
[removed]: https://img.shields.io/badge/Removed-red
[legacy]: https://img.shields.io/badge/legacy-grey

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
