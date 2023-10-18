## Header `<regex>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/regex)  
[Implementation](../ss/include/ss/regex.h)

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
| basic_regex                                  | ![][cpp11]           | ![][notyet]                       |
| sub_match                                    | ![][cpp11]           | ![][notyet]                       |
| match_results                                | ![][cpp11]           | ![][notyet]                       |
| regex_iterator                               | ![][cpp11]           | ![][notyet]                       |
| regex_token_iterator                         | ![][cpp11]           | ![][notyet]                       |
| regex_error                                  | ![][cpp11]           | ![][notyet]                       |
| regex_traits                                 | ![][cpp11]           | ![][notyet]                       |
| **regex constant types**                     |                      |                                   |
| syntax_option_type                           | ![][cpp11]           | ![][notyet]                       |
| match_flag_type                              | ![][cpp11]           | ![][notyet]                       |
| error_type                                   | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| **Algorithm**                                |                      |                                   |
| regex_match                                  | ![][cpp11]           | ![][notyet]                       |
| regex_search                                 | ![][cpp11]           | ![][notyet]                       |
| regex_replace                                | ![][cpp11]           | ![][notyet]                       |
| **Non-member operations**                    |                      |                                   |
| ss::swap(ss::basic_regex)                    | ![][cpp11]           | ![][notyet]                       |
| operator== <br/>~~operator!=~~ <br/>~~operator\<~~ <br/>~~operator\<=~~ <br/>~~operator>~~ <br/>~~operator>=~~ <br/>operator\<=> | ![][legacy] <br/>![][legacy] <br/>![][legacy] <br/>![][legacy] <br/>![][legacy] <br/>![][legacy] <br/>![][cpp20] | ![][notyet]                       |
| operator\<\<                                 | ![][legacy]          | ![][notyet]                       |
| operator== <br/>~~operator!=~~               | ![][legacy] <br/>![][legacy] | ![][notyet]                       |
| ss::swap(ss::match_results)                  | ![][cpp11]           | ![][notyet]                       |
| **Range access**                             |                      |                                   |
| begin <br/>cbegin                            | ![][cpp11] <br/>![][cpp14] | ![][notyet]                       |
| end <br/>cend                                | ![][cpp11] <br/>![][cpp14] | ![][notyet]                       |
| rbegin <br/>crbegin                          | ![][cpp14]           | ![][notyet]                       |
| rend <br/>crend                              | ![][cpp14]           | ![][notyet]                       |
| size <br/>ssize                              | ![][cpp17] <br/>![][cpp20] | ![][notyet]                       |
| empty                                        | ![][cpp17]           | ![][notyet]                       |
| data                                         | ![][cpp17]           | ![][notyet]                       |


<!--
	C++11: 17	| 0
	C++14: 2	| 0
	C++17: 2	| 0
	C++20: 1	| 0

	Total: 22	| 0-->

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
