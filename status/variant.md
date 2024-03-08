## Header `<variant>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/variant)  
[Implementation](../include/lsd/variant.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Includes**                                 |                      |                                   |
| \<compare>                                   | ![][cpp20]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Classes**                                  |                      |                                   |
| variant                                      | ![][cpp17]           | ![][notyet]                       |
| monostate                                    | ![][cpp17]           | ![][notyet]                       |
| bad_variant_access                           | ![][cpp17]           | ![][notyet]                       |
| variant_size <br/>variant_size_v             | ![][cpp17]           | ![][notyet]                       |
| variant_alternative <br/>variant_alternative_t | ![][cpp17]           | ![][notyet]                       |
| lsd::hash\<lsd::variant>                       | ![][cpp17]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Constants**                                |                      |                                   |
| variant_npos                                 | ![][cpp17]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| visit                                        | ![][cpp17]           | ![][notyet]                       |
| holds_alternative                            | ![][cpp17]           | ![][notyet]                       |
| lsd::get(lsd::variant)                         | ![][cpp17]           | ![][notyet]                       |
| get_if                                       | ![][cpp17]           | ![][notyet]                       |
| operator== <br/>operator!= <br/>operator\< <br/>operator\<= <br/>operator> <br/>operator>= <br/>operator\<=> | ![][cpp17] <br/>![][cpp17] <br/>![][cpp17] <br/>![][cpp17] <br/>![][cpp17] <br/>![][cpp17] <br/>![][cpp20] | ![][notyet]                       |
| lsd::swap(lsd::variant)                        | ![][cpp17]           | ![][notyet]                       |


<!--
	C++17: 12	| 0
	C++20: 1	| 0

	Total: 13	| 0-->

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
