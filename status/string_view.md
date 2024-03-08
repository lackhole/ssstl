## Header `<string_view>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/string_view)  
[Implementation](../include/lsd/string_view.h)

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
| basic_string_view                            | ![][cpp17]           | ![][notyet]                       |
| lsd::hash\<lsd::string_view> <br/>lsd::hash\<lsd::wstring_view> <br/>lsd::hash\<lsd::u8string_view> <br/>lsd::hash\<lsd::u16string_view> <br/>lsd::hash\<lsd::u32string_view> | ![][cpp17] <br/>![][cpp17] <br/>![][cpp20] <br/>![][cpp17] <br/>![][cpp17] | ![][notyet]                       |
| **Forward declarations**                     |                      |                                   |
| hash                                         | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| operator== <br/>~~operator!=~~ <br/>~~operator\<~~ <br/>~~operator>~~ <br/>~~operator\<=~~ <br/>~~operator>=~~ <br/>operator\<=> | ![][cpp17] <br/>![][legacy] <br/>![][legacy] <br/>![][legacy] <br/>![][legacy] <br/>![][legacy] <br/>![][cpp20] | ![][notyet]                       |
| operator\<\<                                 | ![][cpp17]           | ![][notyet]                       |
| swap                                         | ![][legacy]          | ![][notyet]                       |
| **Range access**                             |                      |                                   |
| begin <br/>cbegin                            | ![][cpp11] <br/>![][cpp14] | ![][notyet]                       |
| end <br/>cend                                | ![][cpp11] <br/>![][cpp14] | ![][notyet]                       |
| rbegin <br/>crbegin                          | ![][cpp14]           | ![][notyet]                       |
| rend <br/>crend                              | ![][cpp14]           | ![][notyet]                       |
| size <br/>ssize                              | ![][cpp17] <br/>![][cpp20] | ![][notyet]                       |
| empty                                        | ![][cpp17]           | ![][notyet]                       |
| data                                         | ![][cpp17]           | ![][notyet]                       |
| **Literals**                                 |                      |                                   |
| operator""sv                                 | ![][cpp17]           | ![][notyet]                       |


<!--
	C++11: 2	| 0
	C++14: 2	| 0
	C++17: 5	| 0
	C++20: 1	| 0

	Total: 10	| 0-->

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
