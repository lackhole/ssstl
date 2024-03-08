## Header `<tuple>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/tuple)  
[Implementation](../include/lsd/tuple.h)

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
| tuple                                        | ![][cpp11]           | ![][notyet]                       |
| tuple_size                                   | ![][cpp11]           | ![][cpp11]                        |
| tuple_element                                | ![][cpp11]           | ![][cpp11]                        |
| lsd::tuple_size\<lsd::tuple>                   | ![][cpp11]           | ![][cpp11]                        |
| lsd::tuple_element\<lsd::tuple>                | ![][cpp11]           | ![][cpp11]                        |
| lsd::uses_allocator\<lsd::tuple>               | ![][cpp11]           | ![][cpp11]                        |
|                                              |                      |                                   |
| **Constants**                                |                      |                                   |
| ignore                                       | ![][cpp11]           | ![][cpp11]                        |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| make_tuple                                   | ![][cpp11]           | ![][cpp11]                        |
| tie                                          | ![][cpp11]           | ![][cpp11]                        |
| forward_as_tuple                             | ![][cpp11]           | ![][cpp11]                        |
| tuple_cat                                    | ![][cpp11]           | ![][cpp11]                        |
| lsd::get(lsd::tuple)                           | ![][cpp11]           | ![][cpp11]                        |
| operator== <br/>~~operator!=~~ <br/>~~operator\<~~ <br/>~~operator\<=~~ <br/>~~operator>~~ <br/>~~operator>=~~ <br/>operator\<=> | ![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp20] | ![][notyet]                       |
| lsd::swap(lsd::tuple)                          | ![][cpp11]           | ![][notyet]                       |
| apply                                        | ![][cpp17]           | ![][cpp11]                        |
| make_from_tuple                              | ![][cpp17]           | ![][cpp11]                        |


<!--
	C++11: 13	| 10
	C++17: 2	| 2
	C++20: 1	| 0

	Total: 16	| 12-->

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
