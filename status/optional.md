## Header `<optional>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/optional)  
[Implementation](../ss/include/ss/optional.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
    * ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Implemented with C++ N
* ![][notyet]: Not yet implemented


| C++17  Features                  | Implemented in          |
|----------------------------------|:-----------------------:|
| **Classes**                      |                         |
|optional                          | ![][cpppt11]* ![][cpp14] |
|bad_optional_access               | ![][cpppt11]**          |
|ss::hash\<ss::optional>           | ![][cpp11]              |
|nullopt_t                         | ![][cpp11]              |
|                                  |                         |
| **Constants**                    |                         |
|nullopt                           | ![][cpp11]              |
|                                  |                         |
| **Functions**                    |                         |
| Comparison                       |                         |
|operator== <br/> operator!= <br/> operator< <br/> operator<= <br/> operator> <br/> operator>= | ![][cpp11] |
| Specialized algorithms           |                         |
|ss::swap(ss::optional)            | ![][notyet]             |
|make_optional                     | ![][cpp11]              |

| C++20  Features                  | Implemented in          |
|----------------------------------|:-----------------------:|
| **Functions**                    |                         |
| Comparison                       |                         |
|operator<=>                       | ![][notyet]             |

---
\* Non-const member functions is not `constexpr`.
Move and copy constructors are not `constexpr`.  
\*\* Inherits from `std::exception`

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
