## Header `<compare>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/compare)  
[Implementation](../ss/include/ss/compare.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Concepts**                                 |                      |                                   |
| three_way_comparable <br/>three_way_comparable_with | ![][cpp20]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Classes**                                  |                      |                                   |
| partial_ordering                             | ![][cpp20]           | ![][notyet]                       |
| weak_ordering                                | ![][cpp20]           | ![][notyet]                       |
| strong_ordering                              | ![][cpp20]           | ![][notyet]                       |
| common_comparison_category                   | ![][cpp20]           | ![][notyet]                       |
| compare_three_way_result                     | ![][cpp20]           | ![][notyet]                       |
| compare_three_way                            | ![][cpp20]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Customization point objects**              |                      |                                   |
| strong_order                                 | ![][cpp20]           | ![][notyet]                       |
| weak_order                                   | ![][cpp20]           | ![][notyet]                       |
| partial_order                                | ![][cpp20]           | ![][notyet]                       |
| compare_strong_order_fallback                | ![][cpp20]           | ![][notyet]                       |
| compare_weak_order_fallback                  | ![][cpp20]           | ![][notyet]                       |
| compare_partial_order_fallback               | ![][cpp20]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| is_eq <br/>is_neq <br/>is_lt <br/>is_lteq <br/>is_gt <br/>is_gteq | ![][cpp20]           | ![][notyet]                       |


<!--
	C++20: 14	| 0

	Total: 14	| 0-->

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
