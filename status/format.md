## Header `<format>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/format)  
[Implementation](../include/lsd/format.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Concepts**                                 |                      |                                   |
| formattable                                  | ![][cpp23]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Enumerations**                             |                      |                                   |
| range_format                                 | ![][cpp23]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Classes**                                  |                      |                                   |
| formatter                                    | ![][cpp20]           | ![][notyet]                       |
| range_formatter                              | ![][cpp23]           | ![][notyet]                       |
| basic_format_parse_context <br/>format_parse_context <br/>wformat_parse_context | ![][cpp20] <br/>![][cpp20] <br/>![][cpp20] | ![][notyet]                       |
| basic_format_context <br/>format_context <br/>wformat_context | ![][cpp20] <br/>![][cpp20] <br/>![][cpp20] | ![][notyet]                       |
| basic_format_arg                             | ![][cpp20]           | ![][notyet]                       |
| basic_format_args <br/>format_args <br/>wformat_args | ![][cpp20] <br/>![][cpp20] <br/>![][cpp20] | ![][notyet]                       |
| basic_format_string <br/>format_string <br/>wformat_string | ![][cpp20] <br/>![][cpp20] <br/>![][cpp20] | ![][notyet]                       |
| format_error                                 | ![][cpp20]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| format                                       | ![][cpp20]           | ![][notyet]                       |
| format_to                                    | ![][cpp20]           | ![][notyet]                       |
| format_to_n                                  | ![][cpp20]           | ![][notyet]                       |
| formatted_size                               | ![][cpp20]           | ![][notyet]                       |
| vformat                                      | ![][cpp20]           | ![][notyet]                       |
| vformat_to                                   | ![][cpp20]           | ![][notyet]                       |
| ~~visit_format_arg~~ <br/>~~ (deprecated in C++26)~~ | ![][legacy]          | Deprecated in C++26               |
| make_format_args <br/>make_wformat_args      | ![][cpp20] <br/>![][cpp20] | ![][notyet]                       |
|                                              |                      |                                   |
| **Helpers**                                  |                      |                                   |
| format_kind                                  | ![][cpp23]           | ![][notyet]                       |


<!--
	C++20: 9	| 0
	C++23: 4	| 0

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
