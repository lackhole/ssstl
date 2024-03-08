## Header `<string>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/string)  
[Implementation](../include/lsd/string.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Includes**                                 |                      |                                   |
| \<compare>                                   | ![][cpp20]           | ![][notyet]                       |
| \<initializer_list>                          | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Classes**                                  |                      |                                   |
| char_traits                                  | ![][legacy]          | ![][notyet]                       |
| basic_string                                 | ![][legacy]          | ![][notyet]                       |
| lsd::hash\<lsd::string> <br/>lsd::hash\<lsd::u8string> <br/>lsd::hash\<lsd::u16string> <br/>lsd::hash\<lsd::u32string> <br/>lsd::hash\<lsd::wstring> <br/>lsd::hash\<lsd::pmr::string> <br/>lsd::hash\<lsd::pmr::u8string> <br/>lsd::hash\<lsd::pmr::u16string> <br/>lsd::hash\<lsd::pmr::u32string> <br/>lsd::hash\<lsd::pmr::wstring> | ![][cpp11] <br/>![][cpp20] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp17] <br/>![][cpp20] <br/>![][cpp17] <br/>![][cpp17] <br/>![][cpp17] | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| operator+                                    | ![][legacy]          | ![][notyet]                       |
| operator== <br/>~~operator!=~~ <br/>~~operator\<~~ <br/>~~operator>~~ <br/>~~operator\<=~~ <br/>~~operator>=~~ <br/>operator\<=> | ![][legacy] <br/>![][legacy] <br/>![][legacy] <br/>![][legacy] <br/>![][legacy] <br/>![][legacy] <br/>![][cpp20] | ![][notyet]                       |
| lsd::swap(lsd::basic_string)                   | ![][legacy]          | ![][notyet]                       |
| erase(lsd::basic_string) <br/>erase_if(lsd::basic_string) | ![][cpp20]           | ![][notyet]                       |
| **Input/output**                             |                      |                                   |
| operator\<\< <br/>operator>>                 | ![][legacy]          | ![][notyet]                       |
| getline                                      | ![][legacy]          | ![][notyet]                       |
| **Numeric conversions**                      |                      |                                   |
| stoi <br/>stol <br/>stoll                    | ![][cpp11] <br/>![][cpp11] <br/>![][cpp11] | ![][notyet]                       |
| stoul <br/>stoull                            | ![][cpp11] <br/>![][cpp11] | ![][notyet]                       |
| stof <br/>stod <br/>stold                    | ![][cpp11] <br/>![][cpp11] <br/>![][cpp11] | ![][notyet]                       |
| to_string                                    | ![][cpp11]           | ![][notyet]                       |
| to_wstring                                   | ![][cpp11]           | ![][notyet]                       |
| **Range access**                             |                      |                                   |
| begin <br/>cbegin                            | ![][cpp11] <br/>![][cpp14] | ![][notyet]                       |
| end <br/>cend                                | ![][cpp11] <br/>![][cpp14] | ![][notyet]                       |
| rbegin <br/>crbegin                          | ![][cpp14]           | ![][notyet]                       |
| rend <br/>crend                              | ![][cpp14]           | ![][notyet]                       |
| size <br/>ssize                              | ![][cpp17] <br/>![][cpp20] | ![][notyet]                       |
| empty                                        | ![][cpp17]           | ![][notyet]                       |
| data                                         | ![][cpp17]           | ![][notyet]                       |
| **Literals**                                 |                      |                                   |
| operator""s                                  | ![][cpp14]           | ![][notyet]                       |


<!--
	C++11: 9	| 0
	C++14: 3	| 0
	C++17: 2	| 0
	C++20: 2	| 0

	Total: 16	| 0-->

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
