## Header `<functional>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/functional)  
[Implementation](../ss/include/ss/functional.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented


| C++ ≤ 11 Features                | Implemented in          |
|----------------------------------|:-----------------------:|
| **Namespaces**                   |                         |
|placeholders                      | ![][notyet]             |
|                                  |                         |
| **Classes**                      |                         |
| **Wrappers**                     |                         |
|function                          | ![][notyet]             |
|mem_fn                            | ![][notyet]             |
|reference_wrapper                 | ![][cpp11]              |
| **Helper Classes**               |                         |
|bad_function_call                 | ![][notyet]             |
|is_bind_expression                | ![][notyet]             |
|is_placeholder                    | ![][notyet]             |
| **Arithmetic operations**        |                         |
|plus                              | ![][cpp11]              |
|minus                             | ![][cpp11]              |
|multiplies                        | ![][cpp11]              |
|divides                           | ![][cpp11]              |
|modulus                           | ![][cpp11]              |
|negate                            | ![][cpp11]              |
| **Comparisons**                  |                         |
|equal_to                          | ![][cpp11]              |
|not_equal_to                      | ![][cpp11]              |
|greater                           | ![][cpp11]              |
|less                              | ![][cpp11]              |
|greater_equal                     | ![][cpp11]              |
|less_equal                        | ![][cpp11]              |
| **Logical operations**           |                         |
|logical_and                       | ![][cpp11]              |
|logical_or                        | ![][cpp11]              |
|logical_not                       | ![][cpp11]              |
| **Bitwise operations**           |                         |
|bit_and                           | ![][cpp11]              |
|bit_or                            | ![][cpp11]              |
|bit_xor                           | ![][cpp11]              |
| **Hashing**                      |                         |
|hash                              | ![][cpp11]             |
|ss::hash<*Arithmetic*> <br/> ss::hash< ss::nullptr_t> </br> ss::hash<T*> | ![][cpp11] |
|                                  |                         |
| **Constants**                    | defined in namespace ss::placeholders |
|_1, _2, _3, _4, ...               | ![][notyet]             |
|                                  |                         |
| **Functions**                    |                         |
|bind                              | ![][notyet]             |
|ref <br/> cref                    | ![][notyet]             |



| C++ 14 Features                  | Implemented in          |
|----------------------------------|:-----------------------:|
| **Classes**                      |                         |
| **Bitwise operations**           |                         |
|bit_not                           | ![][cpp11]              |


| C++ 17 Features                  | Implemented in          |
|----------------------------------|:-----------------------:|
| **Classes**                      |                         |
| **Negators**                     |                         |
|not_fn                            | ![][notyet]             |
| **Searchers**                    |                         |
|default_searcher                  | ![][notyet]             |
|boyer_moore_searcher              | ![][notyet]             |
|boyer_moore_horspool_searcher     | ![][notyet]             |
|                                  |                         |
| **Functions**                    |                         |
|invoke                            | ![][cpp11]              |


| C++ 20 Features                  | Implemented in          |
|----------------------------------|:-----------------------:|
| **Classes**                      |                         |
| **Concept-constrained comparisons** |                      |
|ranges::equal_to                  | ![][notyet]             |
|ranges::not_equal_to              | ![][notyet]             |
|ranges::greater                   | ![][notyet]             |
|ranges::less                      | ![][notyet]             |
|ranges::greater_equal             | ![][notyet]             |
|ranges::less_equal                | ![][notyet]             |
|compare_three_way                 | ![][notyet]             |
| **Identities**                   |                         |
|identity                          | ![][notyet]             |
|                                  |                         |
| **Functions**                    |                         |
|bind_front                        | ![][notyet]             |



| C++ 23 Features                  | Implemented in          |
|----------------------------------|:-----------------------:|
| **Functions**                    |                         |
|invoke_r                          | ![][cpp11]              |

<!-- 
    C++11 : 30  | 21
    C++14 : 1   | 1
    C++17 : 5   | 1
    C++20 : 9   | 0
    C++23 : 1   | 1

    Total: 46   | 24
-->

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
