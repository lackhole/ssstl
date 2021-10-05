## Header `<type_traits>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/type_traits)  
[Implementation](../ss/include/ss/type_traits.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Implemented with C++ N
* ![][notyet]: Not yet implemented

## Namespace aliases
```c++
namespace ss {
  namespace views = ranges::views;
}
```

| C++20 Features                   | Implemented in                  |
|----------------------------------|:-------------------------------:|
| **Concepts**                     |                                 |
| **Range concepts**               | Defined in namespace ss::ranges |
|ranges::range                     | ![][notyet]                     |
|ranges::borrowed_range            | ![][notyet]                     |
|ranges::sized_range               | ![][notyet]                     |
|ranges::view                      | ![][notyet]                     |
|ranges::input_range               | ![][notyet]                     |
|ranges::output_range              | ![][notyet]                     |
|ranges::forward_range             | ![][notyet]                     |
|ranges::bidirectional_range       | ![][notyet]                     |
|ranges::random_access_range       | ![][notyet]                     |
|ranges::contiguous_range          | ![][notyet]                     |
|ranges::common_range              | ![][notyet]                     |
|ranges::viewable_range            | ![][notyet]                     |
|                                  |                                 |
| **Classes**                      |                                 |
| **Range primitives**             | Defined in namespace ss::range  |
|ranges::iterator_t <br/> ranges::sentinel_t <br/> ranges::range_difference_t <br/> ranges::range_size_t <br/> ranges::range_value_t <br/> ranges::range_reference_t <br/> ranges::range_rvalue_reference_t | ![][notyet] |
| **Views**                        | Defined in namespace ss::range  |
|ranges::view_interface            | ![][notyet]                     |
|ranges::subrange                  | ![][notyet]                     |
| **Dangling iterator handling**   | Defined in namespace ss::range  |
|ranges::dangling                  | ![][notyet]                     |
|ranges::borrowed_iterator_t <br/> ranges::borrowed_subrange_t | ![][notyet] |
| **Factories**                    | Defined in namespace ss::range  |
|ranges::empty_view <br/> views::empty           | ![][notyet]       |
|ranges::single_view <br/> views::single         | ![][notyet]       |
|ranges::iota_view <br/> views::iota             | ![][notyet]       |
|ranges::basic_istream_view <br/> views::istream | ![][notyet]       |
| **Adaptors**                                   | Defined in namespace ss::range |
|views::all_t <br/> views::all                   | ![][notyet]       |
|ranges::ref_view                                | ![][notyet]       |
|ranges::filter_view     <br/> views::filter     | ![][notyet]       |
|ranges::transform_view  <br/> views::transform  | ![][notyet]       |
|ranges::take_view       <br/> views::take       | ![][notyet]       |
|ranges::take_while_view <br/> views::take_while | ![][notyet]       |
|ranges::drop_view       <br/> views::drop       | ![][notyet]       |
|ranges::drop_while_view <br/> views::drop_while | ![][notyet]       |
|ranges::join_view       <br/> views::join       | ![][notyet]       |
|ranges::lazy_split_view <br/> views::lazy_split | ![][notyet]       |
|ranges::split_view      <br/> views::split      | ![][notyet]       |
|views::counted                                  | ![][notyet]       |
|ranges::common_view     <br/> views::common     | ![][notyet]       |
|ranges::reverse_view    <br/> views::reverse    | ![][notyet]       |
|ranges::elements_view   <br/> views::elements   | ![][notyet]       |
|ranges::keys_view       <br/> views::keys       | ![][notyet]       |
|ranges::values_view     <br/> views::values     | ![][notyet]       |
|                                  |                                 |
| **Customization point objects**  |                                 |
| **Range access**                 | Defined in namespace ss::range  |
|ranges::begin                     | ![][notyet]                     |
|ranges::end                       | ![][notyet]                     |
|ranges::cbegin                    | ![][notyet]                     |
|ranges::cend                      | ![][notyet]                     |
|ranges::rbegin                    | ![][notyet]                     |
|ranges::rend                      | ![][notyet]                     |
|ranges::crbegin                   | ![][notyet]                     |
|ranges::crend                     | ![][notyet]                     |
|ranges::size                      | ![][notyet]                     |
|ranges::ssize                     | ![][notyet]                     |
|ranges::empty                     | ![][notyet]                     |
|ranges::data                      | ![][notyet]                     |
|ranges::cdata                     | ![][notyet]                     |
|                                  |                                 |
| **Enumerations**                 |                                 |
| **Range access**                 | Defined in namespace ss::range  |
|ranges::subrange_kind             | ![][notyet]                     |


[notyet]: https://img.shields.io/badge/Not_yet-orange
[removed]: https://img.shields.io/badge/Removed-red

[cppno11]: https://img.shields.io/badge/C%2B%2B-11-red
[cppno14]: https://img.shields.io/badge/C%2B%2B-14-red
[cppno17]: https://img.shields.io/badge/C%2B%2B-17-red
[cppno20]: https://img.shields.io/badge/C%2B%2B-20-red
[cppno23]: https://img.shields.io/badge/C%2B%2B-23-red

[cpp11]: https://img.shields.io/badge/C%2B%2B-11-green

[cpp14]: https://img.shields.io/badge/C%2B%2B-14-green

[cpp17]: https://img.shields.io/badge/C%2B%2B-17-green

[cpp20]: https://img.shields.io/badge/C%2B%2B-20-green

[cpp23]: https://img.shields.io/badge/C%2B%2B-23-green
