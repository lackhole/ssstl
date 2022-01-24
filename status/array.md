## Header `<array>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/array)  
[Implementation](../ss/include/ss/array.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Includes**                                 |                      |                                   |
| \<compare>                                   | ![][cpp20]           | -                                 |
| \<initializer_list>                          | ![][cpp11]           | -                                 |
|                                              |                      |                                   |
| **Classes**                                  |                      |                                   |
| array                                        | ![][cpp11]           | ![][cpp11] ![][cpppt20]           |
| tuple_size                                   | ![][cpp11]           | ![][cpp11]                        |
| tuple_element                                | ![][cpp11]           | ![][cpp11]                        |
| ss::tuple_size\<ss::array>                   | ![][cpp11]           | ![][cpp11]                        |
| ss::tuple_element\<ss::array>                | ![][cpp11]           | ![][cpp11]                        |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| operator== <br/>~~operator!=~~ <br/>~~operator\<~~ <br/>~~operator\<=~~ <br/>~~operator>~~ <br/>~~operator>=~~ <br/>operator\<=> | ![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp20] | ![][cpp11] ![][notyet] |
| ss::swap(ss::array)                          | ![][cpp11]           | ![][cpp11]                        |
| to_array                                     | ![][cpp20]           | ![][cpp11]                        |
| ss::get(ss::array)                           | ![][cpp11]           | ![][cpp11]                        |
| **Range access**                             |                      |                                   |
| begin <br/>cbegin                            | ![][cpp11] <br/>![][cpp14] | ![][cpp11]                  |
| end <br/>cend                                | ![][cpp11] <br/>![][cpp14] | ![][cpp11]                  |
| rbegin <br/>crbegin                          | ![][cpp14]           | ![][cpp11]                        |
| rend <br/>crend                              | ![][cpp14]           | ![][cpp11]                        |
| size <br/>ssize                              | ![][cpp17] <br/>![][cpp20] | ![][cpp11]                  |
| empty                                        | ![][cpp17]           | ![][cpp11]                        |
| data                                         | ![][cpp17]           | ![][cpp11]                        |


<!--
	C++11: 10	| 10
	C++14: 4	| 4
	C++17: 3	| 3
	C++20: 4	| 2

	Total: 21	| 19-->

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
