## Header `<ios>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/ios)  
[Implementation](../ss/include/ss/ios.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Includes**                                 |                      |                                   |
| \<iosfwd>                                    | ![][legacy]          | ![][notyet]                       |
|                                              |                      |                                   |
| **Classes**                                  |                      |                                   |
| ios_base                                     | ![][legacy]          | ![][notyet]                       |
| basic_ios                                    | ![][legacy]          | ![][notyet]                       |
| fpos                                         | ![][legacy]          | ![][notyet]                       |
| io_errc                                      | ![][cpp11]           | ![][notyet]                       |
| is_error_code_enum\<ss::io_errc>             | ![][cpp11]           | ![][notyet]                       |
| streamoff                                    | ![][legacy]          | ![][notyet]                       |
| streamsize                                   | ![][legacy]          | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| iostream_category                            | ![][cpp11]           | ![][notyet]                       |
| make_error_code(ss::io_errc)                 | ![][cpp11]           | ![][notyet]                       |
| make_error_condition(ss::io_errc)            | ![][cpp11]           | ![][notyet]                       |
| boolalpha <br/>noboolalpha                   | ![][legacy]          | ![][notyet]                       |
| showbase <br/>noshowbase                     | ![][legacy]          | ![][notyet]                       |
| showpoint <br/>noshowpoint                   | ![][legacy]          | ![][notyet]                       |
| showpos <br/>noshowpos                       | ![][legacy]          | ![][notyet]                       |
| skipws <br/>noskipws                         | ![][legacy]          | ![][notyet]                       |
| uppercase <br/>nouppercase                   | ![][legacy]          | ![][notyet]                       |
| unitbuf <br/>nounitbuf                       | ![][legacy]          | ![][notyet]                       |
| internal <br/>left <br/>right                | ![][legacy]          | ![][notyet]                       |
| dec <br/>hex <br/>oct                        | ![][legacy]          | ![][notyet]                       |
| fixed <br/>scientific <br/>hexfloat <br/>defaultfloat | ![][legacy] <br/>![][legacy] <br/>![][cpp11] <br/>![][cpp11] | ![][notyet]                       |


<!--
	C++11: 20	| 0

	Total: 20	| 0-->

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
