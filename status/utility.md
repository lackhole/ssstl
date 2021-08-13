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
|make_pair                         | ![][notyet]             |
|operator== <br/> operator!= <br/> operator< <br/> operator<= <br/> operator> <br/> ~~operator<=>~~| ![][notyet] |
|ss::swap(ss::pair)                | ![][notyet]             |
|ss:get(ss::pair)                  | ![][notyet]             |
|                                  |                         |
| **Classes**                      |                         |
|pair                              | ![][notyet]             |
|tuple_size                        | ![][notyet]             |
|tuple_element                     | ![][notyet]             |
|ss::tuple_size\<ss::pair>         | ![][notyet]             |
|ss::tuple_element\<ss::pair>      | ![][notyet]             |
| **Forward declarations**         |                         |
|tuple                             | ![][notyet]             |
|                                  |                         |
| **Helpers**                      |                         |
|piecewise_construct_t             | ![][notyet]             |
|piecewise_construct               | ![][notyet]             |

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
|in_place_type_t <br/> in_place_index_t <br/> | ![][cpp11]   |
|in_place_type <br/> in_place_index | ![][cpppt14] ![][cpp17] |

| C++20 Features                   | Implemented in          |
|----------------------------------|:-----------------------:|
| **Functions**                    |                         |
|cmp_equal <br/> cmp_not_equal <br/> cmp_less <br/> cmp_greater <br/> cmp_less_equal <br/> cmp_greater_equal | ![][notyet] |
|in_range                          | ![][notyet]             |

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
