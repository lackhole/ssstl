## Header `<system_error>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/system_error)  
[Implementation](../ss/include/ss/system_error.h)

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
| error_category                               | ![][cpp11]           | ![][notyet]                       |
| error_condition                              | ![][cpp11]           | ![][notyet]                       |
| errc                                         | ![][cpp11]           | ![][notyet]                       |
| error_code                                   | ![][cpp11]           | ![][notyet]                       |
| system_error                                 | ![][cpp11]           | ![][notyet]                       |
| is_error_code_enum                           | ![][cpp11]           | ![][notyet]                       |
| is_error_condition_enum                      | ![][cpp11]           | ![][notyet]                       |
| ss::hash\<ss::error_code>                    | ![][cpp11]           | ![][notyet]                       |
| **Forward declarations**                     |                      |                                   |
| hash                                         | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| generic_category                             | ![][cpp11]           | ![][notyet]                       |
| system_category                              | ![][cpp11]           | ![][notyet]                       |
| operator== <br/>~~operator!=~~ <br/>~~operator\<~~ <br/>operator\<=> | ![][legacy] <br/>![][legacy] <br/>![][legacy] <br/>![][cpp20] | ![][notyet]                       |
| operator\<\<                                 | ![][legacy]          | ![][notyet]                       |
| make_error_code(ss::errc)                    | ![][cpp11]           | ![][notyet]                       |
| operator== <br/>~~operator!=~~ <br/>~~operator\<~~ <br/>operator\<=> | ![][legacy] <br/>![][legacy] <br/>![][legacy] <br/>![][cpp20] | ![][notyet]                       |
| make_error_condition(ss::errc)               | ![][cpp11]           | ![][notyet]                       |


<!--
	C++11: 14	| 0
	C++20: 1	| 0

	Total: 15	| 0-->

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
