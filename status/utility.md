## Header `<utility>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/utility)  
[Implementation](../ss/include/ss/utility.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented


| C++ ≤ 11 Features                | Implemented in          |
|----------------------------------|:-----------------------:|
| **Namespaces**                   |                         |
|rel_ops                           |                         |
|operator!= <br/> operator> <br/> operator<= <br/> operator>= | ![][cpp11] |
|                                  |                         |
| **Functions**                    |                         |
|swap                              | ![][cpp11]              |
|forward                           | ![][cpp11]              |
|move                              | ![][cpp11]              |
|move_if_noexcept                  | ![][cpp11]              |
|declval                           | ![][cpp11]              |
|make_pair                         | ![][cpp11]             |
|operator== <br/> operator!= <br/> operator< <br/> operator<= <br/> operator> <br/> ~~operator<=>~~| ![][cpp11] |
|ss::swap(ss::pair)                | ![][cpp11]             |
|ss:get(ss::pair)                  | ![][cpp11]             |
|                                  |                         |
| **Classes**                      |                         |
|pair                              | ![][cpp11]             |
|tuple_size                        | ![][cpp11]             |
|tuple_element                     | ![][cpp11]             |
|ss::tuple_size\<ss::pair>         | ![][cpp11]             |
|ss::tuple_element\<ss::pair>      | ![][cpp11]             |
| **Forward declarations**         |                         |
|tuple                             | ![][cpp11]             |
|                                  |                         |
| **Helpers**                      |                         |
|piecewise_construct_t             | ![][cpp11]             |
|piecewise_construct               | ![][cpp11]             |

| C++14 Features                   | Implemented in          |
|----------------------------------|:-----------------------:|
| **Functions**                    |                         |
|exchange                          | ![][cpp11]              |
|                                  |                         |
| **Classes**                      |                         |
|integer_sequence                  | ![][cpp11]              |

| C++17 Features                   | Implemented in          |
|----------------------------------|:-----------------------:|
| **Functions**                    |                         |
|as_const                          | ![][cpp11]              |
|                                  |                         |
| **Helpers**                      |                         |
|in_place_t <br/> in_place         | ![][cpp11]              |
|in_place_type_t <br/> in_place_type <br/> | ![][cpp11]      |
|in_place_index_t <br/> in_place_index | ![][cpppt11] ![][cpp14] |

| C++20 Features                   | Implemented in          |
|----------------------------------|:-----------------------:|
| **Functions**                    |                         |
|cmp_equal <br/> cmp_not_equal <br/> cmp_less <br/> cmp_greater <br/> cmp_less_equal <br/> cmp_greater_equal | ![][cpp11] |
|in_range                          |   ![][cpp11]            |

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
